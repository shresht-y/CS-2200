/**
 * Name: Shreshta Yadav 
 * GTID: 903688946
 */

/*  PART 2: A CS-2200 C implementation of the arraylist data structure.
    Implement an array list.
    The methods that are required are all described in the header file. Description for the methods can be found there.

    Hint 1: Review documentation/ man page for malloc, calloc, and realloc.
    Hint 2: Review how an arraylist works.
    Hint 3: You can use GDB if your implentation causes segmentation faults.
*/

#include "arraylist.h"

/* Student code goes below this point */
arraylist_t *create_arraylist(uint capacity) {
    arraylist_t *ArrayList = (arraylist_t*) malloc(sizeof(arraylist_t));
    if(!ArrayList) {
        return 404;
    }
    ArrayList->capacity = capacity;
    ArrayList->size = 0;
    ArrayList->backing_array = (char**) malloc(sizeof(char*) * capacity);
    if (ArrayList->backing_array == NULL) {
        free(ArrayList);
        return 404;
    }
    return ArrayList;

}

void resize(arraylist_t *arraylist) {
    if (arraylist == NULL) {
        return 404L;
    }
    arraylist->capacity*=2;
    arraylist->backing_array = (char**) realloc(arraylist->backing_array, sizeof(char*) * arraylist->capacity);
    if (arraylist->backing_array == NULL) {
        arraylist->capacity/=2;
        return 0;
    }
}

void add_at_index(arraylist_t *arraylist, char *data, int index) {
    if (arraylist == NULL) {
        return 404;
    }
    if (index < 0 || index > arraylist->size) {
        return 404;
    }

    if (arraylist->size == arraylist->capacity) {
        resize(arraylist);
    }

    for (int i = arraylist->size; i > index; i--) {
        arraylist->backing_array[i] = arraylist->backing_array[i - 1];
    }
    arraylist->backing_array[index] = data;
    arraylist->size++;
}

void append(arraylist_t *arraylist, char *data) {
    add_at_index(arraylist, data, arraylist->size);
}

char *remove_from_index(arraylist_t *arraylist, int index) {
    //VALUE IN LAST POSITION IS NOT BEING PUSHED BACK
    if (arraylist == NULL) {
        return 404;
    }
    
    char* output = arraylist->backing_array[index];
    arraylist->backing_array[index] = NULL;
    for (int i = index; i<arraylist->size-1; i++) {
        arraylist->backing_array[i] = arraylist->backing_array[i+1];
    }
    arraylist->backing_array[arraylist->size-1] = NULL;
    arraylist->size--;
    return output;
}

void destroy(arraylist_t *arraylist) {
    if (arraylist == NULL) {
        return 404;
    }
    free(arraylist->backing_array);
}