all: bin bin/main.o bin/bits.o bin/errors.o
	g++ -o program bin/main.o bin/bits.o bin/errors.o -Wall -g

bin/main.o: src/main.cpp
	g++ -o bin/main.o -c src/main.cpp

bin/errors.o: src/errors.cpp
	g++ -o bin/errors.o -c src/errors.cpp

bin/bits.o: src/bits.cpp
	g++ -o bin/bits.o -c src/bits.cpp

bin:
	mkdir bin

run: all
	./program

clean:
	rm -rf bin
