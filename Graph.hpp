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
        void loadGraph(const vector<vector<int>> &gr); // passing by reference
        void printGraph();
        vector<vector<int>> getGraph() const;
        int getVerNum() const;
        int getEdgeNum() const;
        bool getIsDirected() ;
        bool getIsWeighed() ;  

        //operators
        Graph operator+(const Graph &other) const;
        Graph operator-(const Graph &other) const;
        Graph& operator+=(const Graph &other);
        Graph& operator-=(const Graph &other);
        Graph operator+() const; // unary plus
        Graph& operator-() ; // unary minus
        Graph& operator++(); // pre increment (like ++g)
        Graph operator++(int);   // post increment (like g++)
        Graph& operator--();  // pre decrement (like --g)
        Graph operator--(int); // post decrement (like g--)
        bool operator==(const Graph& other) const;
        bool operator!=(const Graph& other) const;
        bool operator<(const Graph& other) const;
        bool operator<=(const Graph& other) const;
        bool operator>(const Graph& other) const;
        bool operator>=(const Graph& other) const;
        Graph operator*(const Graph other) const;
        Graph& operator*=( const int num);         
        Graph& operator/=( const int num);
        friend ostream& operator<<(ostream& os, const Graph& graph); // output operator- the operator is a "friend" of the graph class and grants 
        // access to private functions and members and returns a refernce to an output stream.
    } ;
}
#endif