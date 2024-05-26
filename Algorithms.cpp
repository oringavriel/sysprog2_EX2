#include "Algorithms.hpp"
#include "Graph.hpp"
#include <iostream>
#include <queue>
#include <algorithm>
#include <limits.h>
#include <stack>
using namespace std;
using namespace ariel;


bool Algorithms:: isConnected(Graph gr) { // check if the graph is connected using BFS algorithm
    size_t numV= (size_t)gr.getVerNum();
    vector<bool> visit(numV,false); //vector to save where we visit
    queue<int> q; 
    q.push(0);
    visit[0] = true; // start the check from 0 vertex
    while (!q.empty())
    {
        size_t v = (size_t)q.front();
        q.pop();
        for (size_t i = 0; i < numV; i++)
        {
            if (gr.getGraph()[v][i] && visit[i]==false) // check neighbors and mark them as visited
            {
                q.push(i);
                visit[i] = true;
            }
        }
    }
    for (size_t i = 0; i < numV; i++) // if not all vertices are visited then the graph is not connected
    {
        if (!visit[i])
        {
            return false;
        }
    }
    return true;
}





string Algorithms:: negativeCycle(Graph gr){ // find if there's a negative cycle by Bellman-Ford algorithm
    if(gr.getIsWeighed()== false) { // if the graph is not weighed then it doesn't contain a negative cycle
        return "The graph doesn't contain a negative cycle";
    }
    else {
        size_t numV = (size_t)gr.getVerNum();
        vector<int> dist(numV,INT_MAX); // vector to save distances and do "relax" process by the algorithm
        dist[0] = 0;
        for (size_t i = 0; i < numV -1; i++) // by looping v-1 times we get the shortest distances
        {
            for (size_t j = 0; j< numV ; j++)
            {
                for (size_t t = 0; t < numV; t++)
                {
                    if (gr.getGraph()[j][t] != 0 && dist[j] != INT_MAX && dist[j] + gr.getGraph()[j][t] < dist[t]) // relax
                    {
                        dist[t] = gr.getGraph()[j][t] + dist[j];
                    }
                }
            }
        }
        for (size_t j = 0; j< numV ; j++)
            {
                for (size_t t = 0; t < numV; t++)
                {
                    if (gr.getGraph()[j][t] != 0 && dist[j] != INT_MAX && dist[j] + gr.getGraph()[j][t] < dist[t]) // if we can do relax one more time (the v'th time) then we have a negative cycle
                    {
                        return "The graph contains a negative cycle";
                    }
                }
            }
        return "The graph doesn't contain a negative cycle";
    }
}





string Algorithms:: isBipartite(Graph gr){ // check if the graph is bipartite or not. if it is- the function return the partition 
//this function is done by cy coloring the vertices in 2 different colors using BFS
    size_t numV= (size_t)gr.getVerNum();
    vector<int> color(numV,-1); // vector to save each vertex color
    color[0]=0;
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        size_t v = (size_t)q.front();
        q.pop();
        for (size_t i = 0; i < numV; i++)
        {
            if (gr.getGraph()[v][i]!=0 && color[i]==-1) // if the neighbor isn't colored we color it in the other color
            {
                color[i] = 1-color[v]; // coloring
                q.push(i);
            }
            else if (gr.getGraph()[v][i] && color[i]==color[v])  // if we find 2 neighbors with the same color then the graph is not bipartite
            {
                return to_string(0);
            }
        }
    }
    // if we didn't return 0 then the graph is bipartite and we need to print the partition
    string out = "The graph is bipartite: ";
    string a= "A={";
    string b= "B={";
    for (size_t i = 0; i < numV; i++){ // looping to find the partition
        if (color[i]==0){
            a=a+ to_string(i) + ", ";
        }
        else {
            b=b+ to_string(i) + ", ";
        }
    }
    a = a.substr(0, a.length() - 2) + "}, "; 
    b = b.substr(0, b.length() - 2) + "}.";
    out=out+a+b;
    return out;
}





string Algorithms:: shortestPath(Graph gr,int start, int end){ // find the shortest path between 2 vertices
//if there isn't a path we return -1 , if the graph is weighed we use Bellman-Ford algorithm and if it's not weighed we use BFS
    if (end>gr.getGraph().size()-1 || start>gr.getGraph().size()-1) { //  if the start/end vertices are bigger than the number of vertices of the graph we return -1
        return to_string(-1);
    }

    if(gr.getIsWeighed()==true) { // if the graph is weighed we use Bellman-Ford algorithm 
        size_t numV = (size_t)gr.getVerNum();
        vector<int> dist(numV, INT_MAX); // vector to save distances and do "relax" process by the algorithm
        vector<size_t> parent(numV,(size_t)-1); //vector to save the parent vertex so we can print the path
        dist[(size_t)start] = 0;
        for (size_t i = 0; i < numV -1; i++) // // by looping v-1 times we get the shortest distances
        {
            for (size_t j = 0; j< numV ; j++)
            {
                for (size_t t = 0; t < numV; t++)
                {
                    if (gr.getGraph()[j][t] != 0 && dist[j] != INT_MAX && dist[j] + gr.getGraph()[j][t] < dist[t]) //  relax
                    {
                        dist[t] = gr.getGraph()[j][t] + dist[j];
                        parent[t]=j;
                    }
                }
            }
        }
        for (size_t j = 0; j< numV ; j++) 
        {
            for (size_t t = 0; t < numV; t++)
            {
                if (gr.getGraph()[j][t] != 0 && dist[j] != INT_MAX && dist[j] + gr.getGraph()[j][t] < dist[t])
                // if we can do relax one more time (the v'th time) then we have a negative cycle - error, there is no shortest path
                {
                    return to_string(-1);
                }
            }
        }
        if (dist[(size_t)end]== INT_MAX) { // if the distance is still inifinite then we didn't find a path 
            return to_string(-1);;
        }
        // after finding the shortest we need to print it using a stack
        size_t s= (size_t)end;
        stack <int> stack;
        while (s!=start){
            stack.push(s);
            s=parent[s];
        }
        stack.push(start);
        string str;
        while(stack.size()!=1){
            str= str+ to_string(stack.top())+ "->";
            stack.pop();
        }
        str=str+ to_string(stack.top()) + ".";
        return str;
    }

    else {  // if the graph is not weighed we use BFS
        size_t numV = (size_t)gr.getVerNum();
        vector<int> dist(numV,-1);  //vector to save  the distances of each vertex from the start point
        vector<size_t> parent(numV,(size_t)-1); // //vector to save the parent vertex so we can print the path
        queue<int> q;
        q.push(start);
        dist[(size_t)start] = 0; 
        while (!q.empty())
        {
            size_t v = (size_t)q.front();
            q.pop();
            for (size_t i = 0; i < numV; i++) 
            {
                if (gr.getGraph()[v][i] && dist[i] == -1) // for each neighbor vertex we save the distance from the starting point and the parent vertex
                {
                    dist[i] = dist[v] + 1; 
                    parent[i] = v; 
                    q.push(i); 
                }
            }
        }
        if (dist[(size_t)end] == -1) // // if we didn't find a distance then there is no path 
        {
            return to_string(-1);
        }
         // after finding the shortest we need to print it using a stack
        size_t s= (size_t)end;
        stack <int> stack;
        while (s!=start){
            stack.push(s);
            s=parent[s];
        }
        stack.push(start);
        string str;
        while(stack.size()!=1){
            str= str+ to_string(stack.top())+ "->";
            stack.pop();
        }
        str=str+ to_string(stack.top()) + ".";
        return str;
    }
}





//string Algorithms:: isContainsCycle(Graph gr) {


//}