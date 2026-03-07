#pragma once
#include <vector>
#include <string>
#include <utility>

namespace Mistercomplete {

        class ICompleter {
        public:
                virtual ~ICompleter() = default;
                virtual void add_entry(int id, const std::string& text) = 0;
                [[nodiscard]] virtual std::vector<std::pair<int, std::string>> suggest(const std::string& text) = 0;
        };

} // end namespace Mistercomplete
