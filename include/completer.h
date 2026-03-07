#pragma once
#include <vector>
#include <string>
#include <utility>
#include "trie.h"
#include "icompleter.h"

namespace Mistercomplete {

template <typename T>
class Completer : public ICompleter<T> {
public:
        Completer() {}

        void add_entry(const T& id, const std::string& text) override
        {
                trie.insert(id, text);
        }

        [[nodiscard]] std::vector<std::pair<T, std::string>> suggest(const std::string& text) override
        {
                return trie.autocomplete(text);
        }

private:
        Trie<T> trie;
};

} // end namespace Mistercomplete
