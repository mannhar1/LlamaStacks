all: LlamaNode.o Llama.o Driver.o 
	g++ -Wall LlamaNode.cpp Llama.cpp Driver.cpp -o driver.out

LlamaNode.o: LlamaNode.cpp
	g++ -Wall -c LlamaNode.cpp

Llama.o: Llama.cpp
	g++ -Wall -c Llama.cpp

Driver.o: Driver.cpp
	g++ -Wall -c Driver.cpp

driver2.o: driver2.cpp
	g++ -Wall -c driver1.cpp

driver3.o: driver3.cpp
	g++ -Wall -c driver1.cpp

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

run:
	./driver.out

valgrind:
	valgrind driver.out

