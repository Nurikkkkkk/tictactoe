#include <iostream> 
#include <vector> 
void printBoard(const char board[3][3]){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			std::cout << board[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

bool movesLeft(const char board[3][3]){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(board[i][j] == '_'){
				return true;
			}
		}
	}
	return false;
}

int winner(const char board[3][3]){
	for(int row = 0; row < 3; row++){
		if(board[row][0] == board[row][1] && board[row][1] == board[row][2]){
			if(board[row][0] == 'x'){
				return 10;
			}
			else if(board[row][0] == 'o'){
				return -10;
			}
		}
	}

	for(int col = 0; col < 3; col++){
		if(board[0][col] == board[1][col] && board[1][col] == board[2][col]){
			if(board[0][col] == 'x'){
				return 10;
			}
			else if(board[0][col] == 'o'){
				return -10;
			}
		}
	}

	if(board[0][0] == board[1][1] && board[1][1] == board[2][2]){
		if(board[0][0] == 'x'){
			return 10;
		}
		else if(board[0][0] == 'o'){
			return -10;
		}
	}
	if(board[0][2] == board[1][1] && board[1][1] == board[2][0]){
		if(board[0][2] == 'x'){
			return 10;
		} 
		else if(board[0][2] == 'o'){
			return -10; 
		}
	} 
	return 0; 
}

int minimax(char board[3][3], int depth, bool max){
	int win = winner(board);

	if(win == 10){
		return win;
	}
	else if(win == -10){
		return win;
	}

	if(movesLeft(board) == false){
		return 0; 
	}
	
	if(max){
		int best = -1000000;
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				if(board[i][j] == '_'){
					board[i][j] = 'x'; 
					best = std::max(best, minimax(board, depth+1, !max));
					board[i][j] = '_';
				}			
			}
		}
		return best;
	}
	else{
		int best = 1000000;
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				if(board[i][j] == '_'){
					board[i][j] = 'o';
					best = std::min(best, minimax(board, depth+1, !max));
					board[i][j] = '_';
				}
			}
		}
		return best; 
	}
}

std::vector<int>  bestMove(char board[3][3], const char comp){
	std::vector<int> best(2, 0);
	int bestMax = -1000000;
	int bestMin = 1000000; 
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(board[i][j] == '_'){
				board[i][j] = comp;
				int move = 0; 
				if(comp == 'x'){
					move = minimax(board, 0, false);
					board[i][j] = '_';
					if(move > bestMax){
						best[0] = i;
						best[1] = j;
						bestMax = move;
					}
				}
				if(comp == 'o'){
					move = minimax(board, 0, true);
					board[i][j] = '_';
					if(move < bestMin){
						best[0] = i;
						best[1] = j;
						bestMin = move;
					}
				}
			}
		}
	}
	return best;
}

bool makeMove(char board[3][3], int row, int column, const char player){
	if((row-1 < 0 || row-1 > 2) || (column-1 < 0 || column-1>2) || board[row-1][column-1] != '_'){
    	return false;
    }
    board[row-1][column-1] = player;
    return true;
}

int main(){
	
	bool active = true; 
	while(active){
		int option = 0;
		char board[3][3] = {{'_', '_', '_'}, {'_', '_', '_'}, {'_', '_', '_'}};
		printBoard(board);
		std::cout << "Do you want to go first? (1-yes, 2-no, 3-exit): ";
		std::cin >> option; 
		std::cout << std::endl;
		bool isGame = true; 
		while(isGame){
			if(option == 1){
				char player = 'x', comp = 'o'; 
				int row = 0, column = 0;
				std::cout << "Make your move(row column): ";
				std::cin >> row >> column;
				while(!makeMove(board, row, column, player)){
					std::cout << "Invalid input, try again: ";
					std::cin >> row >> column; 
				} 
				if(winner(board) == 10){
					printBoard(board);
					std::cout << "Human wins!!!" << std::endl; 
					std::cout << std::endl; 
					isGame = false; 
				}
				else if(!movesLeft(board)){
					printBoard(board);
					std::cout << "Draw:)" << std::endl; 
					std::cout << std::endl;
					isGame = false;
				}
				else{
					printBoard(board);
					std::cout << std::endl;
					std::cout << "Computer makes its move..." << std::endl; 
					std::vector<int> compMove = bestMove(board, comp); 
					board[compMove[0]][ compMove[1]] = comp; 
					if(winner(board) == -10){
						printBoard(board);
						std::cout << "Computer wins:(((" << std::endl; 
						std::cout << std::endl;
						isGame = false; 
					}
					else if(!movesLeft(board)){
						printBoard(board);
						std::cout << "Draw:)" << std::endl;
						std::cout << std::endl; 
						isGame = false;
					}
					else{
						printBoard(board);
						std::cout << std::endl; 
					}
				}
			}
			else if(option == 2){
				char player = 'o', comp = 'x';
				int row = 0, column = 0; 
				std::cout << "Computer makes its move..." << std::endl;
				std::vector<int> compMove = bestMove(board, comp); 
				board[compMove[0]][compMove[1]] = comp;
				if(winner(board) == 10){
					printBoard(board);
					std::cout << "Computer wins:(((" << std::endl; 
					std::cout << std::endl;
					isGame = false;
				}
				else if(!movesLeft(board)){
					printBoard(board);
					std::cout << "Draw;)" << std::endl;
					std::cout << std::endl;
					isGame = false;
				}
				else{
					printBoard(board);
					std::cout << std::endl;
					std::cout << "Make your move(row column): ";
                    std::cin >> row >> column;
                    while(!makeMove(board, row, column, player)){
                    	std::cout << "Invalid input, try again: ";
                        std::cin >> row >> column;
                    }
                    if(winner(board) == -10){
						printBoard(board);
                        std::cout << "Human wins!!!" << std::endl;
						std::cout << std::endl;
                        isGame = false;
					}
					else if(!movesLeft(board)){
						printBoard(board);
						std::cout << "Draw:)" << std::endl;
						std::cout << std::endl;
						isGame = false;
					}
					else{
						printBoard(board);
						std::cout << std::endl;
					}
				}	
			}
			else if(option == 3){
				std::cout << "Bye bye!" << std::endl; 
				isGame = false;
				active = false;
			}
			else{
				isGame = false;
			}
		}
	}
	return 0;
}
