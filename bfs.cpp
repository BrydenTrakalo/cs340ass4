#include "bfs.h"
#include "puzzleGame.h"
#include <iostream>

using namespace std;

list<int*> BreadthFirstSearch::search(int* currentState){
    closedSet.push_front(currentState);
    tuple<int*, list<int*>> currentElement;
    tuple<int*, list<int*>> fringeElement;
    list<int*> path;

    list<int*>::iterator iter;
    list<int*>::iterator iter2;
    list<tuple<int*, list<int*>>>::iterator fIter;

    list<int*> followingStates;

    while(!isGoalState(currentState)){
        if(fringe.empty()){
            currentElement = make_tuple(currentState, path);
        }else{
            currentElement = fringe.back();
            fringe.pop_back();
            currentState = get<0>(currentElement);
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

        for (iter = followingStates.begin(); iter != followingStates.end(); iter++){
            path = get<1>(currentElement);
            path.push_front(currentState);

            fringeElement = make_tuple(*iter, path);
            fringe.push_front(fringeElement);

            closedSet.push_front(*iter);
        }


    }
    return get<1>(currentElement);
}