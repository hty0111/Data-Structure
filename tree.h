#ifndef TREE
#define TREE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <math.h>

typedef char Elem;

//Link(0):指向左右孩子 Thread(1):指向前驱后继
typedef enum { Link, Thread } PointerTag;

typedef struct ThrBiNode
{
    Elem data;
    struct ThrBiNode *lchild, *rchild;
    PointerTag ltag;
    PointerTag rtag;
}ThrBiNode, *ThrBiTree;

#endif