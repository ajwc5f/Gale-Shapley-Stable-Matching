#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <string.h>

int main( int argc, char ** argv ){

	//chacks command line arguments
	if(argc != 2) {
		printf("Error: usage is: ./target input.txt\n");
		return 0;
	}
	
	//opens input file
	FILE *input = fopen(argv[1],"r");
	
	//makes sure file opens correctly
	if (!input){
		printf("Error: Failure to open input file.\n");
		return 0;
	}
	if (input == NULL) {
		printf("Error: Input file is NULL.\n");
		return 0;
	}

	depNode *depHead;
	depHead = NULL;
	
	appNode *appHead;
	appHead = NULL;	

	int numOfVerts = 0;
	
	numOfVerts = getDepsAndApps(input, &depHead, &appHead);
	if(numOfVerts == 0) {
		if(depHead == NULL) {
			printf("Error: List of Departments could not be created.\n");
			return 0;
		}
		if(appHead == NULL) {
			printf("Error: List of Job Applicants could not be created.\n");
			return 0;
		}
	}

	fclose(input);

	printf("\n");
	
	#ifdef PRINTDEPSANDAPPS
	printDepsAndApps(depHead, appHead);
	return 1;
	#endif

	pairGraph *pgraph = NULL;

	pgraph = createPairGraph(numOfVerts, depHead);
	
	pgraph = GSfindPairs(pgraph, depHead, appHead);

	printPairGraph(pgraph);//shows all departments with thier chosen applicants

	freeDepNodes(depHead);
	depHead = NULL;
	freeAppNodes(appHead);
	appHead = NULL;
	freePairGraph(pgraph);
	pgraph = NULL;
	
	return 1;
}

