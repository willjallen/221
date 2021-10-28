ifeq ($(OS), Windows_NT)
		EXECUTABLE=driver.exe
else
		EXECUTABLE=driver.out
endif

all: dtree.o driver.o
	g++ -g -Wall -std=c++11 driver.o dtree.o  -o $(EXECUTABLE)

driver.o: driver.cpp
		g++ -g -Wall -std=c++11  -c driver.cpp

dtree.o: dtree.cpp
		g++ -g -Wall -std=c++11 -c dtree.cpp

valgrind:
		valgrind -s --track-origins=yes ./driver.out

run:
		./$(EXECUTABLE)

clean:
		rm -r *.o
		rm *.out
