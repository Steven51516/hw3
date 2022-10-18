CXX := g++
CXXFLAGS := -g -Wall --std=c++11
VALGRIND := valgrind --tool=memcheck --leak-check=yes

all: llrec-test

#-----------------------------------------------------
# ADD target(s) to build your llrec-test executable
#-----------------------------------------------------
llrec-test: llrec-test.cpp llrec.o 
		g++ -g llrec-test.cpp llrec.o -o llrec-test.o

llrec.o: llrec.cpp
		g++ -g -c llrec.cpp -o llrec.o
	
valgrind: llrec-test
	$(VALGRIND) ./llrec-test.o



clean:
	rm -f *.o rh llrec-test *~

.PHONY: clean 