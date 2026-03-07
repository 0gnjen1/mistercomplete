# WARNFLAG := -Wall -Werror -Wextra -Wpedantic

STATIC_OPTION := -static #Linux
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin) #MacOS
	STATIC_OPTION := ""
endif


# Library =====================================================================================================

mistercomplete.a: lib node.o trie.o completer.o
	@echo " - Archiving into a library"
	@ar rcs ./lib/mistercomplete.a ./lib/node.o ./lib/trie.o ./lib/completer.o

completer.o: ./src/completer.cpp ./include/completer.h
	@echo " - Compiling completer.cpp"
	@g++ $(WARNFLAG) -c ./src/completer.cpp -o ./lib/completer.o

trie.o: ./src/trie.cpp ./include/trie.h
	@echo " - Compiling trie.cpp"
	@g++ $(WARNFLAG) -c ./src/trie.cpp -o ./lib/trie.o

node.o: ./src/node.cpp ./include/node.h
	@echo " - Compiling node.cpp"
	@g++ $(WARNFLAG) -c ./src/node.cpp -o ./lib/node.o

lib:
	@mkdir lib

# Testing =====================================================================================================

test: testing.out
	@echo " - Running tests"
	@./test/testing.out

testing.out: ./lib/mistercomplete.a
	@echo " - Compiling testing.cpp"
	@g++ $(WARNFLAG) -c ./test/testing.cpp -o ./test/testing.o
	@g++ ./test/testing.o $(STATIC_OPTION) ./lib/mistercomplete.a -o ./test/testing.out

# Clean =====================================================================================================

clean:
	@echo " - Cleaning up the object files and the compiled library"
	@rm -f ./test/*.out ./test/*.o
	@rm -rf ./lib/
