# Minimum Spanning Forest
C implementation of Kruskal's algorithm using find-union by rank to find optimum
solutions for Minimum Spanning Forest for a non-directional graph.
There are free nodes and source nodes. All free nodes must be connected to a
source node or to a free node connected to a source node, for example in a water
or electrical grid. This program finds the minimum cost list of connections in
order to fulfill this conditions.

# Instructions
In console type ./solver test_X.txt to solve test_X in test folder.
The result will be printed in the result.txt file in the Program folder.

# Creating a test
The test file must be in the test folder. Every line must contain three numbers
separated by an empty space i j k
In the first line, the first number, i, corresponds to the amount of free nodes,
the second, j, to the amount of source nodes and the third, k, to the amount of
connections. The free nodes are represented by the numbers 0 to i-1 and the
source nodes by the numbers i to i+j
The next lines represent the connections between the nodes. The first and second
number represent the nodes that are connected by that connection and the third
number is the cost/weight of the connection.
