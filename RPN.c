#include <stdio.h>
#include "stack.h"
#include "stack.c"

#define MAXBUFFER 10

int main(void)
{
    Stack s;
    char c;
    
    InitStack( &s );
    puts( "Enter in RPN, put 'space' in each num, # to qiut:" );
    scanf( "%c", &c );
    double d, e;
    char str[MAXBUFFER];
    int i = 0;

    while( c != '#' )
    {
        while( isdigit(c) || c == '.')
        {
            str[i++] = c;
            str[i] = '\0';
            if( i >= 10 )
            {
                puts( "Too big." );
                return -1;
            }
            scanf( "%c", &c );
            if( c == ' ' )
            {
                d = atof(str);
                Push( &s, d );
                i = 0;
                break;
            }
        }

        switch ( c )
        {
        case '+':
            Pop( &s, &e );
            Pop( &s, &d );
            Push( &s, d + e );
            break;
        case '-':
            Pop( &s, &e );
            Pop( &s, &d );
            Push( &s, d - e );
            break;
        case '*':
            Pop( &s, &e );
            Pop( &s, &d );
            Push( &s, d * e );
            break;
        case '/':
            Pop( &s, &e );
            Pop( &s, &d );
            if( e != 0 )
                Push( &s, d / e );
            else{
                puts( "Divisor is 0." );
                return -1;
            }    
            break;
        default:
            break;
        }
        scanf( "%c", &c );
    }
    
    Pop( &s, &d );
    printf( "Final: %.2f\n", d );

    return 0;
}