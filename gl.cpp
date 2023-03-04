#include "nag.hpp"
using namespace std;

Graph::Graph(int v){
    this->g_size=v;
    adjacjency_matrix=new int*[g_size];
    for(int i=0;i<g_size;i++)
    {
        adjacjency_matrix[i]=new int[g_size];
        for(int j=0;j<g_size;j++)
        {
            adjacjency_matrix[i][j]=0;
        }
    }
}

Graph::~Graph(){

    for(int i=0;i<g_size;i++)
    {
        delete [] adjacjency_matrix[i];
    }
    delete [] adjacjency_matrix;
}

void Graph::add_edges(){
    //srand(time(NULL));
    int helper[g_size];

    for(int i=0;i<g_size;i++)  //wypelnia tablice rosnaco
    {
        helper[i]=i;
    }

    for (int i=g_size-1;i>0;i--) //miesza zawartosc tablicy
    {
        int j=rand() & i;
        int tmp=helper[i];
        helper[i]=helper[j];
        helper[j]=tmp;
    }

    for(int i=0;i<g_size;i++)  //tworzy wektor ze stopniami wierzchołkow
    {
        degree.push_back(0);
    }

    for (int i=1;i<g_size;i++)  //wypelnia macierz sasiedztwa w taki sposob ze mamy graf spojny oraz zapisuje na wektorze stopnie wierzcholkow
    {
        int j=rand() % 100+1;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
        adjacjency_matrix[helper[i-1]][helper[i]]=j;
        adjacjency_matrix[helper[i]][helper[i-1]]=j;
        degree[helper[i]]++;
        degree[helper[i-1]]++;
    }

    vector<int> degree_should;  //tworzy wektor przechowujący pozniej wylosowane stopnie wierzcholkow
    for(int i=0;i<g_size;i++)
    {
        degree_should.push_back(0);
    }

    std::random_device rd;                     //do losowania liczb, lepsze od rand()
    std::mt19937::result_type seed = rd() ^ (
    (std::mt19937::result_type)
    std::chrono::duration_cast<std::chrono::seconds>(
    std::chrono::system_clock::now().time_since_epoch()
    ).count() +
    (std::mt19937::result_type)
    std::chrono::duration_cast<std::chrono::microseconds>(
    std::chrono::high_resolution_clock::now().time_since_epoch()
    ).count() );

    std::mt19937 gen(seed);
    std::uniform_int_distribution<unsigned> distrib(1, 6);

    for(int i=0;i<g_size;i++) //tworzy wektor z losowanymi stopniami wierzcholkow
    {
        if(degree[i]>1)
        {
            int j=distrib(gen);
            degree_should[i]=j;
        }
        else
            degree_should[i]=1;//!!!!!!!!1
    }

    vector<int> vertices_to_connect;
    int counter=0;
    int counter_for_adding_eges=0;

    for(int i=0;i<g_size;i++)      //dodaje losowo krawedzie do stworzonego juz grafu spojnego(sciezki prostej)
    {
        if(degree[i]>1 && (degree_should[i]!=degree[i]))
        {
            while(degree_should[i]!=degree[i])
            {
                int weight= rand() % 100+1;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                if(counter>10)
                {
                    int decide=rand() % 4 +1;
                    if(degree_should[i]==1)
                    {
                        degree_should[i]=2;
                        counter=0;
                        continue;
                    }
                    if(decide==1)
                    {
                        for(int j=counter_for_adding_eges;j<i;j++)
                        {
                            if(degree[j]>1 && degree[j]<6 && adjacjency_matrix[i][j]==0)
                            {
                                adjacjency_matrix[i][j]=weight;
                                adjacjency_matrix[j][i]=weight;
                                degree[i]++;
                                degree[j]++;
                                degree_should[j]++;
                                counter=0;
                                break;
                            }
                        }
                        counter_for_adding_eges++;
                        continue;
                    }
                    else
                    {
                        degree_should[i]--;
                        counter=0;
                        continue;
                    }
                }
                std::uniform_int_distribution<unsigned> distrib(i, (g_size-1));
                int vertic=distrib(gen);
                counter++;
                if (vertic==i) continue;

                if(adjacjency_matrix[i][vertic]!=0) continue;
                if(degree_should[i]>2)
                {
                    if(degree[i]<degree_should[i] && degree[vertic]<degree_should[vertic])
                    {
                    adjacjency_matrix[i][vertic]=weight;
                    adjacjency_matrix[vertic][i]=weight;
                    degree[vertic]++;
                    degree[i]++;
                    counter=0;
                    }
                    else continue;
                }
                if(degree_should[i]==1)
                {
                     if(degree[vertic]<degree_should[vertic])
                     {
                        for(int j=0;j<g_size;j++)
                        {
                            if(adjacjency_matrix[i][j]!=0 && adjacjency_matrix[j][i]!=0)
                            {
                                adjacjency_matrix[i][j]=0;
                                adjacjency_matrix[j][i]=0;
                                degree[i]--;
                                degree[j]--;
                                vertices_to_connect.push_back(j);
                            }
                        }
                        int w=rand() % 100+1;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        int x=vertices_to_connect[1];
                        int y=vertices_to_connect[0];
                        vertices_to_connect.pop_back();
                        vertices_to_connect.pop_back();
                        adjacjency_matrix[x][y]=w;
                        adjacjency_matrix[y][x]=w;
                        degree[x]++;
                        degree[y]++;
                        adjacjency_matrix[i][vertic]=weight;
                        adjacjency_matrix[vertic][i]=weight;
                        degree[vertic]++;
                        degree[i]++;
                        counter=0;
                     }
                     else continue;
                }
            }
        }
        else continue;//!!!!!!!!!!!!!
    }

    /*for(int i=0;i<g_size;i++)
    {
        for(int j=0;j<g_size;j++)
        {
            if(adjacjency_matrix[i][j]!=0 && adjacjency_matrix[j][i]!=0) cout<<i<<"\t"<<j<<"\t"<<adjacjency_matrix[i][j]<<"\t"<<degree[i]<<endl;
        }
    }*/

    vector<int> builder;
    for(int i=0;i<g_size;i++) //tworzy liste sasiedztwa na podstawie macierzy
    {
        for(int j=0;j<g_size;j++)
        {
            if(adjacjency_matrix[i][j]!=0 && adjacjency_matrix[j][i]!=0) //cout<<i<<"\t"<<j<<"\t"<<adjacjency_matrix[i][j]<<"\t"<<degree[i]<<endl;
            {
                builder.push_back(j);
            }
        }
        adjacjency_list.push_back(builder);
        builder.clear();
    }
    return;
}

