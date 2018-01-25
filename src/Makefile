all:
	mkdir -p ../out/external
	gcc -o ../out/main main.c
	gcc -o ../out/external/cat external/cat.c
	gcc -o ../out/external/date external/date.c
	gcc -o ../out/external/ls external/ls.c
	gcc -o ../out/external/mkdir external/mkdir.c
	gcc -o ../out/external/rm external/rm.c
	touch ../out/history

clean:
	-rm -rf ../out