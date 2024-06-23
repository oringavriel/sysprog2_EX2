#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;
using namespace ariel;


Graph::Graph(){
    this->edgeNum=0;
    this->verNum=0;
    this->isDirected=false;
    this->isWeighed=false;
}
void Graph::loadGraph(const vector<vector<int>>& gr) {
        if (gr.empty()){
        this->graph=gr;
        this->verNum=0;
        this->edgeNum=0;
        this->isDirected=false;
        this->isWeighed=false;
        }
        else{
        this->graph=gr;
        this->verNum=gr.size();
        this->isDirected=false;
        this->isWeighed=false;
        int count=0;
        if (graph[0].size()!= graph.size()) { //prints an error if the graph is not square
                throw invalid_argument("Invalid graph: The graph is not a square matrix.");
        }
        for (size_t i=0; i<gr.size(); i++){
                for (size_t j=0; j<gr.size(); j++){
                        if (gr[i][j]>1) { // if one of the numbers in the graph is bigger than 1 then the graph is weighed
                                this->isWeighed=true;
                        }
                        if (gr[i][j]!=gr[j][i]) { // check if the graph is symetric (symetric = undirected)
                                this->isDirected=true;
                        }
                        if (gr[i][j]!=0) { //count edges
                                count++;
                        }
                        if (i==j && gr[i][j] !=0){ // diagonal line doesn't equal to 0
                                throw invalid_argument("Invalid graph");
                        }
                }
        }     
        if (this->isDirected == true){
             this->edgeNum=count;   
        }
        else{
             this->edgeNum= count/2;   // if the graph is not directed the we need to divide the number of edges by 2
        }  
        }
}
void Graph:: printGraph(){
        cout<< "Graph with " << this->verNum<< " vertices and " << this->edgeNum<<" edges."<< endl;
}
vector<vector<int>> Graph:: getGraph() const {
        return this->graph;
}
int Graph:: getVerNum() const {
        return this->verNum;
}
int Graph::getEdgeNum() const {
        return this->edgeNum;
}
bool Graph::getIsDirected(){
        return this->isDirected;
}
bool Graph::getIsWeighed(){
        return this->isWeighed;
}


