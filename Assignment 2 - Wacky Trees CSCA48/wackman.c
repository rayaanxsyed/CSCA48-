/**
 * Assignment 1 - Wackman Compression
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * There are also additional notes and clarifications on Quercus.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 */

// No additional imports are allowed. You can make helper functions if you wish.
#include "wackman.h"

/**
 * Given an array of integers and its length, this function calculates
 * the sum of all the elements in the array.
 *
 * @pre The array size (array_size) must be greater than or equal to 0.
 *
 * @param int_array Pointer to the array of integers.
 * @param array_size The number of elements in the array.
 * @return The sum of all integers in the array.
 */
int sum_array_elements(int int_array[], int array_size) {
    // TODO: Complete this function.
    if (array_size == 0) { // If size is 0, there's no elements
        return 0;
    }
    int count = 0;
    for (int i = 0; i < array_size; i++) {
        count += int_array[i]; // Keep incrementing each element value with the count. 
    }
    return count;
}

/**
 * Given an integer array of size ASCII_CHARACTER_SET_SIZE, this function
 * computes the number of occurrences of each ASCII character in the given
 * string. The results are stored in the corresponding indices of the
 * occurrence_array. The computation stops at and does not include the DELIMITER
 * character.
 *
 * @note The occurrence_array[0] should always be 0, representing the DELIMITER.
 * @note The ASCII decimal value of each character corresponds to its index in
 * the array. For example, 'F' with ASCII decimal value 70 will increment
 * occurrence_array[70].
 *
 * @param occurrence_array An array to store the occurrences of each ASCII
 * characters. The array size should be ASCII_CHARACTER_SET_SIZE.
 * @param string The input string to analyze for ASCII character occurrences.
 */
void compute_occurrence_array(int occurrence_array[ASCII_CHARACTER_SET_SIZE], char* string) {
    // TODO: Complete this function.
    memset(occurrence_array, 0, ASCII_CHARACTER_SET_SIZE * sizeof(int));
    
    // Iterate through the string till the delimiter character
    for (int i = 0; string[i] != '\0'; i++) {
        // Increment the count for each ASCII character
        occurrence_array[(int)string[i]]++;
    }
    
}
/**
 * Given an integer array of size ASCII_CHARACTER_SET_SIZE, this function
 * computes and returns the number of characters that occur one or more times.
 *
 * @param occurrence_array An array representing the occurrences of ASCII
 * characters. The array size should be ASCII_CHARACTER_SET_SIZE.
 * @return The number of characters occurring one or more times in the ASCII
 * character set.
 */
int count_positive_occurrences(int occurrence_array[ASCII_CHARACTER_SET_SIZE]) {
    // TODO: Complete this function.
    if (occurrence_array == NULL) { // Sanity check if no elements
        return 0;
    }
    int count = 0;
    for (int i = 0; i < ASCII_CHARACTER_SET_SIZE; i++) { // Iterate over each element till you find element with value >= 0
        if (occurrence_array[i] > 0) {
            count++; // Add count by one 
        }
    }
    return count;
}

/**
 * Given an integer array of size ASCII_CHARACTER_SET_SIZE, representing the
 * number of occurrences of ASCII characters, this function creates and returns
 * a sorted linked list of WackyLinkedNodes.
 *
 * Each node in the list stores a tree with a single leaf node. The node will
 * contain information about the probability of occurrence 'weight' and the
 * ASCII character itself 'val'.
 *
 * @note Exclude elements with a probability of 0 from the linked list.
 * @note Ensure that the linked list is sorted in ascending order from head to
 * tail, first by the probability of occurrence ('weight'), and in case of ties,
 * by the ASCII character ('val') in ascending order.
 * @note Compute the probability of occurrence for each ASCII character α as
 * occurrence_array[α] / SUM(occurrence_array).
 * @note The memory of any required data types must be allocated manually.
 *
 * @param occurrence_array An array representing the occurrences of ASCII
 * characters. The array size should be ASCII_CHARACTER_SET_SIZE.
 * @return A pointer to the head of the created linked list of WackyLinkedNodes.
 */
