#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include "sstream"
using namespace std;


TEST_CASE("Test graph addition and subsraction")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);
    ariel::Graph g2;
    vector<vector<int>> graph2= {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(graph2);
    ariel::Graph g3 = g1 + g2;
    ariel::Graph g4;
    vector<vector<int>> expectedGraph4 = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    g4.loadGraph(expectedGraph4);
    CHECK((g3==g4) == true);

    ariel::Graph g5= g1-g2;
    ariel::Graph g6;
    vector<vector<int>> expectedGraph6 = {
        {0, 0, -1},
        {0, 0, -1},
        {-1, -1, 0}};
    g6.loadGraph(expectedGraph6);
    CHECK((g5==g6) == true);
    CHECK((g3!=g6) == true);

    CHECK(ariel::Algorithms:: isConnected(g1)== true);
    CHECK(ariel::Algorithms:: isConnected(g2)== true);
    CHECK(ariel::Algorithms:: isConnected(g3)==true);
    CHECK(ariel::Algorithms:: isContainsCycle(g1)=="No cycle detected");
    CHECK(ariel::Algorithms:: isContainsCycle(g3)=="0->1->2->0" );
    


    SUBCASE("test += and -="){
        ariel::Graph g1Old;
        vector<vector<int>> graph1Old = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1 , 0}};
        g1Old.loadGraph(graph1Old);
        CHECK((g1+=g2) == g3);
        CHECK((g1!=g1Old)== true );
        CHECK((g1-=g2)== g1Old );
    }

    SUBCASE("unary plus"){
        ariel::Graph g1Old;
        vector<vector<int>> graph1Old = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1 , 0}};
        g1Old.loadGraph(graph1Old);
        ariel:: Graph g7;
        g7= +g1;
        CHECK((g7==g1)==true);
        CHECK((g1==g1Old)==true);
    }

    SUBCASE("unary minus") {
        ariel:: Graph g8;
        g8 = -g1;
        ariel::Graph g9;
        vector<vector<int>> expectedGraph9 = {
        {0, -1, 0},
        {-1, 0, -1},
        {0, -1, 0}};
        g9.loadGraph(expectedGraph9);
        CHECK ((g9==g8)== true);

        ariel::Graph g10;
        vector<vector<int>> graph10 = {
        {0, 3, 0},
        {-1, 0, 2},
        {0, -1, 0}};
        g10.loadGraph(graph10);
        ariel::Graph g11;
        g11= -g10;
        ariel::Graph g12;
        vector<vector<int>> expectedGraph10 = {
        {0, -3, 0},
        {1, 0, -2},
        {0, 1, 0}};
        g12.loadGraph(expectedGraph10);
        CHECK ((g11==g12)== true); 
    }
}

TEST_CASE("increment and decrement"){

    SUBCASE("pre increment"){
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2, 4, 1},
        {1, 0, 1, 3},
        {0, 1, 0, 1},
        {1, 4, 3, 0}};
    g1.loadGraph(graph1);
    ariel::Graph g2;
    g2= ++g1;
    ariel::Graph g3;
    vector<vector<int>> expected3 = {
        {0, 3, 5, 2},
        {2, 0, 2, 4},
        {1, 2, 0, 2},
        {2, 5, 4, 0}};
    g3.loadGraph(expected3);
    CHECK((g2==g3)== true);
    }

    SUBCASE("pre decrement"){
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2, 4, 1},
        {1, 0, 1, 3},
        {0, 1, 0, 1},
        {1, 4, 3, 0}};
    g1.loadGraph(graph1);
    ariel::Graph g2;
    g2= --g1;
    ariel::Graph g3;
    vector<vector<int>> expected3 = {
        {0, 1, 3, 0},
        {0, 0, 0, 2},
        {-1, 0, 0, 0},
        {0, 3, 2, 0}};
    g3.loadGraph(expected3);
    CHECK((g2==g3)== true);

    CHECK(ariel::Algorithms::isBipartite(g1) == "The graph is bipartite: A={0, 3}, B={1, 2}");
    CHECK(ariel::Algorithms::isBipartite(g3) == "The graph is bipartite: A={0, 3}, B={1, 2}");


    }

    SUBCASE("post increment"){
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2, 4, 1},
        {1, 0, 1, 3},
        {0, 1, 0, 1},
        {1, 4, 3, 0}};
    g1.loadGraph(graph1);
    ariel::Graph g2;
    g2= g1++;
    ariel:: Graph g1Old;
    vector<vector<int>> graph1Old = {
        {0, 2, 4, 1},
        {1, 0, 1, 3},
        {0, 1, 0, 1},
        {1, 4, 3, 0}};
    g1Old.loadGraph(graph1Old);
    ariel::Graph g3;
    vector<vector<int>> expected3 = {
        {0, 3, 5, 2},
        {2, 0, 2, 4},
        {1, 2, 0, 2},
        {2, 5, 4, 0}};
    g3.loadGraph(expected3);
    CHECK((g2==g1Old)== true);
    CHECK((g1==g3)== true);
    }

    SUBCASE("post decrement"){
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2, 4, 1},
        {1, 0, 1, 3},
        {0, 1, 0, 1},
        {1, 4, 3, 0}};
    g1.loadGraph(graph1);
    ariel::Graph g2;
    g2= g1--;
    ariel:: Graph g1Old;
    vector<vector<int>> graph1Old = {
        {0, 2, 4, 1},
        {1, 0, 1, 3},
        {0, 1, 0, 1},
        {1, 4, 3, 0}};
    g1Old.loadGraph(graph1Old);
    ariel::Graph g3;
    vector<vector<int>> expected3 = {
        {0, 1, 3, 0},
        {0, 0, 0, 2},
        {-1, 0, 0, 0},
        {0, 3, 2, 0}};
    g3.loadGraph(expected3);
    CHECK((g2==g1Old)== true);
    CHECK((g1==g3)== true);
    
    }
}

