#include "Algorithms.hpp"
#include "Graph.hpp"
#include <iostream>
#include <queue>
#include <algorithm>
#include <limits.h>
#include <stack>
using namespace std;
using namespace ariel;


bool Algorithms:: isConnected(Graph &gr) { // check if the graph is connected using BFS algorithm
    if (gr.getGraph().empty()) {return false;}
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


string Algorithms:: negativeCycle(Graph &gr){ // find if there's a negative cycle by Bellman-Ford algorithm
    if(gr.getIsWeighed()== false || gr.getGraph().empty()) { // if the graph is not weighed then it doesn't contain a negative cycle
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


string Algorithms:: isBipartite(Graph &gr){ // check if the graph is bipartite or not. if it is- the function return the partition 
//this function is done by cy coloring the vertices in 2 different colors using BFS
    if (gr.getGraph().empty()) { return "The graph is bipartite";}
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
    b = b.substr(0, b.length() - 2) + "}";
    out=out+a+b;
    return out;
}


string printWay(vector<size_t> &way) { // a helper function to print the way 
    string str;
    for (size_t j= 0; j < way.size(); j++) {
        str += to_string(way[j]);
        if (j!= way.size()-1){
            str+= "->";
        }
    }
    return str;
}


string shortestPathWeighed(Graph &gr,int start, int end){ // if the graph is weighed we use Bellman-Ford algorithm 
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
        // after finding the shortest path we need to print it 
        vector<size_t> way;
        size_t s= (size_t)end;
        while (s!=start){
            way.push_back(s);
            s=parent[s];
        }
        way.push_back((size_t)start);
        reverse(way.begin(), way.end());
        return printWay(way);
}


string shortestPathUnweighed(Graph &gr,int start, int end){ // if the graph is not weighed we use BFS
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
     // after finding the shortest path we need to print it
    vector<size_t> way;
    size_t s= (size_t)end;
    while (s!=start){
        way.push_back(s);
        s=parent[s];
    }
    way.push_back((size_t)start);
    reverse(way.begin(), way.end());
    return printWay(way);
}


string Algorithms:: shortestPath(Graph &gr,int start, int end){ // find the shortest path between 2 vertices
//if there isn't a path we return -1 , if the graph is weighed we use Bellman-Ford algorithm and if it's not weighed we use BFS
    if (end>gr.getGraph().size()-1 || start>gr.getGraph().size()-1 || gr.getGraph().empty()) { //  if the start/end vertices are bigger than the number of vertices of the graph or graph is empty
        return to_string(-1);
    }

    if(gr.getIsWeighed()==true) { // if the graph is weighed we use Bellman-Ford algorithm 
        return shortestPathWeighed(gr,start,end);
    }

    else {  // if the graph is not weighed we use BFS
        return shortestPathUnweighed(gr,start,end);
    }
}


bool hasCycleDirected(const vector<vector<int>> &graph, size_t node, vector<size_t>& visited, vector<size_t>& path, vector<size_t>& cycle) {
    // helper function to detect cycle in directed graph
    visited[node] = 1; // mark the current node as visited
    path[node] = 1; // mark the current node in the path
    for (size_t i = 0; i < graph.size(); i++) { // loop over all neighbors of the node
        if (graph[node][i] != 0) { // if there is an edge from node to neighbor
            if (visited[i] == 0) { // if neighbor is not visited
                if (hasCycleDirected(graph, i, visited, path, cycle)) { // recursively visit neighbors
                    cycle.push_back(node); // add the current node to the cycle
                    return true; // if a cycle is detected, return true
                }
            }
            else if (path[i] == 1) { // if neighbor is in the current path
                cycle.push_back(i); // add the neighbor to the cycle
                cycle.push_back(node); // add the current node to the cycle
                return true; // found a back edge, cycle detected
            }
        }
    }
    path[node] = 0; // Remove the current node from the path
    return false; // No cycle detected
}


bool hasCycleUndirected(const vector<vector<int>> &graph, size_t node, vector<size_t>& visited, vector<size_t>& parent, vector<size_t>& cycle) {
    // helper function to detect cycle in undirected graph
    visited[node] = 1; // mark the current node as visited
    for (size_t i = 0; i < graph.size(); i++) { // loop over all the node's neighbors
        if (graph[node][i] != 0) { // if there is an edge from node to neighbor
            if (visited[i] == 0) { // if neighbor is not visited
                parent[i] = node; // set parent of neighbor as current node
                if (hasCycleUndirected(graph, i, visited, parent, cycle)) { // Recursively visit neighbors
                    return true; // if a cycle is detected, return true
                }
            } 
            else if (parent[node] != i) { // if visited neighbor is not the parent , check back edge
                // found a back edge, cycle detected
                cycle.push_back(i); // add the neighbor to the cycle
                for (size_t j = node; j != i; j = parent[j]) { // loop to enter all nodes to the cycle
                    cycle.push_back(j); // Add node to cycle
                }
                cycle.push_back(i); // Complete the cycle
                reverse(cycle.begin(), cycle.end()); // Reverse to get the correct order
                return true;
            }
        }
    }
    return false; // No cycle detected
}


string printCycle(vector<size_t>& cycle) {
    string result;
    size_t i=0;
    while (i<cycle.size() && cycle[i] != cycle.back() ) { i++; } // finding the first node of the cycle
    while (i<cycle.size()) { 
        result += to_string(cycle[i]);
        if (i < cycle.size() - 1){
            result += "->"; 
        }
        i++;
    }
    return result;
}


string Algorithms:: isContainsCycle(Graph &gr){ // function to detect a cycle in the graph divided to directed/undirected
    if (gr.getGraph().empty()) {return "No cycle detected";}
    vector<vector<int>> graph= gr.getGraph();
    if (gr.getIsDirected()==true) { // detect a cycle in directed graph
        vector<size_t> visited(graph.size(), 0); // vector to save visited nodes
        vector<size_t> path(graph.size(), 0); // vector to save the path
        vector<size_t> cycle; // vector for the cycle detected
        for (size_t i = 0; i < graph.size(); ++i) { // traverse through each node in the graph
            if (visited[i] == 0) { // if the node is not visited
                if (hasCycleDirected(graph, i, visited, path, cycle)) { // check for cycle using DFS
                    reverse(cycle.begin(), cycle.end()); // reverse to get the correct order
                    return printCycle(cycle);
                }
            }
        }
        return "No cycle detected";
    } 
    else {
        vector<size_t> visited(graph.size(), 0); // vector for visited nodes
        vector<size_t> parent(graph.size(), (size_t)-1); // vector to save parents vertex
        vector<size_t> cycle; // vector to save the cycle
        for (size_t i = 0; i < graph.size(); ++i) { // traverse through each node in the graph
            if (visited[i] == 0) { // if the node is not visited
                if (hasCycleUndirected(graph, i, visited, parent, cycle)) { // check for cycle using DFS
                    return printCycle(cycle);
                }
            }
        }
        return "No cycle detected";
    }
}