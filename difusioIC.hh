#ifndef DIFUSIOIC_HH
#define DIFUSIOIC_HH
#include <vector> 
#include <iostream>
#include <queue>
#include <chrono>
#include <fstream>
#include <list>
#include <cmath>
#include <ctime>

using namespace std;

class difusioIC {

    protected:

        // graph dimension
        int n, m;
        // graph itself
        vector<vector<int>> g;
        // visited nodes during propagation
        vector <bool> spreadedNodes;
        // subset of nodes to spread
        queue <int> nodesToSpread;
        // double representing the spreading probability needed if modeling IC or the influence ratio used if modeling LT
        double p;
        // number of nodes already spreaded when modeling LT
        int spreaded;


    public:
        /***********************************************************************************************************
        DEFAULT AND PARAMETRIZED CONSTRUCTOR
        ***********************************************************************************************************/
        difusioIC(){}

        difusioIC(int n, double p){
            this -> p = p;
            this-> n = n;
            g.resize(n);
            cout << g.size() << endl;
            spreadedNodes.resize(n, false);
            spreaded = 0;
        }

        /***********************************************************************************************************
        GENERIC PUBLIC METHODS
        ***********************************************************************************************************/


        virtual void readEdges(int m){
            this-> m = m;

            for(int i = 0; i < m; i++){
                int a, b;
                cin >> a >> b;
                // add edge
                g[a].push_back(b);
                g[b].push_back(a);
            }
            this-> p = p;     
            this-> spreaded = 0;
        }

        virtual void readEdgesFromFile(double pr, string filename){
            m = 0;
            p = pr;  
            spreaded = 0;   

            // read graph from file
            ifstream file(filename);

            // read graph dimension
            file >> n;
            g.resize(n);
            spreadedNodes.resize(n, false);
            // read graph edges
            int a, b;
            while(file >> a >> b){
                // add edge
                a--;
                b--; 
                
                g[a].push_back(b);
                g[b].push_back(a);
                m++;
            }
            file.close();
        }

        virtual void readEdgesFromFile2(double pr, string filename){
            m = 0;
            p = pr;  
            spreaded = 0;   

            // read graph from file
            ifstream file(filename);

            // read graph dimension
            string s1, s2;
            file >> s1 >> s2 >> n >> m;   // a and b ignored
            cout << "n: " << n << endl << "m : " << m << endl;
            g.resize(n);
            spreadedNodes.resize(n, false);
            // read graph edges
            int a, b;
            while(file >> s1 >> a >> b){
                // add edge
                a--;
                b--; 
                
                g[a].push_back(b);
                g[b].push_back(a);
            }
            file.close();
        }

        double computeNodeInfluenceIC(int src, const vector<bool>& inMinimumSubset){
            // Priority queue for vertices that are being processed
            queue <int> Q;
            Q.push(src);

            // Vector for disntances
            vector <int> distances(this->n, __INT_MAX__);
            distances[src] = 0;

            // Vector for visited nodes
            vector <bool> visited(n, false);
            visited[src] = true;

            while(not Q.empty()){
                // next node
                int u = Q.front();
                Q.pop();
                // visit all neightbours
                for(int i = 0; i < g[u].size(); i++){
                    // next neightbour
                    int v = g[u][i];
                    // if not visited, mark as visited and enqueue
                    if(not visited[v] && not inMinimumSubset[v]){
                        distances[v] = distances[u] + 1;
                        visited[v] = true;
                        Q.push(v);
                    }
                }
            }
            // compute global influence as the sum of all influences
            double globalInfluence = 0.0;
            for(int i = 0; i < n; i++){
                globalInfluence += pow(this->p,distances[i]);
            }
            return globalInfluence;
        }

        // print graph
        void printGraph(){
            for(int i = 0; i<n; i++){
                cout << "node " << i << " :";
                for(int j = 0; j< g[i].size(); j++){
                    cout << " " <<  g[i][j];
                }
                cout << endl;
            }
        }

        // print nodes belong to the diffusion subset
        void printDifusionSubstet(){
            for(int i = 0; i < spreadedNodes.size(); i++){
                if(spreadedNodes[i]) cout << i << " ";
            }
            cout << endl;
        }

        void readStartingSubset(const list<int>& l){
            list<int>::const_iterator it=l.begin();
            while(it != l.end()){
                nodesToSpread.push(*it);
                spreadedNodes[*it] = true;
                it++;
            }
        }

        
        // read starting subset of nodes
        void enqueueStartingSet(){
            for(int i = 0; i < this->n; i++){
                if(spreadedNodes[i]) nodesToSpread.push(i);
            } 
        }

