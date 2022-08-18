// #include "bfs.h"
// #include "puzzleGame.h"
// #include <iostream>

// using namespace std;

// list<int*> BreadthFirstSearch::search(int* currentState, list<int*> path){
//     printGame(currentState);
//     cout << "Nodes generated: " << fringe.size() + closedSet.size() << "-------" << endl;

//     if (isGoalState(currentState)){
//         cout << "found end state!" << endl;
//         printGame(currentState);
//         path.push_front(currentState);
//         closedSet.push_front(currentState);
//         return path;
//     }
//     if((fringe.size() + closedSet.size()) > 10000){
//         cout << "reached 10,000 nodes generated, ending progrram" << endl;
//         exit(0);
//     }

//     // cout << "the current state is: " << endl;
//     // printGame(currentState);

//     list<int*> followingStates = getFollowingStates(currentState);

//     //cout << "the following states are " << endl;
//     list<int*>::iterator iter;
//     // for (iter = followingStates.begin(); iter != followingStates.end(); iter++){
//     //     printGame(*iter);
//     //     cout << "_____________________" << endl;
//     // }

//     //cout << "culling..." << endl;
//     //Remove any following states that are already in the closed set or the fringe.
//     list<int*>::iterator iter2;
//     //list<list<int*>::iterator> toErase;
//     if (!closedSet.empty()){
//         for (iter = closedSet.begin(); iter != closedSet.end(); iter++){
//             // cout << "closed set compare against--" << endl;
//             // printGame(*iter);
//             iter2 = followingStates.begin();
//             for (int i = 0; i < followingStates.size(); i++){
//                 // cout << "closed set check. " << endl;
//                 // printGame(*iter2);
//                 if (isSameState(*iter, *iter2)){
//                     // cout << "erasing becuae of clsoed set. should remove " << "****" << endl;
//                     // printGame(*iter2);
//                     // cout << "*****" << endl;
//                     delete *iter2;
//                     followingStates.erase(iter2);
                    
//                     if(i==followingStates.size()){
//                         //cout << "reached end of follwing states. breaking." << endl;
//                         break;
//                     } 
//                 }
//                 iter2++;
//             }
//         }
//     }
//     if (!fringe.empty()){
//         for (iter = fringe.begin(); iter != fringe.end(); iter++){
//             iter2 = followingStates.begin();
//             for (int i = 0; i < followingStates.size(); i++){
//                 // cout << "Fringe check. " << endl;
//                 // printGame(*iter2);
//                 if (isSameState(*iter, *iter2)){
//                     // cout << "erasing becuae of fringe. should remove " << "****" << endl;
//                     // printGame(*iter2);
//                     // cout << "*****" << endl;
//                     delete *iter2;
//                     followingStates.erase(iter2);
//                     //toErase.push_front(iter);
//                     if(i==followingStates.size()){
//                         //cout << "reached end of follwing states. breaking." << endl;
//                         break;
//                     } 
//                 }
//                 iter2++;
//             }
//         }
//         // while(!toErase.empty()){
//         //     followingStates.erase(toErase.front());
//         //     toErase.pop_front();
//         // }
//     }

//     // cout << "the following states AFTER culling is " << endl;
//     // for (iter = followingStates.begin(); iter != followingStates.end(); iter++){
//     //     printGame(*iter);
//     //     cout << "_____________________" << endl;
//     // }

//     // cout << "Fringe is " << endl;
//     // for (iter = fringe.begin(); iter != fringe.end(); iter++){
//     //     printGame(*iter);
//     //     cout << "********************" << endl;
//     // }

//     while(!followingStates.empty()){        //Add the following states to the fringe
//         fringe.push_front(followingStates.front());
//         followingStates.pop_front();
//     }

//     closedSet.push_front(currentState); //update closed set
//     path.push_front(currentState);  //update the path

//     //cout << endl << endl;


//     iter = fringe.begin();
//     int* nextState = fringe.back();
//     for (int i = 0; i < fringe.size();i++){
//         nextState = fringe.back();
//         //delete *iter;
//         fringe.pop_back();
//         path = search(nextState, path);
//         // cout << "returned, path end is " << endl;
//         // printGame(path.front());
//         // cout << "***" << endl;
//         if(isGoalState(path.front())){
//             cout << "returning for goal" << endl;
//             break;
//         }
//         iter++;
//     }
//     return path;
// }
