pairs: driver.c prefQueue.o depLists.o appLists.o parser.o pairGraph.o findPairs.o functions.h
	gcc -o pairs -Wall driver.c prefQueue.o depLists.o appLists.o parser.o pairGraph.o findPairs.o

depsandapps: driver.c prefQueue.o depLists.o appLists.o parser.o printall.o functions.h
	gcc -D PRINTDEPSANDAPPS -o depsandapps driver.c prefQueue.o depLists.o appLists.o parser.o printall.o

prefQueue.o: prefQueue.c
	gcc -c prefQueue.c

depLists.o: depLists.c prefQueue.c
	gcc -c depLists.c prefQueue.c

appLists.o: appLists.c prefQueue.c
	gcc -c appLists.c prefQueue.c
	
parser.o: parser.c prefQueue.c depLists.c appLists.c
	gcc -c parser.c prefQueue.c depLists.c appLists.c

pairGraph.o: pairGraph.c depLists.c
	gcc -c pairGraph.c depLists.c

findPairs.o: findPairs.c prefQueue.c depLists.c appLists.c pairGraph.c
	gcc -c findPairs.c prefQueue.c depLists.c appLists.c pairGraph.c

clean:
	rm -rf *.o pairs depsandapps
