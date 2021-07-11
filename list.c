#include "list.h"


void CreateList( List * L, int n )
{
	List p, r;
	int i;

	srand( time(0) );
	*L = (Node*)malloc( sizeof(Node) );
	r = *L;

	for( i = 0; i < n; i++ )
	{
		p = (Node *)malloc( sizeof(Node) );
		p->data = rand() % 100 + 1;
		r->next = p;
		r = p;
	}
	r->next = NULL;
}


void ShowList( List L, int n )
{
	List p;
	p = L;
	puts( "Here are the numbers:" );
	while(p)
	{
		if ( p != L ) printf( "%d  ", p->data );
		p = p->next;
	}
	putchar('\n');
}


void FindMiddle( List L )
{
    List mid, search;
	mid = search = L;
	while( L->next != NULL )
	{
		if(	L->next->next )
		{
			mid = mid->next;
		    L = L->next->next;
		}
		else    L = L->next;
	}
	printf( "%d", mid->data );
}


Node * CreateCycleList( int n )
{
	List p, r, head = NULL;
	int i;

	r = head;

	for( i = 0; i < n; i++ )
	{
        p = (Node *)malloc( sizeof(Node) );
		p->data = rand() % n + 1;
		if( head == NULL )    head = p;
		else    r->next = p;
		r = p;
	}
	r->next = head;

	return head;
}


void ShowCycleList( List L, int n )
{
	List p;
	p = L;
	int flag = 1;
	puts( "Here are the numbers:" );
	while( p != L || flag == 1 )
	{
		printf( "%d  ", p->data );
		p = p->next;
		flag = 0;
	}
	putchar('\n');
}


void Josephus( List L, int n )
{
	Node *p = L, *temp;
	int m = 3;
	int i;

	while( p != p->next )
	{
		for( i = 1; i < m - 1; i++ )  //找待删节点之前的节点
		{
			p = p->next;
		}
	printf( "%d -> ", p->next->data );
	temp = p->next;
    p->next = temp->next;
	free(temp);
	p = p->next;
	m = p->data;
	}
	printf( "%d", p->data );
}