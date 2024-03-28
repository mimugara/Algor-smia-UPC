#include "localSearchLT.hh"
#include <string.h>
#define INPUT_PATH "./input-graphs/"

using namespace std;

int askMode() {
    cout << "Select intial solution model:" << endl;
    cout << "Type <R> for select a random nodes solution"<<endl;
    cout << "Type <T> for select all nodes solution"<<endl;
    cout << "Type <G> for select a LocalSearch implementation solution"<<endl;
    string dmode;
    cin >> dmode;
    if(dmode == "R") return 0;
    else if(dmode=="T") return 1;
    else return 2;
}

int main(int argc, char * argv[]){
    // MODE 1: manual graph input  
    if(argc == 1){

        // graph order
        int n, m; double pr; 
        cout << "Number of nodes: " ;
        cin >> n;


        // spreading probability | propagating ratio
        cout << "Introduce Spreading ratio: ";
        cin >> pr; cout << endl;
        if(pr > 1 || pr < 0){
            cerr << "Invalid probability/ratio" << endl;
            return -1;
        }
        
        // build graph
        localSearchLT g = localSearchLT(n,pr);

        cout << "Number of edges: " ;
        cin >> m;
        cout << "Introduce edges in the folllowing format : i j " << endl;
        g.readEdges(m);

        // ask user for computing starting subset
        int mode = askMode();

        // run Local Search
        g.beginDifusionLT(mode);

    }

    // MODE 2: graph input from file
    else if (argc == 2){

        // build graph 
        string filename = argv[1];
        localSearchLT g = localSearchLT();
        double pr;

        // spreading probability | propagating ratio
        cout << "Introduce Spreading ratio: ";
        cin >> pr; cout << endl;
        if(pr > 1 || pr < 0){
            cerr << "Invalid ratio" << endl;
            return -1;
        }

        // read edges
        g.readEdgesFromFile2(pr, INPUT_PATH + filename);
        
        // ask user for computing starting subset      
        int mode = askMode();  

        // run Local Search
        g.beginDifusionLT(mode);   
    }
    
    // MODE 3: Test Graph propagation
    else if(argc == 3 && strcmp(argv[2], "test") == 0){

        // build graph
        string filename = argv[1];
        greedyLT g = greedyLT();
        double pr;

        // spreading probability | propagating ratio
        cout << "Introduce Spreading ratio: ";
        cin >> pr; cout << endl;
        if(pr > 1 || pr < 0){
            cerr << "Invalid ratio" << endl;
            return -1;
        }

        // read graph edges
        g.readEdgesFromFile2(pr, INPUT_PATH + filename);

        // read subset of nodes to propagate
        list<int> l;
        int x;
        int c = 0;
        while(cin >> x && x != -1){
            l.push_back(x);
            ++c;
        }
        // begin difusion 
        cout << g.testDifusionLT(l)+c<<endl;
    }
    
    else{
        cerr << "Invalid arguments." << endl;
        cerr << "USAGE:" << endl;
        cerr << "   manual input:           $ ./program_Greedy " << endl;
        cerr << "   input from file:        $ ./program_Greedy graph_NAME " << endl;
        cerr << "   test propagation:       $ ./program_Greedy graph_NAME test " << endl;
        return -1;
    }

    return 0;

}