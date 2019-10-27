utrello: board.o list.o main.o task.o
	g++ build/board.o build/list.o build/main.o build/task.o -o utrello

board.o: src/board.cpp
	g++ -c src/board.cpp -o build/board.o

list.o: src/list.cpp
	g++ -c src/list.cpp -o build/list.o

main.o: src/main.cpp
	g++ -c src/main.cpp -o build/main.o

task.o: src/task.cpp
	g++ -c src/task.cpp -o build/task.o

clean: clear utrello

clear:
	rm -f build/*.o utrello