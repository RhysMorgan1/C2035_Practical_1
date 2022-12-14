/******** DO NOT EDIT THIS FILE ********/
/* This is application removes a named shared object (identified by its label),
 * Usage:
 *      ./rmsho [-s] label
 * where -s specifies the object is a semaphore
 */
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include "shobject_name.h"
#include "sim_config.h"

#define SEM         04
#define NAME_MASK   03

#define NBUF 32

int get_selector(int argc, char** argv) {
    int r = argc - 1;
    
    return (argc == 3 && strnlen(argv[1], 3) && strncmp(argv[1], "-s", 3) == 0)
            ? r | SEM : r;      
}

int main(int argc, char** argv) {
    if (argc < 2 || argc > 3) {
        printf("usage: %s [-s] label\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    int selector = get_selector(argc, argv);
    
    char name[MAX_NAME_SIZE];
    
    shobject_name(argv[selector & NAME_MASK], name);
    
    if (selector & SEM) {
        printf("unlinking sem: %s\n", name);
        sem_unlink(name);
    } else {
        printf("unlinking shm: %s\n", name);
        shm_unlink(name);
    }
    
    return EXIT_SUCCESS;
}
