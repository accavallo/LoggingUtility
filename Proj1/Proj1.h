//
//  Proj1.h
//  Proj1
//  $Author: o3-cavallo $
//  $Date: 2016/09/18 20:04:18 $
//  $Log: Proj1.h,v $
//  Revision 1.6  2016/09/18 20:04:18  o3-cavallo
//  Added stdlib.h to a different header file
//
//  Created by Tony on 9/7/16.
//  Copyright © 2016 Anthony Cavallo. All rights reserved.
//  This is the main header file for Project 1. It contains other header files that are necessary for me to run everything I need to in my program.

#ifndef Proj1_h
#define Proj1_h

#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <getopt.h>
#include <stdarg.h>
#include "logger.h"

void printUsage();
void getoptError(char*, const char*);
void logRandomMessages(char*);

#endif /* Proj1_h */
