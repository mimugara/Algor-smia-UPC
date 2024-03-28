#include "metaheuristicIC.hh"

#include <string.h>
#define INPUT_PATH "./input-graphs/"

using namespace std;

int main(int argc, char * argv[]){

    if(argc == 2){

        // build graph
        string filename = argv[1];
        greedyIC g = greedyIC();
        double pr;

        // spreading probability | propagating ratio
        cout << "Introduce Spreading probability: ";
        cin >> pr; cout << endl;
        if(pr > 1 || pr < 0){
            cerr << "Invalid probability" << endl;
            return -1;
        }

        // read graph edges
        g.readEdgesFromFile2(pr, INPUT_PATH + filename);

        // read subset of nodes to propagate
        cout << "Introduce subset of nodes to propagate, ending in a -1" << endl;
        list<int> l;
        int x;
        int c = 0;
        while(cin >> x && x != -1){
            l.push_back(x);
            ++c;
        }
        // begin difusion 
        cout << g.testDifusionIC(l)<<endl;
    }
    else{
        cerr << "Invalid arguments." << endl;
        cerr << "USAGE:" << endl;
        cerr << "   $ ./difusioIC graph_NAME " << endl;
        return -1;
    }

    return 0;

}