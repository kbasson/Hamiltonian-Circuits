/*
    Name: Karanvir Basson
    Title: Hamiltonian Circuit by Backtracking
    Date: 06-28-2022
*/

#include "hamiltonianCircuit.h"

int getAdjacencyMatrix(int adjacencyMatrix[NUM_NODES][NUM_NODES]) { //Given a file containing an adjacency matrix and store it in 2d array

    FILE* file = fopen(FILENAME, "r"); //Open file for reading

    if (file == NULL) { //If file doesn't exist

        printf("%s not found!\n", FILENAME);
        return 0;

    }
    
    for (int i = 0; i < NUM_NODES; i++) { //Initialize matrix to all zeores

        for (int j = 0; j < NUM_NODES; j++) {

            adjacencyMatrix[i][j] = 0;

        }

    }

    int size = ((NUM_NODES * 2) + 2) * sizeof(char); //Get size of string contining row of matrix
    char matrixRow[size]; //Initialize string contining row of matrix

    int i = 0; //Row index

    while (fgets(matrixRow, size, file)) { //Read matrix

        int j = 0;//Column index
        char* entry = strtok(matrixRow, " \n"); //Get current matrix entry as string

        while (entry != NULL) { //If string entry is not null

            adjacencyMatrix[i][j] = atoi(entry); //Convert string to int
            entry = strtok(NULL, " \n"); //Get next entry
            j++;

        }

        i++;

    }

    fclose(file); //Close file ptr
    return 1;

}

int connectNodes(Node* nodes[NUM_NODES], int adjacencyMatrix[NUM_NODES][NUM_NODES]) { //Given a list of nodes and an adjacency matrix, create graph edges

    for (int i = 0; i < NUM_NODES; i++) { //For all rows in matrix

        for (int j = 0; j < NUM_NODES; j++) { //For all columns in matrix

            if (adjacencyMatrix[i][j]) { //If edge exists

                if (nodes[i] -> edges == NULL) { //If no edges currently in list

                    nodes[i] -> edges = createEdge(nodes[j]); //Create edge
                    if (nodes[i] -> edges == NULL) return 0; //NULL ptr check

                } else { //if edges already exist

                    Edge* temp = nodes[i] -> edges; //Temp pointer to first edge

                    while (temp -> next != NULL) { //Get last edge

                        temp = temp -> next;

                    }

                    temp -> next = createEdge(nodes[j]); //Create edge
                    if (temp -> next == NULL) return 0; //NULL ptr check

                }

            }

        }

    }

    return 1; //Return 1, indicating success

}

Node* createNode(int ID) { //Given an id, create a node with that id

    Node* node = malloc(sizeof(Node)); //Allocate memory
    if (node == NULL) return NULL; //NULL ptr check

    //Initialize Node
    node -> ID = ID;
    node -> visited = 0;
    node -> edges = NULL;

    return node; //Return node


}

void freeNode(Node* node) { //Given a node, free it

    if (node == NULL) return; //NULL ptr check

    //FREE NODE EDGES
    while (node -> edges != NULL) {

        Edge* temp = node -> edges;
        node -> edges = node -> edges -> next;
        free(temp);

    }

    //FREE NODE
    free(node);

}

Edge* createEdge(Node* dest) { //Given a destination, create edge

    if (dest == NULL) return NULL; //NULL ptr check

    Edge* edge = malloc(sizeof(Edge)); //Allocate struct
    if (edge == NULL) return NULL; //NULL ptr check

    //INITIALIZE EDGE
    edge -> dest = dest;
    edge -> next = NULL;

    return edge; //Return newly allocated edge

}

void addEdge(Node* node, Edge* edge) { //Given a node and an edge, add edge to node

    if (node == NULL || edge == NULL) return; //NULL ptr check

    Edge* temp = node -> edges; //Get edges of node
    
    if (temp == NULL) { //If node has no edges
        
        node -> edges = edge; //If node has no edges currently
        return;

    }

    while (temp -> next != NULL) { //Get last edge in list

        temp = temp -> next;

    }

    temp -> next = edge; //Add edge to end of list

}

void HC_backtracking(Node* start, Node* current, Node* sst, int* numNodes) { //Find Hamiltonian Circuits using Backtracking

    if (current == NULL || sst == NULL) return; //NULL ptr check
    else printf("current = %d\n", current -> ID); //Print current node

    current -> visited = 1; //Visit current node
    int isConnected = 0; //1 if current is connected to start, else zero

    Edge* temp = current -> edges; //Get edges of current node

    while (temp != NULL) { //For all edges of current node

        if (temp -> dest != NULL) { //NULL ptr check

            if (temp -> dest -> ID == start -> ID) isConnected = 1; //If current is connected to start, set isConnected to 1

            if (temp -> dest -> visited == 0) { //If dest node of current edge has not been visited

                Node* dest = createNode(temp -> dest -> ID); //Create copy of unvisited node
                if (dest == NULL) return; //NULL ptr check

                Edge* edge = createEdge(dest); //Create edge to copy
                if (edge == NULL) return; //NULL ptr check

                addEdge(sst, edge); //Add copy to sst
                printf("Adding edge from %d to %d\n", sst -> ID, dest -> ID);

                //Visit destination and add it to sst
                (*numNodes)++;
                HC_backtracking(start, temp -> dest, dest, numNodes);
                
                //Unvisit destination to remove from
                temp -> dest -> visited = 0;
                (*numNodes)--;

            }

        }

        temp = temp -> next; //Go to next edge

    }

    if (sst -> edges == NULL) { //If current node has no unvisited adjacent nodes

        printf("\nnumNodes = %d\n", (*numNodes));

        if ((*numNodes) == NUM_NODES && isConnected) printf("Valid Hamiltonian Cycle\n\n"); //If all nodes in sst and current node can go back to start, (Is a valid Hamiltonian Circuit)
        else printf("Invalid Hamiltonian Cycle\n\n"); //If not all nodes visited or no edge from start to end exists (Invalid Hamiltonian Cycle)

    }

}

void freeSST(Node* sst) { //Given a sst, free it

    if (sst == NULL) return; //NULL ptr check

    Edge* temp = sst -> edges;

    while (temp != NULL) { //DFT of SST

        freeSST(temp -> dest); //Recursive call on child
        
        Edge* copy = temp; //Get copy of current pointer
        temp = temp -> next; //Increment temp pointer
        free(copy); //Free edge

    }

    free(sst); //Free current node

}
