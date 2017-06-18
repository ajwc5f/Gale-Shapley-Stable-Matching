#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <string.h>

//Reads in the input file and creates a list of Departments and Job Applicants and all preferences. Returns the number of vertexs that the graph storing pairs will contain.
int getDepsAndApps (FILE* input, depNode **depHead, appNode **appHead) {
	
	char buf[256];
	int numOfDeps = 0;//keep track of the number of departments
	int numOfApps = 0;//keep track of the number of applicants
	int lineNum = 1;//keep track of current line in input file for error messages
	int vholder = 0;//holds the current departments number of vacancies
	char *dname = NULL;//a department name
	char *aname = NULL;//an applicant name
	char *tok = NULL;
	depNode *dhead = NULL;
	appNode *ahead = NULL;
	depNode *dhtemp = NULL;
	appNode *ahtemp = NULL;
	int i;
	int totvac = 0;//keep track if there are more vacancies than apps
	


	//read in Deps and thier vacancies
	fgets(buf, sizeof(buf), input);
	if((strstr(buf, "Vacancies and Departments\n")) == NULL) {
		printf("Error on file line %d: Must be 'Vacancies and Departments'.\n", lineNum);
		return 0;
	}

	lineNum++;

	fgets(buf, sizeof(buf), input);
	if(strcmp(buf, "\n") != 0) {
		printf("Error on file line %d: Must be blank.\n", lineNum);
		return 0;
	}
	
	//read in valid department names until there is a blank line
	while(1) {
		lineNum++;

		fgets(buf, sizeof(buf), input);
		if(strcmp(buf, "\n") == 0) {
			if(numOfDeps == 0) {
				printf("Error on file line %d: No departments listed.\n", lineNum);
			}
			break;
		}

		tok = strtok(buf, " ");
		if (tok == NULL) {
			printf("Error on file line %d: Department listings is blank.\n", lineNum);
			return 0;
		}

		vholder = atoi(tok);
		if (vholder == 0) {
			printf("Error on file line %d: Department listings must begin w/ a number.\n", lineNum);
			return 0;
		}

		tok = strtok(NULL, "\0");
		if (tok == NULL) {
			printf("Error on file line %d: No department name in the listing.\n", lineNum);
			return 0;
		}
		
		tok[strlen(tok) - 1] = 0;
		dname = strdup(tok);
		
		if(!isValidDepName(dname)) {
			printf("Error on file line %d: Department name contains invalid character(s).\n", lineNum);
			return 0;
		}

		dhead = insertDep(dhead, dname, vholder, numOfDeps+1);
		++numOfDeps;

		totvac += vholder;

		vholder = 0;
		dname = NULL;
	}
	



	//read in Applicants
	++lineNum;

	fgets(buf, sizeof(buf), input);
	if((strstr(buf, "Job Applicants\n")) == NULL) {
		printf("Error on file line %d: Must be 'Job Applicants'.\n", lineNum);
		return 0;
	}

	lineNum++;

	fgets(buf, sizeof(buf), input);
	if(strcmp(buf, "\n") != 0) {
		printf("Error on file line %d: Must be blank.\n", lineNum);
		return 0;
	}

	//read in valid applicant names until there is a blank line
	while(1) {
		lineNum++;

		fgets(buf, sizeof(buf), input);
		if(strcmp(buf, "\n") == 0) {
			if(numOfApps == 0) {
				printf("Error on file line %d: No applicants listed.\n", lineNum);
			}
			break;
		}

		buf[strlen(buf) - 1] = 0;
		aname = strdup(buf);
		if(!strncmp(aname, "Preferences", 11) && numOfApps == 0) {
			printf("Error on file line %d: No applicants listed.\n", lineNum);
		  	return 0;
		}
		else if (!strncmp(aname, "Preferences", 11)) {
			printf("Error on file line %d: Applicant listings not follow by blank line.\n", lineNum);
			return 0;
		}	

		if(!isValidAppName(aname)) {
			printf("Error on file line %d: Job Applicant name contains invalid character(s).\n", lineNum);
			return 0;
		}

		ahead = insertApp(ahead, aname, numOfApps+1);
		++numOfApps;

		aname = NULL;
	}
	
	//make sure there are more applicants than vacancies
	if(numOfApps < totvac) {
		printf("Error: Total number of applicants should be greater than the total number of vacancies.\n");
		return 0;
	}



	//read in Dep pref lists
	for (i=1; i <= numOfDeps; i++) {
		
		dhtemp = dhead;

		++lineNum;

		fgets(buf, sizeof(buf), input);

		tok = strtok(buf, " ");
		if (tok == NULL) {
			printf("Error on file line %d: Preference list heading doesnt exist.\n", lineNum);
			return 0;
		}
		if(strcmp(tok, "Preferences") != 0) {
			printf("Error on file line %d: Preference List heading is incorrect.\n", lineNum);
		  	return 0;
		}

		tok = strtok(NULL, "\0");
		tok[strlen(tok) - 1] = 0;
		
		dhtemp = findDepByIndex(dhtemp, i);
		//verify that we are reading in department  preferences in same order we read in the departments
		if(strcmp(tok, dhtemp->name) != 0) { 
			printf("Error on file line %d: Wrong department's preferences listed.\n", lineNum);
			return 0;
		}

		lineNum++;

		fgets(buf, sizeof(buf), input);
		if(strcmp(buf, "\n") != 0) {
			printf("Error on file line %d: Must be blank.\n", lineNum);
			return 0;
		}

		int ind = 0;//to make sure prefList contains enough names
		//read in and add valid names to current deps prefList until a blank line
		while(1) {
			lineNum++;

			fgets(buf, sizeof(buf), input);
			if(strcmp(buf, "\n") == 0) {
				if (ind == 0) {
					printf("Error on file line %d: No applicants listed in pref list.\n", lineNum);
				}
				break;
			}

			buf[strlen(buf) - 1] = 0;
			aname = strdup(buf);
			//checking to see if we encounter next listing of preferences before we have read any from current listing, meaning listing is blank
			if(!strncmp(aname, "Preferences", 11) && ind == 0) {
				printf("Error on file line %d: No applicants listed in pref list.\n", lineNum);
		  		return 0;
			}

			if(!isValidAppName(aname)) {
				printf("Error on file line %d: Job Applicant name contains invalid character(s).\n", lineNum);
				return 0;
			}

			enque(dhtemp->prefList, aname);//add applicant name to the departments prefList
			ind++;
			
			aname = NULL;

		}
		if(ind != numOfApps) {
			printf("Error on file line %d: Preference List doesnt contain enough applicants.\n", lineNum);
			return 0;
		}
	}



	//read in App pref lists
	for (i=1; i <= numOfApps; i++) {
		
		ahtemp = ahead;

		++lineNum;

		fgets(buf, sizeof(buf), input);

		tok = strtok(buf, " ");
		if (tok == NULL) {
			printf("Error on file line %d: Preference list heading doesnt exist.\n", lineNum);
			return 0;
		}
		if(strcmp(tok, "Preferences") != 0) {
			printf("Error on file line %d: Preference List heading is incorrect.\n", lineNum);
		  	return 0;
		}

		tok = strtok(NULL, "\0");
		tok[strlen(tok) - 1] = 0;
		
		ahtemp = findAppByIndex(ahtemp, i);
		
		//verify that we are reading in appliant preferences in same order we read in the applicants
		if(strcmp(tok, ahtemp->name) != 0) { 
			printf("Error on file line %d: Wrong applicant's preferences listed.\n", lineNum);
			return 0;
		}

		lineNum++;

		fgets(buf, sizeof(buf), input);
		if(strcmp(buf, "\n") != 0) {
			printf("Error on file line %d: Must be blank.\n", lineNum);
			return 0;
		}

		int ind = 0;
		//read in and add valid names to current applicants prefList until a blank line
		while(1) {
			lineNum++;

			fgets(buf, sizeof(buf), input);
			if(strcmp(buf, "\n") == 0) {
				if (ind == 0) {
					printf("Error on file line %d: No departments listed in pref list.\n", lineNum);
				}
				break;
			}

			buf[strlen(buf) - 1] = 0;
			dname = strdup(buf);
			//check to see if we encounter next listing of preferences or the end of the file before any of the current lisitngs, meaning listing is blank
			if((!strncmp(dname, "Preferences", 11) || !strncmp(dname, "END INPUT", 9)) && ind == 0) {
				printf("Error on file line %d: No departments listed in pref list.\n", lineNum);
		  		return 0;
			}

			if(!isValidDepName(dname)) {
				printf("Error on file line %d: Department name contains invalid character(s).\n", lineNum);
				return 0;
			}

			enque(ahtemp->prefList, dname);//add department to applicant's prefList
			ind++;
			
			dname = NULL;

		}
		if(ind != numOfDeps) {
			printf("Error on file line %d: Preference List doesnt contain enough departments.\n", lineNum);
			return 0;
		}
	}

	lineNum++;

	//make sure last line is END INPUT, but even if not, we have gathered all neccessary data at this point so we may continue
	fgets(buf, sizeof(buf), input);	
	if((strstr(buf, "END INPUT")) == NULL) {
		printf("Error on file line %d: File must end with 'END INPUT'. Program will not terminate becuase all info was successfully obtained.\n", lineNum);
	}

	(*depHead) = dhead;//implicit return of the list of departments
	(*appHead) = ahead;//implicit return of the list of applicants

	return numOfDeps;
}

//returns 1 if department has a valid name with only letters, spaces, or underscores. Otherwise, it returns 0.
int isValidDepName (char* name) {
	int i;

	for (i = 0; i < strlen(name); i++) {
		if(!isalpha(name[i]) && name[i] != ' ' && name[i] != '_') {
			return 0;
		}
	}
	return 1;
}

//returns 1 if applicant has a valid name with only letters or spaces. Otherwise, it returns 0.
int isValidAppName (char* name) {
	int i;

	for (i = 0; i < strlen(name); i++) {
		if(!isalpha(name[i]) && name[i] != ' ') {
			return 0;
		}
	}
	return 1;
}
