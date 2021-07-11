#define BIN_TO_OCT
#include <stdio.h>
#include "stack.h"
#include "stack.c"

int main(void)
{
	Elem c;
	Stack bin, oct;
	int len, i, j, count = 0, sum = 0;

	InitStack(&bin);
	InitStack(&oct);
	printf( " number in binary: \n" );
    scanf( "%c", &c );
	while ( c != '#' )
	{
		Push( &bin, c );
		scanf( "%c", &c );
	}

	while( getchar() != '\n' );

	len = Len(bin);
	printf( "capacity: %d\n", len );
	
	for( i = 0; i < len; )
	{
		j = 0;
		do
		{
			Pop( &bin, &c );
		    sum += ( c - 48 ) * pow( 2, j );
			j++;
			i++;
		}while( j % 3 != 0 && i < len );
		Push( &oct, sum );
		sum = 0;
		count++;
	}
	printf( "number in decimal: " );
    for( i = 0; i < count; i++ )
	{
		Pop( &oct, &c );
		printf( "%d", c );
	}
}