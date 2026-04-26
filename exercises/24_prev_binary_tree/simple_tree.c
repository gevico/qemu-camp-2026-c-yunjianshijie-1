#include "simple_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// 创建队列
Queue* create_queue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}
// 进入队列
void enqueue(Queue *q, TreeNode *tree_node) {
       QueueNode * new_node = (QueueNode*)malloc(sizeof(QueueNode));
       new_node->tree_node = tree_node;
       new_node->next = NULL;
       if (q->rear == NULL) {
           q->front = q->rear = new_node;
       } else {
           q->rear->next = new_node;
           q->rear = new_node;
       }
}

// 出队列
TreeNode* dequeue(Queue *q) {
    if(is_empty(q)) {
        return NULL;
    }
    QueueNode *temp = q->front;
    q->front = q->front->next;

    // 如果队列变空了，更新rear指针
    if (q->front == NULL) {
        q->rear = NULL;
    }

    TreeNode *tree_node = temp->tree_node;
    free(temp);
    return tree_node;
}

bool is_empty(Queue *q) {
    return q->front == NULL;
}

void free_queue(Queue *q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
}

TreeNode* create_tree_node(int val) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

// 构建二叉树
TreeNode* build_tree_by_level(int *level_order, int size) {
    // 
     if(size == 0) {
        return NULL;}
     Queue * q = create_queue();

    // 先创建更节点    
    TreeNode *root = create_tree_node(level_order[0]);
    enqueue(q, root);
    int c =1;
    while (1)
    {
        TreeNode * m = dequeue(q);
        if(c >= size) {
            break;
        }
        // 
        if(level_order[c] != INT_MIN) {
            TreeNode *node = create_tree_node(level_order[c]);
            m->left = node;
            enqueue(q, node);
        }
        c++;
        if(c >= size) {
            break;
        }
        //
        if(level_order[c] != INT_MIN) {
            TreeNode *node = create_tree_node(level_order[c]);
            m->right = node;
            enqueue(q, node);
        }
        c++;
    }
    return root;
}


// 前序遍历递归版本
void preorder_traversal(TreeNode *root) {
    if(root == NULL) {
        return;
    }
    printf("%d ", root->val);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

// 前序遍历迭代版本
void preorder_traversal_iterative(TreeNode *root) {
    if(root == NULL) {
        return;
    }
    TreeNode * stack[100];
    int top = -1;
    stack[++top] = root;

    while(top >= 0) {
        TreeNode * node = stack[top--];
        printf("%d ", node->val);
        if(node->right) {
            stack[++top] = node->right;
        }
        if(node->left) {
            stack[++top] = node->left;
        }
    }
}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
