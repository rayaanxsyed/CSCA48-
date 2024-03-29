/**
 * Exercise 8 - More BST Operations
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BSTNode BSTNode;
struct BSTNode {
    int value;
    BSTNode* left;
    BSTNode* right;
};

/**
 * This function allocates a new node for a Binary Search Tree (BST) with the
 * specified value. If the allocation fails, it returns NULL.
 *
 * @param value The value to be assigned to the new node.
 * @return Pointer to the newly allocated BST node or NULL if allocation fails.
 */
BSTNode* allocate_new_node(int value) {
    // NOTE: This function is already completed for you.
    BSTNode* node = malloc(sizeof(BSTNode));
    if (node == NULL) {
        return NULL;
    }

    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * Given the root of a BST, this function recursively frees the memory
 * associated with the entire tree, including all nodes and their values.
 *
 * @param root Pointer to the root of the BST to be freed.
 */
void free_tree(BSTNode* root) {
    // NOTE: This function is already completed for you.
    if (root == NULL) {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

/**
 * Given the root of a BST and a value, this function inserts a new node with
 * the specified value into the BST. Returns the root of the modified BST.
 *
 * @param root Pointer to the root of the BST.
 * @param value The value to be inserted into the BST.
 * @return Pointer to the root of the modified BST.
 */
BSTNode* insert_value(BSTNode* root, int value) {
    // NOTE: This function is already completed for you.
    if (root == NULL) {
        return allocate_new_node(value);
    } else if (root->value == value) {
        return root;
    } else if (root->value > value) {
        root->left = insert_value(root->left, value);
        return root;
    } else {
        root->right = insert_value(root->right, value);
        return root;
    }
}

/**
 * Given the root of a BST and a value, this function searches for the value
 * in the BST. Returns true if the value was found, false otherwise.
 *
 * @param root Pointer to the root of the BST.
 * @param value The value to be searched for in the BST.
 * @return true if the value was found, false otherwise.
 */
bool contains_value(BSTNode* root, int value) {
    // NOTE: This function is already completed for you.
    if (root == NULL) {
        return false;
    } else if (root->value == value) {
        return true;
    } else if (value > root->value) {
        return contains_value(root->right, value);
    } else {
        return contains_value(root->left, value);
    }
}

BSTNode* find_min(BSTNode* node) {
    // Traverse the left subtree until reaching the leftmost leaf node
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

/**
 * Given the root of a BST and a value, this function deletes the node with
 * the specified value from the BST and deallocates any unused nodes. Returns
 * the root of the modified BST.
 *
 * @param root Pointer to the root of the BST.
 * @param value The value to be deleted from the BST.
 * @return Pointer to the root of the modified BST.
 */
BSTNode* delete_value(BSTNode* root, int value) {
    // TODO: Complete this function.
    if (root == NULL) {
        return NULL;
    }
    if (value < root->value) {
        root->left = delete_value(root->left, value);
    }
    else if (value > root->value) {
        root->right = delete_value(root->right, value);
    }
    else {
        if (root->left == NULL) {
            BSTNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            BSTNode* temp = root->left;
            free(root);
            return temp;
        }

        BSTNode* temp = find_min(root->right);
        root->value = temp->value;
        root->right = delete_value(root->right, temp->value);
    }
    return root;
}

// ===========================================================================
// DO NOT CHANGE ANY 'ifndef' AND 'endif' MACROS.
// These macros help ensure your parts of your code does not conflict with the
// automarker. Changing them will result in your code not compiling and you
// receiving a 0 for the entire assignment.
// ===========================================================================
#ifndef __testing__

int main() {
    // This is our initial BST.
    BSTNode* root = NULL;
    root = insert_value(root, 60);
    root = insert_value(root, 41);
    root = insert_value(root, 74);
    root = insert_value(root, 16);
    root = insert_value(root, 53);
    root = insert_value(root, 65);
    root = insert_value(root, 25);
    root = insert_value(root, 46);
    root = insert_value(root, 55);
    root = insert_value(root, 63);
    root = insert_value(root, 70);
    root = insert_value(root, 42);
    root = insert_value(root, 62);
    root = insert_value(root, 64);

    // Try to delete a node that doesn't exist. Nothing should happen.
    root = delete_value(root, 10000);

    // Delete a node that exists.
    root = delete_value(root, 53);
    assert(contains_value(root, 53) == false);

    root = delete_value(root, 55);
    assert(contains_value(root, 55) == false);

    // Don't forget to release any memory!
    free_tree(root);

    printf("All test cases passed. Have you written any of your own?\n");
    return 0;
}

#endif
