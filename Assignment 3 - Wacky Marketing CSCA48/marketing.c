/**
 * Assignment 3 - Wacky Marketing
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
 *
 * Starter code:  (Updated by) Charles Xu, 2024
 *             (Originally by) William Song, Mustafa Quraish, 2020
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 1024

#ifndef MAT_SIZE
#define MAT_SIZE 3  // A small graph
#endif

typedef struct user_struct {
    char name[MAX_STR_LEN];
    struct friend_node_struct *friends;
    struct brand_node_struct *brands;
    bool visited;
} User;

typedef struct friend_node_struct {
    User *user;
    struct friend_node_struct *next;
} FriendNode;

typedef struct brand_node_struct {
    char brand_name[MAX_STR_LEN];
    struct brand_node_struct *next;
} BrandNode;

// Note: These are global variables.
FriendNode *allUsers = NULL;
int brand_adjacency_matrix[MAT_SIZE][MAT_SIZE];
char brand_names[MAT_SIZE][MAX_STR_LEN];

/**
 * Given the head of a linked list of FriendNode, this function checks if
 * a given user's name exists in the list. Returns true if the user's name
 * is found, and false otherwise.
 *
 * @param head Pointer to the head of the linked list of FriendNode.
 * @param node Pointer to the user whose name is to be searched in the list.
 * @return true if the user's name exists in the list, false otherwise.
 */
bool in_friend_list(FriendNode *head, User *node) {
    for (FriendNode *cur = head; cur != NULL; cur = cur->next) {
        if (strcmp(cur->user->name, node->name) == 0) {
            return true;
        }
    }
    return false;
}

/**
 * Given the head of a linked list of BrandNode, this function checks if
 * a given brand's name exists in the list. Returns true if the brand's name
 * is found, and false otherwise.
 *
 * @param head Pointer to the head of the linked list of BrandNode.
 * @param name Pointer to the brand name to be searched in the list.
 * @return true if the brand's name exists in the list, false otherwise.
 */
bool in_brand_list(BrandNode *head, char *name) {
    for (BrandNode *cur = head; cur != NULL; cur = cur->next) {
        if (strcmp(cur->brand_name, name) == 0) {
            return true;
        }
    }
    return false;
}

/**
 * Given the head of a linked list of FriendNode, this function inserts
 * a given user into the linked list in alphabetical order of names. If
 * the user already exists, no modifications are made and the original
 * list is returned. Returns the head of the new linked list after insertion.
 *
 * @param head Pointer to the head of the linked list of FriendNode.
 * @param node Pointer to the user to be inserted into the list.
 * @return Pointer to the head of the new linked list after insertion.
 */
FriendNode *insert_into_friend_list(FriendNode *head, User *node) {
    if (node == NULL) return head;

    if (in_friend_list(head, node)) {
        printf("User already in list\n");
        return head;
    }

    FriendNode *fn = calloc(1, sizeof(FriendNode));
    fn->user = node;
    fn->next = NULL;

    if (head == NULL) return fn;

    if (strcmp(head->user->name, node->name) > 0) {
        fn->next = head;
        return fn;
    }

    FriendNode *cur;
    for (cur = head;
         cur->next != NULL && strcmp(cur->next->user->name, node->name) < 0;
         cur = cur->next)
        ;

    fn->next = cur->next;
    cur->next = fn;

    return head;
}

/**
 * Given the head of a linked list of BrandNode, this function inserts
 * a given brand into the linked list in alphabetical order of names. If
 * the brand already exists, no modifications are made and the original
 * list is returned. Returns the head of the new linked list after insertion.
 *
 * @param head Pointer to the head of the linked list of BrandNode.
 * @param node Pointer to the brand name to be inserted into the list.
 * @return Pointer to the head of the new linked list after insertion.
 */
