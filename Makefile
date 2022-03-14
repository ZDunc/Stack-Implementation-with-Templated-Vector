in2post.x: in2post.o stack.h stack.hpp
	g++ -o in2post.x in2post.o

in2post.o: in2post.cpp stack.h stack.hpp
	g++ -c -std=c++11 in2post.cpp

clean:
	rm -f in2post.x *.o
