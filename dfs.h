#include <string>
#include <list>
#include <tuple>

using namespace std;

class DepthFirstSearch {
public:
    list<int*> closedSet;
    list<tuple<int*, list<int*>>> fringe;

    list<int*> search(int*);
};