BrandNode *insert_into_brand_list(BrandNode *head, char *node) {
    if (node == NULL) return head;

    if (in_brand_list(head, node)) {
        printf("Brand already in list\n");
        return head;
    }

    BrandNode *fn = calloc(1, sizeof(BrandNode));
    strcpy(fn->brand_name, node);
    fn->next = NULL;

    if (head == NULL) return fn;

    if (strcmp(head->brand_name, node) > 0) {
        fn->next = head;
        return fn;
    }

    BrandNode *cur;
    for (cur = head;
         cur->next != NULL && strcmp(cur->next->brand_name, node) < 0;
         cur = cur->next);

    fn->next = cur->next;
    cur->next = fn;

    return head;
}

/**
 * Given the head of a linked list of FriendNode, this function removes
 * a given user from the linked list. If the user does not exist in the list,
 * no modifications are made and the original list is returned. Returns the
 * head of the new linked list after deletion.
 *
 * @param head Pointer to the head of the linked list of FriendNode.
 * @param node Pointer to the user to be removed from the list.
 * @return Pointer to the head of the new linked list after deletion.
 */
FriendNode *delete_from_friend_list(FriendNode *head, User *node) {
    if (node == NULL) return head;

    if (!in_friend_list(head, node)) {
        printf("User not in list\n");
        return head;
    }

    if (strcmp(head->user->name, node->name) == 0) {
        FriendNode *temp = head->next;
        free(head);
        return temp;
    }

    FriendNode *cur;
    for (cur = head; cur->next->user != node; cur = cur->next)
        ;

    FriendNode *temp = cur->next;
    cur->next = temp->next;
    free(temp);

    return head;
}

/**
 * Given the head of a linked list of BrandNode, this function removes
 * a given brand from the linked list. If the brand does not exist in the list,
 * no modifications are made and the original list is returned. Returns the
 * head of the new linked list after deletion.
 *
 * @param head Pointer to the head of the linked list of BrandNode.
 * @param node Pointer to the brand name to be removed from the list.
 * @return Pointer to the head of the new linked list after deletion.
 */
BrandNode *delete_from_brand_list(BrandNode *head, char *node) {
    if (node == NULL) return head;

    if (!in_brand_list(head, node)) {
        printf("Brand not in list\n");
        return head;
    }

    if (strcmp(head->brand_name, node) == 0) {
        BrandNode *temp = head->next;
        free(head);
        return temp;
    }

    BrandNode *cur;
    for (cur = head; strcmp(cur->next->brand_name, node) != 0; cur = cur->next)
        ;

    BrandNode *temp = cur->next;
    cur->next = temp->next;
    free(temp);

    return head;
}

/**
 * Given a user, this function prints their name, friends, and liked brands.
 *
 * @param user Pointer to the user whose data is to be printed.
 */
void print_user_data(User *user) {
    printf("User name: %s\n", user->name);

    printf("Friends:\n");
    for (FriendNode *f = user->friends; f != NULL; f = f->next) {
        printf("   %s\n", f->user->name);
    }

    printf("Brands:\n");
    for (BrandNode *b = user->brands; b != NULL; b = b->next) {
        printf("   %s\n", b->brand_name);
    }
}

/**
 * Given a brand name, this function returns the index of the brand inside
 * the brand_names array. If the brand doesn't exist in the array, it
 * returns -1.
 *
 * @param name Pointer to the brand name.
 * @return The index of the brand in the brand_names array, or -1
 * if it doesn't exist.
 */
int get_brand_index(char *name) {
    for (int i = 0; i < MAT_SIZE; i++) {
        if (strcmp(brand_names[i], name) == 0) {
            return i;
        }
    }

    printf("Brand '%s' not found\n", name);
    return -1;  // Not found
}

/**
 * Given a brand name, this function prints its name, index inside the
 * brand_names array, and the names of other similar brands.
 *
 * @param brand_name Pointer to the brand name.
 */
void print_brand_data(char *brand_name) {
    int idx = get_brand_index(brand_name);
    if (idx < 0) {
        printf("Brand '%s' not in the list.\n", brand_name);
        return;
    }

    printf("Brand name: %s\n", brand_name);
    printf("Brand idx: %d\n", idx);

    printf("Similar brands:\n");
    for (int i = 0; i < MAT_SIZE; i++) {
        if (brand_adjacency_matrix[idx][i] == 1 &&
            strcmp(brand_names[i], "") != 0) {
            printf("   %s\n", brand_names[i]);
        }
    }
}

