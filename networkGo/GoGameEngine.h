#ifndef GO_GAME_ENGINE_H
#define GO_GAME_ENGINE_h

#include <vector>

class GoGameEngine {
private:
	static const int kBoardSize = 9;
	const int kBlackPlayer = 1;
	const int kWhitePlayer = 2;
	int playerNumber;
	std::vector<std::vector<int> > board_state_;

public:
	//Constructor that fills empty board state vector with 0's
	GoGameEngine();

	/*
	Modifies board_state_ vector
	@param player - The number of the player (black or white represented by the numbers 1 and 2, respectively)
	@param row - Row that player wishes to play in
	@param col - Column that player wishes to play in
	*/
	void playMove(int player, int row, int col);

	/*
	Helper method for playMove function. Checks whether or not the move a player intends to play is legal or not.
	@param player - The number of the player (black or white represented by the numbers 1 and 2, respectively)
	@param row - Row that player wishes to play in
	@param col - Column that player wishes to play in
	@return bool that indicates whether or not
	*/
	bool checkLegalMove(int player, int row, int col);

	int getBoardSize() { return kBoardSize; }

};



#endif
