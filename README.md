# MisterComplete
### Vision
MisterComplete is a small project that I am working on. The idea is to create a well documented and easily usable header-only C++ library. The initial plan is not to have a lot of functionality, but to provide a good developer experience and good interfaces for anyone using this library.

### Use case
The goal of the library is to serve as a text autocompletion tool. You set it up with data people could be possibly searching for (e.g. movie names), and then, as the user is typing, MisterComplete would make guesses on what the user might be looking for.

### How to use
Just include the header — no compilation or linking required.

``` C++
#include "completer.h"
#include <string>

int main() {

    Mistercomplete::Completer<int> mc;
    mc.add_entry(1, "cat buffet");    // takes an id and a string
    mc.add_entry(2, "catzilla");
    mc.add_entry(3, "breaking bad");
    mc.suggest("ca");                 // returns vector<pair<int, string>>
                                      // with all completions for the prefix

}
```

The id type is a template parameter, so you can use any type — `int`, `std::string`, a UUID, etc.:

``` C++
Mistercomplete::Completer<std::string> mc;
mc.add_entry("550e8400-e29b-41d4-a716-446655440000", "cat buffet");
mc.add_entry("550e8400-e29b-41d4-a716-446655440001", "catzilla");
mc.suggest("ca");                 // returns vector<pair<std::string, std::string>>
```
