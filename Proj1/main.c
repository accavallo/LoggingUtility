//  main.c
//  Proj1
//  $Author: o3-cavallo $ Tony on 9/7/16.
//  $Date: 2016/09/18 20:05:23 $
//  $Log: main.c,v $
//  Revision 1.10  2016/09/18 20:05:23  o3-cavallo
//  Tried some other random things, still no reason why my string is printing random garbage in two spots, and only two spots, when getlog() is called. There is absolutely no reason for it. My professor still hasn't answered my emails either, and it's been 4 days this time.
//
//  Copyright © 2016 Anthony Cavallo. All rights reserved.
//  This is the main file for Project 1. The purpose of this project is to implement a logging tool or something to record errors, or something, and to show errors, I think, and maybe write something to a file, I'm overall not entirely sure. As it is right now, my project creates a linked list of messages. The messages themselves are of no value, but they contain the time since epoch in nanoseconds.

#include "Proj1.h"

int main(int argc, const char * argv[]) {
    int option, long_index = 0;
    unsigned int num = 42;
    char buff[200];
    memset(buff, '\0', sizeof(char)*200);
    
    opterr = 0;
    
    //getopt_long and getopt_long_only need an array of the whole words to look for and what variable they'll resolve to.
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };
    
    //This while loop with the getopt code is directly from the getopt manual. The only differences are the getopt_long_only with the necessary arguments and the actual cases.
    while ((option = getopt_long_only(argc, (char **)argv, "hn:l:", long_options, &long_index)) != -1) {
        switch (option) {
            case 'h':
                printUsage();
                break;
            case 'n':
                if (isdigit(*optarg)) {
                    printf("Setting number");
                    num = atoi(optarg);
                } else {
                    printf("Invalid argument for parameter '-n'.\nExpected Integer, found '%s' instead\n", optarg);//argv[optind-1]);
                    sprintf(buff, "Invalid argument for parameter '-n'.\nExpected Integer, found '%s' instead", optarg);
                    getoptError(buff, argv[0]);
                }
                break;
            case 'l':
                printf("Setting file name");
                fileName = optarg;
                break;
            case '?':
                if (optopt == 'l' || optopt == 'n') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                    sprintf(buff, "Option -%c requires an argument.", optopt);
                    getoptError(buff, argv[0]);
                }
                else if (isprint (optopt)) {
                    fprintf(stderr, "Unknown option '-%c'.\n", optopt);
                    sprintf(buff, "Unknown option '-%c'.", optopt);
                    getoptError(buff, argv[0]);
                }
                else {
                    fprintf(stderr, "Unknown option character '%s'.\n", argv[optind-1]);
                    sprintf(buff, "Unknown option character '%s'.", argv[optind-1]);
                    getoptError(buff, argv[0]);
                }
                //return 1;
            default:
                printUsage();
                //abort();
        }
    }
    //This remaining for loop goes through the entire argv array and keeps track of everything that wasn't used. It then prints out everything that wasn't an option.
    int index;
    int err = 0;
    for (index = optind; index < argc; index++) {
        sprintf(buff, "Non-option argument %s.", argv[index]);
        getoptError(buff, argv[0]);
        
        printf("Non-option argument %s.\n", argv[index]);
    }
    
    sprintf(buff, "The number is %i", num);
    logRandomMessages(buff);
    memset(buff, '\0', sizeof(char)*200);
    
    //The functions for the logger are called here.
    printf("%s\n", getlog());
    
    sprintf(buff, "This is a stupid message.");
    
    logRandomMessages(buff);
    err = savelog(fileName);
    if(err == -1)
        perror("File Save Error: ");
    
    printf("%s\n", getlog());
    clearlog();
    sprintf(buff, "This is another stupid message");
    logRandomMessages(buff);

    sprintf(buff, "This is a slightly less stupid message.");
    logRandomMessages(buff);
    err = savelog(fileName);
    if(err == -1)
        perror("File Save Error: ");
    
    sprintf(buff, "Stuff");
    logRandomMessages(buff);
    
    printf("%s\n", getlog());
    clearlog();
    
    return 0;
}

//Method to print the help message in case I need to use it more than the two times I have it already.
void printUsage () {
    printf("-h/-help displays this help message  \n**NOTE -help CANNOT have other options attached to it! i.e. -helpn 4 will not work!**\n");
    printf("-n x sets the Integer argument 'x' to the variable 'n'\n");
    printf("-l filename sets the filename to be used for the log file\n");
}

//Method to provide logging for Getopt errors.
void getoptError(char* errMsg, const char* file) {
    char buffer[200];
    memset(buffer, '\0', sizeof(char)*200);
    data_t *optionError = (data_t*)malloc(sizeof(data_t));
    clock_gettime(CLOCK_REALTIME, &optionError->time);
    unsigned long long time = optionError->time.tv_sec * 1000000000 + optionError->time.tv_nsec;
    sprintf(buffer, "%s:\t%llu\tGetopt Error: %s\n", file, time, errMsg);
    optionError->dataString = buffer;
    int err = addmsg(*optionError);
    if(err == -1)
        perror("Getopt Error: ");
    free(optionError);
}

void logRandomMessages(char* msg) {
    char buffer[200];
    memset(buffer, '\0', sizeof(char)*200);
    data_t *randomMessage = malloc(sizeof(data_t));
    clock_gettime(CLOCK_REALTIME, &randomMessage->time);
    unsigned long long time = randomMessage->time.tv_sec * 1000000000 + randomMessage->time.tv_nsec;
    sprintf(buffer, "Random Log Message:\t%llu\t%s\n", time, msg);
    randomMessage->dataString = buffer;
    int err = addmsg(*randomMessage);
    if(err == -1)
        perror("Log Error: ");
    free(randomMessage);
}
