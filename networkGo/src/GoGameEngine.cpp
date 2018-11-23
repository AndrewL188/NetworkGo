#include "GoGameEngine.h";

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
	for (int i = 0; i < board_size_; i++) {
		for (int j = 0; j < board_size_; j++) {
			flat_board_state_.push_back(kEmpty);
		}
	}

}

GoGameEngine::GoGameEngine(int board_size)
{
	board_size_ = board_size;
	vector<int> temp(board_size_, kEmpty);
	for (int i = 0; i < board_size_; i++) {
		board_state_.push_back(temp);
	}
	for (int i = 0; i < board_size_; i++) {
		for (int j = 0; j < board_size_; j++) {
			flat_board_state_.push_back(kEmpty);
		}
	}
}

void GoGameEngine::playMove(int row, int col)
{
	if (!LegalMove(row, col)) {
		return;
	}

	board_state_[row][col] = current_player_;
	flat_board_state_[flatten(row, col)] = current_player_;
	checkCaptures(row, col);

	//Checks for suicide moves, which are not allowed in this implementation of go
	if (!hasOpenLiberties(findLiberties(row, col))) {
		board_state_[row][col] = kEmpty;
		flat_board_state_[flatten(row, col)] = kEmpty;
		return;
	}

	//Sets current_player to opposite color and pass_counter_ back to 0 (since passes must be consecutive)
	current_player_ = (current_player_ == kBlackPlayer) ? kWhitePlayer : kBlackPlayer;
	pass_counter_ = 0;
}

void GoGameEngine::pass()
{
	current_player_ = (current_player_ == kBlackPlayer) ? kWhitePlayer : kBlackPlayer;
	pass_counter_++;
}

void GoGameEngine::resign()
{
	winner_ = (current_player_ == kBlackPlayer) ? WHITEPLAYER : BLACKPLAYER;
}

bool GoGameEngine::LegalMove(int row, int col)
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

bool GoGameEngine::isOnBoard(int row, int col)
{
	return (row < board_size_ && row >= 0 && col < board_size_ && col >= 0);
}

int GoGameEngine::flatten(int row, int col)
{
	return row * board_size_ + col;
}

std::vector<int> GoGameEngine::unflatten(int coordinate)
{
	vector<int> temp;
	//row coordinate
	temp.push_back(coordinate / board_size_);
	//column coordinate
	temp.push_back(coordinate % board_size_);
	return temp;
}

std::vector<int> GoGameEngine::findChain(int row, int col)
{
	vector<int> chain;
	vector<int> nodes_to_visit;
	nodes_to_visit.push_back(flatten(row, col));
	int current_color = board_state_[row][col];
	//Adds the current space to the chain
	chain.push_back(flatten(row, col));

	while (!nodes_to_visit.empty()) {
		int new_x = unflatten(nodes_to_visit.back())[0];
		int new_y = unflatten(nodes_to_visit.back())[1];
		nodes_to_visit.pop_back();
		if (isOnBoard(new_x + 1, new_y) && board_state_[new_x + 1][new_y] == current_color && 
			!contains(chain, flatten(new_x + 1, new_y))) {
			chain.push_back(flatten(new_x + 1, new_y));
			nodes_to_visit.push_back(flatten(new_x + 1, new_y));
		}
		if (isOnBoard(new_x - 1, new_y) && board_state_[new_x - 1][new_y] == current_color &&
			!contains(chain, flatten(new_x - 1, new_y))) {
			chain.push_back(flatten(new_x - 1, new_y));
			nodes_to_visit.push_back(flatten(new_x - 1, new_y));
		}
		if (isOnBoard(new_x, new_y + 1) && board_state_[new_x][new_y + 1] == current_color &&
			!contains(chain, flatten(new_x, new_y + 1))) {
			chain.push_back(flatten(new_x, new_y + 1));
			nodes_to_visit.push_back(flatten(new_x, new_y + 1));
		}
		if (isOnBoard(new_x, new_y - 1) && board_state_[new_x][new_y - 1] == current_color &&
			!contains(chain, flatten(new_x, new_y - 1))) {
			chain.push_back(flatten(new_x, new_y - 1));
			nodes_to_visit.push_back(flatten(new_x, new_y - 1));
		}
	}
	return chain;
}

std::vector<int> GoGameEngine::findLiberties(int row, int col)
{
	vector<int> chain = findChain(row, col);
	vector<int> liberty_coordinates;
	int current_color = board_state_[row][col];
	for (int i : chain) {
		int new_x = unflatten(i)[0];
		int new_y = unflatten(i)[1];
		if (isOnBoard(new_x + 1, new_y) && board_state_[new_x + 1][new_y] != current_color && 
			!contains(liberty_coordinates, flatten(new_x+1, new_y))) {

			liberty_coordinates.push_back(flatten(new_x + 1, new_y));
		}
		if (isOnBoard(new_x - 1, new_y) && board_state_[new_x - 1][new_y] != current_color &&
			!contains(liberty_coordinates, flatten(new_x - 1, new_y))) {

			liberty_coordinates.push_back(flatten(new_x - 1, new_y));
		}
		if (isOnBoard(new_x, new_y + 1) && board_state_[new_x][new_y + 1] != current_color &&
			!contains(liberty_coordinates, flatten(new_x, new_y + 1))) {

			liberty_coordinates.push_back(flatten(new_x, new_y + 1));
		}
		if (isOnBoard(new_x, new_y - 1) && board_state_[new_x][new_y - 1] != current_color &&
			!contains(liberty_coordinates, flatten(new_x, new_y - 1))) {

			liberty_coordinates.push_back(flatten(new_x, new_y - 1));
		}
	}
	return liberty_coordinates;
}


void GoGameEngine::checkCaptures(int row, int col) {
	int current_color = board_state_[row][col];
	checkCapturedStones(row + 1, col, current_color);
	checkCapturedStones(row - 1, col, current_color);
	checkCapturedStones(row, col + 1, current_color);
	checkCapturedStones(row, col - 1, current_color);
}

void GoGameEngine::checkCapturedStones(int row, int col, int current_color)
{
	if (isOnBoard(row,col) && board_state_[row][col] != kEmpty && board_state_[row][col] != current_color) {
		vector<int> current_group = findChain(row, col);
		vector<int> current_liberties = findLiberties(row, col);
		if (!hasOpenLiberties(current_liberties)) {
			removeStones(current_group);
			if (current_color == kBlackPlayer) {
				black_captures_ += current_group.size();
			}
			else {
				white_captures_ += current_group.size();
			}
		}
	}
}

bool GoGameEngine::hasOpenLiberties(std::vector<int> &liberties)
{
	for (int i : liberties) {
		if (flat_board_state_[i] == kEmpty) {
			return true;
		}
	}
	return false;
}

void GoGameEngine::removeStones(std::vector<int>& stones)
{
	for (int i : stones) {
		flat_board_state_[i] = kEmpty;
		board_state_[unflatten(i)[0]][unflatten(i)[1]] = kEmpty;
	}
}

bool GoGameEngine::contains(std::vector<int> vec, int value)
{
	return (std::find(vec.begin(), vec.end(), value) != vec.end());
}
