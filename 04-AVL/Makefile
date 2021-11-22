ifeq ($(OS), Windows_NT)
		EXECUTABLE=driver.exe
else
		EXECUTABLE=driver.out
endif

all: driver.o utree.o dtree.o
	g++ -Wall -Werror -std=c++11 driver.o utree.o dtree.o -o $(EXECUTABLE) 

driver.o: driver.cpp
	g++ -g -Wall -Werror -std=c++11 -c driver.cpp

utree.o: utree.cpp
	g++ -g -Wall -Werror -std=c++11 -c utree.cpp

dtree.o: dtree.cpp
	g++ -g -Wall -std=c++11 -c dtree.cpp


valgrind:
		valgrind -s --track-origins=yes ./driver.out

run:
		./$(EXECUTABLE)

clean:
		rm driver.o
		rm dtree.o
		rm utree.o
		rm *.out
