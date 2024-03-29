/**
 * Exercise 7 - Quick Sort
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 */
#include "wackylist.h"

/**
 * Given the head of a linked list, this function calculates and returns the
 * length (number of nodes) of the linked list.
 *
 * @param head Pointer to the head of the linked list.
 * @return The length of the linked list.
 */
int get_length(LinkedListNode* head) {
    // TODO: Complete this function.
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

/**
 * Given the head of a linked list, this function converts the linked list
 * into an array of linked list node addresses. The ith element of the array
 * is the address of the ith node in the linked list, starting from the head.
 *
 * @note For a non empty array, array[0] = head.
 * @note It is assumed that the array has enough memory to fit all addresses.
 *
 * @param head Pointer to the head of the linked list.
 * @param array Array to store the addresses of linked list nodes. The array
 * should have enough memory to fit the entire linked list.
 */
void convert_list_to_array(LinkedListNode* head, LinkedListNode* array[]) {
    // TODO: Complete this function.

    int i = 0;
    while (head != NULL) {
        array[i] = malloc(sizeof(LinkedListNode));

        if (array[i] != NULL) {
            array[i]->next = NULL;
            strncpy(array[i]->utorid, head->utorid, sizeof(array[i]->utorid) - 1);
            strncpy(array[i]->major, head->major, sizeof(array[i]->major) - 1);
            array[i]->gpa = head->gpa;
        } else {
            while (i > 0) {
                i--;
                free(array[i]);
            }
            return;
        }

        head = head->next;
        i++;

    }
    array[i] = NULL;
}
/**
 * Given an array of addresses to linked list nodes, this function joins each
 * linked list node together where the following element of the node at array[i]
 * is the address of the node at array[i+1]. The final node has no next element.
 * Return the new head of the linked list.
 *
 * @param array Array of addresses to linked list nodes.
 * @param size The size of the array.
 * @return Pointer to the new head of the linked list.
 */
LinkedListNode* convert_array_to_list(LinkedListNode* array[], int size) {
    // TODO: Complete this function.
    if (size == 0) {
        return NULL;
    }

    for (int i = 0; i < size - 1; i++) {
        if (array[i] != NULL) {
            array[i]->next = array[i + 1];
        }
    }

    array[size - 1]->next = NULL;

    return array[0];
}

/**
 * Given the head of a linked list and a comparison function, this function
 * sorts the linked list in ascending order and returns the head of the new
 * linked list.
 *
 * @note The second argument may look very intimidating! It is just a function
 * address that returns an integer given two address pointers as parameters.
 * You can find a sample implementation inside main::compare_nodes(). You do
 * not need to understand how this function works yet! Simply pass it into
 * qsort() as your last parameters. Eg. qsort(..., compare_function);
 * 
 * @param head Pointer to the head of the linked list to be sorted.
 * @param compare_function Pointer to the comparison function used for sorting.
 * The function should return a negative value if the first argument is less
 * than the second, zero if they are equal, and a positive value if the first
 * argument is greater than the second.
 * @return Pointer to the head of the new sorted linked list.
 */
LinkedListNode* sort_linked_list(LinkedListNode* head, int (*compare_function)(const void*, const void*)) {
    // TODO: Complete this function.

    if (head == NULL || head->next == NULL) {
        return head;
    }

    int length = get_length(head);

    LinkedListNode** array = malloc(length * sizeof(LinkedListNode*));

    if (array == NULL) {
        return NULL;
    }

    convert_list_to_array(head, array);

    qsort(array, length, sizeof(LinkedListNode*), compare_function);

    LinkedListNode* sorted_list = convert_array_to_list(array, length);

    free(array);
    free_linked_list(head);
    return sorted_list;
}
