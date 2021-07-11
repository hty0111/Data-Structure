#include <stdio.h>
#include <stdio.h>
#include "tree.h"

ThrBiTree pre = NULL;

//前序遍历创建线索二叉树
void Create( ThrBiTree *t )
{
    char c;

    scanf( "%c", &c );
    if( ' ' == c )
    {
        *t = NULL;
    }
    else{
        *t = (ThrBiNode*)malloc( sizeof(ThrBiNode) );
        (*t)->data = c;
        (*t)->ltag = Link;
        (*t)->rtag = Link;
        
        Create( &(*t)->lchild );
        Create( &(*t)->rchild );
    }
}


//中序遍历线索化
void Threading( ThrBiTree t )
{
    if( t )
    {
        Threading( t->lchild );
        
        if( ! t->lchild )
        {
            t->ltag = Thread;
            t->lchild = pre;
        }

        if( ! pre->rchild )
        {
            pre->rtag = Thread;
            pre->rchild = t;
        }

        pre = t;

        Threading( t->rchild );
    }
}


void InOrderThreading( ThrBiTree *p, ThrBiTree t )
{
    *p = (ThrBiNode*)malloc(sizeof(ThrBiNode));
    (*p)->ltag = Link;
    (*p)->rtag = Thread;
    (*p)->rchild = *p;
    if( !t )
    {
        (*p)->lchild = *p;
    }
    else
    {
        (*p)->lchild = t;
        pre = *p;
        Threading(t);
        pre->rchild = *p;
        pre->rtag = Thread;
        (*p)->rchild = pre;
    }
}


void visit( char c )
{
    printf( "%c ", c );
}

//中序迭代遍历
void Traverse( ThrBiTree t )
{
    ThrBiTree p;
    p = t->lchild;

    while( p != t )
    {
        while( p->ltag == Link )
        {
            p = p->lchild;
        }

        visit( p->data );

        while( p->rtag == Thread && p->rchild != t )
        {
            p = p->rchild;
            visit( p->data );
        }

        p = p->rchild;
    }
}


int main( void )
{
    ThrBiTree p, t = NULL;
    Create( &t );
    InOrderThreading( &p, t );
    Traverse( p );

    return 0;

}