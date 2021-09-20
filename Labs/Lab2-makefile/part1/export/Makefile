all: driver.o 
	g++ -Wall driver.o -o output.out

driver.o: driver.cpp Point.h
	g++ -Wall -c driver.cpp

run: 
	echo $$(./output.out)

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#
