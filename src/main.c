#include "clit.h"

int main(int argc, char *argv[]){
    if (argc < 2) {
        printf("usage: clit <command> [args]\n");
        return 1;
    }

    if (strcmp(argv[1], "init") == 0) {
        return cmd_init(argc - 1, argv + 1);
    }
}