ORI_T01: ORI_T01.o
	gcc ORI_T01.o -o ORI_T01

ORI_T01_HEADER.o: ORI_T01_HEADER.h
	gcc -c ORI_T01_HEADER.c

ORI_T01.o: ORI_T01.c ORI_T01_HEADER.o
	gcc -c ORI_T01.c

clean:
	rm ORI_T01 *.o