#pragma once
#include <string>
#include <vector>
#include <utility>
#include "node.h"

namespace Mistercomplete {

template <typename T>
class Trie {
public:
        Trie() { root = new Node<T>(); }

        void insert(const T& id, const std::string& entry)
        {
                Node<T>* current_node = root;
                for (int i = 0; i < (int)entry.size(); i++)
                {
                        int child_index = (int)entry[i] - 97;
                        Node<T>* next_node = current_node->children[child_index];
                        if (!current_node->children[child_index])
                        {
                                current_node->children[child_index] = new Node<T>();
                                next_node = current_node->children[child_index];
                                next_node->parent = current_node;
                                next_node->character = entry[i];
                        }
                        if (i == (int)(entry.size() - 1))
                        {
                                next_node->ending = true;
                                next_node->id = id;
                                return;
                        }
                        current_node = next_node;
                }
        }

        void remove(const std::string& entry)
        {
                std::vector<Node<T>*> node_path;
                Node<T>* current_node = root;
                for (int i = 0; i < (int)entry.size(); i++)
                {
                        int char_index = (int)entry[i] - 97;
                        if (current_node->children[char_index] == nullptr) return;
                        current_node = current_node->children[char_index];
                        node_path.push_back(current_node);
                }
                current_node->id = std::nullopt;
                current_node->ending = false;
                for (int i = (int)entry.size() - 1; i >= 0; i--)
                {
                        if (node_path[i]->child_count() || node_path[i]->ending) return;
                        int char_index = (int)entry[i] - 97;
                        node_path[i]->parent->children[char_index] = nullptr;
                        delete node_path[i];
                }
        }

        std::vector<std::pair<T, std::string>> autocomplete(const std::string& prefix)
        {
                Node<T>* prefix_end = get_node_by_prefix(prefix);
                std::vector<std::pair<T, std::string>> results;
                if (prefix_end == nullptr) return results;
                results = get_all_from_node(prefix_end);
                for (auto& result : results)
                {
                        result.second = prefix + result.second;
                }
                return results;
        }

private:
        Node<T>* root;

        Node<T>* get_node_by_prefix(const std::string& prefix)
        {
                Node<T>* current_node = root;
                for (int i = 0; i < (int)prefix.size(); i++)
                {
                        int char_index = (int)prefix[i] - 97;
                        if (current_node->children[char_index] == nullptr) return nullptr;
                        current_node = current_node->children[char_index];
                }
                return current_node;
        }

        std::vector<std::pair<T, std::string>> get_all_from_node(Node<T>* node)
        {
                std::vector<std::pair<T, std::string>> results;
                std::string current_word;
                get_all_from_node_recursive(node, results, current_word);
                return results;
        }

        void get_all_from_node_recursive(Node<T>* node, std::vector<std::pair<T, std::string>>& results, std::string& current_word)
        {
                if (node->ending)
                {
                        results.push_back(std::make_pair(*node->id, current_word));
                }
                for (int i = 0; i < 26; i++)
                {
                        if (node->children[i] == nullptr) continue;
                        current_word += (char)((int)'a' + i);
                        get_all_from_node_recursive(node->children[i], results, current_word);
                        current_word.pop_back();
                }
        }
};

} // end namespace Mistercomplete