/**
 * Given a file name, this function reads from the file and populates the brand
 * list and brand matrix.
 *
 * @param file_name Pointer to the name of the file to be read.
 */
void populate_brand_matrix(char *file_name) {
    // Read the file
    char buff[MAX_STR_LEN];
    FILE *f = fopen(file_name, "r");
    fscanf(f, "%s", buff);
    char *line = buff;
    // Load up the brand_names matrix
    for (int i = 0; i < MAT_SIZE; i++) {
        if (i == MAT_SIZE - 1) {
            strcpy(brand_names[i], line);
            break;
        }
        int index = strchr(line, ',') - line;
        strncpy(brand_names[i], line, index);
        line = strchr(line, ',') + sizeof(char);
    }
    // Load up the brand_adjacency_matrix
    for (int x = 0; x < MAT_SIZE; x++) {
        fscanf(f, "%s", buff);
        for (int y = 0; y < MAT_SIZE; y++) {
            int value = (int)buff[y * 2];
            if (value == 48) {
                value = 0;
            } else {
                value = 1;
            }
            brand_adjacency_matrix[x][y] = value;
        }
    }
}

/**
 * Given a name, this function creates a new user on the platform. The user is
 * then inserted into the allUsers linked list. If a user already existed with
 * the same name, no action is taken, and NULL is returned instead.
 *
 * @param name Pointer to the name of the user to be created.
 * @return Pointer to the created user, or NULL if a user with
 * the same name already exists.
 */
User *create_user(char *name) {
    // TODO: Complete this function.

    if (name == NULL) {
        return NULL; // Sanity check 
    }

    FriendNode* current_node = allUsers;
    while (current_node != NULL) {
        if (strcmp(current_node->user->name, name) == 0) {
            return NULL; // User with the same name already exists
        }
        current_node = current_node->next;
    }
    User* new_user = malloc(sizeof(User));

    if (new_user == NULL) {
        return NULL; // No more memory available
    }

    strcpy(new_user->name, name);
    new_user->brands = NULL;
    new_user->friends = NULL;
    new_user->visited = false;

    FriendNode* current_address = allUsers; 
    FriendNode* previous_address = NULL;

    while (current_address != NULL && strcmp(current_address->user->name, name) < 0)  {// Check for alphabetic orders
        previous_address = current_address;
        current_address = current_address->next;
    }
    // Add to our allUsers linked list
    FriendNode* new_node = malloc(sizeof(FriendNode));
    if (new_node == NULL) { // No more memory available
        free(new_user);
        return NULL;
    }
    new_node->user = new_user;
   
   if (previous_address == NULL) {
        // Insert at the beginning of the list
        new_node->next = allUsers;
        allUsers = new_node;
    } else {
        // Insert in the middle or end of the list
        new_node->next = previous_address->next;
        previous_address->next = new_node;
    }

    return new_user;
}

/**
 * Removes a given user from the platform. The user is removed from the allUsers
 * linked list and the friend lists of any users that they belong to. Returns 0
 * if the user was successfully removed. If the user does not exist, returns -1
 * instead.
 *
 * @param user Pointer to the user to be removed.
 * @return 0 if the user was successfully removed,
 * -1 if the user does not exist.
 */
int delete_user(User *user) {
    // TODO: Complete this function.
    if (user == NULL) {
        return -1; // Sanity check
    }
    FriendNode* previous_address = NULL;
    FriendNode* current_address = allUsers;

    while (current_address != NULL && current_address->user != user) {
        previous_address = current_address;
        current_address = current_address->next;
    }

    if (current_address == NULL) {
        return -1; // User doesn't exist
    }

    // Remove the user from the allUsers linked list
    if (previous_address != NULL) {
        previous_address->next = current_address->next;
    } else {
        allUsers = current_address->next;
    }

    // Free the memory of the user
    free(current_address->user);

    // Free the memory of the friend node
    FriendNode *temp = current_address->user->friends;
    while (temp != NULL) {
        FriendNode *next = temp->next;
        free(temp);
        temp = next;
    }
    free(current_address);
    return 0;
}

