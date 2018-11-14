#ifndef GO_GAME_ENGINE_H
#define GO_GAME_ENGINE_h

#include <vector>

class GoGameEngine {
private:
	const int kDefaultBoardSize = 9;
	const int kEmpty = 0;
	const int kBlackPlayer = 1;
	const int kWhitePlayer = 2;
	
	int current_player_ = kBlackPlayer;
	int board_size_;

	std::vector<std::vector<int> > board_state_;

public:
	//Constructors that fills empty board state vector with 0's
	GoGameEngine();
	GoGameEngine(int board_size);

	/*
	Modifies board_state_ vector
	@param player - The number of the player (black or white represented by the numbers 1 and 2, respectively)
	@param row - Row that player wishes to play in
	@param col - Column that player wishes to play in
	*/
	void playMove(int row, int col);

	/*
	Helper method for playMove function. Checks whether or not the move a player intends to play is legal or not.
	@param player - The number of the player (black or white represented by the numbers 1 and 2, respectively)
	@param row - Row that player wishes to play in
	@param col - Column that player wishes to play in
	@return bool that indicates whether or not
	*/
	bool checkLegalMove(int row, int col);

	//Getter methods to access various aspects of the game
	int getDefaultBoardSize() { return kDefaultBoardSize; }
	int getBoardSize() { return board_size_; }
	std::vector<std::vector<int> > getBoardState() { return board_state_; }

};



#endif