TEST_CASE("test output operator"){
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);
    ostringstream s;
    s << g1;
    CHECK(s.str()== "[0,1,0], [1,0,1], [0,1,0]\n");
}

TEST_CASE("test equal/not equal"){
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);
    ariel::Graph g1copy;
    vector<vector<int>> graph1copy = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1copy.loadGraph(graph1copy);
    ariel::Graph g2;
    vector<vector<int>> graph2= {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(graph2);
    CHECK((g1==g1copy) == true);
    CHECK_FALSE(g1==g2);
    CHECK((g1!=g2)==true);
}

TEST_CASE("test multiplication and division")
{
    SUBCASE("test graph multiplication"){
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    ariel:: Graph g3;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    g3.loadGraph(expectedGraph);
    CHECK((g3==g4) == true);

    ariel::Graph g11;
    vector<vector<int>> graph1 = {
        {0, 1, 5, 2},
        {1, 0, 2, 0},
        {3, 5, 0, 5},
        {0,5 ,1, 0}};
    g11.loadGraph(graph1);
    ariel::Graph g22;
    vector<vector<int>> weightedGraph2 = {
        {0, 3, -1, 0},
        {2, 0, 2, 1},
        {1, 2, 0, 6}, 
        {0, 0 ,0 , 0}};
    g22.loadGraph(weightedGraph2);
    ariel::Graph g44 = g11 * g22;
    ariel:: Graph g33;
    vector<vector<int>> expectedGraph2 = {
        {0, 10, 2, 31},
        {2, 0, -1, 12},
        {10, 9, 0, 5},
        {11, 2 , 10 , 0}};
    g33.loadGraph(expectedGraph2);
    CHECK((g33==g44) == true);

    CHECK(ariel::Algorithms::isConnected(g11) == true);
    CHECK(ariel::Algorithms::shortestPath(g11, 0, 2) == "0->1->2");
    CHECK(ariel::Algorithms::isConnected(g22) == true);
    CHECK(ariel::Algorithms::shortestPath(g22, 0, 2) == "0->2");
    CHECK(ariel::Algorithms::isConnected(g33) == true);
    CHECK(ariel::Algorithms::shortestPath(g33, 0, 2) == "0->2");
}

 SUBCASE ("test multiplication of graph with number"){
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 5, 2},
        {1, 0, 1},
        {0, 7, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> Graph2 = {
        {0, 10, 4},
        {2, 0, 2},
        {0, 14, 0}};
    g2.loadGraph(Graph2);
    g1 *=2;
    CHECK((g1==g2)== true);
 }

 SUBCASE ("test division of graph by number"){
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 5, 2},
        {1, 0, 1},
        {0, 7, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> Graph2 = {
        {0, 10, 4},
        {2, 0, 2},
        {0, 14, 0}};
    g2.loadGraph(Graph2);
    g2 /=2;
    CHECK((g1==g2)== true);
    ariel::Graph g3;
    g3.loadGraph(Graph2);
    g3/=-2;

    CHECK((g3==(g2*=-1))== true);
    CHECK(ariel::Algorithms::negativeCycle(g1) == "The graph doesn't contain a negative cycle");
    CHECK(ariel::Algorithms::negativeCycle(g3) == "The graph contains a negative cycle");

 }
}

TEST_CASE("test comparison operators") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);
    ariel::Graph g2;
    vector<vector<int>> graph2= {
        {0, 1, 0, 1},
        {1, 0, 1, 4},
        {0, 1, 0, 3},
        {3, 2, 2, 0}};
    g2.loadGraph(graph2);
    CHECK((g1<g2)== true);
    CHECK((g1<=g2)== true);
    CHECK((g1>g2)== false);

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 2, 0},
        {3, 0, 1},
        {0, 1, 0}};
    g3.loadGraph(graph3);
    CHECK((g3<g2)== false);
    CHECK((g3<g1)== false);
    CHECK((g3>g1)== true);
    CHECK((g2>g3)== false);
    CHECK((g2<g3)== true);
    CHECK((g3>g2)== true);
    CHECK((g3>=g2)== true);
    CHECK((g3<g3)== false);
    CHECK((g3>g3)== false);
    CHECK((g3>=g3)== true);
    CHECK((g3<=g3)== true);

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 1},
        {1, 0}};
    g4.loadGraph(graph4);
    ariel::Graph g5;
    vector<vector<int>> graph5 = {
        {0, 2},
        {1, 0}};
    g5.loadGraph(graph5);
    CHECK((g4<g5)== false);
    CHECK((g4>g5)== true);
    CHECK((g4<=g5)== false);
    CHECK((g4>=g5)== true);



}

TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);

}