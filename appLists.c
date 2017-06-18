#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

//returns a pointer to the node at the head of the appList
appNode* insertApp (appNode* head, char* name, int index) {

	if (head == NULL) {
		head = (appNode*)malloc(sizeof(appNode));
		if(head==NULL) {
			printf("Error: department Node is NULL\n");
			return NULL;
		}
		head->index = index;
		head->name = name;
		head->assignedTo = NULL;
		head->next = NULL;
		head->prefList = initQueue();
	}
	else {
		head->next = insertApp(head->next, name, index);
	}
	return head;
}

//returns a pointer to the appNode with the given name, otherwise NULL if no such appNode exists
appNode* findAppByName (appNode* head, char* name) {
	appNode *temp = head;

	while(temp != NULL) {
		if (strcmp(name,temp->name) == 0){//if current appNode's name is the same
			return temp;
		}
		temp = temp->next;
	}
	if (temp == NULL) {
		printf("Applicant with given name was not found\n");
		return NULL;
	}
}

//returns a pointer to the appNode with the given index, otherwise NULL if no such appNode exists
appNode* findAppByIndex (appNode* head, int index) {
	appNode *temp = head;

	while(temp != NULL) {
		if (index == temp->index){
			return temp;
		}
		temp = temp->next;
	}
	if (temp == NULL) {
		printf("Applicant with given index was not found\n");
		return NULL;
	}
}

void freeAppNodes (appNode* head) {
	
	appNode* temp;

	while(head != NULL) {
		temp = head;
		head = head->next;
		freeQueue(temp->prefList);
		free(temp);
	}
}
