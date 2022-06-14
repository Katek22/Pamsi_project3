#ifndef TTT_HH
#define TTT_HH

#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

using std::cout;
using std::cin;
using std::endl;


#define WIN 1000
#define	DRAW 0
#define LOSS -1000

#define AI_MARKER 'O'
#define PLAYER_MARKER 'X'
#define EMPTY_SPACE '-'

#define START_DEPTH 0


// structure with constructor that contain row, colum and score of board 
struct move{
    int row,col,score;
    move(){col=0;
    row=0;
    score=0;};
};

void print_board(char board[3][3]);
std::vector<move> get_legal_moves(char board[3][3]);
bool position_occupied(char board[3][3], move pos);
std::vector<move> get_occupied_positions(char board[3][3], char marker);
bool board_is_full(char board[3][3]);
bool win(char tab[3][3]);
int who_won(char board[3][3]);
int get_board_state(char board[3][3], char marker);
char get_opponent_marker(char marker);
bool game_is_done(char board[3][3]);
std::pair<int, move> minimax(char board[3][3], char marker, int depth, int alpha, int beta);


#endif