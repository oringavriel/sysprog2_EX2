#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>
using namespace std;
#include <stdexcept>


namespace ariel
{
    class Graph
    {
    private:
        vector<vector<int>> graph;
        int verNum;
        int edgeNum;
        bool isDirected;
        bool isWeighed;
    public:
        Graph(); // constructor
        void loadGraph(vector<vector<int>> gr);
        void printGraph();
        vector<vector<int>> getGraph() const;
        int getVerNum() const;
        int getEdgeNum() const;
        bool getIsDirected() ;
        bool getIsWeighed() ;  

        //assignment 2
        Graph operator+(const Graph other) const;
        Graph operator-(const Graph other) const;
        Graph& operator+=(Graph other);
        Graph& operator-=(Graph other);
        Graph operator+() const;
        Graph& operator-() ;
        Graph& operator++();
        Graph operator++(int);
        Graph& operator--();
        Graph operator--(int);
        bool operator==(const Graph other) const;
        bool operator!=(const Graph other) const;
        bool operator<(const Graph& other) const;
        bool operator<=(const Graph& other) const;
        bool operator>(const Graph& other) const;
        bool operator>=(const Graph& other) const;
        Graph operator*(Graph other)const;
        Graph& operator*=( const int num);
        friend ostream& operator<<(ostream& os, const Graph& graph);
    } ;
}
#endif