#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <utility>
#include "../include/trie.h"

static int passed = 0;
static int failed = 0;

static void check(bool condition, const std::string& description)
{
        if (condition) {
                passed++;
        } else {
                std::cout << "[FAIL] " << description << '\n';
                failed++;
        }
}

using Results = std::set<std::pair<int, std::string>>;

static Results as_set(const std::vector<std::pair<int, std::string>>& v)
{
        return Results(v.begin(), v.end());
}

static void test_empty_trie()
{
        Mistercomplete::Trie trie;
        check(trie.autocomplete("").empty(),  "empty trie: no results for empty prefix");
        check(trie.autocomplete("a").empty(), "empty trie: no results for 'a'");
}

static void test_remove_on_empty_trie()
{
        Mistercomplete::Trie trie;
        trie.remove("");
        trie.remove("a");
        check(trie.autocomplete("").empty(), "remove on empty trie is safe");
}

static void test_insertion()
{
        Mistercomplete::Trie trie;
        trie.insert(1, "a");
        trie.insert(2, "aa");
        trie.insert(3, "aaa");
        trie.insert(4, "aaaa");
        trie.insert(5, "aaaaa");
        trie.insert(6, "aaaaaa");

        check(as_set(trie.autocomplete("")) == (Results{{1,"a"},{2,"aa"},{3,"aaa"},{4,"aaaa"},{5,"aaaaa"},{6,"aaaaaa"}}),
              "insertion: all entries returned for empty prefix");
        check(as_set(trie.autocomplete("aaaaa")) == (Results{{5,"aaaaa"},{6,"aaaaaa"}}),
              "insertion: prefix filter works");
        check(trie.autocomplete("aaaaaaa").empty(),
              "insertion: no results for non-existent prefix");
}

static void test_removal()
{
        Mistercomplete::Trie trie;
        trie.insert(1, "a");
        trie.insert(2, "aa");
        trie.insert(3, "aaa");
        trie.insert(4, "aaaa");
        trie.insert(5, "aaaaa");
        trie.insert(6, "aaaaaa");

        trie.remove("a");
        trie.remove("aaaaaa");
        trie.remove("aaaaaaa"); // not present, should be safe

        check(as_set(trie.autocomplete("")) == (Results{{2,"aa"},{3,"aaa"},{4,"aaaa"},{5,"aaaaa"}}),
              "removal: removed entries no longer returned");
        check(as_set(trie.autocomplete("aaaaa")) == (Results{{5,"aaaaa"}}),
              "removal: prefix filter correct after removal");
}

static void test_prefix_is_entry()
{
        // "cat" is both an entry and a prefix of "cats"
        Mistercomplete::Trie trie;
        trie.insert(1, "cat");
        trie.insert(2, "cats");

        check(as_set(trie.autocomplete("cat")) == (Results{{1,"cat"},{2,"cats"}}),
              "prefix-as-entry: autocomplete on entry that is also a prefix returns both");
        check(as_set(trie.autocomplete("cats")) == (Results{{2,"cats"}}),
              "prefix-as-entry: autocomplete on longer entry returns only that entry");
}

static void test_remove_prefix_entry()
{
        // "cat" node must not be deleted since "cats" still needs it
        Mistercomplete::Trie trie;
        trie.insert(1, "cat");
        trie.insert(2, "cats");
        trie.remove("cat");

        check(as_set(trie.autocomplete("cat")) == (Results{{2,"cats"}}),
              "remove prefix entry: 'cats' still reachable after removing 'cat'");
        check(as_set(trie.autocomplete("")) == (Results{{2,"cats"}}),
              "remove prefix entry: only 'cats' remains in trie");
}

static void test_remove_leaf_with_prefix_entry()
{
        // "cat" node must survive after "cats" is removed
        Mistercomplete::Trie trie;
        trie.insert(1, "cat");
        trie.insert(2, "cats");
        trie.remove("cats");

        check(as_set(trie.autocomplete("cat")) == (Results{{1,"cat"}}),
              "remove leaf: 'cat' still present after removing 'cats'");
        check(trie.autocomplete("cats").empty(),
              "remove leaf: 'cats' is gone");
}

static void test_overwrite_entry()
{
        // Inserting the same text twice — second id wins
        Mistercomplete::Trie trie;
        trie.insert(1, "hello");
        trie.insert(99, "hello");

        check(as_set(trie.autocomplete("")) == (Results{{99,"hello"}}),
              "overwrite: second insert replaces id");
}

static void test_remove_twice()
{
        Mistercomplete::Trie trie;
        trie.insert(1, "abc");
        trie.remove("abc");
        trie.remove("abc"); // second remove on a now-deleted node

        check(trie.autocomplete("").empty(), "double remove: safe and entry gone");
}

static void test_remove_then_reinsert()
{
        Mistercomplete::Trie trie;
        trie.insert(1, "abc");
        trie.remove("abc");
        trie.insert(2, "abc");

        check(as_set(trie.autocomplete("")) == (Results{{2,"abc"}}),
              "remove then reinsert: entry back with new id");
}

static void test_branching_prefixes()
{
        Mistercomplete::Trie trie;
        trie.insert(1, "ab");
        trie.insert(2, "ac");
        trie.insert(3, "abc");

        check(as_set(trie.autocomplete("a")) == (Results{{1,"ab"},{2,"ac"},{3,"abc"}}),
              "branching: all entries under shared prefix 'a'");
        check(as_set(trie.autocomplete("ab")) == (Results{{1,"ab"},{3,"abc"}}),
              "branching: only 'ab' branch entries");
        check(as_set(trie.autocomplete("ac")) == (Results{{2,"ac"}}),
              "branching: only 'ac' branch entries");
        check(trie.autocomplete("b").empty(),
              "branching: unrelated prefix returns nothing");
}

int main()
{
        test_empty_trie();
        test_remove_on_empty_trie();
        test_insertion();
        test_removal();
        test_prefix_is_entry();
        test_remove_prefix_entry();
        test_remove_leaf_with_prefix_entry();
        test_overwrite_entry();
        test_remove_twice();
        test_remove_then_reinsert();
        test_branching_prefixes();

        if (failed == 0)
                std::cout << "all " << passed << " tests passed\n";
        else
                std::cout << '\n' << passed << " passed, " << failed << " failed\n";
        return failed > 0 ? 1 : 0;
}
