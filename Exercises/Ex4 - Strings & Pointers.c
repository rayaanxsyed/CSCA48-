/**
 * Exercise 4 - Strings & POinters
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 */

// #############################################################################
// # READ THIS! READ THIS! READ THIS!
// #############################################################################
// No additional imports are allowed. You can make helper functions if you wish.
// Importing other header files will result in an automatic fail.
// Using any array notations "[]" outside of main() will result in an automatic fail.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Function: reverse
 * -----------------
 * Reverse a given string in-place. This means that the reversed string should
 * replace the original.
 *
 * string: the string to reverse
 */

int length(char* string) {
    char *size = string; 
    int count = 0;

    while (*size != '\0') {
        count++; 
        size++;
    }
    return count;
}
void reverse(char* string) {
    // TODO: Complete this function.
    int count = length(string);
    char* begin_pointer = string;
    char* end_pointer = string + count -1;

    while (begin_pointer < end_pointer) {
        char ch = *end_pointer; 
        *end_pointer = *begin_pointer; 
        *begin_pointer = ch; 

        begin_pointer++; 
        end_pointer--;
    }
    return;
    }

/**
 * Function: replace_all
 * -----------------
 * Given a source string, replace all occurrences of a specified substring with
 * another string and write the resulting string to the destination.
 *
 * source: the input string to be replaced
 * dest: the location to write the replaced string to
 * find: the substring to be replaced
 * replace: the string to replace occurrences of "find" with
 */
void replace_all(char* source, char* dest, char* find, char* replace) {
    // TODO: Complete this function.
    *dest = '\0';
    int MAX_LENGTH = 1024;

    int count_source = length(source);
    int count_find = length(find);
    int count_replace = length(replace);
    
    int counter = 0;

    for (int i = 0; i <= count_source && i < MAX_LENGTH; i++) {

        int j=0;
		// finding
		for (j=0;j<count_find;j++) {
			
			if (*(find+j) == *(source+i)) {
				
                i++;
			}
			else {
				break;
			}
		}
        // replacing
		if (j==count_find) {
		
			for (j=0;j<count_replace && counter < MAX_LENGTH ;j++) {
				
				*(dest+counter) = *(replace+j);
                counter++;
			}
			
		}
        if (counter < MAX_LENGTH) {
            *(dest+counter)= *(source+i);
            counter++;
        }
    }
    if (counter < MAX_LENGTH) {
        *(dest+counter)='\0';
    }
    else {

        *(dest + MAX_LENGTH -1) = '\0';
    }
    return;
    }

// ===========================================================================
// DO NOT CHANGE ANY 'ifndef' AND 'endif' MACROS.
// These macros help ensure your parts of your code does not conflict with the
// automarker. Changing them will result in your code not compiling and you
// receiving a 0 for the entire assignment.
// ===========================================================================
#ifndef __testing__

void test_reverse() {
    char string[1024] =
        "!dekrow evah yam noitcnuf ruoy ekil skooL ?ylraelc siht daer uoy naC";
    printf("String: %s\n", string);

    reverse(string);

    // "Can you read this clearly? Looks like your function may have worked!"
    printf("Reversed String: %s\n", string);
}

void test_replace_all() {
    char source[1024] = "the quick brown fox jumps over the lazy dog";
    printf("Source: %s\n", source);

    char dest[1024];
    replace_all(source, dest, "the", "a");

    // "a quick brown fox jumps over a lazy dog"
     printf("Dest: %s\n", dest);
}

int main() {
    // Testing reverse() function.
    printf("Calling test_reverse() ...\n");
    test_reverse();

    // Testing test_replace_all() function.
    printf("Calling test_replace_all() ...\n");
    test_replace_all();
    return 0;
}

#endif
