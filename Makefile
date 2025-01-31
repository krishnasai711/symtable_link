CXX = g++
CXXFLAGS = -I./include -Wall -g

all: build/test_linked

build/symtable_link.o: src/symtable_link.cpp include/SymTable.h
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/test_linked.o: tests/symtable_test.cpp include/SymTable.h
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/test_linked: build/symtable_link.o build/test_linked.o
	$(CXX) $^ -lgtest -lgtest_main -lgmock -lpthread -o $@

clean:
	@echo "Cleaning up generated files..."
	@rm -rf build

test: build/test_linked
	./build/test_linked

.PHONY: all clean test
