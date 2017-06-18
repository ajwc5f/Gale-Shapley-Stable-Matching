typedef struct prefQNode {//preference queue node
	char* name;
	struct prefQNode* next;
} prefQNode;

typedef struct prefQ {//list of prefernce queue nodes
	prefQNode *front;
	prefQNode *rear;
} prefQ;

typedef struct depNode {//department node
	int index;
	char* name;
	int vacancies;
	struct depNode* next;
	prefQ *prefList;
} depNode;

typedef struct appNode {//applicant node
	int index;
	char* name;
	char* assignedTo;
	struct appNode* next;
	prefQ *prefList;
} appNode;

typedef struct pairListNode {//essentially a vertex
	char* vertex;
	struct pairListNode* next;
} pairListNode;

typedef struct pairList {//list of vertexs
	pairListNode *head;
} pairList;

typedef struct pairGraph {//array of list of vertexs
	int V;
	pairList* array;
} pairGraph;

//appLists functions
appNode* insertApp (appNode* head, char* name, int index);
appNode* findAppByName (appNode* head, char* name);
appNode* findAppByIndex (appNode* head, int index);
void freeAppNodes (appNode* head);

//depLists functions
depNode* insertDep (depNode* head, char* name, int vacancies, int index);
depNode* findDepByName (depNode* head, char* name);
depNode* findDepByIndex (depNode* head, int index);
void freeDepNodes (depNode* head);

//prefQueue functions
prefQ* initQueue();
prefQNode* newNode (char* name);
void enque(prefQ *prefList, char* name);
char* deque (prefQ *prefList);
int isEmpty (prefQ *prefList);
void printQueue(prefQ *prefList);
void freeQueue(prefQ *prefList);

//parser functions
int getDepsAndApps (FILE* input, depNode **depHead, appNode **appHead);
int isValidDepName (char* name);
int isValidAppName (char* name);

//pairGraph functions
pairGraph* createPairGraph (int V, depNode *dhead);
pairListNode* newPairListNode (char* name);
void addPair (pairGraph* graph, char* dep, char* app, depNode *dhead);
void printPairGraph (pairGraph* graph);
void freePairGraph (pairGraph* graph);

//findPairs functions
int checkPref (prefQ *prefList, char* curr, char* poten);
pairGraph* GSfindPairs (pairGraph *graph, depNode *depHead, appNode *appHead);
depNode* findDep (depNode* depHead);

//printall functions
void printDepsAndApps (depNode *depHead, appNode *appHead);
