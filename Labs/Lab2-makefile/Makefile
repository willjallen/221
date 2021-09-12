all: driver.o 
	g++ -Wall driver.o -o output.out

# point.o: Point.h
# 	g++ -Wall –std=c++17 -c Point.h

driver.o: driver.cpp Point.h
	g++ -Wall -c driver.cpp

run: ./output.out

clean:
	del -r *.o
	del *.out
	del *~ *.h.gch *#
