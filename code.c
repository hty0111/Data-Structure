#include <stdio.h>
int a = 5;

void print()
{
    printf( "%d", a );
}

int main(void)
{
    printf( "%d\n", a );
    float a = 3.14;
    printf( "%f\n", a );
    print();
}