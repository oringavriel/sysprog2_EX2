#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "Graph.hpp"
using namespace std;

namespace ariel
{
    class Algorithms {
        public:
            static bool isConnected(Graph& gr); 
            static string shortestPath(Graph &gr,int start, int end);
            static string isContainsCycle(Graph &gr);
            static string isBipartite(Graph &gr);
            static string negativeCycle(Graph &gr);       
    } ;
}
#endif
