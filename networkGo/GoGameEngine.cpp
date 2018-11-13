#include "GoGameEngine.h"

#include <iostream>
#include <algorithm>

using namespace std;

GoGameEngine::GoGameEngine()
{
	vector<int> temp(kBoardSize, kEmpty);
	for (int i = 0; i < kBoardSize; i++) {
		board_state_.push_back(temp);
	}
}

void GoGameEngine::playMove(int row, int col)
{
	if (checkLegalMove(row, col)) {
		board_state_[row][col] = current_player;
		//Sets current_player to opposite color
		(current_player == kBlackPlayer) ? kWhitePlayer : kBlackPlayer;
	}
}

bool GoGameEngine::checkLegalMove(int row, int col)
{
	if (row >= kBoardSize || col >= kBoardSize) {
		return false;
	}
	//Checks if stone has already been played there
	if (board_state_[row][col] != kEmpty) {
		return false;
	}

	return true;
}
