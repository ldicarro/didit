#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{

    struct stat st = {0};
    char *dir = argv[1];

    if(stat(dir,&st) == -1)
    {
        mkdir(dir,0744);
    }
    
    return 0;

}