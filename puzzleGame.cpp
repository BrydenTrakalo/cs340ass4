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

//positionofnum[0] should hold the position of 0 ont he puzzle. [1] will hold position 1, 
int totDist(int* currentState){
    int* goalPosition = new int[9];
    goalPosition[0] = 4; goalPosition[1] = 0; goalPosition[2] = 1; goalPosition[3] = 2; goalPosition[4] = 5; goalPosition[5] = 8; goalPosition[6] = 7; goalPosition[7] = 6; goalPosition[8] = 3; 

    int positionOfNum[9];
    int totalMoves = 0;

    for (int i = 0; i < 9; i++){
       for (int j = 0; j < 9; j++){
            if(currentState[j] == i){
                positionOfNum[i] = j;
            }
        }
    }

    for (int i = 1; i < 9; i++){
        //cout << "checking on " << i << " which is " << positionOfNum[i] << " on the puzzle and is " << goalPosition[i] << " on the goal" << endl;
        while((positionOfNum[i]%3) != (goalPosition[i]%3)){ //Move the position to be on the same row as the goal position
            //cout << i << " are not in line " << positionOfNum[i] << " " << goalPosition[i] << endl;
            //cout << "comparison " << positionOfNum[i]%3 << " and " << goalPosition[i]%3 << endl;
            if(positionOfNum[i]%3 > goalPosition[i]%3){
                positionOfNum[i] -= 1;
                totalMoves++;
            }
            if(positionOfNum[i]%3 < goalPosition[i]%3){
                positionOfNum[i] += 1;
                totalMoves++;
            }
        }
        while(positionOfNum[i] != goalPosition[i]){ //Shift up and down the puzzle until they match
            //cout << i << " are not matching " << positionOfNum[i] << " " << goalPosition[i] << endl;
            if(positionOfNum[i] > goalPosition[i]){
                //cout << "too big" << endl;
                positionOfNum[i] -= 3;
                totalMoves++;
            }
            if(positionOfNum[i] < goalPosition[i]){
                //cout << "too small" << endl;
                positionOfNum[i] += 3;
                //cout << positionOfNum[i] << " is now " << 
                totalMoves++;
            }

        }
    }

    return totalMoves;
}