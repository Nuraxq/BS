#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "vector.h"
#include <stdbool.h>
#include <stdio.h>

static void* ptr = NULL;
static int _size = 0;
static int _sizePerUnit = 0;
static int count = 0;
static bool* bitmap; // Bool Array als sehr einfache Bitliste -> bissl uneffizient aber juckt nicht


void vec_init(size_t n, size_t size){
    bitmap = malloc(sizeof(bool) * n); 
    if (bitmap == NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++){
        bitmap[i] = false;
    }

    ptr = malloc(n * size);
    if (ptr == NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    _size = size*n;
    _sizePerUnit = size;
    count = n;
}

ssize_t vec_add(void *obj){
    size_t index = 0;
    // Freie Stelle finden

    char* free_space;

    for (int i = 0; i < count; i++){
        if (bitmap[i] == false){
            free_space = (char*)ptr + i*_sizePerUnit;
            bitmap[i] = true;
            memcpy(free_space,obj,_sizePerUnit);
            return i;
        }
    }
    return -1;
}

void *vec_get(size_t i){
    if (i >= (size_t)count || bitmap[i] == false ){
        return NULL;
    }
    return (void*) ((char*)ptr + (i*_sizePerUnit));
}

void vec_remove(size_t i){

    if(i >= (size_t)count){return;}

    memset((char*)ptr + (i*_sizePerUnit),0,_sizePerUnit);
    bitmap[i] = false;
}


void vec_destroy(){
    if (ptr) free(ptr);
    if (bitmap) free(bitmap);
}
