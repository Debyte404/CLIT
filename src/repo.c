#include "clit.h"

int cmd_init(int argc, char *argv[]){
    if (mkdir(".clit", 0755) != 0) {
        perror("Error: Could not create .clit directory. It might already exist.\n");
        return 1;
    }

    // we gotta make objects,refs and refs/heads folder inside .clit

    // Grouped if else
    if (mkdir(".clit", 0755) != 0) { perror("base dir failed"); return 1; }
    if (mkdir(".clit/objects", 0755) != 0) { perror("objects dir failed"); return 1; }
    if (mkdir(".clit/refs", 0755) != 0) { perror("refs dir failed"); return 1; }

    // we also gotta make a HEAD file in .clit

    FILE *head = fopen(".clit/HEAD", "w");
    if (head == NULL) {
        perror("Error: Could not create HEAD file.\n");
        return 1;
    }

    // Write the reference pointer and close
    fprintf(head, "ref: refs/heads/main\n");
    fclose(head);

    printf("Initialized empty Clit repository in .clit/\n");
    return 0;
}