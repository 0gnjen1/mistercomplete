#pragma once
#include <vector>
#include <string>
#include <utility>
#include "trie.h"
#include "icompleter.h"

namespace Mistercomplete {

        class Completer : public ICompleter {

        public:
                Completer();
                void add_entry(const int id, const std::string& text);
                [[nodiscard]] std::vector<std::pair<int, std::string>> suggest(const std::string& text);

        private:
                Trie trie;

        };

} // end namespace Mistercomplete
