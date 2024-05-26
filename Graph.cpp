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
void Graph::loadGraph(vector<vector<int>> gr) {
        this->graph=gr;
        this->verNum=gr.size();
        this->isDirected=false;
        this->isWeighed=false;
        int count=0;
        if (graph[0].size()!= graph.size()) { //prints an error if the graph is not square
                cout<< "Invalid graph: The graph is not a square matrix.";
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
                }
        }     
        if (this->isDirected == true){
             this->edgeNum=count;   
        }
        else{
             this->edgeNum= count/2;   // if the graph is not directed the we need to divide the number of edges by 2
        }  
}
void Graph:: printGraph(){
        cout<< "Graph with " << this->verNum<< " vertices and " << this->edgeNum<<" edges."<< endl;
}
vector<vector<int>> Graph:: getGraph() const {
        return this->graph;
}
int Graph:: getVerNum() const{
        return this->verNum;
}
int Graph::getEdgeNum() const{
        return this->edgeNum;
}
bool Graph::getIsDirected(){
        return this->isDirected;
}
bool Graph::getIsWeighed() {
        return this->isWeighed;
}


//operators
        Graph Graph:: operator+(const Graph other)const{
                if(this->getVerNum()!=other.getVerNum()) {
                        throw "the matrices has defferent sizes";
                }
                Graph g;
                g.loadGraph(this->getGraph());
                for (size_t i=0; i<this->getVerNum(); i++){
                        for (size_t j=0; j<this->getVerNum(); j++){
                                g.graph[i][j]=+other.getGraph()[i][j];
                        }
                }
                return g;
        }

        Graph Graph:: operator-(const Graph other) const {
                if(this->getVerNum()!=other.getVerNum()) {
                        throw "the matrices has defferent sizes";
                }
                Graph g;
                g.loadGraph(this->getGraph());
                g.verNum=this->getVerNum();
                for (size_t i=0; i<other.getVerNum(); i++){
                        for (size_t j=0; j<other.getVerNum(); j++){
                                g.graph[i][j]=-other.getGraph()[i][j];
                        }
                }
                return g;
        }

        Graph& Graph:: operator+=(Graph other) {
                if(this->getVerNum()!=other.getVerNum()) {
                        throw "the matrices has defferent sizes";
                }
                for (size_t i=0; i<other.getVerNum(); i++){
                        for (size_t j=0; j<other.getVerNum(); j++){
                                this->graph[i][j]= this->getGraph()[i][j]+other.getGraph()[i][j];
                        }
                }
                return *this;
        }

        Graph& Graph:: operator-=(Graph other){
                if(this->getVerNum()!=other.getVerNum()) {
                        throw "the matrices has defferent sizes";
                }
                for (size_t i=0; i<other.getVerNum(); i++){
                        for (size_t j=0; j<other.getVerNum(); j++){
                                this->graph[i][j]= this->getGraph()[i][j]-other.getGraph()[i][j];
                        }
                }
                return *this;
        }

        Graph Graph:: operator+() const{
                return *this;
        }

        Graph& Graph:: operator-() {
                for (size_t i=0; i<this->getVerNum(); i++){
                        for (size_t j=0; j<this->getVerNum(); j++){
                                this->graph[i][j]= -1* this->getGraph()[i][j];
                        }
                }
                return *this;
        }

        Graph& Graph:: operator++(){
                for (size_t i=0; i<this->getVerNum(); i++){
                        for (size_t j=0; j<this->getVerNum(); j++){
                                this->graph[i][j]= this->getGraph()[i][j]+1;
                        }
                }
                return *this;

        }

        Graph Graph:: operator++(int){
                Graph g;
                g.graph=this->graph;
                g.verNum=this->verNum;
                g.edgeNum=this->edgeNum;
                g.isDirected=this->isDirected;
                g.isWeighed=this->isWeighed;
                for (size_t i=0; i<this->getVerNum(); i++){
                        for (size_t j=0; j<this->getVerNum(); j++){
                                this->graph[i][j]= this->getGraph()[i][j]+1;
                        }
                }
                return g;
        }

        Graph& Graph:: operator--(){
                for (size_t i=0; i<this->getVerNum(); i++){
                        for (size_t j=0; j<this->getVerNum(); j++){
                                this->graph[i][j]= this->getGraph()[i][j]-1;
                        }
                }
                return *this;
        }

        Graph Graph:: operator--(int){
                Graph g;
                g.graph=this->graph;
                g.verNum=this->verNum;
                g.edgeNum=this->edgeNum;
                g.isDirected=this->isDirected;
                g.isWeighed=this->isWeighed;
                for (size_t i=0; i<this->getVerNum(); i++){
                        for (size_t j=0; j<this->getVerNum(); j++){
                                this->graph[i][j]= this->getGraph()[i][j]-1;
                        }
                }
                return g;
        }
        
        bool Graph:: operator==(const Graph other)const{
                if (this->getVerNum()!=other.getVerNum()){
                        return false;
                }
                for (size_t i=0; i<other.getVerNum(); i++){
                        for (size_t j=0; j<other.getVerNum(); j++){
                                if (this->getGraph()[i][j]!=other.getGraph()[i][j]){
                                        return false;
                                }
                        }
                }
                return true;
        }
        
        bool Graph:: operator!=(const Graph other) const{
                if ( (*this==other) ==true){
                        return false;
                }
                else {
                        return true;
                }
        }

        bool Graph:: operator<(const Graph& other) const{
                for (size_t i=0; i<this->getVerNum(); i++){
                        for (size_t j=0; j<this->getVerNum(); j++){
                                if (this->getGraph()[i][j] != other.getGraph()[i][j]){
                                        return false;
                                }
                        }
                }
                if (*this==other) {
                        return false;
                }
                if (this->getEdgeNum()<other.getEdgeNum()){
                        return false;
                }
                if (this->getVerNum()<other.getVerNum()){ 
                        return false;
                }
                return true;
        }
        
        bool Graph:: operator<=(const Graph& other) const {
                if (other<*this || other==*this) {
                        return true;
                } 
                else {
                        return false;
                }
        }

         bool Graph:: operator>(const Graph& other) const{
                return !(other<*this);
        }

        bool Graph:: operator>=(const Graph& other) const{
                return !(other<=*this);
        }

        Graph Graph:: operator*(Graph other) const{
                if(this->getVerNum()!=other.getVerNum()) {
                        throw "the matrices has defferent sizes";
                }
                Graph g;
                g.loadGraph(this->graph);
                for (size_t i=0; i<g.getVerNum(); i++){
                        for (size_t j=0; j<g.getVerNum(); j++){
                                g.graph[i][j]=0;
                                for (size_t t=0; t<g.getVerNum(); t++){
                                        g.graph[i][j]=g.graph[i][j]+(this->getGraph()[i][t]+other.getGraph()[t][j]);
                                }
                        }
                }
                return g;
        }
        Graph& Graph:: operator*=(const int num){
                for (size_t i=0; i<this->getVerNum(); i++){
                        for (size_t j=0; j<this->getVerNum(); j++){
                                this->graph[i][j]= this->getGraph()[i][j]*num;
                        }
                }
                return *this;
        }

        ostream& ariel:: operator<<(ostream& os, const Graph& graph) {
                vector<vector<int>> g= graph.graph;
                for (size_t i = 0;i < g.size(); ++i) {
                        os << "[";
                        for (size_t j = 0; j < g.size(); ++j) {
                                os << g[i][j];
                        }
                        os << "]" ;
                }
                os<< endl;
                return os;
        }