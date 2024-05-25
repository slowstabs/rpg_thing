#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure
typedef struct Node {
    char description[256];
    struct Node* option1;
    struct Node* option2;
    struct Node* option3;
    int isDeath;
    int isCheckpoint; // Flag to indicate if this node is a checkpoint
} Node;

// Function to create a new node
Node* createNode(const char* description, int isDeath, int isCheckpoint) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strncpy(newNode->description,description,sizeof(newNode->description) - 1);
    newNode->description[sizeof(newNode->description) - 1] = '\0';
    newNode->option1 = NULL;
    newNode->option2 = NULL;
    newNode->option3 = NULL;
    newNode->isDeath = isDeath;
    newNode->isCheckpoint = isCheckpoint;
    return newNode;
}

// Function to add options to a node
void addOptions(Node* parent, Node* option1, Node* option2, Node* option3) {
    parent->option1 = option1;
    parent->option2 = option2;
    parent->option3 = option3;
}

Node* lastCheckpoint = NULL;

// Function to build the game tree
Node* buildGameTree() {
    // Create nodes
    Node* start = createNode("You are at the start of your journey.", 0, 1); // Checkpoint
    Node* option1 = createNode("You encounter a friendly villager.", 0, 0);
    Node* option2 = createNode("You fall into a trap and die.", 1, 0);
    Node* option3 = createNode("You find a hidden path.", 0, 1); // Checkpoint
    Node* option1_1 = createNode("The villager gives you a sword.", 0, 0);
    Node* option1_2 = createNode("The villager attacks you and you die.", 1, 0);
    Node* option1_3 = createNode("The villager shows you a shortcut.", 0, 0);
    
    // Link nodes
    addOptions(start, option1, option2, option3);
    addOptions(option1, option1_1, option1_2, option1_3);
    
    return start;
}

// Function to play the game
void playGame(Node* currentNode) {
    lastCheckpoint = currentNode; // Start at the first node, which is also the first checkpoint

    while (currentNode != NULL) {
        printf("%s\n", currentNode->description);
        if (currentNode->isDeath) {
            printf("You have died. Game over.\n");
            printf("Restarting from the last checkpoint...\n");
            currentNode = lastCheckpoint;
            continue; // Restart the loop from the last checkpoint
        }

        if (currentNode->isCheckpoint) {
            lastCheckpoint = currentNode;
        }

        printf("Choose an option:\n");
        printf("1. Option 1\n");
        printf("2. Option 2\n");
        printf("3. Option 3\n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                currentNode = currentNode->option1;
                break;
            case 2:
                currentNode = currentNode->option2;
                break;
            case 3:
                currentNode = currentNode->option3;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function to free the memory allocated for the tree
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->option1);
    freeTree(root->option2);
    freeTree(root->option3);
    free(root);
}

// Main function
int main() {
    Node* gameTree = buildGameTree();
    playGame(gameTree);
    freeTree(gameTree);
    return 0;
}
