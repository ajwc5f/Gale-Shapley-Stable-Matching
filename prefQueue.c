#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

//returns a pointer to a new preference queue
prefQ* initQueue() {
	prefQ* newQ = (prefQ*)malloc(sizeof(prefQ));
	newQ->front = NULL;
	newQ->rear = NULL;
	return newQ;
}

//returns a pointer to a new preference queue node
prefQNode* newNode (char* name) {
	prefQNode* new = (prefQNode*)malloc(sizeof(prefQNode));
	new->name = name;
	new->next = NULL;
	return new;
}

void enque(prefQ *prefList, char* name) {
	
	prefQNode *new = newNode(name);
	
	//if prefList is empty, new node will be front and rear of the list
	if(isEmpty(prefList)) {
		prefList->front = new;
		prefList->rear = new;
		return;
	}
	else {//loop through the prefList and find correct spot for the new node
		prefList->rear->next = new;
		prefList->rear = new;
	}
}

//returns the name of the dequed element
char* deque (prefQ *prefList) {
	prefQNode* temp = prefList->front;
	char* n = temp->name;
	
	//if front equals rear, then only one node was in list, so we set front and rear to null
	if (prefList->front == prefList->rear) {
		prefList->front = NULL;
		prefList->rear = NULL;
	}
	else {//make the front of the queue point to the second node in the queue, so we can free the first
		prefList->front = prefList->front->next;
	}
	
	free(temp);
	return n;
}

//returns 1 is empty, 0 otherwise
int isEmpty (prefQ *prefList) {
	if(prefList->front == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

//prints out the preference List
void printQueue(prefQ *prefList) {
	prefQ *temp = prefList;

	if(temp->front == NULL && temp->rear == NULL) {
		printf("Error: Queue is empty.\n");
		return;
	}
	while(temp->front != temp->rear) {
		printf("%s -> ", temp->front->name);
		temp->front = temp->front->next;
	}
	if (temp->front == temp->rear) {
		printf("%s\n", temp->front->name);
	}
}

void freeQueue (prefQ *prefList) {
	prefQNode *temp;

	while(prefList->front != prefList->rear) {
		temp = prefList->front;
		prefList->front = prefList->front->next;
		free(temp);
	}
	if (prefList->front == prefList->rear) {
		temp = prefList->front;
		free(temp);
	}
}



