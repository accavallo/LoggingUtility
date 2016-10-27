//  logger.c
//  Proj1
//  $Author: o3-cavallo $
//  $Date: 2016/09/18 20:05:23 $
//  $Log: logger.c,v $
//  Revision 1.6  2016/09/18 20:05:23  o3-cavallo
//  Tried some other random things, still no reason why my string is printing random garbage in two spots, and only two spots, when getlog() is called. There is absolutely no reason for it. My professor still hasn't answered my emails either, and it's been 4 days this time.
//
//  Created by Tony on 9/1/16.
//  Copyright © 2016 Anthony Cavallo. All rights reserved.
//  This code is straigt from the book "UNIX Systems Programming" on page 56. As instructed by my professor, I have included the code from the book for my project. That code was only the method definitions, everything inside each method I have produced on my own.

#include "logger.h"

typedef struct list_struct {
    data_t item;
    struct list_struct *next;
} log_t;

static log_t *headptr = NULL;
static log_t *tailptr = NULL;

//The error log, or message log, or whatever it is, is apparently only saved locally until we actually save it to a file. Thus, we have to create a linked list of all the messages that are added. This method is supposed to return -1 if it fails and 0 if it succeeds.
int addmsg(data_t data) {
    if (data.dataString == NULL) {
        printf("Error:\tNo data string\n");
	errno = ENOENT;
        return -1;
    }
    
    
    log_t *newNode = malloc(sizeof(log_t));
    if (newNode == NULL) {
        printf("Error:\tNode was not created\n");
	errno = ENOENT;
        return -1;
    }
    newNode->item = *(data_t*)malloc(sizeof(data_t));

    newNode->item.dataString = malloc(sizeof(char) * strlen(data.dataString));
    strncpy(newNode->item.dataString, data.dataString, strlen(data.dataString));
    newNode->next = NULL;
    
    if (!headptr) {
        headptr = newNode;
        tailptr = headptr;
    } else {
        tailptr->next = newNode;
        tailptr = tailptr->next;
    }
    printf("Message successfully added\n");
    return 0;
}

//This method clears the entire list of messages.
void clearlog(void) {
    printf("Clearing log\n");
    log_t *delNode = headptr;
    while(delNode) {
        log_t *ptr = delNode->next;
        free(delNode);
        delNode = ptr;
    }
    headptr = NULL;
    tailptr = NULL;
    delNode = NULL;
}

//Method to go through the entire list of messages and display them.
char *getlog(void) {
    char *log = malloc(sizeof(char*));
    if (headptr) {
        printf("Retrieving log:\n");
        log_t *ptr = headptr;
        while (ptr) {
	    log = realloc(log, strlen(log) + strlen(ptr->item.dataString));
            strcat(log, ptr->item.dataString);
            ptr = ptr->next;
        }
	ptr = NULL;
    } else {
	errno = ENOENT;
        return NULL;
    }
    
    return log;
}

//Method to save the entire contents of the message list to a file.
int savelog(char *filename) {
    printf("Saving to file %s\n", filename);
    
    FILE *file;
    file=fopen(filename, "a");
    if (file == NULL) {
	errno = ENOENT;
        return -1;
    }
    
    log_t *ptr = headptr;
    while (ptr) {
        fprintf(file, "%s", ptr->item.dataString);
        ptr = ptr->next;
    }
    fclose(file);
    printf("Log successfully saved\n");
    return 0;
}