WackyLinkedNode* create_wacky_list(int occurrence_array[ASCII_CHARACTER_SET_SIZE]) {
    // TODO: Complete this function.
   int sum = sum_array_elements(occurrence_array, ASCII_CHARACTER_SET_SIZE); // Get the sum of all elements in the array.

    if (sum == 0) { // Zero sum case
        return NULL;
    }
    
    WackyLinkedNode* head = NULL;

    for (int i = 0; i < ASCII_CHARACTER_SET_SIZE; i++) {
        if (occurrence_array[i] > 0) {
            double probability = (double) occurrence_array[i] / sum; // Find probability of elements
            WackyTreeNode* leaf_node = new_leaf_node(probability, (char)i);
            WackyLinkedNode* node = new_linked_node(leaf_node); // Create nodes for the the letter to take place

            if (head == NULL || head->val->weight > probability) {
                node->next = head;
                head = node;    // Start adding the nodes based on their probability sort and whether there's any links yet
            } else {
                WackyLinkedNode* current = head;
                while (current->next != NULL && current->next->val->weight < probability) {
                    current = current->next;    // Move to the next node
                }

                // Check for same probability but different ASCII values
                while (current->next != NULL && current->next->val->weight == probability && current->next->val->val < (char)i) {
                    current = current->next;
                }

                // Insert the node
                node->next = current->next;
                current->next = node;
            }
        }
    }
    return head;
}
/**
 * Given a sorted linked list of WackyTreeNodes, where each node (initially)
 * contains a tree with a single leaf node, this function generates a tree based
 * on the following algorithm:
 * - If the size of the linked list is 2 or more:
 *    - Remove 2 WackyLinkedNodes from the head.
 *    - Create a new WackyTreeNode that joins the tree nodes inside the removed
 *      linked nodes. The first node ('head') goes to the LEFT, and the
 *      following node ('head->next') goes to the RIGHT.
 *    - Create a new WackyLinkedNode and add the newly created WackyTreeNode
 *      back into the linked list. The linked list must remain in sorted order
 *      by the probability of occurrence 'weight'. If the newly created node has
 *      the same weight as another node already in the list, add it in front of
 *      all existing similarily weighted nodes.
 *    - Repeat this algorithm until the size of the linked list is 1.
 * - If the size of the linked list is 1:
 *    - Return the address of the tree held at the head of the linked list.
 * - Otherwise:
 *    - Return NULL.
 *
 * @note The memory of any WackyLinkedNodes must be freed by the end of this
 * function.
 *
 * @param linked_list The sorted linked list of WackyTreeNodes.
 * @return A pointer to the root of the generated tree or NULL if the list is
 * empty.
 */
WackyTreeNode* merge_wacky_list(WackyLinkedNode* linked_list) {
    // TODO: Complete this function.
    if (linked_list == NULL) { // Sanity check
        return NULL;
    }

    while (linked_list->next != NULL) { // Given it's not an empty linked list. 
        WackyLinkedNode* first_node = linked_list;
        WackyLinkedNode* second_node = linked_list->next;
        linked_list = second_node->next; // Modify linked list to the nodes after second node


        WackyTreeNode* tree_node = new_branch_node(first_node->val, second_node->val); // Create new node for the root of the BST

        WackyLinkedNode* linked_node = new_linked_node(tree_node); // Create the node for the linked list

        if (linked_list == NULL || tree_node->weight <= linked_list->val->weight) {
            // Insert at the beginning if the list is empty or if the new node's weight is less than the first node's weight
            linked_node->next = linked_list;
            linked_list = linked_node;
        } 
        else {
            // Find the sorted position
            WackyLinkedNode* current = linked_list;
            while (current->next != NULL && current->next->val->weight < tree_node->weight) {
                current = current->next;
            }
            // Insert the new node after the current node
            linked_node->next = current->next;
            current->next = linked_node;
        }
        free(first_node);
        free(second_node); // Free our detached nodes from before
    }

    WackyTreeNode* root = linked_list->val; // Create our root of BST
    free(linked_list);
    return root;
}
/**
 * Given a tree, this function calculates and returns the height of the tree.
 *
 * @note An empty tree (NULL) has a height of 0.
 *
 * @param tree Pointer to the root of the tree.
 * @return The height of the tree.
 */
