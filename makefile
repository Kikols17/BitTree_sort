test: test.c BitTree_sort.o
	gcc -Wall -Wextra test.c BitTree_sort.o -o test

BitTree_sort.o: BitTree_sort.c BitTree_sort.h
	gcc -Wall -Wextra -c BitTree_sort.c


clean:
	rm -f *.o
	rm -f test