/*
    Name: Karanvir Basson
    Title: Hamiltonian Circuit by Backtracking
    Date: 06-28-2022
*/

//INCLUDE HEADER FILES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_NODES 6 //Number of nodes in graph
#define FILENAME "graph.txt" //Name of file containing adjacency matrix
#define INF_VAL 100 //Number used to represent infinity

typedef struct node { //Struct representing graph node

    int ID; //ID of node
    int visited; //Integer indicating if node has been visited
    struct edge* edges; //List of edges

} Node;

typedef struct edge { //Struct representing graph edge

    struct node* dest; //String containing destination node ID
    struct edge* next; //Pointer to next edge

} Edge;

int getAdjacencyMatrix(int adjacencyMatrix[NUM_NODES][NUM_NODES]); //Given a file containing an adjacency matrix and store it in 2d array
int connectNodes(Node* nodes[NUM_NODES], int adjacencyMatrix[NUM_NODES][NUM_NODES]); //Given a list of nodes and an adjacency matrix, create graph edges

Node* createNode(int ID); //Given an id, create a node with that id
void freeNode(Node* node); //Given a node, free it

Edge* createEdge(Node* dest); //Given a destination, create edge
void addEdge(Node* node, Edge* edge); //Given a node and an edge, add edge to node

void HC_backtracking(Node* start, Node* current, Node* HC, int* numNodes); //Find Hamiltonian Circuit using Backtracking
void freeSST(Node* sst); //Given a sst, free it
int nodesConnected(Node* start, Node* end); //Returns 1 if edge from start to end nodes exists, else returns 0
