#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORKERS 50
#define MAX_PROJECTS 100
#define MAX_NAME_LEN 81
#define MAX_PROJ_NAME_NAME_LEN 81
#define MAX_WORKERS_ON_PROJECT 4

#define OP_1 1
#define OP_2 2
#define OP_2 2
#define OP_3 3
#define OP_4 4
#define OP_5 5
#define OP_6 6
#define OP_7 7
#define OP_8 8
typedef enum {false,true} bool;
// Forward declarations
typedef struct Worker Worker;
typedef struct FeatureNode FeatureNode;
typedef struct Project Project;

struct Worker
{
    char *name;
    Project **projects;
    int projectCount;
};

struct FeatureNode
{
    char *feature;
    struct FeatureNode *next;
};

struct Project
{
    char *name;
    Worker **workers;
    int workerCount;
    FeatureNode *features;
};

void menu(void);
void clearInputBuffer(void);
char *getChars(void);
int isWorkerNameExists(Worker *workers[MAX_WORKERS], int workerCount, const char *name);
int isProjectNameExists(Project *projects[MAX_PROJECTS], int projectCount, char *name);
bool isFeatureExists(FeatureNode *head, const char *featureName);
void joinCompany(Worker *workers[MAX_WORKERS], int *workerCount);
void openNewProject(Worker *workers[MAX_WORKERS], int workerCount, Project *projects[MAX_PROJECTS], int *projectCount);
bool workerJoinsProject(Worker *company[MAX_WORKERS], int workerCount, Project *projects[MAX_PROJECTS], int projectCount);
void displayAllWorkersProjects(Worker *workers[MAX_WORKERS], int workerCount);
void displayProjectsAtWork(Project *projects[MAX_PROJECTS], int projectCount);
void displayAllProjects(Project *projects[MAX_PROJECTS], int projectCount);
void displayAllWorkers(Worker *workers[MAX_WORKERS], int workerCount);
void workOnProject(Worker *workers[MAX_WORKERS], int workerCount, int *projectCount);
void leaveCompany(Worker *workers[MAX_WORKERS], int *workerCount, Project *projects[MAX_PROJECTS], int *projectCount);
void freeProject(Project *project);
void freeFeatures(FeatureNode *head);
void freeAllAllocations(Worker *workers[MAX_WORKERS], int workerCount, Project *projects[MAX_PROJECTS], int projectCount);
