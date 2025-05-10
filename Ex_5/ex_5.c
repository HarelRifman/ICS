/*****************
 * Created by Harel
 * id: 217398338
 * Assignment: ex_5
******************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ex_5.h"

void menu(){
    printf("Welcome!\n"
           "Please select the desired option:\n"
           "1. Join the company\n"
           "2. Open a new project\n"
           "3. Join an existing project\n"
           "4. See what projects are in work\n"
           "5. See which people are in what projects\n"
           "6. Work on existing project\n"
           "7. Leave the company\n"
           "8. Exit\n"
           "Enter your choice: ");
}

// returns if a string is empty by checking its first spo
bool isStringEmpty(char *str){
    if (str[0] == '\0') {
        return true;
    }
    return false;
}

void checkAllocation(void *ptr){
    if (ptr == NULL) {
        printf("Failed to allocate");
        exit(1);
    }
}

// Function to get a string of characters from user input
char* getChars() {
    int len = 0;
    char *str = (char*)malloc(sizeof(char));
    checkAllocation(str);

    char chr;
    scanf(" %c", &chr);

    while (chr != '\n') {
        str[len] = chr;
        len++;

        char *temp = (char*)realloc(str, sizeof(char) * (len + 1));
        checkAllocation(temp);
        str = temp;

        scanf("%c", &chr);
    }

    str[len] = '\0';
    return str;
}

// if the worker exist it will return his index else it will return -1
int isWorkerNameExists(Worker *workers[MAX_WORKERS], int workerCount, const char *name) {
    if (workers == NULL || workerCount <= 0 || workerCount >= MAX_WORKERS) {
        return -1; // Invalid input
    }

    for (int i = 0; i < workerCount; ++i) {
        if (workers[i] != NULL && workers[i]->name != NULL && strcmp(workers[i]->name, name) == 0) {
            return i;
        }
    }
    // Name not found
    return -1;
}

// if the project exist it will return his index else it will return -1
int isProjectNameExists(Project *projects[MAX_PROJECTS], int projectCount, char *name) {
    for (int i = 0; i < projectCount; i++) {
        if (strcmp(projects[i]->name, name) == 0) {
            return i; // Name exists, return the index
        }
    }
    //project not found
    return -1;
}

void displayAllWorkers(Worker *company[MAX_WORKERS], int workerCount){
    for (int i = 0; i < workerCount; i++) {
        printf("%d. %s\n", i + 1, company[i]->name);
    }
    clearInputBuffer();
}

// checks whether a feature exist
bool isFeatureExists(struct FeatureNode *head, const char *featureName) {
    while (head != NULL) {
        if (strcmp(head->feature, featureName) == 0) {
            return true;
        }
        head = head->next;
    }
    free(featureName);
    return false;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void displayAllProjects(Project *projects[MAX_PROJECTS], int projectCount){
    for (int i = 0; i < projectCount; i++) {
        printf("%d. %s (Workers: %d)\n", i + 1, projects[i]->name, projects[i]->workerCount);
    }
}

void joinCompany(Worker *company[MAX_WORKERS], int *workerCount) {
    if(*workerCount >= MAX_WORKERS){
        printf("The company is at full capacity.");
        return;
    }
    printf("Enter the name of the new worker: ");

    char *workerName = getChars();

    while (isStringEmpty(workerName)) {
        workerName = getChars();
    }

    int existingIndex = isWorkerNameExists(company, *workerCount, workerName);

    if (existingIndex != -1) {
        printf("A worker with this name already exists.\n"
               "There is not enough space in this company for both of us.\n");
    } else {
        company[*workerCount] = (Worker *)malloc(sizeof(Worker));
        checkAllocation(company[*workerCount]);

        company[*workerCount]->name = (char *)malloc(strlen(workerName) + 1);
        strcpy(company[*workerCount]->name , workerName);
        checkAllocation(company[*workerCount]->name);

        company[*workerCount]->projectCount = 0;
        company[*workerCount]->projects = (Project **)malloc(sizeof(Project *));
        checkAllocation(company[*workerCount]->projects);

        (*workerCount)++;
    }
    free(workerName);
}

// opens a new project
void openNewProject(Worker *company[MAX_WORKERS], int workerCount, Project *projects[MAX_PROJECTS], int *projectCount){
    if(*projectCount == MAX_PROJECTS){
        printf("Maximum number of projects reached.");
        return;
    }
    if (workerCount == 0) {
        printf("There are no workers in the company yet, please join the company first.\n");
        return;
    }

    printf("Who are you? Choose a number:\n");
    displayAllWorkers(company,workerCount);

    printf("Enter your choice: ");
    int choice;
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > workerCount) {
        printf("Invalid choice. Please try again.\n");
        clearInputBuffer(); // Ensure to clear buffer to remove any remaining input.
        return;
    }

    printf("Enter the name of the new project: ");
    char *name = getChars(); // Assume getChars dynamically allocates and returns a non-NULL string.
    while (isStringEmpty(name)) {
        name = getChars();
    }

    if (isProjectNameExists(projects,  *projectCount, name) != -1) {
        printf("A project with this name already exists.\nBetter be more creative\n");
        free(name); // Free the allocated memory to avoid memory leak.
        return;
    }

    Project *newProject = (Project*) malloc(sizeof(Project));
    checkAllocation(newProject);
    newProject->name = name;

    Worker **workers = (Worker**) malloc(sizeof(Worker*)*MAX_WORKERS);
    checkAllocation(workers);
    workers[0] = company[choice-1];

    newProject->workerCount =1;
    newProject->workers = workers;
    newProject->features = NULL;

    projects[*projectCount] = newProject;


    //update the worker
    Worker *worker = company[choice-1];
    worker->projects = (Project**) realloc(worker->projects ,sizeof(Project*) * (worker->projectCount + 1));
    worker->projects[worker->projectCount] = projects[*projectCount];
    (worker->projectCount)++;

    (*projectCount)++;
}

bool workerJoinsProject(Worker *company[MAX_WORKERS], int workerCount, Project *projects[MAX_PROJECTS], int projectCount){
    if (workerCount == 0){
        printf("There are no workers in the company yet, please join the company first.\n");
        return false;
    }
    if (projectCount == 0){
        printf("There are no projects in the company yet, please create one first.\n");
        return false;
    }

    printf("Select a worker to join a project:\n");
    displayAllWorkers(company,workerCount);

    printf("Enter the worker's number: ");
    int numOfWorker;
    scanf("%d", &numOfWorker);
    if (numOfWorker < 1) {
        printf("Invalid project selection.\n");
        clearInputBuffer(); // Ensure to clear buffer to remove any remaining input.
        return false;
    }
    if(numOfWorker > workerCount){
        printf("Project is full.\n");
        clearInputBuffer();
        return false;
    }

    printf("Select a project to join:\n");
    displayAllProjects(projects,projectCount);

    printf("Enter the project's number: ");
    clearInputBuffer();
    int numOfProject;
    scanf("%d", &numOfProject);

    if (numOfProject < 1 || numOfProject > projectCount) {
        printf("Invalid choice. Please try again.\n");
        clearInputBuffer(); // Ensure to clear buffer to remove any remaining input.
        return false;
    }

    if(projects[numOfProject-1]->workerCount >= MAX_WORKERS_ON_PROJECT ){
        printf("Invalid project selection.\n");
        return false;
    }

    if(isProjectNameExists(company[numOfWorker-1]->projects,company[numOfWorker-1]->projectCount,projects[numOfProject-1]->name) != -1){
        printf("This worker is already part of the project '%s'\n",projects[numOfProject-1]->name);
        return false;
    }

    //change the company worker
    company[numOfWorker-1]->projects[company[numOfWorker-1]->projectCount] = projects[numOfProject-1];
    company[numOfWorker-1]->projectCount += 1;

    //change the project
    projects[numOfProject-1]->workers[projects[projectCount-1]->workerCount] = company[numOfWorker-1];
    projects[numOfProject-1]->workerCount += 1;
    return true;
}

void displayProjectsAtWork(Project *projects[MAX_PROJECTS], int projectCount){
    if (projectCount == 0){
        printf("There are no projects to display.\n");
        return;
    }
    FeatureNode *temp;
    for (int i = 0; i < projectCount; i++) {
        printf("Project: %s\n  Workers in this project:\n",projects[i]->name);
        for (int j = 0; j < projects[i]->workerCount; ++j) {
            printf("    - %s\n",projects[i]->workers[j]->name);
        }
        printf("  Features of the project:\n");
        temp = projects[i]->features;
        if(temp == NULL){
            printf("    No features\n\n");
        }
        while(temp != NULL){
            printf("    - %s\n", temp->feature);
            temp = temp->next;
        }

    }

}

void displayAllWorkersProjects(Worker *company[MAX_WORKERS], int workerCount){
    if (workerCount == 0){
        printf("There are no workers to display.\n");
        return;
    }

    for (int i = 0; i < workerCount; i++) {
        printf("Worker: %s\n",company[i]->name);
        if(company[i]->projectCount == 0)
            printf("  Not involved in any projects.\n");
        else{
            printf("    Projects this worker is involved in:\n");
            for (int j = 0; j < company[i]->projectCount; ++j) {
                printf("    - %s\n", company[i]->projects[j]->name);
            }
        }
        printf("\n");
    }
}

void removeFeature(Project *project, int index) {
    FeatureNode *temp = project->features;

    // Check if the list is empty
    if (temp == NULL) {
        return;
    }

    // If removing the first node
    if (index == 0) {
        project->features = temp->next;
        free(temp); // Free the memory of the removed node
        return;
    }

    // Traverse to the node before the one to be removed
    for (int i = 0; temp != NULL && i < index - 1; i++) {
        temp = temp->next;
    }

    // Check if the given index is valid
    if (temp == NULL || temp->next == NULL) {
        return;
    }

    // Adjust pointers to skip the node to be removed
    FeatureNode *nextNode = temp->next->next;
    free(temp->next->feature);
    free(temp->next); // Free the memory of the removed node
    temp->next = nextNode;
}

void workOnProject(Worker *company[MAX_WORKERS], int workerCount, int *projectCount){
    if (workerCount == 0){
        printf("There are no workers in the company yet, please join the company first.\n");
        return;
    }
    if (*projectCount == 0){
        printf("There are no projects in the company yet, please create one first.\n");
        return;
    }
    printf("Select a worker:\n");
    displayAllWorkers(company,workerCount);
    int numOfWorker;
    printf("Enter the worker's number: ");
    scanf("%d", &numOfWorker);

    if(numOfWorker>workerCount || numOfWorker <= 0){
        printf("Invalid worker selection.\n");
        return;
    }

    if(company[numOfWorker-1]->projectCount == 0){
        printf("This worker is not involved in any projects.\n");
        return;
    }

    printf("Select a project:\n");
    for (int i = 0; i < company[numOfWorker-1]->projectCount; i++) {
        printf("%d. %s\n", i + 1, company[numOfWorker-1]->projects[i]->name);
    }

    printf("Enter the project number: ");
    clearInputBuffer();
    int numOfProject;
    scanf("%d", &numOfProject);

    if(numOfProject> company[numOfWorker-1]->projectCount || numOfProject <= 0){
        printf("Invalid project selection.\n");
        return;
    }

    Project *projectChosen = company[numOfWorker-1]->projects[numOfProject-1];

    char *opperation;
    printf("Do you want to add or remove a feature? (add/remove): ");
    opperation = getChars();

    if(strcmp(opperation, "remove") == 0){
        free(opperation);
        if(projectChosen->features == NULL){
            printf("There are no features to remove.\n");
            return;
        }

        printf("Select a feature to remove:\n");
        FeatureNode *temp = projectChosen->features;
        int i = 1;
        while(temp != NULL){
            printf("%d. %s\n",i,temp->feature);
            i++;
            temp = temp->next;
        }

        printf("Enter your choice: ");
        int placeToRemove;
        if (scanf("%d", &placeToRemove) != 1 || placeToRemove < 1 || placeToRemove > i) {
            printf("Invalid choice. Please try again.\n");
            clearInputBuffer(); // Ensure to clear buffer to remove any remaining input.
            return;
        }
        removeFeature(projectChosen,placeToRemove-1);
    }

    else if(strcmp(opperation, "add") == 0){
        free(opperation);
        char *newFeatureName = NULL;

        printf("Enter the new feature: ");
        newFeatureName = getChars();
        while (isStringEmpty(newFeatureName) == true){
            newFeatureName = getChars();
        }

        FeatureNode *temp = projectChosen->features;
        if (isFeatureExists(temp , newFeatureName) == true){
            printf("A feature with this name already exists.\n");
            free(newFeatureName);
            return;
        }

        FeatureNode *newFeatureNode = (FeatureNode*) malloc(sizeof(FeatureNode));
        newFeatureNode->feature = newFeatureName;
        newFeatureNode->next = NULL;
        if (temp != NULL) {
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newFeatureNode;
        }
        else {
            projectChosen->features = newFeatureNode;
        }
    }
    else{
        free(opperation);
        printf("Invalid choice.\n");
    }
}

void leaveCompany(Worker *company[MAX_WORKERS], int *workerCount, Project *projects[MAX_PROJECTS], int *projectCount){
    if (*workerCount == 0){
        printf("There are no workers in the company yet, please join the company first.\n");
        return;
    }
    printf("Select a worker to leave the company:\n");
    displayAllWorkers(company,*workerCount);
    printf("Enter the worker's number: ");
    int numOfWorker;
    scanf("%d", &numOfWorker);


    // Remove the worker from the projects
    for (int i = 0; i < company[numOfWorker - 1]->projectCount; i++) {
        int projectLocation = isProjectNameExists(projects, *projectCount, company[numOfWorker - 1]->projects[i]->name);
        if (projectLocation != -1) {

            if (projects[projectLocation]->workerCount == 1) {
                // If there's only one worker in the project, remove the entire project
                freeProject(projects[projectLocation]);
                for (int j = projectLocation; j < *projectCount - 1; j++) {
                    projects[j] = projects[j + 1];
                }
                (*projectCount)--;
            } else {
                // If there are multiple workers, remove only the specified worker
                int workerLocationInTheProject = isWorkerNameExists(projects[projectLocation]->workers, projects[projectLocation]->workerCount, company[numOfWorker - 1]->name);
                if (workerLocationInTheProject != -1) {
                    for (int j = workerLocationInTheProject; j < projects[projectLocation]->workerCount - 1; j++) {
                        projects[projectLocation]->workers[j] = projects[projectLocation]->workers[j + 1];
                    }
                    projects[projectLocation]->workerCount--;
                }
            }
        }
    }

    //remove the worker from the company
    free(company[numOfWorker-1]->name);
    free(company[numOfWorker-1]->projects);
    free(company[numOfWorker-1]);
    for(int i = numOfWorker -1; i < *workerCount-1; i++){
        company[i] = company[i+1];
    }

    (*workerCount)--;
}
void freeFeatures(FeatureNode *head){
    FeatureNode *temp1 = head;
    FeatureNode *temp2 = NULL;
    while (temp1 != NULL){
        temp2 = temp1->next;
        free(temp1->feature);
        free(temp1);
        temp1 = temp2;
    }
}

void freeProject(Project *project){
    freeFeatures(project->features);
    free(project->name);
    free(project->workers);
    free(project);
}

void freeAllAllocations(Worker *workers[MAX_WORKERS], int workerCount, Project *projects[MAX_PROJECTS], int projectCount){
    for(int i = 0; i < projectCount; i++){
        freeProject(projects[i]);
    }

    for (int i = 0; i < workerCount; ++i) {
        free(workers[i]->name);
        free(workers[i]->projects);
        free(workers[i]);
    }
}

int main(){
    int workerCount = 0;
    int option = 0;
    Worker *company[MAX_WORKERS];
    Project *projects[MAX_PROJECTS];
    int projectCount = 0;

    while(option != 8){

        menu();
        scanf("%d",&option);

        if(option == OP_1){
            joinCompany(company, &workerCount);
        }
        else if(option == OP_2){
            openNewProject(company, workerCount, projects, &projectCount);
        }
        else if(option == OP_3){
            workerJoinsProject(company,workerCount,projects,projectCount);
        }
        else if(option == OP_4){
            displayProjectsAtWork(projects,projectCount);
        }
        else if(option == OP_5){
            displayAllWorkersProjects(company,workerCount);
        }
        else if(option == OP_6){
            workOnProject(company,workerCount, &projectCount);
        }
        else if(option == OP_7){
            leaveCompany(company,&workerCount,projects,&projectCount);
        }
        else if(option == OP_8){
            freeAllAllocations(company,workerCount,projects,projectCount);
            printf("Exiting...");
        }
        else{
            printf("Invalid choice. Please try again.\n");
            clearInputBuffer();
        }
    }

    return  0;
}
