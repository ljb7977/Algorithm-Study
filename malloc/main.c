#include <stdio.h>

int main() {
    void *p = malloc(1);
    void *q = malloc(1);
    printf("%p %p", p, q);
    return 0;
}