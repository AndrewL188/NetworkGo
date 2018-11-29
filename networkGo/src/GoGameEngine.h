#ifndef GO_GAME_ENGINE_H
#define GO_GAME_ENGINE_h

#include <vector>
#include <algorithm>

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
	double black_score_ = 0;
	double white_score_ = 0;
	const double kKomi = 6.5;
	Player winner_ = NOPLAYER;
	bool resigned_ = false;

	//Variables used for ko detection
	bool possible_ko = false;
	int last_captured_stone_coordinate = -1;

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
	Returns the coordinates in the 2d vector of the board given a coordinate in the 1d vector. Returns a vector in 
	the following format:
	[row,col]
	*/
	std::vector<int> unflatten(int coordinate);

	/*
	Flood-fill type algorithm to find a chain of connected stones of the same color. Models the go board as a graph
	with different colored nodes. Returns a list of numbers that represent the flattened coordinates of each stone
	(or empty space) in the connected chain. 
	*/
	std::vector<int> findChain(int row, int col);
	/*
	Finds the liberties of a chain of stones using the findChain method
	*/
	std::vector<int> findLiberties(int row, int col);

	/*
	Method that checks from captured stones and removes stones accordingly. Prioritizes opponent captures
	first, and only checks the neighboring nodes of the specified row and column. Called after a move is
	played
	*/
	void checkCaptures(int row, int col);

	/*
	Helper method for checkCapturedStones. Takes a row and column and checks whether or not the specified
	group has any liberties, and removes the group and increments captures when appropriate
	*/
	void checkCapturedStones(int row, int col, int current_color);

	/*
	Helper method for checkCapturedStones. Takes a vector of integers as a parameter that specify the
	liberties of a group of stones. Returns a boolean indicating whether or not the specified
	coordinates have any empty liberties.
	*/
	bool hasOpenLiberties(std::vector<int> &liberties);

	/*
	Helper method for checkCapturedStones. Takes a reference to a vector of integers as a parameter that
	specify the stones to be removed from the board. 
	*/
	void removeStones(std::vector<int> &stones);

	/*
	Helper method that determines whether or not a vector contains a particular value
	Returns a boolean indicating whether or not the vector contains the value
	*/
	bool contains(std::vector<int> vec, int value);

	/*
	Method that counts the score for each player and sets a winner. Called when players pass consecutively.
	This method utilizes the Chinese counting method, so players are expected to capture the dead stones
	within their own territory before ending the game.
	*/
	void countScore();

	/*
	Helper method for countScore. Determines whether or not the all the "liberties" of a chain of empty
	coordinates are one color. 
	@param current_color is the color of the player we wish to determine whether or not the chain of empty 
	stones is territory for
	@param border is a vector that represents the border of the territory
	@return boolean indicating whether or not the chain of empty stones is territory for the player
	*/
	bool isTerritory(int current_color, std::vector<int> &border);







	//Getter methods to access various aspects of the game
	int getDefaultBoardSize() { return kDefaultBoardSize; }
	int getBoardSize() { return board_size_; }
	std::vector<std::vector<int> > getBoardState() { return board_state_; }
	std::vector<int> getFlatBoardState() { return flat_board_state_; }
	int getBlackCaptures() { return black_captures_; }
	int getWhiteCaptures() { return white_captures_; }
	int getPassCounter() { return pass_counter_; }
	Player getWinner() { return winner_; }
	double getBlackScore() { return black_score_; }
	double getWhiteScore() { return white_score_; }
	double getScoreDifference() { return abs(black_score_ - white_score_); }
	bool getResigned() { return resigned_; }
};



#endif