/**
 * Given a pair of valid users, this function creates a friendship between them.
 * The user's friends list must remain in alphabetical order. Returns 0 if the
 * friendship was successfully created. Returns -1 if the pair were already
 * friends.
 *
 * @param user Pointer to the user initiating the friendship.
 * @param friend Pointer to the user to be added as a friend.
 * @return 0 if the friendship was successfully created,
 * -1 if the pair were already friends.
 */
int add_friend(User *user, User *friend) {
    // TODO: Complete this function.
   if (user == NULL || friend == NULL) {
        return -1; // Sanity check 
    }

    if (in_friend_list(user->friends, friend) || in_friend_list(friend->friends, user)) {
        return -1; // They're already friends
    }

    FriendNode* new_friend = malloc(sizeof(FriendNode));
    if (new_friend == NULL) {
        return -1; // Memory unavailable
    }
    new_friend->user = friend;
    new_friend->next = NULL;

    FriendNode* new_friend_friend = malloc(sizeof(FriendNode));
    if (new_friend_friend == NULL) {
        free(new_friend);
        return -1; // Memory unavailable
    }
    new_friend_friend->user = user;
    new_friend_friend->next = NULL;

    // If the user has no friends yet, insert the new friend as the first friend
    if (user->friends == NULL || strcmp(user->friends->user->name, friend->name) > 0) {
        new_friend->next = user->friends;
        user->friends = new_friend;
    } else {
        // Find alphabetic position to be inserted
        FriendNode* current_friend_user = user->friends;
        while (current_friend_user->next != NULL && strcmp(current_friend_user->next->user->name, friend->name) < 0) {
            current_friend_user = current_friend_user->next;
        }

        // Insert the new friend node into the user's friend list
        new_friend->next = current_friend_user->next;
        current_friend_user->next = new_friend;
    }

    // If the user has no friends, insert the Friend node
    if (friend->friends == NULL || strcmp(friend->friends->user->name, user->name) > 0) {
        new_friend_friend->next = friend->friends;
        friend->friends = new_friend_friend;
    } else {
        // Find the correct alphabetic position
        FriendNode* current_friend_friend = friend->friends;
        while (current_friend_friend->next != NULL && strcmp(current_friend_friend->next->user->name, user->name) < 0) {
            current_friend_friend = current_friend_friend->next;
        }
        // Insert the new friend node into the friend's friend list
        new_friend_friend->next = current_friend_friend->next;
        current_friend_friend->next = new_friend_friend;
    }

    return 0; // Successfully friended
}

/**
 * Given a pair of valid users, this function removes their friendship. The
 * user's friends list must remain in alphabetical order. Returns 0 if the pair
 * are no longer friends. Returns -1 if the pair were not friends to begin with.
 *
 * @param user Pointer to the user initiating the removal of friendship.
 * @param friend Pointer to the user to be removed as a friend.
 * @return 0 if the friendship was successfully removed,
 * -1 if the pair were not friends.
 */
int remove_friend(User *user, User *friend) {
    // TODO: Complete this function.
    if (user == NULL || friend == NULL) {
        return -1; // Sanity check 
    }

    if (!in_friend_list(user->friends, friend) || !in_friend_list(friend->friends, user)) {
        return -1; // They were never friends anyways 
    }

    FriendNode* current_friend = user->friends;
    FriendNode* old_friend = NULL;

    while (current_friend != NULL && current_friend->user != friend) { // Find the position of our friend in our list
        old_friend = current_friend;
        current_friend = current_friend->next;
    }

    if (old_friend == NULL) { // Our friend to be removed is the first friend in the list
        user->friends = current_friend->next;
    }
     else {
        // Friend to be removed is not the first friend in the list
        old_friend->next = old_friend->next;
    }
    free(current_friend);

    // Remove user from friend's friend list
    FriendNode *current_friend_friend = friend->friends;
    FriendNode *previous_friend_friend = NULL;

    while (current_friend_friend != NULL && current_friend_friend->user != user) {
        previous_friend_friend = current_friend_friend;
        current_friend_friend = current_friend_friend->next;
    }
    if (previous_friend_friend == NULL) {
        // User to be removed is the first friend in the list
        friend->friends = current_friend_friend->next;
    } else {
        // User to be removed is not the first friend in the list
        previous_friend_friend->next = current_friend_friend->next;
    }
    free(current_friend_friend);

    return 0; // Successfully unfriended 
}