void Graph::remove_edges(){

    for(int i=0;i<g_size;i++)
    {
        for(int j=0;j<g_size;j++)
        {
            adjacjency_matrix[i][j]=0;
        }
    }
    degree.clear();
    adjacjency_list.clear();
    return;
}

void solution_generator(Graph &g1, vector<vector<int>> &paths, vector<int> &costs){

    int current_vertic=rand() % 100;
    set<int> visited;
    vector<int> current_path;
    int current_cost=0;
    visited.insert(current_vertic);
    current_path.push_back(current_vertic);
    int x=3;

    while(visited.size() != g1.g_size)
    {
        if(g1.adjacjency_list[current_vertic].size()==1){
             int next_vertic=g1.adjacjency_list[current_vertic][0];
              visited.insert(next_vertic);
              current_path.push_back(next_vertic);
              current_vertic=next_vertic;
             continue;
        }
        unsigned seed=0;
        shuffle(g1.adjacjency_list[current_vertic].begin(), g1.adjacjency_list[current_vertic].end(), default_random_engine(seed));
        int next_vertic=g1.adjacjency_list[current_vertic][0];
        //cout<<"Next vertic: "<<next_vertic<<endl;
        visited.insert(next_vertic);
        current_path.push_back(next_vertic);
        current_vertic=next_vertic;

    }
    paths.push_back(current_path);
    for(unsigned int i=0;i<current_path.size();i++)
    {
        if(i==current_path.size()-2)
        {
            current_cost+=g1.adjacjency_matrix[current_path[i]][current_path[i+1]];
            break;
        }
        if(g1.adjacjency_matrix[current_path[i]][current_path[i+1]] > g1.adjacjency_matrix[current_path[i+1]][current_path[i+2]])
        {
            current_cost+=((g1.adjacjency_matrix[current_path[i]][current_path[i+1]])*x);
        }
        else
        {
            current_cost+=g1.adjacjency_matrix[current_path[i]][current_path[i+1]];
        }
    }
    costs.push_back(current_cost);
    visited.clear();
    current_path.clear();
    return;
}

