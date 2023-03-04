#include <iostream>
#include <string>
#include<vector>
#include <time.h>
#include <random>
#include <chrono>
#include <ctime>
#include <set>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

class Graph
{
    int g_size;
    int **adjacjency_matrix;
    vector<vector<int>> adjacjency_list;
    vector<int> degree;

public:
    Graph(int v);
    ~Graph();
    void add_edges();
    void remove_edges();
    friend void solution_generator(Graph &, vector<vector<int>> &paths, vector<int> &costs);
    friend void aco(Graph &, vector<vector<int>> &paths, vector<int> &costs, float feromone_matrix[][100], vector<int> &path_solution, int &cost_solution, vector<int> &costs_on_time, int aco_time);
};

void solution_generator(Graph &g1, vector<vector<int>> &paths, vector<int> &costs);
void aco(Graph &g1, vector<vector<int>> &paths, vector<int> &costs, float feromone_matrix [][100], vector<int> &path_solution, int &cost_solution, vector<int> &costs_on_time, int aco_time);
