#ifndef CLIT_H
#define CLIT_H

#include<stdio.h>
#include<stdlib.h>

#ifdef _WIN32
    #include <io.h>
    #include <direct.h>
    #define mkdir(path, mode) _mkdir(path) // Windows _mkdir doesn't take a mode
#else
    #include <unistd.h>
    #include <sys/stat.h>
#endif

int cmd_init(int argc, char *argv[]);

#endif