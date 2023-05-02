#include "stdio.h"
#include "stdlib.h"
#define ARR_SIZE 1000

int count = 0;

struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int new_data){
    struct Node* root = (struct Node*) malloc(sizeof(struct Node));
    root->data = new_data;
    root->left = NULL;
    root->right = NULL;

    return root;
}

struct Node* createBalancedBST(int arr[], int start, int end){
    if(start > end){
        return NULL;
    }

    int mid = (start + end) / 2;
    struct Node* root = createNode(arr[mid]);

    root->left = createBalancedBST(arr, start, mid-1);
    root->right = createBalancedBST(arr, mid+1, end);

    return root;

}

void print_level(struct Node* root, int level){
    if(root == NULL){
        return;
    }
    count++;
    printf("%d-Value: %d - NodeLevel: %d\n", count, root->data, level);

    print_level(root->left, level+1);
    print_level(root->right, level+1);
}

int main(){

    int arr[ARR_SIZE];
    for(int i = 0; i<ARR_SIZE; i++){
        arr[i] = i+1;
    }

    struct Node* node = createBalancedBST(arr, 0, ARR_SIZE - 1);

    print_level(node, 1);

    return 0;
}