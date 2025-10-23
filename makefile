
build/prog: build/main.o build/code.o build/paragraph.o build/codelist.o build/text.o
	gcc main.o code.o paragraph.o codelist.o build/text.o -o build/prog

build/main.o: src/main.c src/paragraph.h src/code.h src/globals.h
	gcc -c src/main.c -o build/main.o

build/code.o: src/code.c src/paragraph.h src/globals.h
	gcc -c src/code.c -o build/code.o

build/codelist.o: src/codelist.c src/globals.h src/code.h
	gcc -c src/codelist.c -o build/codelist.o

build/paragraph.o: src/paragraph.c src/globals.h
	gcc -c src/paragraph.c -o build/paragraph.o


build/text.o: src/text.c src/paragraph.h
	gcc -c src/text.c -o build/text.o

