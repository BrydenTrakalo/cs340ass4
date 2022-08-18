#include "bfs.h"
#include "puzzleGame.h"
#include <iostream>

using namespace std;

    //Searches using a queue like fringe
list<int*> BreadthFirstSearch::search(int* currentState){
    closedSet.push_front(currentState); //Update the closedSet with the first state

    tuple<int*, list<int*>> currentElement; //Initalization
    tuple<int*, list<int*>> fringeElement;
    list<int*> path;

    list<int*>::iterator iter;
    list<int*>::iterator iter2;
    list<tuple<int*, list<int*>>>::iterator fIter;

    list<int*> followingStates;

    while(!isGoalState(currentState)){  // The main loop for running the search
        if(fringe.empty()){ // Either makes the first state, path pair, or gets one from the fringe
            currentElement = make_tuple(currentState, path);
        }else{
            currentElement = fringe.back();     //Queue funtionality
            fringe.pop_back();
            currentState = get<0>(currentElement);
        }

        if(isGoalState(currentState)){  //Checks if the goalState has been reached. Updates the path and return it
            get<1>(currentElement).push_front(currentState);
            return get<1>(currentElement);
        }

        if(closedSet.size() > 5000){    //Saftey
            cout << "Reached 5000 generated states. Terminating program" << endl;
            exit(0);
        }

        followingStates = getFollowingStates(currentState); //Collect all possible successor(following) states

        //Remove any following states that are already in the closed set or the fringe.
        if (!closedSet.empty()){
            for (iter = closedSet.begin(); iter != closedSet.end(); iter++){
                iter2 = followingStates.begin();
                for (int i = 0; i < followingStates.size(); i++){
                    if (isSameState(*iter, *iter2)){
                        delete *iter2;
                        followingStates.erase(iter2);
                        
                        if(i==followingStates.size()){
                            
                            break;
                        } 
                    }
                    iter2++;
                }
            }
        }
        if (!fringe.empty()){   //Removing if they are in the fringe
            for (fIter = fringe.begin(); fIter != fringe.end(); fIter++){
                iter2 = followingStates.begin();
                for (int i = 0; i < followingStates.size(); i++){
                    if (isSameState(get<0>(*fIter), *iter2)){;
                        delete *iter2;
                        followingStates.erase(iter2);
                        
                        if(i==followingStates.size()){
                            break;
                        } 
                    }
                    iter2++;
                }
            }
        }

        for (iter = followingStates.begin(); iter != followingStates.end(); iter++){    //For every following state - insert a new fringe element with the new state, and the path to get there
            path = get<1>(currentElement);
            path.push_front(currentState);

            fringeElement = make_tuple(*iter, path);
            fringe.push_front(fringeElement);   //Update the fringe

            closedSet.push_front(*iter);    //Update the closed set
        }


    }
    return get<1>(currentElement);
}