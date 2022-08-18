#include <iostream>
#include <list>

using namespace std;

void printGame(int* array);

int* copyPuzzle(int* original);

list<int*> getFollowingStates(int* array);

bool isSameState(int* state1, int* state2);

bool isGoalState(int* currentState);

int numOfTilesOutOfPlace(int* currentState);

int totDist(int* currentState);

int seq(int* currentState);