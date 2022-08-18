#include "puzzleGame.h"

#include <iostream>
#include <list>

using namespace std;

void printGame(int* array){
    for (int i = 0; i < 9; i++){
        if(i == 3 || i == 6){
            cout << endl;
        }
        if (array[i] == 0){
            cout << "_" << " ";
        }else{
            cout << array[i] << " ";
        }
    }
    cout << endl;
}

int* copyPuzzle(int* original){
    int* copyArray = new int[9];
    for (int i = 0; i < 9; i++){
        copyArray[i] = original[i];
    }
    return copyArray;
}


//I made a bunch of pointers to arrays. Delete them later or memory overflow
list<int*> getFollowingStates(int* array){
    list<int*> followingStates;

    int* copyArray;

    int emptyPosition;
    for (int i = 0; i < 9; i++){
       if (array[i] == 0){
        emptyPosition = i;
       }
    }

    //Move the hole up
    if (emptyPosition > 3){
        copyArray = copyPuzzle(array);
        copyArray[emptyPosition] = copyArray[emptyPosition-3];
        copyArray[emptyPosition-3] = 0;
        followingStates.push_front(copyArray);
    }

    //Move the hole down
    if (emptyPosition < 6){
        copyArray = copyPuzzle(array);
        copyArray[emptyPosition] = copyArray[emptyPosition+3];
        copyArray[emptyPosition+3] = 0;
        followingStates.push_front(copyArray);
    }

    //Move the hole left
    if ((emptyPosition > 0 && emptyPosition < 3) || (emptyPosition > 3 && emptyPosition < 6 || (emptyPosition > 6 && emptyPosition < 9))){
        copyArray = copyPuzzle(array);
        copyArray[emptyPosition] = copyArray[emptyPosition-1];
        copyArray[emptyPosition-1] = 0;
        followingStates.push_front(copyArray);
    }

    //Move hole right
    if ((emptyPosition >= 0 && emptyPosition < 2) || (emptyPosition >= 3 && emptyPosition < 5 || (emptyPosition >= 6 && emptyPosition < 8))){
        copyArray = copyPuzzle(array);
        copyArray[emptyPosition] = copyArray[emptyPosition+1];
        copyArray[emptyPosition+1] = 0;
        followingStates.push_front(copyArray);
    }

    return followingStates;
}


bool isSameState(int* state1, int* state2){
    bool isSame = true;
    for (int i = 0; i < 9; i++){
        if(state1[i] != state2[i]){
            isSame = false;
            break;
        }
    }
    return isSame;
}

bool isGoalState(int* currentState){
    int* goalState = new int[9];
    goalState[0] = 1; goalState[1] = 2; goalState[2] = 3; goalState[3] = 8; goalState[4] = 0; goalState[5] = 4; goalState[6] = 7; goalState[7] = 6; goalState[8] = 5; 
    bool isGoal = isSameState(currentState, goalState);
    delete goalState;
    return isGoal;
}

int numOfTilesOutOfPlace(int* currentState){
    int* goalState = new int[9];
    goalState[0] = 1; goalState[1] = 2; goalState[2] = 3; goalState[3] = 8; goalState[4] = 0; goalState[5] = 4; goalState[6] = 7; goalState[7] = 6; goalState[8] = 5; 
    
    int numOutOfPlace = 0;
    for (int i = 0; i < 9; i++){
        if(currentState[i] != goalState[i]){
            numOutOfPlace++;
        }
    }
    return numOutOfPlace;
}