        int propagateIC_v1(){
            srand ( time(0) );
            int steps = 0;
            int numPropagatedNodes = nodesToSpread.size();
            auto begin = std::chrono::high_resolution_clock::now();

            while(not nodesToSpread.empty()){
                
                // get next element to propagate
                int tmp = nodesToSpread.front();
                steps++;
                // check neightbours
                for(int i = 0; i < g[tmp].size(); i++){
                        
                        if(not spreadedNodes[g[tmp][i]]){
                            // tries propagation
                            double shot_p = (rand()%100)/100.0;
                            if(shot_p > (1-this-> p)){
                                // propagates to new node
                                numPropagatedNodes++;
                                nodesToSpread.push(g[tmp][i]);
                                spreadedNodes[g[tmp][i]] = true;
                            }
                        }
                }
                // node tmp does not try propagation again
                nodesToSpread.pop();
            }

            // empty used data structures
            queue<int>empty;
            swap(this-> nodesToSpread, empty);
            spreadedNodes = vector<bool>(n, false);

            return numPropagatedNodes;
        }

        int propagateIC_v23(){
            srand ( time(0) );
            int steps = 0;
            int numPropagatedNodes = nodesToSpread.size();

            while(not nodesToSpread.empty()){
                
                // get next element to propagate
                int tmp = nodesToSpread.front();
                steps++;
                // check neightbours
                for(int i = 0; i < g[tmp].size(); i++){
                        
                        if(not spreadedNodes[g[tmp][i]]){
                            // tries propagation
                            double shot_p = (rand()%100)/100.0;
                            if(shot_p >= (1-this-> p)){
                                // propagates to new node
                                numPropagatedNodes++;
                                nodesToSpread.push(g[tmp][i]);
                                spreadedNodes[g[tmp][i]] = true;
                            }
                        }
                }
                // node tmp does not try propagation again
                nodesToSpread.pop();
            }
            return numPropagatedNodes;
        }

        int testDifusionIC(const list<int>& l){
            readStartingSubset(l);
            return propagateIC_v23();
        }

        //Comprova si el conjunt de nodes 'sol' és una solució vàlida
        //Si checkIC es true comprova pel model de solució per IC, en cas contrari comprova la solució
        //pel model de difusió de LT
        bool isSolutionIC(const vector<bool>& sol) {
            vector<bool> aux = spreadedNodes;
            spreadedNodes = sol;
            spreaded = 0;
            for(int i = 0; i<sol.size(); i++) {
                if(sol[i]) {
                    spreaded ++;
                    nodesToSpread.push(i);
                }
            }
            if(propagateIC_v23() == n) return true;
            else {
                spreadedNodes = aux;
                return false;
            }
        }
        
        vector<bool> getRandomNodesIC() {
            srand ( time(NULL) );
            vector<bool> result(n,false);
            bool findSolution = false;
            while(!findSolution) {
                int rand_num = rand() % n;
                if(!result[rand_num]) {
                    result[rand_num] = true;
                    findSolution = isSolutionIC(result);
                } 
            }
            spreadedNodes = result;
            return result; 
        }
        vector<bool> getMinDominantSet() {
            vector<bool> uncovered(n, true);
            queue<int> q;
            vector<int> scores(n,0);
            //Initialize scores in function of how nodes could influence one node
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < g[i].size(); j++) {
                    if (g[i][j] != i) {
                        scores[i]++;
                    }
                }
            }
            // Minimum dominant set
            bool mdsFind = false;
            while(!mdsFind) {
                int maxScore = -1;
                int maxNode = -1;
                
                for(int i = 0; i<n;++i) {
                    if (uncovered[i] && scores[i] > maxScore) {
                    maxScore = scores[i];
                    maxNode = i;
                    }
                }
                if(maxNode != -1) {
                    q.push(maxNode);
                    uncovered[maxNode] = false;
                    for ( int i = 0; i < g[maxNode].size(); i++)
                    {
                       int neighbor = g[maxNode][i];
                       if(neighbor != maxNode && uncovered[neighbor]) {
                            uncovered[neighbor] = false;
                            for(int j = 0; j < g[neighbor].size(); ++j) {
                                if(g[neighbor][j] != neighbor) {
                                    scores[g[neighbor][j]]--;
                                }
                            }
                       }
                       
                    }
                    
                }else {
                    mdsFind = true;
                }

            }
            vector<bool>result(n,false);
            while(!q.empty()) {
                result[q.front()] = true;
                q.pop();
            }
            spreadedNodes = result;
            return result;
        }
};
#endif