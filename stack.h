#ifndef STACK
#define STACK 2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <math.h>

#if STACK == 1
typedef char Elem;
#elif STACK == 2
typedef double Elem;
#endif

typedef struct stack{
    Elem *base;
    Elem *top;
    int size;
}Stack;

void InitStack( Stack *S );
void Push( Stack *S, Elem e );
void Pop( Stack *S, Elem *e );
int Len( Stack S );

#endif