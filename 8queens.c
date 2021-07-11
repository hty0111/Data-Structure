#include <stdio.h>

void EightQueens( int row, int col, int (*chess)[8] );
int Danger( int row, int j, int (*chess)[8] );

int count = 0;

int main(void)
{
    int chess[8][8] = {};
    int i, j;
    EightQueens( 0, 8, chess );
    printf( "%d in all:", count );
    
    return 0;
}

void EightQueens( int row, int col, int (*chess)[8] )
{
    int chess2[8][8];
    int i, j;

    for( i = 0; i < 8; i++ )
    {
        for( j = 0; j < 8; j++ )
        {
            chess2[i][j] = chess[i][j];
        }
    }

    if( row == 8 )
    {
        printf( "%d of n:\n", count + 1 );
        for( i = 0; i < 8; i++ )
        {
            for( j = 0; j < 8; j++ )
            {
                printf( "%d ", *( *( chess2 + i ) + j ) );
            }
            putchar('\n');
        }
        putchar('\n');
        count++;
    }
    else
    {
        for( j = 0; j < col; j++ )
        {
            if( Danger( row, j, chess ) )
            {
                for( i = 0; i < 8; i++ )
                {
                    *( *( chess2 + row ) + i ) = 0;
                }
                *( *( chess2 + row ) + j ) = 1;
                
                EightQueens( row + 1, col, chess2 );
            }
        }
    }
}

int Danger( int row, int j, int (*chess)[8] )
{
    int i, k, flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0;
    
    for( i = 0; i < 8; i++ )
    {
        if( *( *( chess + i ) + j ) != 0 )
        {
            flag1 = 1;
            break;
        }
    }
    
    for( i = row, k = j; i >= 0 && k >= 0; i--, k-- )
    {
        if( *( *( chess + i ) + k ) != 0 )
        {
            flag2 = 1;
            break;
        }
    }

    for( i = row, k = j; i < 8 && k > 8; i++, k++ )
    {
        if( *( *( chess + i ) + k ) != 0 )
        {
            flag3 = 1;
            break;
        }
    }
    
    for( i = row, k = j; i >= 0 && k < 8; i--, k++ )
    {
        if( *( *( chess + i ) + k ) != 0 )
        {
            flag4 = 1;
            break;
        }
    }

    for( i = row, k = j; i < 8 && k >= 0; i++, k-- )
    {
        if( *( *( chess + i ) + k ) != 0 )
        {
            flag5 = 1;
            break;
        }
    }

    if( flag1 || flag2 || flag3 || flag4 || flag5 )  return 0;
    else  return 1;
}