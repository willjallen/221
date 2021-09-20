all: driver.o A.o C.o
	g++ -Wall driver.o A.o C.o -o output.out

driver.o: driver.cpp A.h B.h C.h
	g++ -Wall -c driver.cpp

C.o: B.cpp C.h B.h 
	g++ -Wall -c B.cpp

A.o: driver.cpp A.h
	g++ -Wall -c driver.cpp

run: ./output.out

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#
