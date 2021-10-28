all: driver.o Triangle.o
	g++ -Wall driver.o Triangle.o -o output.out

Triangle.o: Triangle.cpp Triangle.h
	g++ -Wall -c Triangle.cpp

driver.o: driver.cpp Point.h Triangle.h
	g++ -Wall -c driver.cpp

run: 
	echo $$(./output.out)

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

$(ZIP_TARGETS): %.zip : $$(shell find % -type f ! -path "%/.*")
	cd $(basename $@)/.. && zip -FSr $(notdir $@) $(notdir $(basename $@)) -x $(notdir $(basename $@))/.\*

CIBLE := $(notdir $(abspath .))

zip: 
	echo $$(cd ../ && zip -r proj.zip $(CIBLE))