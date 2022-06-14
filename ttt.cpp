#include "ttt.hh"

// Print the current board state
void print_board(char board[3][3])
{
	cout << endl;
	cout << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
	cout << "----------" << endl;
	cout << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
	cout << "----------" << endl;
	cout << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl << endl;
}

// Get all available legal moves (spaces that are not occupied)
std::vector<move> get_legal_moves(char board[3][3])
{
	std::vector<move> legal_moves;
    move temp;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] != AI_MARKER && board[i][j] != PLAYER_MARKER)
			{   
                temp.row=i;
                temp.col=j;
				//temp.temp1++;
				legal_moves.push_back(temp);

			}
		}
	}

	return legal_moves;
}

// Check if a position is occupied
bool position_occupied(char board[3][3], move pos)
{
	std::vector<move> legal_moves = get_legal_moves(board);

	for (int i = 0; i < legal_moves.size(); i++)
	{
		if (pos.row == legal_moves[i].row && pos.col == legal_moves[i].col)
		{
			return false;
		}
	}

	return true;
}

// Get all board positions occupied by the given marker
std::vector<move> get_occupied_positions(char board[3][3], char marker)
{
	std::vector<move> occupied_positions;
    move temp;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (marker == board[i][j])
			{
                temp.row=i;
                temp.col=j;
				occupied_positions.push_back(temp);
			}
		}
	}

	return occupied_positions;
}

// Check if the board is full
bool board_is_full(char board[3][3])
{
	std::vector<move> legal_moves = get_legal_moves(board);

	if (0 == legal_moves.size())
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Check if the game has been won
bool win(char tab[3][3]){
    int winner[8][3]= {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    for(int i=0;i<8;i++){
        int temp = 1;
        int first_row = winner[i][0]/3, first_column = winner[i][0]%3;
        for(int j = 0; j<3 ; j++){
            int row=winner[i][j]/3, column=winner[i][j]%3;
            if(tab[first_row][first_column] == '-' || tab[first_row][first_column] != tab[row][column] || tab[first_row][first_column] == ' ') temp = 0;
        }
        if(temp) return true;
    }
    return false;
}

//1 - AI 0 - player 
int who_won(char board[3][3]){
	if(!win(board)) return 2;
	int temp=0;
	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
	{
		if(board[i][j]==AI_MARKER || board[i][j]==PLAYER_MARKER)
		temp++;
	}

	if(temp%2==0)
	return 1;
	else
	return 0;

}

// Changing marker
char get_opponent_marker(char marker)
{
	char opponent_marker;
	if (marker == PLAYER_MARKER)
	{
		opponent_marker = AI_MARKER;
	}
	else
	{
		opponent_marker = PLAYER_MARKER;
	}

	return opponent_marker;
}

// Check if someone has won or lost
int get_board_state(char board[3][3], char marker)
{

	char opponent_marker = get_opponent_marker(marker);

	bool is_won=win(board);
	int temp=who_won(board);
	if (is_won && temp)
	{	
		return WIN;
	}

	//occupied_positions = get_occupied_positions(board, opponent_marker);
	bool is_lost = win(board);

	if (is_lost && temp ==0)
	{
		return LOSS;
	}

	bool is_full = board_is_full(board);
	if (is_full)
	{
		return DRAW;
	}

	return DRAW;

}

// Apply the minimax game optimization algorithm
std::pair<int, move> minimax(char board[3][3], char marker, int depth, int alpha, int beta)
{
	// Initialize best move
	move best_move;
    best_move.row = -1;
    best_move.col = -1;
	int best_score = (marker == AI_MARKER) ? LOSS : WIN;

	// If we hit a terminal state (leaf node), return the best score and move
	if (board_is_full(board) || DRAW != get_board_state(board, AI_MARKER))
	{
		best_score = get_board_state(board, AI_MARKER);
		return std::make_pair(best_score, best_move);
	}

	std::vector<move> legal_moves = get_legal_moves(board);

	for (int i = 0; i < legal_moves.size(); i++)
	{
		move curr_move = legal_moves[i];
		board[curr_move.row][curr_move.col] = marker;

		// Maximizing player's turn
		if (marker == AI_MARKER)
		{
			int score = minimax(board, PLAYER_MARKER, depth + 1, alpha, beta).first;

			// Get the best scoring move
			if (best_score < score)
			{
				best_score = score - depth * 10;
				best_move = curr_move;

				// Check if this branch's best move is worse than the best
				// option of a previously search branch. If it is, skip it
				alpha = std::max(alpha, best_score);
				board[curr_move.row][curr_move.col] = EMPTY_SPACE;
				if (beta <= alpha) 
				{ 
					break; 
				}
			}

		} // Minimizing opponent's turn
		else
		{
			int score = minimax(board, AI_MARKER, depth + 1, alpha, beta).first;

			if (best_score > score)
			{
				best_score = score + depth * 10;
				best_move = curr_move;

				// Check if this branch's best move is worse than the best
				// option of a previously search branch. If it is, skip it
				beta = std::min(beta, best_score);
				board[curr_move.row][curr_move.col] = EMPTY_SPACE;
				if (beta <= alpha) 
				{ 
					break; 
				}
			}

		}

		board[curr_move.row][curr_move.col] = EMPTY_SPACE; // Undo move

	}

	return std::make_pair(best_score, best_move);
}

// Check if the game is finished
bool game_is_done(char board[3][3])
{
	if (board_is_full(board))
	{
		return true;
	}

	if (DRAW != get_board_state(board, AI_MARKER))
	{
		return true;
	}

	return false;
}
