utrello: directories build/board.o build/list.o build/main.o build/task.o build/task_utility.o build/user.o build/utrello_interface.o
	g++ build/board.o build/list.o build/main.o build/task.o build/task_utility.o build/user.o build/utrello_interface.o -o utrello

build/board.o: src/board.cpp src/board.hpp
	g++ -c src/board.cpp -o build/board.o

build/list.o: src/list.cpp src/list.hpp
	g++ -c src/list.cpp -o build/list.o

build/main.o: src/main.cpp
	g++ -c src/main.cpp -o build/main.o

build/task.o: src/task.cpp src/task.hpp
	g++ -c src/task.cpp -o build/task.o

build/task_utility.o: src/task_utility.cpp src/task_utility.hpp
	g++ -c src/task_utility.cpp -o build/task_utility.o

build/user.o: src/user.cpp src/user.hpp
	g++ -c src/user.cpp -o build/user.o

build/utrello_interface.o: src/utrello_interface.cpp src/utrello_interface.hpp
	g++ -c src/utrello_interface.cpp -o build/utrello_interface.o

clean: clear utrello

clear:
	rm -f build/*.o utrello
directories:
	mkdir -p build