//operators
        Graph Graph:: operator+(const Graph &other)const{ // adding variables of two matrices into a new one
                if(this->getGraph().size()!=other.getGraph().size()) {// check if the matrices has same number of vertices
                        throw invalid_argument("the matrices has different sizes");
                }
                Graph g;
                g.loadGraph(this->graph); //load a graph in the same size
                for (size_t i=0; i<this->getVerNum(); i++){
                        for (size_t j=0; j<this->getVerNum(); j++){
                                g.graph[i][j]= g.graph[i][j] +other.getGraph()[i][j]; // adding
                        }
                }
                return g;
        }

        Graph Graph:: operator-(const Graph &other) const { // like +
                if(this->getGraph().size()!=other.getGraph().size()  ) {
                        throw invalid_argument("the matrices has different sizes");
                }
                Graph g;
                g.loadGraph(this->graph);
                for (size_t i=0; i<this->getVerNum(); i++){
                        for (size_t j=0; j<this->getVerNum(); j++){
                                g.graph[i][j]= g.graph[i][j] -other.getGraph()[i][j];
                        }
                }
                return g;
        }

        Graph& Graph:: operator+=(const Graph &other) { // updating the graph by adding another graph to it
                if(this->getGraph().size()!=other.getGraph().size()  ) {
                        throw invalid_argument("the matrices has different sizes");
                }
                for (size_t i=0; i<other.getVerNum(); i++){
                        for (size_t j=0; j<other.getVerNum(); j++){
                                this->graph[i][j]= this->getGraph()[i][j]+other.getGraph()[i][j];// adding the variables of the other graph to the origin
                        }
                }
                return *this; // return thr graph itself
        }

        Graph& Graph:: operator-=(const Graph &other){ // like +=
                if(this->getGraph().size()!=other.getGraph().size()  ) {
                        throw invalid_argument("the matrices has different sizes");
                }
                for (size_t i=0; i<other.getVerNum(); i++){
                        for (size_t j=0; j<other.getVerNum(); j++){
                                this->graph[i][j]= this->getGraph()[i][j]-other.getGraph()[i][j];
                        }
                }
                return *this;
        }

        Graph Graph:: operator+() const{ // unary plus ( returns the same graph)
                return *this;
        }

        Graph& Graph:: operator-() { // unary minus ( returns the graph after changing it signs)
                if (this->getGraph().empty()) { 
                        return *this;
                }
                for (size_t i=0; i<this->getVerNum(); i++){
                        for (size_t j=0; j<this->getVerNum(); j++){
                                this->graph[i][j]= -1* this->getGraph()[i][j];
                        }
                }
                return *this;
        }

        Graph& Graph:: operator++(){ // pre- increment by 1
                for (size_t i=0; i<this->getVerNum(); i++){
                        for (size_t j=0; j<this->getVerNum(); j++){
                                if(i!=j){
                                this->graph[i][j]= this->getGraph()[i][j]+1; // update the graph by adding 1
                        }
                        }
                }
                return *this; // returns the updated graph

        }

        Graph Graph:: operator++(int){ // post- increment by 1
        Graph g(*this); // copy the graph
        ++(*this); // pre increment of the graph
        return g; // return the copied graph (the graph before changes)
        }

        Graph& Graph:: operator--(){ // pre- decrement by 1
                for (size_t i=0; i<this->getVerNum(); i++){
                        for (size_t j=0; j<this->getVerNum(); j++){
                                if(i!=j){
                                this->graph[i][j]= this->getGraph()[i][j]-1; // // update the graph by substarcting 1
                        }
                        }
                }
                return *this; // // returns the updated graph
        }

        Graph Graph:: operator--(int){  // post- decrement by 1
        Graph g(*this); // copy the graph
        --(*this); // pre increment of the graph
        return g; // return the copied graph (the graph before changes)
        }
        
        bool Graph:: operator==(const Graph &other)const{ //  comparing if two graphs are equal
                if (this->getVerNum()!=other.getVerNum()){
                        return false; // if the matrices has differnet vertices number they are not equal
                }
                for (size_t i=0; i<other.getVerNum(); i++){
                        for (size_t j=0; j<other.getVerNum(); j++){
                                if (this->getGraph()[i][j]!=other.getGraph()[i][j]){ // comparing all of the edges
                                        return false;
                                }
                        }
                }
                return true;
        }
        
        bool Graph:: operator!=(const Graph &other) const{ // comparing if two graphs are'nt equal using the opposite of the equal operator
                return !(*this==other);
        }

        bool Graph:: operator<(const Graph& other) const{ // check if this matrix is smaller than the other
                if (*this==other) { // check if the matrices are equal
                        return false;
                }
                bool temp= true; 
                if (this->getVerNum()<= other.getVerNum()){ // check sub-matrix
                for (size_t i=0; i<this->getVerNum(); i++){
                        for (size_t j=0; j<this->getVerNum(); j++){
                                if (this->getGraph()[i][j] != other.getGraph()[i][j]){ // change the temp value if one isn't sub-matrix of the other
                                        temp= false;
                                }
                        }
                }
                if (temp== true ) {
                        return temp; // if this is sub-matrix of the other 
                }
                }  
                else if (this->getEdgeNum()<other.getEdgeNum()){ // check if the this matrix edge number is smaller than the other
                        temp= false;
                }
                else if (this->getVerNum()<other.getVerNum()){ // check if the this matrix vertices number is smaller than the other
                        temp= false;
                }
                return temp; 
        }
        
        bool Graph:: operator<=(const Graph& other) const { // check if thia matrix is smaller or equal to the other using the < and == operators
                return (*this<other || other==*this);
        }

        bool Graph:: operator>(const Graph& other) const{ //check if this matrix is bigger than the other using the opposite of the < operator
                if (*this==other){
                        return false;
                }
                else{
                        return !(*this<other);
                }
        }
        bool Graph:: operator>=(const Graph& other) const{ // check if this matrix is bigger or equal to the other using the opposite of the <= operator
                return (*this>other || other==*this);
        }

        Graph Graph:: operator*(const Graph other) const{ // multiplication of two matrices
                if(this->getGraph().size()!=other.getGraph().size() || this->getGraph()[0].size()!=other.getGraph()[0].size()  ) {
                        throw invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix."); // if the matrices has different vertex number they can't be multiplied
                }
                Graph g;
                g.loadGraph(this->graph); // saving a graph in the size of the original
                for (size_t i=0; i<g.getVerNum(); i++){
                        for (size_t j=0; j<g.getVerNum(); j++){
                                g.graph[i][j]=0;// reseting the graph
                                for (size_t t=0; t<g.getVerNum(); t++){ // for loop to calculate the multiplication (row*col)
                                        if(i!=j){  
                                        g.graph[i][j]+= this->getGraph()[i][t]*other.getGraph()[t][j];}
                                }

                        }
                }
                return g;
        }
        Graph& Graph:: operator*=(const int num){ // multiply a matrix by a number
                for (size_t i=0; i<this->getVerNum(); i++){
                        for (size_t j=0; j<this->getVerNum(); j++){
                                this->graph[i][j]= this->getGraph()[i][j]*num;
                        }
                }
                return *this;
        }

        Graph& Graph:: operator/=( const int num){ // division by number
                for (size_t i=0; i<this->getVerNum(); i++){
                        for (size_t j=0; j<this->getVerNum(); j++){
                                this->graph[i][j]= this->getGraph()[i][j]/num;
                        }
                }
                return *this;
        }

        ostream& ariel:: operator<<(ostream& os, const Graph& graph) { // output operator that returns a reference to an output stream which represent the graph matrix
                for (size_t i = 0;i < graph.getVerNum(); i++) {
                        os << "[";
                        for (size_t j = 0; j < graph.getVerNum(); j++) {
                                if(j==graph.getVerNum()-1){
                                        os << graph.getGraph()[i][j];
                                }
                                else{
                                os << graph.getGraph()[i][j] << ",";
                                }
                        }
                        os << "]" ;
                        if (i!= graph.getVerNum()-1) { os<< ", ";}
                }
                os<< endl;
                return os;
        }