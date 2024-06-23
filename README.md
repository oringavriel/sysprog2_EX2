# System programming- assignment 2
This project extends the Graph class by adding operators to it.
## Operators
1.	Graph operator+(const Graph &other) const - addition of 2 graphs- returns a new graph which represent the addition of the two matrices (can be done only if the matrices are from the same size, else- throw exception).
2.	Graph operator-(const Graph &other) const- subtraction of 2 graphs- returns the a new graph which represent the subtraction of the two matrices (can be done only if the matrices are from the same size , else- throw exception). 
3.	Graph& operator+=(const Graph &other)- adds one graph to another- returns the graph  itself after adding the other graph to it  (can be done only if the matrices are from the same size, else- throw exception).
4.	Graph& operator-=(const Graph &other)- subtract one graph from another- returns the graph itself after subtracting  the other graph from it  (can be done only if the matrices are from the same size, else- throw exception).
5.	Graph operator+() const- unary plus- returns the graph as is.
6.	Graph& operator-()- unary minus- returns the graph after switching the adjacency signs . it works by multiplying the graph by -1.  
7.	Graph& operator++()- pre increment(++g)– the operator first increases the graph by 1 and then returns it.
8.	Graph operator++(int)- post increment (g++)- the operator saves a new copy of the graph and then increases the graph itself by 1. It returns the copied graph (before the change).
9.	Graph& operator--() - pre decrement(--g)- the operator first decreases the graph by 1 and then returns it.
10.	Graph operator--(int)- post decrement (g--)- the operator saves a new copy of the graph and then decreases the graph itself by 1. It returns the copied graph (before the change).        
11.	bool operator==(const Graph &other) const- equals check- the operator returns true if the matrices are equal, otherwise-false. The matrices are equal if they are from the same size (same vertex number) and all of weights are equal. 
12.	 bool operator!=(const Graph &other) const- not equal check- the operator returns true if the matrices aren't equal, otherwise-false. It works by using the opposite of the return value of the == operator.
13.	bool operator<(const Graph& other) const- smaller check- other is bigger if this graph is sub-matrix of it. If not and they are not equal, it's bigger if it's adjacency number of other  is bigger . if it is also equal, it's bigger if the number of vertices is bigger.
14.	 bool operator<=(const Graph& &other) const- smaller or equal check - the operator returns true or false if the matrix itself is smaller or equal to the other. It works by using the < and == operators.
15.	 bool operator>(const Graph& &other) const—bigger check- the operator returns true or false if the matrix itself is bigger than the other. It works by using the opposite of the return value of the < operator.
16.	bool operator>=(const Graph& other) const- bigger or equal check- the operator returns true or false if the matrix itself is bigger or equal to the other. It works by using the opposite of the return value of the <= operator.
17.	Graph operator*(const Graph other) const- multiplication of 2 graphs- the operator returns a new graph which is the multiplication of two graphs (can be done only if the matrices are from the same size).
18.	Graph& operator*=( const int num)- multiplication of a graph by a number- the operator returns the graph itself after multiplying it by a number given.     
19.	Graph& operator/=( const int num)- division operator- operator which divides the matrix by a number given and returns it. 
20.	friend ostream& operator<<(ostream& os, const Graph& graph)-  output operator- the operator is a "friend" of the graph class and grants access to private functions and members in the class. It returns a reference to an output stream.
