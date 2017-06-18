#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include <string.h>


/*creates pair graph with given num of vertexs and returns a pointer to that graph*/
pairGraph* createPairGraph (int V, depNode *dhead) {
	pairGraph* graph = (pairGraph*) malloc(sizeof(pairGraph));
	graph->V = V;
	graph->array = (pairList*) malloc(V * sizeof(pairList));

	int i;
	depNode *dtemp = NULL;
	for (i=1; i<=V; i++) {
		dtemp = findDepByIndex(dhead, i);
		graph->array[i].head = newPairListNode (dtemp->name);
	}

	return graph;
}

/*creates a node for a new vertice in the pair graph*/
pairListNode* newPairListNode (char* name) {
	pairListNode* newNode = (pairListNode*) malloc(sizeof(pairListNode));
	newNode->vertex = name;
	newNode->next = NULL;
	return newNode;
}

//essentially like adding an edge, this adds the parameter app to dep's pairList
void addPair (pairGraph* graph, char* dep, char* app, depNode *dhead) {
	int i = 0;
	int ind = 0;
	pairListNode* temp = (pairListNode*) malloc(sizeof(pairListNode));

	depNode *dtemp = NULL;
	dtemp = findDepByName(dhead, dep);

	ind = dtemp->index;	

	temp = graph->array[ind].head;
		
	//loops thorugh current vertex's adjlist to check if edge to be entered is a duplicate
	while (temp != NULL) {
		if (strcmp(temp->vertex, app) == 0) {
			i = 1;
			break;
		}
		temp = temp->next;
	}
	if (i == 1) {
		return;
	}
	else {
		pairListNode* newNode = newPairListNode(app);
		pairListNode* temp2 = (pairListNode*) malloc(sizeof(pairListNode));
		temp2 = graph->array[ind].head;
		while (temp2->next != NULL) {//adds edge by adding new node to temp2s pairlist
			temp2 = temp2->next;
		}
		temp2->next = newNode;
	}
}

//deletes the paramter app from dep's pairList. essentially like deleting an edge from the graph
void deletePair (pairGraph* graph, char* dep, char* app, depNode *dhead) {
	int i = 0;
	int ind = 0;
	pairListNode* temp = (pairListNode*) malloc(sizeof(pairListNode));
	pairListNode* temp2 = (pairListNode*) malloc(sizeof(pairListNode));

	depNode *dtemp = NULL;
	dtemp = findDepByName(dhead, dep);

	ind = dtemp->index;	

	if(strcmp(graph->array[ind].head->vertex, app) == 0) {//if the first element in the list is the one to be deleted
		temp = graph->array[ind].head;
		graph->array[ind].head = graph->array[ind].head->next;
		free(temp);
		return;
	}
	temp2 = graph->array[ind].head;
	while(temp2->next->next != NULL) {//element to be deleted in somewhere in the middle of the pairList
		if(strcmp(temp2->next->vertex, app) == 0){
			temp = temp2->next;
			temp2->next = temp->next;
			free(temp);
			return;
		}
		temp2=temp2->next;
	}
	if(strcmp(temp2->next->vertex, app) == 0) {//element is at the end of the pairList
		temp = temp2->next;
		free(temp);
		temp2->next = NULL;
	}

}

//prints the pair Graph as a list of each department, each with a list of applicants selected to fill its vacancies
void printPairGraph (pairGraph* graph) {

	int v;
	int looper = 0;
	int index = 1;

	for (v=1; v<=graph->V; v++) {
		looper = 0;
		index = 1;

		pairListNode* pCrawl = graph->array[v].head;
		printf("Job Applicants selected to fill %s's departmental vacancies:\n", pCrawl->vertex);
		pCrawl = pCrawl->next;
		if(pCrawl == NULL) {
			printf("Error: No pairings listed in pairList.\n");
			looper = 1;
		}	
		while (looper == 0) {//loops through the array of linked lists to print out pairList rep. of the graph
			printf("%d: %s\n", index, pCrawl->vertex);
			++index;
			pCrawl = pCrawl->next;
			if (pCrawl == NULL) {
				break;
			}
		}
		printf("\n");
	}
}

void freePairGraph (pairGraph* graph) {
	
	int v;
	pairListNode* temp;

	for (v=1; v<=graph->V; v++) {
		
		while(graph->array[v].head != NULL) {
			temp = graph->array[v].head;
			graph->array[v].head = graph->array[v].head->next;
			free(temp);
		}
	}
	free(graph);
}
