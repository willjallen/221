all: driver.o SquareList.o InnerSquareList.o
	g++ -Wall driver.o SquareList.o InnerSquareList.o -o output.out

driver.o: driver.cpp SquareList.h
	g++ -Wall -c driver.cpp -o driver.o

SquareList.o: SquareList.cpp SquareList.h InnerSquareList.h
	g++ -Wall -c SquareList.cpp

InnerSquareList.o: InnerSquareList.cpp InnerSquareList.h
	g++ -Wall -c InnerSquareList.cpp


run:
	./output.out

clean:
	rm -f *.o
	rm -f output.out