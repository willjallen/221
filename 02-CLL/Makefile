

# all, run, valgrind, clean, and targets to compile each object class individually 

ifeq ($(OS), Windows_NT)
	EXECUTABLE=driver.exe
else
	EXECUTABLE=driver.out
endif

all: driver bufferlist buffer.o
	g++ -g -Wall -std=c++11 driver.o bufferlist.o buffer.o -o $(EXECUTABLE)

driver: src/driver.cpp
	g++ -g -Wall -std=c++11  -c src/driver.cpp

bufferlist: src/bufferlist.cpp
	g++ -g -Wall -std=c++11 -c src/bufferlist.cpp

buffer: src/buffer.cpp
	g++ -g -Wall -std=c++11 -c src/buffer.cpp

valgrind:
	valgrind -s --track-origins=yes ./driver.out

run:
	./$(EXECUTABLE)

clean:
	rm -r *.o
	rm *.out





