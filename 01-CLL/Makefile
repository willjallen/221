

# all, run, valgrind, clean, and targets to compile each object class individually 


all: driver.o bufferlist.o buffer.o
	g++ -Wall -std=c++11 driver.o bufferlist.o buffer.o -o driver.exe

driver.o: src/driver.cpp
	g++ -Wall -c src/driver.cpp

bufferlist.o: src/bufferlist.cpp
	g++ -Wall -c src/bufferlist.cpp

buffer.o: src/buffer.cpp
	g++ -Wall -c src/buffer.cpp

valgrind:
	valgrind ./driver.exe

run:
	$$(driver.exe)

clean:
	rm -rf *.o*
	rm -rf *~
	rm -f *.out
	rm -f *~*.h.gcg *#




