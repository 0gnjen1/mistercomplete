# WARNFLAG := -Wall -Werror -Wextra -Wpedantic

# Testing =====================================================================================================

test: test/testing.out
	@echo " - Running tests"
	@./test/testing.out

test/testing.out: ./test/testing.cpp ./include/node.h ./include/trie.h ./include/icompleter.h ./include/completer.h
	@echo " - Compiling testing.cpp"
	@g++ $(WARNFLAG) -std=c++17 ./test/testing.cpp -o ./test/testing.out

# Clean =======================================================================================================

clean:
	@echo " - Cleaning up"
	@rm -f ./test/*.out ./test/*.o
