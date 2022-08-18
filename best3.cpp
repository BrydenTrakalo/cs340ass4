#include "best3.h"
#include "puzzleGame.h"
#include <iostream>

using namespace std;

    // A search alorithm that uses depth + Huerisitc 'H' as a priority in the queue
    // The code is very similar to BFS. please check there for comments about the algorithm, and best1 for comments about the priority
    // The logic for H is in puzzleGame.cpp
list<int*> Best3Search::search(int* currentState){
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
        if(fringe.empty()){
            currentElement = make_tuple(currentState, path, depth);
        }else{
            bestPrority = 9999;
            bestFIter = fringe.begin();
            for (fIter = fringe.begin(); fIter != fringe.end(); fIter++){       //Select next state based off of priority
                if(get<2>(*fIter) < bestPrority){
                    bestPrority = get<2>(*fIter);
                    bestFIter = fIter;
                }
            }
            currentElement = *bestFIter;
            fringe.erase(bestFIter);
            currentState = get<0>(currentElement);
        }

        if(isGoalState(currentState)){
            get<1>(currentElement).push_front(currentState);
            return get<1>(currentElement);
        }

        followingStates = getFollowingStates(currentState);

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

            priority = depth + totDist(*iter) + 3*seq(*iter);       //Update priority

            fringeElement = make_tuple(*iter, path, priority);  
            fringe.push_front(fringeElement);

            closedSet.push_front(*iter);
        }
    }
    return get<1>(currentElement);
}