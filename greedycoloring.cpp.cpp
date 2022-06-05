#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

class Graph
{
    int V; // Number of vertices
    list<int> *neighbors; // neighhbors list
public:
    Graph() // constructor
    {
        V = 7; // number of regions
        neighbors = new list<int>[V];
    }
    void addEdge(int v, int w);
    void colorGraph();
};
 
void Graph::addEdge(int v, int w) // add both vertices to each other's neighbors list
{
    neighbors[v-1].push_back(w-1);
    neighbors[w-1].push_back(v-1);  
}

void Graph::colorGraph()
{
    int coloredArray[V]; // this array holds the colored graph vertices
 
    coloredArray[0]  = 0; // first color is assigned to first vertex
 
    // remaining V-1 vertices are colorless
    for (int u = 1; u < V; u++)
    {
        coloredArray[u] = -1;  // no color is assigned to current vertex
    }
 
    bool available[V]; // there will be 7 available colors that can be used
    for (int i = 0; i < V; i++)
    {
        available[i] = true; // all the colors are available to be used at first
    }
 
    for (int u = 1; u < V; u++) // traverse the remaining nodes
    {
        list<int>::iterator i;
        for (i = neighbors[u].begin(); i != neighbors[u].end(); i++) // traverse the neighbors of vertex
        {
            if (coloredArray[*i] != -1) // if the neighbor is colored
            {
                 available[coloredArray[*i]] = false; // mark that color as unavailable
            }
        }

 
        // Find the first available color among available colors
        int color;
        for (color = 0; color < V; color++) // increment color until there is an available color
        {
            if (available[color] == true) // when available color is found -> break
            {
                break;
            }
        }
 
        coloredArray[u] = color; // assign the color to vertex

        // revert the availability of color to before, unmark the color as unavailable
        for (i = neighbors[u].begin(); i != neighbors[u].end(); ++i) // traverse through the neighbors again
        {
            if (coloredArray[*i] != -1) // if the neighbor has color
            {
                available[coloredArray[*i]] = true; // set availability as true again
            }
        }
    }
 
    // print the coloredArray
    for (int u = 0; u < V; u++) // I increment u with 1 here because array's index begins with zero
    {
        cout << "Vertex " << u+1 << " --->  Color " << coloredArray[u] + 1<< endl;
    }

    // finally calculate distinct entries in the coloredArray to find how many colors is used
    int count = 1;
    int k, z = 0;
    for(k = 1; k < V; k++)
    {
        for(z = 0; z < k; z++)
        {
            if(coloredArray[k] == coloredArray[z])
            {
                break;
            }
        }
        if(k == z)
        {
            count++;
        }
    }

    cout << "Number of different colors: " << count << endl;
}
 
// Driver program to test above function
int main()
{
    clock_t t; // clock the algorithm
    Graph regions;

    // add edges
    regions.addEdge(1,2);
    regions.addEdge(1,4);
    regions.addEdge(1,5);
    regions.addEdge(2,3);
    regions.addEdge(2,4);
    regions.addEdge(3,4);
    regions.addEdge(3,6);
    regions.addEdge(3,7);
    regions.addEdge(4,5);
    regions.addEdge(4,6);
    regions.addEdge(5,6);
    regions.addEdge(5,7);

    t = clock();
    regions.colorGraph();
    t = clock() - t;
    cout << "Time in ms. " << ((float)t)/CLOCKS_PER_SEC * 1000.0 << endl;
    return 0;
}