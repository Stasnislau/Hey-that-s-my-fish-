#ifdef __APPLE__
    #include <sys/syscall.h>
#elif __linux__
    #include "syscalls.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char **argv) {
    FILE *fp = fopen("test_results.txt", "w");
    int t = atoi(argv[1]);
   
     
    char name[64];
    char call[128];   
    for (int i=0; i<t; ++i) {
        strcpy(call, "./random_test ");
        char seed[10];
        sprintf(seed,"%d",i+1);
        strcat(call, seed);
        strcat(call, " | ../output > ");
        char nbr[10];
        sprintf(nbr,"%d",i+1);
        strcpy(name, "./games/game");
        strcat(name, nbr);
        strcat(call, name);
        strcat(call, ".txt");
//        printf("%s\n",call);
        int status = system(call);
        fprintf(fp, "TEST #%d: %s\n", i+1, status ? "FAILED" : "OK");
        printf("TEST #%d: %s\n", i+1, status ? "FAILED" : "OK");
    }
    fclose(fp);
}

