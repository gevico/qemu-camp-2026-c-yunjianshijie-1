#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

// 定义BST节点结构
typedef struct TreeNode {
    char letter;        // 存储字母
    int count;          // 计数
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 创建新节点
TreeNode* create_node(char letter) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->letter = tolower(letter);  // 转换为小写
    newNode->count = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 向BST中插入节点或更新计数
TreeNode* insert_or_update(TreeNode* root, char letter) {
    // 如果不是字母，直接返回原树
    if (!isalpha(letter)) {
        return root;
    }
    if (root == NULL) {
        return create_node(letter);
    }
    // 转换为小写
    letter = tolower(letter);
    // 用循环不
    TreeNode* current = root;
    while (current != NULL) {
        if (letter < current->letter) {
            if (current->left == NULL) {
                current->left = create_node(letter);
                return root;
            }
            current = current->left;
        } else if (letter > current->letter) {
            if (current->right == NULL) {
                current->right = create_node(letter);
                return root;
            }
            current = current->right;
        } else {
            // 字母已存在，增加计数
            current->count++;
            return root;
        }
    }
    return root;
}

// 中序遍历BST并打印结果（按字母顺序）
void inorder_traversal(TreeNode* root) {
    //
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%c:%d ", root->letter, root->count);
        inorder_traversal(root->right);
    }
}

// 释放BST内存
void free_tree(TreeNode* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main(int argc, char *argv[]) {
    const char* file_path = "paper.txt";
    
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    TreeNode* root = NULL;
    int c;
    
    while ((c = fgetc(file)) != EOF) {
        if (isalpha(c)) {  // 只处理字母字符
            root = insert_or_update(root, c);
        }
    }
    
    fclose(file);
    
    // 按字母顺序输出结果
    inorder_traversal(root);
    
    // 释放内存
    free_tree(root);
    
    return 0;
}