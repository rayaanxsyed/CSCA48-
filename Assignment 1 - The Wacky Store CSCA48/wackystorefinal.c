/**
 * Assignment 1 - The Wacky Store
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
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 1024

typedef struct ItemNode ItemNode;
struct ItemNode {
    char name[MAX_NAME_LENGTH];
    int count;
    ItemNode* next;
};

typedef struct Customer Customer;
struct Customer {
    char name[MAX_NAME_LENGTH];
    ItemNode* cart;
};

typedef struct CheckoutLaneNode CheckoutLaneNode;
struct CheckoutLaneNode {
    Customer* customer;

    CheckoutLaneNode* front;
    CheckoutLaneNode* back;
};

typedef struct CheckoutLane CheckoutLane;
struct CheckoutLane {
    CheckoutLaneNode* first;
    CheckoutLaneNode* last;
};

/**
 * Function: new_item_node
 * -----------------------
 * Allocate a new ItemNode. Allocation must be done manually (with malloc or
 * calloc). Initialize all variables using the arguments provided. Assume that
 * count will always be greater than 0.
 */
ItemNode* new_item_node(char* name, int count) {
    // TODO: Complete this function.
    if (name == NULL) { // If name is NULL.
        return NULL;
    }

    ItemNode* new_item = malloc(sizeof(ItemNode));

    if (new_item == NULL) { 
        return NULL;
    }
    strncpy(new_item->name, name, MAX_NAME_LENGTH - 1);
    new_item->name[MAX_NAME_LENGTH - 1] = '\0';  
    new_item->count = count;
    new_item->next = NULL;

    return new_item;
}

/**
 * Function: new_customer
 * ----------------------
 * Allocate a new Customer. Allocation must be done manually (with malloc or
 * calloc). Initialize all variables using the arguments provided.
 */
Customer* new_customer(char* name) {
    // TODO: Complete this function.
    if (name == NULL) { // If name is NULL.
        return NULL;
    }

    Customer* customer = malloc(sizeof(Customer));

    if (customer == NULL) {
        return NULL;
    }

    strncpy(customer->name, name, MAX_NAME_LENGTH - 1);
    customer->name[MAX_NAME_LENGTH - 1] = '\0';
    customer->cart = NULL;
    return customer;
}

/**
 * Function: free_customer
 * -----------------------
 * Release all memory associated with a Customer back to the system. This
 * includes any items they may have had in their cart.
 */
void free_customer(Customer* customer) {
    // TODO: Complete this function.

    if (customer == NULL) {
        return;
    }
    ItemNode* item = customer->cart;

    while (item != NULL) {
        ItemNode* next_item = item->next;
        free(item);
        item = next_item;
    }
    free(customer);
    // printf("The customer is: %s", customer->name);
}

/**
 * Function: open_new_checkout_line
 * --------------------------------
 * Allocate a new empty checkout lane. Allocation must be done manually (with
 * malloc or calloc).
 */
CheckoutLane* open_new_checkout_line() {
    // TODO: Complete this function.
    CheckoutLane* new_lane = malloc(sizeof(CheckoutLane));

    if (new_lane == NULL) {
        return NULL;
    }
    new_lane->first = NULL;
    new_lane->last = NULL;
    return new_lane;
}
/**
 * Function: new_checkout_node
 * ---------------------------
 * Allocate a new CheckoutLaneNode. Allocation must be done manually (with
 * malloc or calloc). Initialize all variables using the arguments provided. Do
 * not allocate a new customer; instead copy the existing reference over.
 */
CheckoutLaneNode* new_checkout_node(Customer* customer) {
    // TODO: Complete this function.
    CheckoutLaneNode* new_lane_node = malloc(sizeof(CheckoutLaneNode));

    if (new_lane_node == NULL) { 
        return NULL;
    }
    new_lane_node->front = NULL;
    new_lane_node->back = NULL;
    new_lane_node->customer = customer;

    return new_lane_node;
}

/**
 * Function: add_item_to_cart
 * --------------------------
 * Add an item to a customer's cart, given its name and amount.
 *
 * If the given amount is 0 or less, do nothing.
 *
 * IMPORTANT: The items in a customer's cart should always be arranged in
 * lexicographically smallest order based on the item names. Consider the use of
 * the ASCII strcmp() function from <string.h>.
 *
 * No two ItemNodes in a customer's cart can have the same name.
 * If the customer already has an ItemNode with the same item name in their
 * cart, increase the node's count by the given amount instead.
 */