template <typename T>
vector<size_t> sort_indexes(const vector<T> &v) {

  vector<size_t> idx(v.size());
  iota(idx.begin(), idx.end(), 0);

  stable_sort(idx.begin(), idx.end(),
       [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

  return idx;
}

// TESTOWANIE: ILOSC PUSZCZANYCH MROWEK, %NAJLEPSZYCH ROZIWAZAN, %UZYCIA MACIERZY PRZEZ MROWKE, WARTOSC FEROMONU
void aco(Graph &g1, vector<vector<int>> &paths, vector<int> &costs, float feromone_matrix [][100], vector<int> &path_solution, int &cost_solution, vector<int> &costs_on_time, int aco_time){

    g1.adjacjency_list.clear();
     vector<int> pomocnik;
    for(int i=0;i<g1.g_size;i++) //tworzy liste sasiedztwa na podstawie macierzy
    {
        for(int j=0;j<g1.g_size;j++)
        {
            if(g1.adjacjency_matrix[i][j]!=0 && g1.adjacjency_matrix[j][i]!=0) //cout<<i<<"\t"<<j<<"\t"<<adjacjency_matrix[i][j]<<"\t"<<degree[i]<<endl;
            {
                pomocnik.push_back(j);
            }
        }
        g1.adjacjency_list.push_back(pomocnik);
        pomocnik.clear();
    }


    vector<vector<int>>adjacjency_list_cp;
    for(unsigned int i=0;i<g1.adjacjency_list.size();i++)
    {
        vector<int> helper = g1.adjacjency_list[i];
        adjacjency_list_cp.push_back(helper);
    }
    int x=12;
    vector<int> best_paths;

    int ant_uses_matrix=1;//% uzycia macierzy
    double alfa=1.3;
    double beta=0.4;
    float parowanie=0.05;
    int time=aco_time;

    int i=0;
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    while((std::chrono::duration_cast<std::chrono::seconds>(end - start).count() != time))//GLOWNA PETLA ALGORYTMU!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    {
        end = std::chrono::system_clock::now();
        if(i==0)
        {
            for(unsigned int j=0;j<100;j++)//ILOSC MROWEK //////////////100
            {
                solution_generator(g1, paths, costs);//paths zawiera 100 sciezek costs 100 kosztow
            }

            for (auto i: sort_indexes(costs)) {
                best_paths.push_back(i);  //zawiera indeksy od najlepszych sciezek do najgorszych
            }

            float dif=0.0;   //WARTOSC ODEJMOWANA OD 1 FEROMONU
            for(int i=0;i<10;i++) // ILOSC NAJLEPSZYCH ROZWIAZAN///////////////15
            {
                int index_nmbr=best_paths[i];
                for(unsigned int j=0;j<(paths[index_nmbr].size())-1;j++)
                {
                    feromone_matrix[paths[index_nmbr][j]][paths[index_nmbr][j+1]]+=(1.0-dif);//odkladanie feromonow
                }
                dif+=0.1;
            }
            path_solution=paths[best_paths[0]];
            cost_solution=costs[best_paths[0]];
           /* cout<<"najlepsze rozwiazanie losowe: "<<endl;
            cout<<"koszt: "<<cost_solution<<endl;
            cout<<"rozmiar sciezki: "<<path_solution.size()<<endl;
            cout<<endl<<"sciezka: "<<endl;
            for (auto it=path_solution.begin(); it!=path_solution.end(); it++)
            {
               cout<< " " << *it << " ";
            }
            cout<<endl;*/
            best_paths.clear();
            costs.clear();
            paths.clear();
            i++;
        }

        else{
                for(int j=0;j<100;j++)//ILOSC PUSZCZONYCH MROWEK
                {
                       set<int> visited;
                       vector<int> current_path;
                       int current_cost=0;
                       int current_vertic=rand() % 100;
                       visited.insert(current_vertic);
                       current_path.push_back(current_vertic);
                       int next_vertic;
                       int previous_vertic;///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                       while(visited.size() != g1.g_size){

                           int can_ant_use_matrix=rand() % 100;
                           if(can_ant_use_matrix<ant_uses_matrix){

                                vector<float>feromone_values;
                                if(g1.adjacjency_list[current_vertic].size()==1){
                                    next_vertic=adjacjency_list_cp[current_vertic][0];
                                    visited.insert(next_vertic);
                                    current_path.push_back(next_vertic);
                                    previous_vertic=current_vertic;//!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                    current_vertic=next_vertic;
                                    continue;
                                }
                                for(int x=0;x<g1.g_size;x++)
                                {
                                    if(feromone_matrix[current_vertic][x] != 0.0){
                                         feromone_values.push_back(feromone_matrix[current_vertic][x]);
                                    }
                                }
                                if(feromone_values.empty())
                                {
                                    next_vertic=adjacjency_list_cp[current_vertic][0]; /////CP CZY ORYGINAL!!!!
                                    visited.insert(next_vertic);
                                    current_path.push_back(next_vertic);
                                    previous_vertic=current_vertic;//!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                    current_vertic=next_vertic;
                                    continue;
                                }

                                if(feromone_values.size()==1)
                                {
                                    next_vertic=adjacjency_list_cp[current_vertic][0];
                                    visited.insert(next_vertic);
                                    current_path.push_back(next_vertic);
                                    previous_vertic=current_vertic;//!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                    current_vertic=next_vertic;
                                    continue;
                                }

                                vector<int> unvisited;
                                for(unsigned int x=0;x<adjacjency_list_cp[current_vertic].size();x++)
                                {
                                    const bool is_in = visited.find(adjacjency_list_cp[current_vertic][x]) != visited.end();
                                    if(is_in==false)
                                    {
                                        unvisited.push_back(adjacjency_list_cp[current_vertic][x]);
                                    }
                                }

                                if(unvisited.empty()==true)
                                {
                                    vector<double>probabilities;
                                    for(unsigned int x=0;x<feromone_values.size();x++)
                                    {
                                        double licznik=pow(feromone_values[x],alfa);
                                        double weight=g1.adjacjency_matrix[current_vertic][adjacjency_list_cp[current_vertic][x]];
                                        weight=1.0/weight;
                                        double licznik_multiply=pow(weight,beta);
                                        licznik=licznik*licznik_multiply;
                                        double mianownik=0.0;
                                        for(unsigned int y=0;y<feromone_values.size();y++)
                                        {
                                           double cos=pow(feromone_values[y],alfa);
                                           double ccc1=g1.adjacjency_matrix[current_vertic][adjacjency_list_cp[current_vertic][y]];
                                           ccc1=1.0/ccc1;
                                           double cos2=pow(ccc1,beta);
                                           cos=cos*cos2;
                                           mianownik+=cos;
                                        }
                                       double number=licznik/mianownik;
                                       probabilities.push_back(number);
                                    }
                                    double sum=accumulate(probabilities.begin(),probabilities.end(),0.0);
                                    sum=sum*100.0;
                                    int sum2=round(sum);
                                    int losowanie=rand() % sum2;
                                    int previous_number=0;
                                    int just_checking=0;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                    for(unsigned int z=0;z<probabilities.size();z++)
                                    {
                                        double prob=(probabilities[z])*100.0;
                                        int number=round(prob);
                                        if(z==probabilities.size()-1)
                                        {
                                            next_vertic=adjacjency_list_cp[current_vertic][z];
                                            just_checking=1;
                                            break;
                                        }
                                        if(losowanie<=(number+previous_number) && losowanie>=previous_number)
                                        {
                                            next_vertic=adjacjency_list_cp[current_vertic][z];
                                            if(next_vertic==previous_vertic){//!!!!!!!!!!!!!!!!!
                                                just_checking=11;//!!!!!!!!
                                            }
                                            if(just_checking==11)
                                            {
                                                int maximum=probabilities.size();//!!!!!!!!!!!!!!!!!!!!!!!!!
                                                int choicee=rand() % maximum;//!!!!!!!!!!!!!!!!!
                                                next_vertic=adjacjency_list_cp[current_vertic][choicee];//!!!!!!!!!!!
                                            }
                                            just_checking=1;
                                            break;
                                        }
                                        previous_number+=number;
                                    }
                                    if(just_checking==1)
                                    {
                                        visited.insert(next_vertic);
                                        current_path.push_back(next_vertic);
                                        previous_vertic=current_vertic;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                        current_vertic=next_vertic;
                                    }
                                    else{cout<<"MAMY PROBLEM"<<endl;return;}
                                    continue;
                                }

                                else if(unvisited.size()==1)
                                {
                                    next_vertic=unvisited[0];
                                    visited.insert(next_vertic);
                                    current_path.push_back(next_vertic);
                                    current_vertic=next_vertic;
                                    continue;
                                }

                                else
                                {
                                    vector<double>probabilities;
                                    for(auto it=unvisited.begin(); it!=unvisited.end(); it++)
                                    {
                                        double licznik=pow(feromone_matrix[current_vertic][*it],alfa);
                                        double weight=g1.adjacjency_matrix[current_vertic][*it];
                                        weight=1.0/weight;
                                        double licznik_multiply=pow(weight,beta);
                                        licznik=licznik*licznik_multiply;
                                        double mianownik=0.0;
                                        for(auto that=unvisited.begin(); that!=unvisited.end(); that++)
                                        {
                                           double cos=pow(feromone_matrix[current_vertic][*that],alfa);
                                           double ccc1=g1.adjacjency_matrix[current_vertic][*that];
                                           ccc1=1.0/ccc1;
                                           double cos2=pow(ccc1,beta);
                                           cos=cos*cos2;
                                           mianownik+=cos;
                                        }
                                       double number=licznik/mianownik;
                                       probabilities.push_back(number);
                                    }
                                    double sum=accumulate(probabilities.begin(),probabilities.end(),0.0);
                                    sum=sum*100.0;
                                    int sum2=round(sum);
                                    int losowanie=rand() % sum2;
                                    int previous_number=0;
                                    int just_checking=0;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                    for(unsigned int z=0;z<probabilities.size();z++)
                                    {
                                        double prob=(probabilities[z])*100.0;
                                        int number=round(prob);
                                        if(z==probabilities.size()-1)
                                        {
                                            next_vertic=adjacjency_list_cp[current_vertic][z];
                                            just_checking=1;
                                            break;
                                        }
                                        if(losowanie<=(number+previous_number) && losowanie>=previous_number)
                                        {
                                            next_vertic=unvisited[z];
                                            just_checking=1;
                                            break;
                                        }
                                        previous_number+=number;
                                    }
                                    if(just_checking==1)
                                    {
                                        visited.insert(next_vertic);
                                        current_path.push_back(next_vertic);
                                        previous_vertic=current_vertic;//!!!!!!!!!!!!!!!!!!!!!!!!
                                        current_vertic=next_vertic;
                                    }
                                    else{cout<<"MAMY PROBLEM"<<endl;return;}
                                    continue;
                                }
                           }
                           else{

                               if(g1.adjacjency_list[current_vertic].size()==1){
                                    next_vertic=g1.adjacjency_list[current_vertic][0];
                                    visited.insert(next_vertic);
                                    current_path.push_back(next_vertic);
                                    previous_vertic=current_vertic;
                                    current_vertic=next_vertic;
                                    continue;
                                }
                               /* int already_done=0;
                                for(unsigned int x=0;x<adjacjency_list_cp[current_vertic].size();x++)
                                {
                                    const bool is_in = visited.find(adjacjency_list_cp[current_vertic][x]) != visited.end();
                                    if(is_in==false)
                                    {
                                        next_vertic=adjacjency_list_cp[current_vertic][x];
                                        already_done=1;
                                        break;
                                    }
                                }*/
                                //if(already_done==0)
                                //{
                                   unsigned seed=0;
                                   shuffle(g1.adjacjency_list[current_vertic].begin(), g1.adjacjency_list[current_vertic].end(), default_random_engine(seed));
                                   next_vertic=g1.adjacjency_list[current_vertic][0];
                               // }
                                visited.insert(next_vertic);
                                current_path.push_back(next_vertic);
                                previous_vertic=current_vertic;
                                current_vertic=next_vertic;
                           }
                        }
                        paths.push_back(current_path);

                        for(unsigned int i=0;i<current_path.size();i++)
                        {
                             if(i==current_path.size()-2)
                             {
                                 current_cost+=g1.adjacjency_matrix[current_path[i]][current_path[i+1]];
                                 break;
                             }
                             if(g1.adjacjency_matrix[current_path[i]][current_path[i+1]] > g1.adjacjency_matrix[current_path[i+1]][current_path[i+2]])
                             {
                                 current_cost+=((g1.adjacjency_matrix[current_path[i]][current_path[i+1]])*x);
                             }
                             else
                             {
                                 current_cost+=g1.adjacjency_matrix[current_path[i]][current_path[i+1]];
                             }
                         }
                         costs.push_back(current_cost);
                }

                for (auto i: sort_indexes(costs)) {
                    best_paths.push_back(i);  //zawiera indeksy od najlepszych sciezek do najgorszych
                }

                float dif=0.0;   //WARTOSC ODEJMOWANA OD 1 FEROMONU
                for(int i=0;i<10;i++) // ILOSC NAJLEPSZYCH ROZWIAZAN
                {
                    int index_nmbr=best_paths[i];
                    for(unsigned int j=0;j<(paths[index_nmbr].size())-1;j++)
                    {
                       feromone_matrix[paths[index_nmbr][j]][paths[index_nmbr][j+1]]+=(1.0-dif);//odkladanie feromonow
                    }
                    dif+=0.1;
                }

                if(costs[best_paths[0]]<=cost_solution){
                path_solution=paths[best_paths[0]];
                cost_solution=costs[best_paths[0]];
                }
                best_paths.clear();
                costs.clear();
                paths.clear();
                i++;

        }
        ant_uses_matrix+=9;
        float parowanie_value=1.0-parowanie;
        for(unsigned int j=0;j<g1.g_size;j++) //parowanie
        {
            for(unsigned int x=0;x<g1.g_size;x++)
            {
                if(feromone_matrix[j][x]!=0)
                    feromone_matrix[j][x]=feromone_matrix[j][x]*parowanie_value;
            }
        }

      if(i%10==0){//wygladzanie macierzy!
            float srednia=0.0;
            for(int j=0;j<g1.g_size;j++)
            {
                for(int x=0;x<g1.g_size;x++)
                {
                    if(feromone_matrix[j][x]!=0.0)
                    {
                        srednia+=feromone_matrix[j][x];
                    }
                }
                for(int x=0;x<g1.g_size;x++)
                {
                    if(feromone_matrix[j][x]!=0.0)
                    {
                        if(feromone_matrix[j][x]<=srednia*0.2)
                        {
                            feromone_matrix[i][j]=feromone_matrix[i][j]*3.0;
                            continue;
                        }
                        else if(feromone_matrix[j][x]<=srednia*0.4 && feromone_matrix[j][x]>srednia*0.2)
                        {
                            feromone_matrix[i][j]=feromone_matrix[i][j]*2.5;
                            continue;
                        }
                        else if(feromone_matrix[j][x]<=srednia*0.6 && feromone_matrix[j][x]>srednia*0.4)
                        {
                            feromone_matrix[i][j]=feromone_matrix[i][j]*2.0;
                            continue;
                        }
                        else if(feromone_matrix[j][x]<=srednia*0.8 && feromone_matrix[j][x]>srednia*0.6)
                        {
                            feromone_matrix[i][j]=feromone_matrix[i][j]*1.5;
                            continue;
                        }
                        else if(feromone_matrix[j][x]<=srednia*1.0 && feromone_matrix[j][x]>srednia*0.8)
                        {
                            feromone_matrix[i][j]=feromone_matrix[i][j]*1.25;
                            continue;
                        }
                        else if(feromone_matrix[j][x]>srednia)
                        {
                            feromone_matrix[i][j]=feromone_matrix[i][j]*0.7;
                            continue;
                        }
                    }
                }
                srednia=0.0;
            }
        }

    }
        costs_on_time.push_back(cost_solution);
        cout<<"Wpycham "<<cost_solution<<endl;
        cout<<"zrobione!"<<endl;
        /*cout<<endl<<endl;
        cout<<"Najlepsze rozwiazanie: "<<endl;
        cout<<"koszt: "<<cost_solution<<endl;
        cout<<"rozmiar sciezki: "<<path_solution.size()<<endl;
        cout<<endl<<"sciezka: "<<endl;
        for (auto it=path_solution.begin(); it!=path_solution.end(); it++)
        {
            cout<< " " << *it << " ";
        }
        cout<<endl;*/

        for(int i=0; i<100;i++)
       {
           for(int j=0;j<100;j++)
           {
              feromone_matrix[i][j]=0.0;
           }
       }

 return;

}
