build : map_reduce

map_reduce : main.cpp reducer.cpp shuffle.cpp mapper.cpp mapper.h reducer.h shuffle.h
	g++ -g -std=c++11 -o map_reduce main.cpp reducer.cpp shuffle.cpp mapper.cpp

# Clean rule to remove object files and the executable
clean:
	rm -f *.o
