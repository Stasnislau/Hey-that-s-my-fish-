#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv) {
    //int *seed;
    //*seed = 0;
    int seed = atoi(argv[1]);
    srand(seed);
    int players = 2;
    int penguins = 2;
    int xdim = rand()%(16-5+1) + 5; 
    int ydim = rand()%(16-5+1) + 5; 
    int bot = 1;
    int bot_level = 1;
    printf("%d\n",players);
    printf("%c\n",'a');
    printf("%d\n%d\n",bot,bot_level);


    printf("%d\n",players);
    printf("%c\n",'b');
    printf("%d\n%d\n",bot,bot_level);
    printf("%d\n",penguins);
    printf("%d\n%d\n",xdim,ydim);
}
