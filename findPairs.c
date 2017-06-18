#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"

//uses Gale-Shapley algorithm to find a well-formed allocation of applicants to departmetnal vacancies.
//returns pairGraph containing list of department and applicant pairings
pairGraph* GSfindPairs (pairGraph *graph, depNode *depHead, appNode *appHead) {

	depNode *dtemp = NULL;
	dtemp = depHead;

	appNode *atemp = NULL;
	atemp = NULL;

	char* app = NULL;
	char* curAssgn = NULL;

	depNode *curAssgnDep = NULL;
	
	//while there is a department with an open vacancy, who hasnt already offered a position to every applicant
	while(dtemp != NULL) {
		while(dtemp->vacancies > 0 && !isEmpty(dtemp->prefList)) {
			//find the highest rated applicant in current department's prefList
			app = deque(dtemp->prefList);
			atemp = findAppByName (appHead, app);

			if(atemp->assignedTo == NULL) {//if this applicant hasnt been assigned to a department
				//this applicant is assigned to the current department
				addPair(graph, dtemp->name, atemp->name, depHead);
				--dtemp->vacancies;//update department's vacancies
				atemp->assignedTo = strdup(dtemp->name);
			}
			
			else if(atemp->assignedTo != NULL) {//otherwise, this applicant has already been assigned
				curAssgn = strdup(atemp->assignedTo);//find the name of the dep this applicant is assigned to
				//if the applicant prefers the current dep to the one its assigned to
				if(checkPref(atemp->prefList, curAssgn, dtemp->name) == 0) {
					//this applicant is unassigned to its currently assigned dep
					curAssgnDep = findDepByName(depHead, curAssgn);
					deletePair(graph, curAssgnDep->name, atemp->name, depHead);
					++curAssgnDep->vacancies;//updates currently assigned dep's vacancies
					atemp->assignedTo = NULL;
					
					//assign this applicant to current department
					addPair(graph, dtemp->name, atemp->name, depHead);
					--dtemp->vacancies;//update current departments vacancies
					atemp->assignedTo = strdup(dtemp->name);
				}
			}
		app = NULL;
		atemp = NULL;
		curAssgn = NULL;
		curAssgnDep = NULL;
		}
	dtemp = findDep(depHead);	
	}
	return graph;
}	

//checks if the poten department is higher on the applicants pref list than than its current assgned dep. return 0 if it is, 1 otherwise.
int checkPref (prefQ *prefList, char* curr, char* poten) {
	
	prefQ *temp = prefList;

	if(temp->front == NULL && temp->rear == NULL) {
		printf("Error: Queue is empty.\n");
		return;
	}
	while(temp->front != temp->rear) {
		if(strcmp(curr, temp->front->name) == 0) {
			return 1;
		}
		else if (strcmp(poten, temp->front->name) == 0) {
			return 0;
		}
		temp->front = temp->front->next;
	}
	if (temp->front == temp->rear) {
		if(strcmp(curr, temp->front->name) == 0) {
			return 1;
		}
		else if (strcmp(poten,temp->front->name) == 0) {
			return 0;
		}
	}
}

//returns a pointer to a depNode than still has an open vacancy and hasnt yet offered a postion to every applicant, NULL otherwise
depNode* findDep (depNode* depHead) {

	depNode* temp = depHead;
	while(temp != NULL) {
		if(temp->vacancies > 0 && !isEmpty(temp->prefList)) {
			return temp;
		}
	temp = temp->next;
	}

	return NULL;
}
