CXX=g++
CXXFLAGS=-g -Wall -std=c++11 
# Uncomment for parser DEBUG
#DEFS=-DDEBUG


all: bst-test equal-paths-test

bst-test: bst-test.cpp bst.h avlbst.h
	$(CXX) $(CXXFLAGS) $(DEFS) $< -o $@

# Brute force recompile all files each time
equal-paths-test: equal-paths-test.cpp equal-paths.cpp equal-paths.h
	$(CXX) $(CXXFLAGS) $(DEFS) equal-paths-test.cpp equal-paths.cpp -o $@

clean:
	rm -f *~ *.o bst-test equal-paths-test
