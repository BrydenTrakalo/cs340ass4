#include "puzzleGame.h"
#include "dfs.h"
#include "bfs.h"
#include "best1.h"
#include "best2.h"
#include "best3.h"
#include <iostream>

using namespace std;

    //Driver code for the searching algorithms
int main(){
    cout << "What intial position would oyu like to use? Enter the numbers 0-8 in any order with a space between each. 0 will be the empty space. Numbers will be placed left-right, top-down starting at the top left of the puzzle." << endl;
    cout << "Input 'a' to use a default puzzle with a 1 move solution" << endl;
    cout << "Input 'b' to use a default puzzle with a 4 move solution" << endl;
    char input;
    int* puzzle;
    puzzle = new int[9];

    //Build the puzzle
    for (int i = 0; i < 9; i++){
        cin >> input;
        switch (input){
        case 'a':
            puzzle[0] = 1; puzzle[1] = 0; puzzle[2] = 3; puzzle[3] = 8; puzzle[4] = 2; puzzle[5] = 4; puzzle[6] = 7; puzzle[7] = 6; puzzle[8] = 5; 
            break;
        case 'b':
            puzzle[0] = 1; puzzle[1] = 3; puzzle[2] = 4; puzzle[3] = 8; puzzle[4] = 0; puzzle[5] = 2; puzzle[6] = 7; puzzle[7] = 6; puzzle[8] = 5; 
            break;
        default:
            puzzle[i] = input;
        }
        if (input > 9){
            break;
        }

    }

    cout << "The intial state is: which has " << totDist(puzzle) << " min moves to solve, witch a Sequence score of " << seq(puzzle) << endl;
    printGame(puzzle);

    cout << "Now please input a search method. \n'd' - depth first search. \n'b' - breadth first search. \n'x' - Best first with # of tiles out of place. \n'y' - best first with min # of moves to goal state. \n'z' best frist with heuristic H." << endl;
    cin >> input;

    int nodesGenerated;
    list<int*> soluPath;
    DepthFirstSearch dfs;
    BreadthFirstSearch bfs;
    Best1Search best1;
    Best2Search best2;
    Best3Search best3;
    switch (input){
        case 'd':
            soluPath = dfs.search(puzzle);
            nodesGenerated = dfs.closedSet.size();
            break;
        case 'b':
            soluPath = bfs.search(puzzle);
            nodesGenerated = bfs.closedSet.size();
            break;
        case 'x':
            soluPath = best1.search(puzzle);
            nodesGenerated = best1.closedSet.size();
            break;
        case 'y':
            soluPath = best2.search(puzzle);
            nodesGenerated = best2.closedSet.size();
            break;
        case 'z':
            soluPath = best3.search(puzzle);
            nodesGenerated = best3.closedSet.size();
            break;
        default:
            cout << "Hey!";
            break;
    }

    cout << "The solution path is: " << endl;
    list<int*>::iterator iter;
    int loopAmount = soluPath.size();
    for (int i = 0; i < loopAmount; i++){
        printGame(soluPath.back());
        soluPath.pop_back();
        if(i != loopAmount-1){
            cout << "then..." << endl;
        }
    }
    cout << "the amount of nodes generated is: " << nodesGenerated << endl;

    return 0;
}