#include <stdio.h>
#include <stdlib.h>
#include "math.h"

int main(int argc, char** argv){
    int a = 2, b = 3;
    if(argc >= 3){
        a = atoi(argv[1]);
        b = atoi(argv[2]);
    }
    printf("add(%d,%d) = %d\n", a, b, add(a,b));
    return 0;
}
