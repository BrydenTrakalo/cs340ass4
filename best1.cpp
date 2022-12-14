#include "best1.h"
#include "puzzleGame.h"
#include <iostream>

using namespace std;

    // A search alorithm that uses depth + number of tiles out of place as a priority in the queue
    // The code is very similar to BFS, only priority related code will be commented. please check there for comments about the algorithm
    // The logic for tiles out of place is in puzzleGame.cpp
list<int*> Best1Search::search(int* currentState){
    int depth = 0;
    int priority;
    int bestPrority;
    closedSet.push_front(currentState);
    tuple<int*, list<int*>, int> currentElement;
    tuple<int*, list<int*>, int> fringeElement;
    list<int*> path;

    list<int*>::iterator iter;
    list<int*>::iterator iter2;
    list<tuple<int*, list<int*>, int>>::iterator fIter;
    list<tuple<int*, list<int*>, int>>::iterator bestFIter;

    list<int*> followingStates;

    while(!isGoalState(currentState)){
        if(fringe.empty()){ //Makes the first state, path, priority element, or picks the lowest priority element off of the fringe
            currentElement = make_tuple(currentState, path, depth);
        }else{
            bestPrority = 9999;
            bestFIter = fringe.begin();
            for (fIter = fringe.begin(); fIter != fringe.end(); fIter++){
                if(get<2>(*fIter) < bestPrority){
                    bestPrority = get<2>(*fIter);
                    bestFIter = fIter;
                }
            }
            currentElement = *bestFIter;
            fringe.erase(bestFIter);
            currentState = get<0>(currentElement);  //Sets the current state as that of the lowest priority in the fringe. Removes the element off the fringe
        }


        if(isGoalState(currentState)){
            get<1>(currentElement).push_front(currentState);
            return get<1>(currentElement);
        }


        followingStates = getFollowingStates(currentState);

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
        if (!fringe.empty()){
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

        depth++;

        for (iter = followingStates.begin(); iter != followingStates.end(); iter++){
            path = get<1>(currentElement);
            path.push_front(currentState);

            priority = depth + numOfTilesOutOfPlace(*iter);     //Update the priority of the following state with depth + numOfTilesOutOfPlace

            fringeElement = make_tuple(*iter, path, priority);
            fringe.push_front(fringeElement);

            closedSet.push_front(*iter);
        }


    }
    return get<1>(currentElement);
}