int get_height(WackyTreeNode* tree) {
    // TODO: Complete this function.
    if (tree == NULL) { // Sanity check
        return 0;
    }
    int left_height = get_height(tree->left);
    int right_height = get_height(tree->right); // Recursively traverse both directions of BST

    return MAX(left_height, right_height) + 1; // Return the largest branch 
}

/**
 * Given a WackyTree and a specific character, this function computes the
 * traversal of the character based on its position in the tree. Movement to the
 * LEFT is FALSE, and movement to the RIGHT is TRUE. The steps are written
 * inside boolean_array, and the total number of steps is stored in array_size.
 *
 * @note the size of boolean_array is greater than or equal to get_height(tree)
 *
 * @param tree Pointer to the root of the WackyTree.
 * @param character The specific ASCII character to compute the encoding for.
 * @param boolean_array An array to store the traversal steps.
 * @param array_size Pointer to the variable holding the total number of steps.
 * If the character is not found, -1 is written to array_size instead.
 */
bool bFound = false;
WackyTreeNode* rootNode = NULL;

void get_wacky_code(WackyTreeNode* tree, char character, bool boolean_array[], int* array_size) {
    // TODO: Complete this function.

	// Only for root node so we know traversing is complete
	if (rootNode == NULL) {
		rootNode = tree;
		bFound = false;
        (*array_size) = 0; // For first iteration
	}
	// if recursive function found searching character, it should return no need to process
	if (bFound==true ) {
		return ;

	}
	// No more nodes, go up one
	if (tree == NULL) { // Sanity check
    	(*array_size)--;
        return;
    }

	// We found it, just go back now without processing.
   if (tree->val == character) { // If root contains the character, no need to traverse
	   bFound = true;
	   return;
   }
   int current = (*array_size);

   if (bFound==false ) {
	   boolean_array[current] = false;
	   (*array_size)++;
	   get_wacky_code(tree->left, character, boolean_array, array_size); // Recursively find on left side

   }
   if (bFound==false ) {
		boolean_array[current] = true;
		(*array_size)++;
		get_wacky_code(tree->right, character, boolean_array, array_size); // Recursively find on right side
   }
   // If no findings, go back
   if (bFound==false) {
	   (*array_size)--;
	}
   // Go back to root after finding
   if (rootNode==tree ) {
	   rootNode= NULL;
   }
}
/**
 * Given the root of a WackyTree, a boolean array, and the size of the array,
 * this function traverses the tree. FALSE indicates a movement to the left,
 * and TRUE indicates a movement to the right. The function returns the
 * character at the node reached after all the steps have been taken. If the
 * node is not a leaf node (LEFT and RIGHT are NOT NULL), it returns the
 * DELIMITER ('\0') instead.
 *
 * @param tree Pointer to the root of the WackyTree.
 * @param boolean_array An array representing the traversal steps.
 * @param array_size The size of the boolean array.
 * @return The character at the reached node or the DELIMITER ('\0') if the node
 * is not a leaf node.
 */
char get_character(WackyTreeNode* tree, bool boolean_array[], int array_size) {
    // TODO: Complete this function.
    WackyTreeNode* current_node = tree;
    for (int i = 0; i < array_size; i++) {
        if (boolean_array[i] == true) { // If it's right then go right
            current_node = current_node->right;
        }
        else {
            current_node = current_node->left; // Go left otherwise
        }
        // Verify that the current node is not null
        if (current_node != NULL && current_node->left == NULL && current_node->right == NULL) {
            return current_node->val;
        }
    }
    return '\0'; // None found
}

/**
 * Given a binary tree, this function frees the memory associated with the
 * entire tree.
 *
 * @param tree Pointer to the root of the binary tree to be freed.
 */
void free_tree(WackyTreeNode* tree) {
    // TODO: Complete this function.
    if (tree == NULL) {
        return; // Sanity check
    }
    free_tree(tree->right); 
    free_tree(tree->left); // Free our branches
    free(tree); // Free the tree s
}