void add_item_to_cart(Customer* customer, char* item_name, int amount) {
    // TODO: Complete this function.

    if (amount <= 0 || item_name == NULL) {  // Given amount is invalid, 0 or negative
        return;
    }
    if (customer->cart == NULL) { // If there's no pre-existing items, simply insert into cart. 
        customer->cart = new_item_node(item_name, amount);
        return;
    }

    ItemNode* current_address = customer->cart;
    ItemNode* previous_address = NULL;

    while (current_address != NULL && strcmp(item_name, current_address->name) > 0) { // Check for lexographic order to insert our item.
        previous_address = current_address;
        current_address = current_address->next; //Finds the correct position until it's smaller than item name. 
    } 
    if ((current_address != NULL) && (strcmp(item_name, current_address->name) == 0)) { // If they are the same item. 
        current_address->count += amount;
    }
    else {
        ItemNode* new_item = new_item_node(item_name, amount);

       if (previous_address == NULL) {
            // Insert at the beginning
            new_item->next = customer->cart;
            customer->cart = new_item;
        } else {
            // Insert in the middle or at the end
            new_item->next = current_address;
            previous_address->next = new_item;
        }
    }
}
/**
 * Function: remove_item_from_cart
 * -------------------------------
 * Attempt to reduce the quantity of an item in a customer's cart, given its
 * name and amount.
 *
 * If no ItemNode in the customer's cart match the given item name, or the
 * amount given is <= 0, do nothing.
 *
 * If the quantity is reduced to a value less than or equal to 0, remove the
 * ItemNode from the customer's cart. This means you will need to do memory
 * cleanup as well.
 */
void remove_item_from_cart(Customer* customer, char* item_name, int amount) {
    // TODO: Complete this function.
      if (amount <= 0 || customer->cart == NULL || item_name == NULL) {  // Given amount is invalid such as 0 or negative, as well as if there's no items. 
        return;
    }
    ItemNode* current_address = customer->cart;
    ItemNode* previous_address = NULL;
    
    while (current_address != NULL) { // Check for lexographic order to insert our item.
        if (strcmp(current_address->name, item_name) == 0) { // If they match
            current_address->count -= amount;

            if (current_address->count <= 0) { // If the items are now 0 or negative, remove the node. 
                if (previous_address == NULL) { // If the node is the first item in the linked list. 
                    customer->cart = current_address->next;
                }
                else { // If the item is anywhere else in the linked list. 

                    previous_address->next = current_address->next;
                }
                free(current_address); // Release the node. 
            }
        }
        previous_address = current_address;
        current_address = current_address->next;  //Finds the correct position until it's smaller than item name. 
    
        // No matches
    }
    return;
}
/**
 * Function: total_number_of_items
 * -------------------------------
 * Count the total number of items in a customer's cart by summing all ItemNodes
 * and their associated quantities.
 */
int total_number_of_items(Customer* customer) {
    // TODO: Complete this function.
    if (customer == NULL) {
        return 0;
    }
    int count = 0;
    if (customer->cart == NULL) { // No items. 
        return count;
    }
    ItemNode* current_address = customer->cart;

    while (current_address != NULL) {
        count += current_address->count;
        current_address = current_address->next;
    }
    // printf("The count is %d", count);
    return count;
}

/**
 * Function: queue
 * ---------------
 * A customer has finished shopping and wishes to checkout. Add the given
 * customer to the end of the given checkout lane.
 */
void queue(Customer* customer, CheckoutLane* lane) {
    // TODO: Complete this function.
    CheckoutLaneNode* new_node = new_checkout_node(customer); // Create a starting checkout lane node.
    if (lane == NULL || new_node == NULL) {
        free(new_node);
        return;
    }
    if (lane->first == NULL && lane->last == NULL) { // No one in line. 
        lane->first = new_node; // Initialize our lane to take both first and last for our new node. 
        lane->last = new_node;
       
    } 
    else {
    new_node->front = lane->last;
    lane->last->back = new_node;
    new_node->back = NULL; 
                                    // Fix the issues on Piazza later. 
    lane->last = new_node;
    }
   
}
/**
 * Function: process
 * -----------------
 * Serve the customer at the head of the checkout lane and return the
 * total_number_of_items() the customer had in their cart.
 *
 * The customer leaves the store after being processed. Therefore, you must also
 * free any memory associated with them.
 *
 * If this function is called on an empty lane, return 0.
 */
int process(CheckoutLane* lane) {
    // TODO: Complete this function.
    if (lane == NULL || (lane->first == NULL && lane->last == NULL)) { // Empty lane
        return 0;
    }

    CheckoutLaneNode* remove_node = lane->first;
    int total_items = total_number_of_items(remove_node->customer);

    lane->first = remove_node->back;

    if (lane->first != NULL) {
        lane->first->front = NULL;
    } else {
        // The lane is now empty, update last accordingly
        lane->last = NULL;
    }
    free_customer(remove_node->customer);
    free(remove_node); // Removed the node. 
    return total_items;
}
/*Return the number of customers in a given lane. If the lane is null or has no customers it will return 0.*/
int count_customers(CheckoutLane* lane) {
    if (lane == NULL || (lane->first == NULL && lane->last == NULL)) {
        return 0; // If null or no customers. 
    }
    int count = 0;
    CheckoutLaneNode* current_address = lane->first;

    while (current_address != NULL) {
        count++;
        current_address = current_address->back;
    }
    return count;
} 

