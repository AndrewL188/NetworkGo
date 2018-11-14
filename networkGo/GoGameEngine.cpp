#include "GoGameEngine.h"

#include <iostream>
#include <algorithm>

using namespace std;

GoGameEngine::GoGameEngine()
{
	board_size_ = kDefaultBoardSize;
	vector<int> temp(board_size_, kEmpty);
	for (int i = 0; i < board_size_; i++) {
		board_state_.push_back(temp);
	}

}

GoGameEngine::GoGameEngine(int board_size)
{
	board_size_ = board_size;
	vector<int> temp(board_size_, kEmpty);
	for (int i = 0; i < board_size_; i++) {
		board_state_.push_back(temp);
	}
}

void GoGameEngine::playMove(int row, int col)
{
	if (checkLegalMove(row, col)) {
		board_state_[row][col] = current_player_;
		//Sets current_player to opposite color
		current_player_ = (current_player_ == kBlackPlayer) ? kWhitePlayer : kBlackPlayer;
	}
}

bool GoGameEngine::checkLegalMove(int row, int col)
{
	if (row >= board_size_ || col >= board_size_ || row < 0 || col < 0) {
		return false;
	}
	//Checks if stone has already been played there
	if (board_state_[row][col] != kEmpty) {
		return false;
	}

	return true;
}
