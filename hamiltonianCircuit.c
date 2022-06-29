/*
    Name: Karanvir Basson
    Title: Hamiltonian Circuit by Backtracking
    Date: 06-28-2022
*/

#include "hamiltonianCircuit.h"

int main() {

    int adjacencyMatrix[NUM_NODES][NUM_NODES]; //Integer matrix representing adjacency matrix
    int res = getAdjacencyMatrix(adjacencyMatrix); //Initialize adjacency matrix from file
    if (res == 0) return -1; //If file read doesn't work

    Node* nodes[NUM_NODES]; //Array of nodes in graph

    for (int i = 0; i < NUM_NODES; i++) { //Create all nodes in array

        nodes[i] = createNode(i); //Create node
        if (nodes[i] == NULL) return -1; //If node creation fails

    }

    res = connectNodes(nodes, adjacencyMatrix); //Connect all nodes using adjacency matrix
    if (res == 0) return -1; //If node connection fails

    Node* sst = createNode(nodes[0] -> ID); //Create SST 
    int numNodes = 1; //Number of nodes in sst

    HC_backtracking(nodes[0], nodes[0], sst, &numNodes); //Find Hamiltonian Circuits using Backtracking Algorithm

    for (int i = 0; i < NUM_NODES; i++) { //For all nodes

        freeNode(nodes[i]); //Free current node

    }

    freeSST(sst); //Free SST
    return 1;

}
