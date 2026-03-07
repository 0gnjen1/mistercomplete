#pragma once
#include <vector>
#include <string>
#include <utility>

namespace Mistercomplete {

template <typename T>
class ICompleter {
public:
        virtual ~ICompleter() = default;
        virtual void add_entry(const T& id, const std::string& text) = 0;
        [[nodiscard]] virtual std::vector<std::pair<T, std::string>> suggest(const std::string& text) = 0;
};

} // end namespace Mistercomplete
