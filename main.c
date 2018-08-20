#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

int debug = 0;

int main(int argc, char** argv)
{
    extern char *optarg;
    extern int optind;
    int cursor; // where we are in the option loop
    int err = 0;
    int fflag = 0; // file flag
    char *mtext = "default message";
    char *home = getenv("HOME");
    char dname[255] = "Documents/diditfiles"; // hold the directory
    char fname[255]; // hold the file name
    static char usage[] = "usage: %s -f filename 'message'\n"; // printed when error
    time_t t = time(NULL);
    struct tm timeinfo = *localtime(&t);
    struct stat st = {0};

    while((cursor = getopt(argc, argv, "f:d:")) != -1)
    {
        switch(cursor)
        {
            case 'd':
                strcpy(dname,home);
                strcat(dname,"/");
                strcat(dname,optarg);
                break;
            case 'f':
                fflag = 1;
                snprintf(fname, sizeof fname,"%s%s",optarg,".txt");
                break;
            case '?':
                err = 1;
                break;
        }
    }

    if(fflag == 0)
    {
        fprintf(stderr, "%s: missing -f filename\n",argv[0]);
        err++;
    }
    
    if((optind + 1) > argc)
    {
        fprintf(stderr, "%s: missing message\n", argv[0]);
        err++;
    }
    else
    {
        mtext = argv[argc - 1];
    }
    
    
    if(err)
    {
        fprintf(stderr,usage,argv[0]);
        exit(1);
    }

    char *timestamp = ctime(&t);

    printf("fname = \"%s/%s\"\n", dname, fname);
    //printf("message = \"%s\"\n", mtext);
    //printf("timestamp = %s\n", timestamp);
    printf("entry = %s\t%s\n\n",timestamp,mtext);

    if(stat(dname, &st) == -1)
    {
        mkdir(dname, 0755);
    }

    char filePath[255];
    sprintf(filePath,"%s/%s",dname,fname);

    FILE *didfile = fopen(filePath, "a");

    if (didfile == NULL)
    {
        fprintf(stderr, "file could not be found\n");
        exit(-1);
    }

    fprintf(didfile,"%s\t%s\n\n", timestamp, mtext);

    return 0;
}