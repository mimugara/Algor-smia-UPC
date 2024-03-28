#ifndef METAHEURISTICLT_HH
#define METAHEURISTICLT_HH

#include "difusioLT.hh"
#include "greedyLT.hh"
#include <cmath>
#include <list>
#include <queue>
#include <fstream>




class metaheuristicLT: public difusioLT {

    public:

        // constructor and parametrized constructor ------------------------
        metaheuristicLT(){}

        metaheuristicLT(int n, double r){
            this -> n = n;
            this -> p = r;
            spreaded = 0;
            g.resize(n);
            spreadedNodes.resize(n, false);
        }

        // public methods --------------------------------------------------

        void simulated_annealingLT(int mode, int temp, double varEn) {
            int r;
            vector<bool> sol;
            srand ( time(0) );
            ofstream file;
            file.open("output_SA_LT");   
            auto begin = std::chrono::high_resolution_clock::now();
            if(mode == 0) sol = getRandomNodesLT();
            else if(mode == 1) sol = getMinDominantSet();
            else {
                greedyLT gred = greedyLT(g,p);
                gred.beginDifusion_startingSubset_LT(sol);
            }
            file << "----------SOLUCIÓ INICIAL:----------" << endl;
            int solSize = 0;
            for(int i = 0; i < sol.size();++i){
                if (sol[i]){
                    file << i << ' ';
                    solSize++;
                }
            }
            file << endl << "Size: " << solSize << endl;
            file << endl;
            
            solSize = 0;
            vector<int> espai_solucions;
            while(temp > 0) {
                for (int j = 0; j < 20; ++j) {   
                    espai_solucions.clear();
                    for(int i = 0; i < sol.size(); ++i) {
                        if (sol[i]) {
                            sol[i] = false;
                            if(isSolutionLT(sol))  espai_solucions.push_back(i);                     
                            sol[i] = true;
                        }
                        else espai_solucions.push_back(i);
                    }             
                    r = rand()%espai_solucions.size();
                    //forma part de S 
                    if (sol[espai_solucions[r]]) sol[espai_solucions[r]] = false;  
                    //no forma part de S (veiem si el podem afegir)
                    else {
                        double prob = pow(10.0, -varEn/temp);
                        int al = rand()%100;
                        if (al <= prob*100) sol[r] = true;
                    }
                }
                --temp;
            }           
            auto end = std::chrono::high_resolution_clock::now();
            file << "----------SOLUCIÓ FINAL:----------" << endl;
            for(int i = 0; i < sol.size();++i){
                if (sol[i]){
                    file << i << ' ';
                    solSize++;
                }
            }
            file << endl << "Size: " << solSize << endl;
            file << endl<< "----------------------------------" << endl;
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            file << "Difusion completed in " << elapsed.count() * 1e-9 << "s." << endl;
            file.close();
        }

};
#endif