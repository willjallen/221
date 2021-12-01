ifeq ($(OS), Windows_NT)
		EXECUTABLE=driver.exe
else
		EXECUTABLE=driver.out
endif

all: driver.o rqueue.o
	g++ -Wall -Werror -std=c++11 driver.o rqueue.o -o $(EXECUTABLE) 

driver.o: driver.cpp
	g++ -g -Wall -Werror -std=c++11 -c driver.cpp

rqueue.o: rqueue.cpp rqueue.h
	g++ -g -Wall -Werror -std=c++11 -c rqueue.cpp

valgrind:
		valgrind -s --track-origins=yes ./driver.out

run:
		./$(EXECUTABLE)

clean:
		rm driver.o
		rm rqueue.o
		rm *.out
