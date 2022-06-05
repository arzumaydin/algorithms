// Arzum Aydın 04.06.2022
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <queue>
#include <fstream>
#include <cmath>
#include <limits.h>

using namespace std;

class Graph
{
    int V; // Number of vertices
    vector<vector<int>> capacities; // nodes list
    vector<vector<float>> probabilities;
    public:
    Graph(int v) // constructor
    {
        this->V = v;
        init(capacities, probabilities);
    }
    void init(vector<vector<int>> &capacities, vector<vector<float>> &probabilities);
    void setMatrix(int row, int column, int weight);
    void setProbs(int i, int j, float value);
    vector<vector<float>> getProbs();
    int getV();
    vector<vector<int>> getCapacity();
    bool bfs(vector<vector<int>> &capacities, int source, int sink, int path[]);
};
 
void Graph::setMatrix(int row, int column, int weight) // create an adjacency matrix
{
    capacities[row][column] = weight;   
}

void Graph::setProbs(int i, int j, float value)
{
    probabilities[i][j] += value;
}

void Graph::init(vector<vector<int>> &capacities, vector<vector<float>> &probabilities)
{
    for (int i = 0; i < V; i++) {
        // Vector to store column elements
        vector<int> v1;
    
        for (int j = 0; j < V; j++) {
            v1.push_back(0);
        }
    
        // Pushing back above 1D vector
        // to create the 2D vector
        capacities.push_back(v1);
    }
    for (int i = 0; i < V; i++) {
        // Vector to store column elements
        vector<float> v1;
    
        for (int j = 0; j < V; j++) {
            v1.push_back(0.0);
        }
    
        // Pushing back above 1D vector
        // to create the 2D vector
        probabilities.push_back(v1);
    }
}

int Graph::getV()
{
    return V;
}

vector<vector<float>> Graph::getProbs()
{
    return probabilities;
}

vector<vector<int>> Graph::getCapacity()
{
    return capacities;
}

bool Graph::bfs(vector<vector<int>> &capacities,int source, int sink, int path[])
{
    vector<bool> is_visited(V, false); // holds information of whether the node is visited or not yet, initial values are false
    queue<int> q; // add node if the node are reachable in certain number of steps

    is_visited[source] = true; // set is_visited true for this index 
    q.push(source); // add index to queue since it is visited
    path[source] = -1;
    
    while(!q.empty()) // while queue is not empty
    {
        int index = q.front(); // set v to the item in front of the queue
        q.pop();

        for(int i = 0; i < V; i++) // traverse through vertices
        {
            if(is_visited[i] == false && capacities[index][i] > 0) // if index is not visited, mark as visited and dequeue
            {
                if(i == sink)
                {
                    path[i] = index;
                    return true; // if path from source to sink is found, return 1
                }
                q.push(i);
                is_visited[i] = true;
                path[i] = index; 
            }
        }
    }
    return false;
}

int ford_fulkerson(Graph graph, Graph residual, int source, int sink)
{
    int max_flow = 0, flow = 0; // flow holds current flow and max_flow is maximum
    int v = graph.getV();
    // set gcap and rcap equal to each graph's flow capacities
    vector<vector<int>> gcap = graph.getCapacity();
    vector<vector<int>> rcap = residual.getCapacity();

    int path[v];
    int i, j;
    for (i = 0; i < v; i++) // set residual graph's capacity to graph's capacity for each node
    {
        for (j = 0; j < v; j++)
        {
            rcap[i][j] = gcap[i][j];
        }
    }
    while (residual.bfs(rcap, source, sink, path)) // call bfs to find a path
    {
        flow = INT_MAX;
        for (j = sink; j != source; j = path[j]) // find the maximum possible flow along a single path
        {
            i = path[j];
            flow = min(flow, rcap[i][j]); // flow will be equal to the minimum of the edges along that path
        }
 
        for (j = sink; j != source; j = path[j]) // updating the residual graph according to the path taken before
        {
            i = path[j];
            rcap[i][j] -= flow;
            rcap[j][i] += flow;
        }
 
        // Add flow to overall flow
        max_flow += flow;
    }

    return max_flow;
}

int main(int argc, char *argv[])
{
    int vertices = 4;
    //get vertices as input
    Graph graph(vertices);
    Graph residual(vertices);
    float total = 1.0;

    ifstream fin;
    string line;
    fin.open(argv[1]);
    int size = 0;
    string a = argv[2];
    string b = argv[3];
    int source = stoi(a)-1;
    int sink = stoi(b)-1;

    int count = 0;
    if (!fin.is_open()) // error handling
    {
      cerr<<"Could not open file\n";
      exit(1);
    }
    else {
        fin >> size;
        for(int i = 0; i < size; i++) // while not end of file
        {
            for(int j = 0; j < size; j++)
            {
                int input;
                fin >> input;
                graph.setMatrix(i, j, input);
            }
        }
        getline(fin, line);

        for(int i = 0; i < size; i++) // while not end of file
        {
            for(int j = 0; j < size; j++)
            {
                float input;
                fin >> input;
                graph.setProbs(i, j, input);
                total *= (1-input);
                if(input != 0) count++;
            }
        }
    }

    fin.close();

    //int max_flow = ford_fulkerson(graph, residual, source, sink);

    vector<vector<float>> probs = graph.getProbs();
    float p = 0;
    float ptotal = 1.0;
    vector<int> flows;
    vector<float> result;
    Graph temp2 = graph;
    float allp = 1.0;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(probs[i][j] != 0)
            {
                p = (total / (1- probs[i][j]) * probs[i][j]);
                ptotal *= (1-probs[i][j]);
                allp *= probs[i][j];
                Graph temp1 = graph;
                temp1.setMatrix(i, j, 0); // set this node to 0 flow
                temp2.setMatrix(i, j, 0);
                flows.push_back(ford_fulkerson(temp1, residual, source, sink));
                result.push_back(p);
            }
        }
    }
    flows.insert(flows.begin(), ford_fulkerson(graph, residual, source, sink));
    result.insert(result.begin(), ptotal);
    flows.push_back(ford_fulkerson(temp2, residual, source, sink));
    result.push_back(allp);

    for(int i = 0; i < (int) result.size(); i++)
    {
        for(int j = i+1; j < (int) result.size(); j++)
        {
            if(flows[i] == flows[j])
            {
                result[i] += result[j];
                result.erase(result.begin()+j);
                flows.erase(flows.begin()+j);
            }
        }
    }

    cout.precision(5);
    float res = 0.0;
    for(int i = 0; i < (int) result.size(); i++)
    {
        cout << "Probability of occurrence: " << result[i] << ", Maximum Flow: " << flows[i] << endl;
        res += result[i] * flows[i];
    }
    cout << "Expected Maximum flow from node" << source + 1 << " to node "<< sink + 1 << ": " << res << endl;

    return EXIT_SUCCESS;
}