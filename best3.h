#include <string>
#include <list>
#include <tuple>

using namespace std;

class Best3Search {
public:
    list<int*> closedSet;
    list<tuple<int*, list<int*>, int>> fringe;

    list<int*> search(int*);
};
