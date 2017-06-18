#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <string.h>

//prints list of all departments with their index, vacancies and prefLists, and all applicants with thier index and prefLists
void printDepsAndApps (depNode *depHead, appNode *appHead) {
	
	depNode *dtemp;
	dtemp = depHead;
	printf("------Departments------\n");
	while(dtemp != NULL) {
		printf("%d - Name: %s, vac: %d\n", dtemp->index, dtemp->name, dtemp->vacancies);
		printf("Pref List: ");
		printQueue(dtemp->prefList);
		dtemp = dtemp->next;
		printf("\n");
	}

	appNode *atemp;
	atemp = appHead;
	printf("-----Job Applicants-----\n");
	while(atemp != NULL) {
		printf("%d - Name: %s\n", atemp->index, atemp->name);
		printf("Pref List: ");
		printQueue(atemp->prefList);
		atemp = atemp->next;
		printf("\n");
	}
}
