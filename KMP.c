#include <stdio.h>

void GetNext( char *str, int *next )
{
    int i = 1, j = 0;
    next[0] = next[1] = 0;
    while( i < str[0] )
    {
        if( j == 0 || str[i] == str[j] )
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
}

int main(void)
{
    int i;
    int next[10] = {};
    char str[] = " ababaaab";
    
    str[0] = 8;
    GetNext( str, next );
    
    for( i = 0; i <= str[0]; i++ )
    {
        printf( "%d ", next[i] );
    }
}