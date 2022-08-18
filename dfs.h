#include <string>
#include <list>

using namespace std;

class DepthFirstSearch {
public:
    //int nodesGenerated; //should just be closedset.size + finrge.size 
    //list<int*> path;

    list<int*> closedSet;
    list<int*> fringe;

    list<int*> search(int*, list<int*>);
};