/**
 * Given a valid user and the name of a brand, this function creates a link
 * between the user and the brand. The user's brands list must remain in
 * alphabetical order. Returns 0 if the link was successfully created. Returns
 * -1 if the link already existed or if the brand name is invalid.
 *
 * @param user Pointer to the user.
 * @param brand_name Pointer to the name of the brand to follow.
 * @return 0 if the link was successfully created,
 * -1 if the link already existed or the brand name is invalid.
 */
int follow_brand(User *user, char *brand_name) {
    // TODO: Complete this function.
    if (user == NULL || brand_name == NULL) {
        return -1; // Invalid
    }
    if (in_brand_list(user->brands, brand_name)) {
        return -1; // Already followed
    }

    user->brands = insert_into_brand_list(user->brands, brand_name);

    if (user->brands == NULL) {
        return -1; // Unsuccessful follow due to memory issues
    }

    return 0; // Successfully followed
}

/**
 * Given a valid user and the name of a brand, this function removes the link
 * between the user and the brand. The user's brands list must remain in
 * alphabetical order. Returns 0 if the link was successfully removed. Returns
 * -1 if the link did not previously exist or if the brand name is invalid.
 *
 * @param user Pointer to the user.
 * @param brand_name Pointer to the name of the brand to unfollow.
 * @return 0 if the link was successfully removed, -1 if the link did not
 * previously exist or the brand name is invalid.
 */
int unfollow_brand(User *user, char *brand_name) {
    // TODO: Complete this function.
    if (user == NULL || brand_name == NULL) {
        return -1; // Invalid 
    }

    if (!in_brand_list(user->brands, brand_name)) {
        return -1; // Not in the brand list
    }

    user->brands = delete_from_brand_list(user->brands, brand_name);

    return 0;
}

/**
 * Given a pair of valid users, this function returns the number of mutual
 * friends between them. A mutual friend is a user that exists in the friends
 * list of both User a and User b.
 *
 * @param a Pointer to the first user.
 * @param b Pointer to the second user.
 * @return The number of mutual friends between the two users.
 */
int get_mutual_friends(User *a, User *b) {
    // TODO: Complete this function.
    if (a == NULL || b == NULL) {
        return 0; // Invalid 
    }

    int count = 0;
    FriendNode* a_friends = a->friends;

    while (a_friends != NULL) { 
        if (in_friend_list(b->friends, a_friends->user)) { // Find our mutual friends 
            count++;
        }
        a_friends = a_friends->next; // Iterate to next
    }
    return count;
}
// Employs depth first search on our user to find the connections using a current user to find it's target and the depth of our graph.
int dfs(User* current, User* target, int depth) {
    // We mark our user as visited
    current->visited = true;

    // If current user is what we want, return the depth
    if (current == target) {
        return depth;
    }

    // Iterate through current user's friends
    FriendNode *current_friend = current->friends;
    while (current_friend != NULL) {
        // If friend has not been visited, recursively call DFS
        if (!current_friend->user->visited) {
            int result = dfs(current_friend->user, target, depth + 1);
            if (result != -1) {
                return result; // Return depth if target is found in the subtree
            }
        }
        current_friend = current_friend->next;
    }
    // Not found
    return -1;
}

/**
 * Given a pair of valid users, this function returns the degree of connection
 * between both users. The degree of connection is the shortest number of steps
 * it takes to get from one user to the other. If a connection cannot be formed,
 * returns -1.
 *
 * @param a Pointer to the first user.
 * @param b Pointer to the second user.
 * @return The degree of connection between the two users, or -1 if no
 * connection can be formed.
 */
