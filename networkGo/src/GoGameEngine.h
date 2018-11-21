#ifndef GO_GAME_ENGINE_H
#define GO_GAME_ENGINE_h

#include <vector>

class GoGameEngine {
public:
	//Enum class representing the players
	enum Player {
		BLACKPLAYER,
		WHITEPLAYER,
		NOPLAYER
	};
private:
	const int kDefaultBoardSize = 9;
	const int kNoWinner = -1;
	const int kEmpty = 0;
	const int kBlackPlayer = 1;
	const int kWhitePlayer = 2;

	int current_player_ = kBlackPlayer;
	int pass_counter_ = 0;
	int board_size_;

	int black_captures_ = 0;
	int white_captures_ = 0;
	const double kKomi = 6.5;
	Player winner_ = NOPLAYER;

	std::vector<std::vector<int> > board_state_;
	std::vector<int> flat_board_state_;

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
	Called when player opts to pass rather than play a move on the board. Gives turn to opponent. If both players
	pass consecutively, the game is over and will be scored.
	*/
	void pass();

	/*
	Called when player opts to resign the game
	*/
	void resign();

	/*
	Helper method for playMove function. Checks whether or not the move a player intends to play is legal or not.
	@param player - The number of the player (black or white represented by the numbers 1 and 2, respectively)
	@param row - Row that player wishes to play in
	@param col - Column that player wishes to play in
	@return bool that indicates whether or not
	*/
	bool LegalMove(int row, int col);

	/*
	Checks if given coordinates are on the go board
	*/
	bool isOnBoard(int row, int col);

	/*
	Returns the coordinate in the 1d vector given a row and column in the 2d vector
	*/
	int flatten(int row, int col);


	/*
	Returns the coordinates in the 2d vector of the board given a coordinate in the 1d vector
	*/
	std::vector<int> unflatten(int coordinate);

	/*
	Flood-fill type algorithm to find a chain of connected stones of the same color
	*/







	//Getter methods to access various aspects of the game
	int getDefaultBoardSize() { return kDefaultBoardSize; }
	int getBoardSize() { return board_size_; }
	std::vector<std::vector<int> > getBoardState() { return board_state_; }
	int getBlackCaptures() { return black_captures_; }
	int getWhiteCaptures() { return white_captures_; }
	int getPassCounter() { return pass_counter_; }
	/*
	Returns the player number of the winner: -1 if there is no winner, 1 if black wins, 2 if white wins
	*/
	Player getWinner() { return winner_; }
};



#endif