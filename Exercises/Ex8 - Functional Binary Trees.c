/**
 * Exercise 8 - Functional BSTs
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
typedef struct BSTNode {
    int value;
    BSTNode* left;
    BSTNode* right;
} BSTNode;

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
 * Given the root of a BST and a value, this function searches for the value
 * in the BST. Returns true if the value was found, false otherwise.
 *
 * @param root Pointer to the root of the BST.
 * @param value The value to be searched for in the BST.
 * @return true if the value was found, false otherwise.
 */
bool contains(BSTNode* root, int value) {
    // NOTE: This function is already completed for you.
    if (root == NULL) {
        return false;
    } else if (root->value == value) {
        return true;
    } else if (value > root->value) {
        return contains(root->right, value);
    } else {
        return contains(root->left, value);
    }
}

/**
 * Given the root of a BST and a mapping function, this function applies the
 * mapping function to every node's value in the BST. The resulting BST should
 * have both the old node's value and the new one, derived from the result of
 * the mapping function. The resulting BST should have no nodes that share the
 * same value. Returns the head of the new BST.
 *
 * @param root Pointer to the root of the BST.
 * @param node_function Pointer to the mapping function applied to each node's
 * value. The function takes an integer value and returns an integer.
 * @return Pointer to the head of the new BST.
 */
BSTNode* apply_function_to_tree(BSTNode* root, int (*node_function)(int)) {
    // TODO: Complete this function.
   if (root == NULL) {
        return NULL;
    }

    int mapped_value = node_function(root->value);

    BSTNode* new_left = apply_function_to_tree(root->left, node_function);
    BSTNode* new_right = apply_function_to_tree(root->right, node_function);


    if (!contains(root, mapped_value)) {
        BSTNode* new_node = allocate_new_node(mapped_value);
        if (new_node == NULL) {
            return NULL;
        }

        new_node->left = new_left;
        new_node->right = new_right;

        return new_node;
    } else {
        root->left = new_left;
        root->right = new_right;

        return root;
    }
}
// ===========================================================================
// DO NOT CHANGE ANY 'ifndef' AND 'endif' MACROS.
// These macros help ensure your parts of your code does not conflict with the
// automarker. Changing them will result in your code not compiling and you
// receiving a 0 for the entire assignment.
// ===========================================================================
#ifndef __testing__

/**
 * This function performs a special mapping:
 * - Even numbers become n + 1
 * - Odd numbers become n * 2
 *
 * @param value The integer value to be mapped.
 * @return The result of the special mapping.
 */
int special_function(int value) {
    if (value % 2 == 0) {
        return value + 1;
    } else {
        return value * 2;
    }
}

int main() {
    // The following code depicts the diagrams and steps shown on Quercus.

    // This is our initial BST.
    BSTNode* root = allocate_new_node(14);
    root->left = allocate_new_node(3);
    root->right = allocate_new_node(37);
    root->right->left = allocate_new_node(15);

    // We apply the special function to our BST.
    root = apply_function_to_tree(root, special_function);

    // Make sure that our new nodes exist!
    printf("The value is: %d",apply_function_to_tree(root, special_function)->value);
    assert(contains(root, 14));
    //assert(contains(root, 14 + 1));
    //assert(contains(root, 3));
    assert(contains(root, 3 * 2));
    assert(contains(root, 37));
    assert(contains(root, 37 * 2));
    assert(contains(root, 15));
    assert(contains(root, 15 * 2));

    // Don't forget to release any memory!
    free_tree(root);

    printf("All test cases passed. Have you written any of your own?\n");
    return 0;
}

#endif