/**
 * Function: balance_lanes
 * -----------------------
 * Move a single customer from the end of the most busy checkout lane to the end
 * of the least busy checkout lane.
 *
 * Busyness is defined as the total number of customers in a checkout lane.
 *
 * If multiple lanes have the same busyness, select the lane that comes first in
 * the CheckoutLane* array.
 *
 * If the difference between the MAX and MIN checkout lanes is <= 1, do nothing.
 *
 * If there are less than 2 lanes, do nothing.
 *
 * Return true if and only if a customer was moved; otherwise false.
 */
bool balance_lanes(CheckoutLane* lanes[], int number_of_lanes) {
    // TODO: Complete this function.
   if (number_of_lanes < 2) {
        return false; // If less than 2
    }

    int total_customers[MAX_NAME_LENGTH]= {0};
    for (int i = 0; i < number_of_lanes; i++) {
        total_customers[i] = count_customers(lanes[i]); // Find the total customers. 
    }   

    int max_customers = total_customers[0];
    int min_customers = total_customers[0]; 
    int max_lane_index = 0;
    int min_lane_index = 0;

    for (int i = 1; i < number_of_lanes; i++) {
        if (total_customers[i] > max_customers) {
            max_customers = total_customers[i];
            max_lane_index = i;
        } else if (total_customers[i] < min_customers) { // Find max and min of lanes. 
            min_customers = total_customers[i];
            min_lane_index = i;
        }
    }

    if (total_customers[min_lane_index] == 0) { // If we have an empty lane open. Start moving people in there. 
        if (total_customers[max_lane_index] <= 1) { // If there's no difference in really moving them. 
            return false;
        }
        CheckoutLaneNode* move_customer = lanes[max_lane_index]->last;
        lanes[max_lane_index]->last = move_customer->front;
        if (move_customer->front != NULL) {
            move_customer->front->back = NULL;
        } else {
            lanes[max_lane_index]->first = NULL;
        }

        move_customer->back = NULL;
        move_customer->front = NULL;
        lanes[min_lane_index]->first = move_customer;
        lanes[min_lane_index]->last = move_customer;

        return true;
    }

    if (max_customers - min_customers <= 1) {
        return false;
    }

    CheckoutLaneNode* move_customer = lanes[max_lane_index]->last;
    lanes[max_lane_index]->last = move_customer->front; // Shift the people from the last of the lanes to the new lanes.
    move_customer->front->back = NULL;

    lanes[min_lane_index]->last->back = move_customer;
    move_customer->front = lanes[min_lane_index]->last;
    lanes[min_lane_index]->last = move_customer;
    move_customer->back = NULL;

    return true;
}

/**
 * Function: process_all_lanes
 * ---------------------------
 * Given an array of CheckoutLane*, process() each CheckoutLane a single time
 * and return the the sum of the result.
 */
int process_all_lanes(CheckoutLane* lanes[], int number_of_lanes) {
    // TODO: Complete this function.
    if (lanes == NULL || number_of_lanes <= 0) { // No lanes or 
        return 0;
    }                           
    int total_items = 0;
    for (int i = 0; i < number_of_lanes; i++) {
        while (lanes[i]->first != NULL) {
            total_items += process(lanes[i]);
            
    }
    }
    return total_items;
}

/**
 * Function: close_store
 * ---------------------
 * It's closing time. Given an array of CheckoutLane*, free all memory
 * associated with them. Any customers still left in the queue is kicked out and
 * also freed from memory.
 */
void close_store(CheckoutLane* lanes[], int number_of_lanes) {
    // TODO: Complete this function.

    if (lanes == NULL) { //If there are no lanes. 
        return;
    }
    for (int i = 0; i < number_of_lanes; i++) {
        if (lanes[i] == NULL) {
            continue;   // We skip that lane if it's NULL. It can be freed after. 
        }

        CheckoutLaneNode* current_address = lanes[i]->first;
        while (current_address != NULL) {
            CheckoutLaneNode* next = current_address->back; // Save next node before freeing the current one
            free_customer(current_address->customer); // Free the customer
            free(current_address); // Free the lane node
            current_address = next; // Move to the next node
        }
        free(lanes[i]);
    }
}
