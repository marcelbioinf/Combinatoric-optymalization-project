#include "nag.hpp"
using namespace std;

int main()
{
    srand(time(NULL));
    Graph G1(100);
    vector<int> costs_on_time;

    for(int graphs_number=0;graphs_number<10;graphs_number++)
    {
       G1.add_edges();
       vector<int> costs;
       vector<vector<int>> paths;
       float feromone_matrix[100][100]; //dynamiczna implementacja nie jest potrzebna, ilosc wierzcholkow sie nie zmienia ///FLOAT CZY DOUBLE
       for(int i=0; i<100;i++)
       {
           for(int j=0;j<100;j++)
           {
              feromone_matrix[i][j]=0.0;
           }
       }
       vector<int> path_solution;
       int cost_solution;
       int time_of_aco=15;
       cout<<"Numer grafu: "<<graphs_number<<endl;

       aco(G1, paths, costs, feromone_matrix, path_solution, cost_solution, costs_on_time, time_of_aco);
       paths.clear();
       costs.clear();
       path_solution.clear();
       cost_solution=0;

       G1.remove_edges();
    }

        int sredni_koszt=accumulate(costs_on_time.begin(),costs_on_time.end(),0);
        sredni_koszt=sredni_koszt/10;
        cout<<"Sredni koszt dla czasu: "<<sredni_koszt<<endl;


    return 0;
}

