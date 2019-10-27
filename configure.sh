#!/bin/bash
MAKETEXT='utrello:'
function make_all {
	MAKETEXT="$MAKETEXT $1.o"
}
function make_all_g {
	MAKETEXT="$MAKETEXT build/$1.o"
}
function make_individual {
	MAKETEXT="$MAKETEXT\n$1.o: src/$1.cpp\n\tg++ -c src/$1.cpp -o build/$1.o\n"
}
function make_individual_with_hpp {
	MAKETEXT="$MAKETEXT\n$1.o: src/$1.cpp src/$1.hpp\n\tg++ -c src/$1.cpp -o build/$1.o\n"
}
if [ $# -eq 0 ]
then for file in src/*.cpp
    do make_all "$(echo $file| cut -d'.' -f 1| cut -d'/' -f 2)"
done
MAKETEXT="$MAKETEXT\n\tg++"
for file in src/*.cpp
    do make_all_g "$(echo $file| cut -d'.' -f 1| cut -d'/' -f 2)"
done
MAKETEXT="$MAKETEXT -o utrello"
MAKETEXT="$MAKETEXT\n"
for file in src/*.cpp 
do
	if [[ -f "$(echo $file| cut -d'.' -f 1| cut -d'/' -f 2).hpp" ]]; then
		make_individual_with_hpp "$(echo $file| cut -d'.' -f 1| cut -d'/' -f 2)"
	else
    	make_individual "$(echo $file| cut -d'.' -f 1| cut -d'/' -f 2)"
	fi
done
MAKETEXT="$MAKETEXT\nclean: clear utrello\n"
MAKETEXT="$MAKETEXT\nclear:\n\trm -f build/*.o utrello"
fi
printf "$MAKETEXT" > makefile
