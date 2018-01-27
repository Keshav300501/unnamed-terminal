all:
	mkdir -p ../out/external
	gcc -w -o ../out/main main.c
	gcc -w -o ../out/external/cat external/cat.c
	gcc -w -o ../out/external/date external/date.c
	gcc -w -o ../out/external/ls external/ls.c
	gcc -w -o ../out/external/mkdir external/mkdir.c
	gcc -w -o ../out/external/rm external/rm.c
	touch ../out/history

clean:
	-rm -rf ../out