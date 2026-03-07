#pragma once
#include <optional>

namespace Mistercomplete {

template <typename T>
class Node {
public:
        Node* parent = nullptr;
        char character = 0;
        bool ending = false;
        std::optional<T> id;
        Node* children[26] = { nullptr };

        int child_count()
        {
                int count = 0;
                for (int i = 0; i < 26; i++) count += (children[i] != nullptr);
                return count;
        }
};

} // end namespace Mistercomplete