int get_degrees_of_connection(User *a, User *b) {
    // TODO: Complete this function.
    if (a == NULL || b == NULL || !in_friend_list(a->friends, b) || !in_friend_list(b->friends, a)) {
        return -1; // Invalid
    }
    if (a->friends->next == NULL && b->friends->next == NULL && strcmp(a->friends->user->name,b->friends->user->name) == 0) { // They're the only people in their friend lists
        return 1;
    }
    if (a->friends->user == NULL || b->friends->user == NULL) { // They have no friends 
        return -1;
    }

    if (a == b) {
        return 0; // They are the same user
    }

    FriendNode *current_user = allUsers;
    while (current_user != NULL) {
        current_user->user->visited = false;
        current_user = current_user->next;
    }

    // Use our Depth-first search algorithm to find the connections
    return dfs(a, b, 0);
}

/**
 * Given two brand names, this function marks the two brands as similar in the
 * brand_adjacency_matrix variable. If either brand name is invalid, no action
 * is taken.
 *
 * @param brandNameA Pointer to the first brand name.
 * @param brandNameB Pointer to the second brand name.
 */
void connect_similar_brands(char *brandNameA, char *brandNameB) {
    // TODO: Complete this function.
    if (brandNameA == NULL || brandNameB == NULL) {
        return; // Invalid
    }

    int brand_a = get_brand_index(brandNameA);
    int brand_b = get_brand_index(brandNameB);

    if (brand_a == -1 || brand_b == -1) {
        return; // Invalid names
    }

    brand_adjacency_matrix[brand_a][brand_b] = 1;
    brand_adjacency_matrix[brand_b][brand_a] = 1; // Mark the indexes in our adjacency matrix

    return;
}

/**
 * Given two brand names, this function marks the two brands as different (not
 * similar) in the brand_adjacency_matrix variable. If either brand name is
 * invalid, no action is taken.
 *
 * @param brandNameA Pointer to the first brand name.
 * @param brandNameB Pointer to the second brand name.
 */
void remove_similar_brands(char *brandNameA, char *brandNameB) {
    // TODO: Complete this function.
    if (brandNameA == NULL || brandNameB == NULL) {
        return; // Sanity check
    }

    int brand_a = -1;
    int brand_b = -1;

    for (int i = 0; i < MAT_SIZE; i++) {
        if (strcmp(brand_names[i], brandNameA) == 0) {
            brand_a = i;    // Find our brand position for A
        }
        if (strcmp(brand_names[i], brandNameB) == 0) {
            brand_b = i;    // Find our brand position for B 
        }
        if (brand_a == -1 || brand_b == -1) {
            return; // Not found
        }
    }
    brand_adjacency_matrix[brand_a][brand_b] = 0;
    brand_adjacency_matrix[brand_b][brand_a] = 0; // Mark the indexes in our adjacency matrix
    return;
}
// Returns the mutual brand count of two users. -1 if invalid.
int get_mutual_brand_count(User* a, User* b) {
    if (a == NULL || b == NULL) {
        return -1; // Sanity check
    }
    int mutual_count = 0;

    for (BrandNode* brand_a = a->brands; brand_a != NULL; brand_a = brand_a->next) {
        // Check if the brand exists in brand b's list
        if (in_brand_list(b->brands, brand_a->brand_name)) {
            mutual_count++; // If found
        }
    }
    return mutual_count;
}

/**
 * Given a user, suggest a new friend for them.
 *
 * To find the best match, the new suggested friend should have the highest
 * number of mutually liked brands amongst all other valid candidates.
 *
 * If a tie needs to be broken, select the user with the name that comes first
 * in reverse-alphanumerical order.
 *
 * The suggested friend must be a valid user, cannot be the user themself, nor
 * cannot be someone that they're already friends with.
 *
 * If the user is already friends with everyone on the platform, returns NULL.
 *
 * At times, a similarity rating of 0 is the best option.
 *
 * @param user Pointer to the user for whom a friend is being suggested.
 * @return Pointer to the suggested friend, or NULL if no suitable friend is
 * found.
 */
