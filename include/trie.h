#pragma once
#include <string>
#include <vector>
#include <utility>
#include "node.h"

namespace Mistercomplete {

        class Trie {

        public:
                Trie();
	        void insert(const int id, const std::string& entry);
                void remove(const std::string& entry);
                std::vector<std::pair<int, std::string>> autocomplete(const std::string& prefix);

        private:
                Node* root;
                Node* get_node_by_prefix(const std::string& prefix);
                std::vector<std::pair<int, std::string>> get_all_from_node(Node* node);
                void get_all_from_node_recursive(Node* node, std::vector<std::pair<int, std::string>>& results, std::string& current_word);

        };

} // end namespace Mistercomplete
