#include "Cat.h"
#include <stdio.h>
void Cat::jump() {
    y++;
    printf("cat y: %i",y);
}
int Cat::getY() {
    return y;
}