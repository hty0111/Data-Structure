#include "stack.h"

#define INITSIZE 20
#define INCREASESIZE 10


void InitStack( Stack *S )
{
    S->base = (Elem*)malloc( sizeof(Elem) * INITSIZE );
    if( !S->base )    exit(0);

    S->top = S->base;
    S->size = INITSIZE;
}


void Push( Stack *S, Elem e )
{
    if( S->top - S->base >= S->size )
    {
        S->base = (Elem*)realloc( S->base, ( S->size + INCREASESIZE ) * sizeof(Elem) );
        //top重新赋值
        S->size += INCREASESIZE;
    }        
    *(S->top) = e;
    S->top++;
}


void Pop( Stack *S, Elem *e )
{
    if( S->top == S->base )    return;
    S->top--;
    *e = *(S->top);
}

int Len( Stack S )
{
    return ( S.top - S.base );
}
