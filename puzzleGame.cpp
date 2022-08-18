#include "puzzleGame.h"

#include <iostream>
#include <list>

using namespace std;

    // Prints the puzzle game
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


    // Creates all of the successor(following) states of a state, returns them
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

    //Compares two states
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

    //Checks if currentState is goal state
bool isGoalState(int* currentState){
    int* goalState = new int[9];
    goalState[0] = 1; goalState[1] = 2; goalState[2] = 3; goalState[3] = 8; goalState[4] = 0; goalState[5] = 4; goalState[6] = 7; goalState[7] = 6; goalState[8] = 5; 
    bool isGoal = isSameState(currentState, goalState);
    delete goalState;
    return isGoal;
}

    // COunts the number of tiels out of place by comparing against the goal state
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

    //Finds the total distance each out of place peice needs to be moved
    //positionofnum[0] should hold the position of 0 on the puzzle. [1] will hold position 1...
int totDist(int* currentState){
    int* goalPosition = new int[9];
    goalPosition[0] = 4; goalPosition[1] = 0; goalPosition[2] = 1; goalPosition[3] = 2; goalPosition[4] = 5; goalPosition[5] = 8; goalPosition[6] = 7; goalPosition[7] = 6; goalPosition[8] = 3; 

    int positionOfNum[9];
    int totalMoves = 0;

    //Finds the positions of every number from 0-8
    for (int i = 0; i < 9; i++){
       for (int j = 0; j < 9; j++){
            if(currentState[j] == i){
                positionOfNum[i] = j;
            }
        }
    }

    // Moves each peice of the puzzle to the correct position. Counts the moves needed
    for (int i = 1; i < 9; i++){
        while((positionOfNum[i]%3) != (goalPosition[i]%3)){ //Move the position to be on the same row as the goal position
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
            if(positionOfNum[i] > goalPosition[i]){
                positionOfNum[i] -= 3;
                totalMoves++;
            }
            if(positionOfNum[i] < goalPosition[i]){
                positionOfNum[i] += 3;
                totalMoves++;
            }
        }
    }
    return totalMoves;
}

    //Counts the sequence score of a state.
int seq(int* currentState){
    int seqScore = 0;
    int positionOfNum[9];

    //Get positions of all peices
    for (int i = 0; i < 9; i++){
       for (int j = 0; j < 9; j++){
            if(currentState[j] == i){
                positionOfNum[i] = j;
            }
        }
    }

    //Check if each piece has a sequential following piece
    for (int i = 1; i < 8; i++){
        if(positionOfNum[i] < 2){   //Checking top row
            if(positionOfNum[i]+1 != positionOfNum[i+1]){
                seqScore += 2;
            }
        }
        if(positionOfNum[i] == 2 || positionOfNum[i] == 5){     //Checking right column
            if(positionOfNum[i]+3 != positionOfNum[i+1]){
                seqScore += 2;
            }
        }
        if(positionOfNum[i] == 7 || positionOfNum[i] == 8){   //Checking bottom row
            if(positionOfNum[i]-1 != positionOfNum[i+1]){
                seqScore += 2;
            }
        }
        if(positionOfNum[i] == 3 || positionOfNum[i] == 6){     //Checking left column
            if(positionOfNum[i]-3 != positionOfNum[i+1]){
                seqScore += 2;
            }
        }

        //Middle piece
        if(positionOfNum[i] == 4){
            seqScore += 1;
        }
    }

    //One last run to check for 8 to make sure its succesor is 1, an anonamly
    for (int i = 8; i < 9; i++){
        if(positionOfNum[i] < 2){   //Checking top row
            if(positionOfNum[i]+1 != positionOfNum[1]){
                seqScore += 2;
            }
        }
        if(positionOfNum[i] == 2 || positionOfNum[i] == 5){     //Checking right column
            if(positionOfNum[i]+3 != positionOfNum[1]){
                seqScore += 2;
            }
        }
        if(positionOfNum[i] == 7 || positionOfNum[i] == 8){   //Checking bottom row
            if(positionOfNum[i]-1 != positionOfNum[1]){
                seqScore += 2;
            }
        }
        if(positionOfNum[i] == 3 || positionOfNum[i] == 6){     //Checking left column
            if(positionOfNum[i]-3 != positionOfNum[1]){
                seqScore += 2;
            }
        }
        if(positionOfNum[i] == 4){
            seqScore += 1;
        }
    }
    return seqScore;
}