#ifndef LIST
#define LIST

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <math.h>

typedef struct node
{
    int data;
    struct node * next;
}Node;

typedef Node * List;

void CreateList( List * L, int n );
void ShowList( List L, int n );
void FindMiddle( List L );
Node * CreateCycleList( int n );
void ShowCycleList( List L, int n );
void Josephus( List L, int n );

#endif