User *get_suggested_friend(User *user) {
    // TODO: Complete this function.
    if (user == NULL) {
        return NULL; // Sanity check
    }
    User* suggested_friend = NULL;
    int max_mutual_brands = -1;

    // Iterate through all users
    FriendNode* current_address = allUsers;
    while (current_address != NULL) {
        User* potential_friend = current_address->user;

        // Skip the input user, already friends, and already suggested friend
        if (potential_friend != user && !in_friend_list(user->friends, potential_friend)) {
            int mutualBrands = get_mutual_brand_count(user, potential_friend);

            // Update the suggested friend if necessary
            if (mutualBrands > max_mutual_brands ||
                (mutualBrands == max_mutual_brands &&
                 strcmp(potential_friend->name, suggested_friend->name) > 0)) {
                suggested_friend = potential_friend;
                max_mutual_brands = mutualBrands;
            }
        }
        current_address = current_address->next;
    }

    return suggested_friend;
}

/**
 * Given a user and a positive integer n, this function adds n suggested friends
 * using the get_suggested_friend() function. There might not be enough users on
 * the platform to satisfy n completely, so it returns the amount of friends
 * successfully added.
 *
 * @param user Pointer to the user for whom suggested friends are being added.
 * @param n The number of suggested friends to add.
 * @return The number of friends successfully added.
 */
int add_suggested_friends(User *user, int n) {
    // TODO: Complete this function.
    if (user == NULL || n < 0) {
        return -1; // Sanity check
    }
    if (n == 0) {
        return 0; // We don't want to suggest any friends in this case
    }

    int suggested_friends = 0;

    while (suggested_friends < n) {
        User* new_friend = get_suggested_friend(user);
        
        if (new_friend == NULL) {
            break; // We have reached the limit of suggested friends than our n times, escape
        }
        
        if (add_friend(user, new_friend) == 0) {
            suggested_friends++; // Our friendship was successful 
        }

    }
    return suggested_friends;
}

/**
 * Given a user and a positive integer n, this function suggests and follows n
 * new brands for them.
 *
 * To find the best matches, suggested brands have the most similarities with
 * the brands that the user already follows.
 *
 * If a tie needs to be broken, the brands with the names that comes first in
 * reverse-alphanumerical order is selected.
 *
 * The suggested brand must be a valid brand and cannot be a brand that the user
 * already follows.
 *
 * There might not be enough brands on the platform to satisfy n completely, so
 * the function returns the amount of brands successfully followed.
 *
 * At times, a similarity rating of 0 is the best option.
 *
 * @param user Pointer to the user for whom brands are being suggested.
 * @param n The number of suggested brands to follow.
 * @return The number of brands successfully followed.
 */
int follow_suggested_brands(User *user, int n) {
    // TODO: Complete this function.
    if (user == NULL || n < 0) {
        return -1; // Invalid inputs
    }

    if (n == 0) {
        return 0; // We aren't finding any suggested brands
    }

    int suggested_brands = 0;

    while (suggested_brands < n) {  
        int max_similar_brands = -1;
        char* suggested_brand_name = NULL;

        for (int i = 0; i < MAT_SIZE; i++) {
            // If the user already follows the brand
            if (!in_brand_list(user->brands, brand_names[i])) {
                int similar_brands = 0;
                // Check for similarities of those already followed
                for (BrandNode* b = user->brands; b != NULL; b = b->next) {
                    if (brand_adjacency_matrix[i][get_brand_index(b->brand_name)] == 1) {
                        similar_brands++;
                    }
                }
                // Update suggested brand if needed 
                if (similar_brands > max_similar_brands ||
                    (similar_brands == max_similar_brands &&
                     (suggested_brand_name == NULL || strcmp(brand_names[i], suggested_brand_name) > 0))) {
                    max_similar_brands = similar_brands;
                    suggested_brand_name = brand_names[i];
                }
            }
        }
        // Once there are no more suggested brands for the user
        if (suggested_brand_name == NULL) {
            break;
        }
        // Follow the suggested brand
        if (follow_brand(user, suggested_brand_name) == 0) {
            suggested_brands++;
        }
    }
    return suggested_brands; // Successful
}