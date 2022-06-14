#include "ttt.hh"




int main()
{
	char board[3][3];
	   for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
       board[i][j]='-';
	   
	cout << "******* TicTacToe *******"<<endl;
	cout << "Player = X\t AI Computer = O" << endl << endl;

	//Drawing the initial board
	print_board(board);

	while (!game_is_done(board))
	{   
        move temp;
		int row, col;
		cout << "Row play: ";
		cin >> row;
		cout << "Col play: ";
		cin >> col;
		cout << endl << endl;
        temp.row=row;
        temp.col=col;

		if (position_occupied(board, temp))
		{
			cout << "This position is occupied. Please insert another position " << endl;
			continue;
		}
		else
		{
			board[row][col] = PLAYER_MARKER;
		}

		std::pair<int, move> ai_move = minimax(board, AI_MARKER, START_DEPTH, LOSS, WIN);

		board[ai_move.second.row][ai_move.second.col] = AI_MARKER;

		print_board(board);
	}

	cout << "********** GAME OVER **********" << endl << "SCORE:"<<endl;
	if(win(board)){
		if(who_won(board)==1)
		cout<<"Player lost"<<endl;
		if(who_won(board)==0)
		cout<<"Player win"<<endl;
	}
	else
	cout<<"TIE"<<endl;
	return 0;

}