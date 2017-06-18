#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

//returns a pointer to a the head of the depNode list
depNode* insertDep (depNode* head, char* name, int vacancies, int index) {

	if (head == NULL) {
		head = (depNode*)malloc(sizeof(depNode));
		if(head==NULL) {
			printf("Error: department Node is NULL\n");
			return NULL;
		}
		head->index = index;
		head->name = name;
		head->vacancies = vacancies;
		head->next = NULL;
		head->prefList = initQueue();
	}
	else {//recursively add the node on the end of the list
		head->next = insertDep(head->next, name, vacancies, index);
	}
	return head;
}

//returns a pointer to the depNode with the given name, otherwise NULL is no such depNode exists
depNode* findDepByName (depNode* head, char* name) {
	depNode *temp = head;

	while(temp != NULL) {
		if (strcmp(name, temp->name) == 0){//if the current node has the same name
			return temp;
		}
		temp = temp->next;
	}
	if (temp == NULL) {
		printf("Dep with given name was not found\n");
		return NULL;
	}
}

//returns a pointer to the depNode with the given index, otherwise NULL is no such depNode exists
depNode* findDepByIndex (depNode* head, int index) {
	depNode *temp = head;

	while(temp != NULL) {
		if (index == temp->index){
			return temp;
		}
		temp = temp->next;
	}
	if (temp == NULL) {
		printf("Dep with given index was not found\n");
		return NULL;
	}
}

void freeDepNodes (depNode* head) {
	
	depNode* temp;

	while(head != NULL) {
		temp = head;
		head = head->next;
		freeQueue(temp->prefList);
		free(temp);
	}
}
