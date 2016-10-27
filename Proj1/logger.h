//
//  logger.h
//  Proj1
//  $Author: o3-cavallo $
//  $Date: 2016/09/18 20:04:18 $
//  $Log: logger.h,v $
//  Revision 1.5  2016/09/18 20:04:18  o3-cavallo
//  Added stdlib.h to a different header file
//
//  Created by Tony on 9/7/16.
//  Copyright © 2016 Anthony Cavallo. All rights reserved.
//

#ifndef logger_h
#define logger_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>

typedef struct data_struct {
    struct timespec time;
    char *dataString;
} data_t;

static char *fileName = "logfile.txt";

int addmsg(data_t data);
void clearlog(void);
char *getlog(void);
int savelog(char *filename);

#endif /* logger_h */
