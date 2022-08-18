#include <iostream>
#include <list>

using namespace std;

void printGame(int* array);

int* copyPuzzle(int* original);


//I made a bunch of pointers to arrays. Delete them later or memory overflow
list<int*> getFollowingStates(int* array);


bool isSameState(int* state1, int* state2);

bool isGoalState(int* currentState);

int numOfTilesOutOfPlace(int* currentState);