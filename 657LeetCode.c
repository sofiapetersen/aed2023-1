/*
657. Robot Return to Origin

There is a robot starting at the position (0, 0), the origin, on a 2D plane. 
Given a sequence of its moves, judge if this robot ends up at (0, 0) after it completes its moves.
You are given a string moves that represents the move sequence of the robot where moves[i] represents 
its ith move. Valid moves are 'R' (right), 'L' (left), 'U' (up), and 'D' (down).
Return true if the robot returns to the origin after it finishes all of its moves, or false otherwise.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Coordenates{
    int x;
    int y;
}Coord;

bool judgeCircle( char * moves );

int main(){

    Coord coord;
    coord.x = 0;
    coord.y=0;
    char moves[10];
    bool result = true;

    printf( "Current location: (%d,%d)", coord.x, coord.y );

    printf( "\nType your moves: " );
    gets(moves);

    result = judgeCircle(moves);
    if(result == 0){
    printf( "\nResult: False" );
    } else{
        printf( "\nResult: True" );
    }


    return 0;
}


bool judgeCircle( char * moves ){

    int i;
    Coord coord;
    coord.x = 0;
    coord.y=0;
    for ( i = 0; i < strlen(moves); i++ ){
        if( moves[i] == 'U' ){
            coord.y++;
        }
        if( moves[i] == 'D' ){
            coord.y--;
        }
        if( moves[i] == 'R' ){
            coord.x++;
        }
        if( moves[i] == 'L' ){
            coord.x--;
        }

    }

    printf( "Final location: (%d,%d)", coord.x, coord.y );

    if( ( coord.x == 0 ) && ( coord.y == 0 ) ){
        return true;
    } else {
        return false;
    }

}

