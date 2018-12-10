#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	client_.setup("10.194.209.87", 1000);
	ofSetFrameRate(60);

	//Adding listeners to buttons
	pass_button_.addListener(this, &ofApp::passButtonPressed);
	resign_button_.addListener(this, &ofApp::resignButtonPressed);
	
	gui_.setup();
	gui_.add(pass_button_.setup("Pass",200,40));
	gui_.add(resign_button_.setup("Resign",200,40));

	//Initializes empty board state
	std::vector<int> temp(9, 0);
	for (int i = 0; i < 9; i++) {
		board_state_.push_back(temp);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	
	std::string string_received = client_.receiveRaw();
	//Ensuring that the client received all the necessary data
	if (string_received.find("#") == std::string::npos || string_received.find("@") == std::string::npos) {
		return;
	}
	//If client received all data, remove the tag at the beginning of the message
	string_received = string_received.substr(2);
	stringstream ssin(string_received);
	
	
	//Finds board state
	for (int i = 0; i < board_size_; i++) {
		for (int j = 0; j < board_size_; j++) {
			if (ssin.good()) {
				int temp;
				ssin >> temp;
				board_state_[i][j] = temp;
			}
		}
	}
	//Finds black and white captures
	
	if (ssin.good()) {
		int temp;
		ssin >> temp;
		black_captures_ = temp;
	}
	
	if (ssin.good()) {
		int temp;
		ssin >> temp;
		white_captures_ = temp;
	}
	//Finds winner
	if (ssin.good()) {
		int temp;
		ssin >> temp;
		winner_ = temp;
	}
	
	//Finds whether or not player resigned
	if (ssin.good()) {
		int temp;
		ssin >> temp;
		if (temp == 1) {
			player_resigned_ = true;
		}
		else {
			player_resigned_ = false;
		}
	}

	if (ssin.good()) {
		double temp;
		ssin >> temp;
		score_difference_ = temp;
	}
	//Changes game state based on whether or not there is a winner
	if (winner_ != kNoPlayer) {
		current_state_ = GAME_OVER;
	}	
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	if (current_state_ == IN_PROGRESS) {
		drawGoBoard(board_size_);
		drawBoardState(board_size_);
		drawCapturedStones(black_captures_, white_captures_);
		gui_.draw();
	}
	else if (current_state_ == GAME_OVER) {
		drawGoBoard(board_size_);
		drawBoardState(board_size_);
		drawWinScreen(winner_);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	//If the mouse is not on the board, clicking does nothing
	if (x < kBoardXCoordinate + kSquareSize / 2 || x > kBoardXCoordinate + board_size_ * kSquareSize + kSquareSize / 2 ||
		y < kBoardYCoordinate + kSquareSize / 2 || y > kBoardYCoordinate + board_size_ * kSquareSize + kSquareSize / 2) {
		return;
	}
	//Calculates the indicies of where user wants to play on the board
	double board_coord_x = ((double)(x - kBoardXCoordinate - kSquareSize)) / kSquareSize;
	double board_coord_y = ((double)(y - kBoardXCoordinate - kSquareSize)) / kSquareSize;
	int board_coord_x_int = (int)round(board_coord_x);
	int board_coord_y_int = (int)round(board_coord_y);

	std::string string_coordinates = std::to_string(board_coord_x_int) + "," + std::to_string(board_coord_y_int);
	cout << string_coordinates;
	client_.send(string_coordinates);
	update();
}

void ofApp::resignButtonPressed() {
	client_.send("resign");
	update();
}

void ofApp::passButtonPressed() {
	client_.send("pass");
	update();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}


void ofApp::drawGoBoard(int size) {
	ofSetColor(kBoardColorRed, kBoardColorGreen, kBoardColorBlue);
	ofDrawRectangle(kSquareSize, kSquareSize, kSquareSize*(1 + size),
		kSquareSize*(1 + size));

	//Draws grid
	ofSetColor(0, 0, 0);
	for (int i = 0; i < size; i++) {
		ofDrawLine(kBoardXCoordinate + (i + 1) * kSquareSize, kBoardYCoordinate + kSquareSize,
			kBoardXCoordinate + (i + 1) * kSquareSize, kBoardYCoordinate + size * kSquareSize);

		ofDrawLine(kBoardXCoordinate + kSquareSize, kBoardYCoordinate + (i + 1) * kSquareSize,
			kBoardXCoordinate + size * kSquareSize, kBoardYCoordinate + (i + 1) * kSquareSize);
	}
}

void ofApp::drawBoardState(int board_size)
{
	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
			if (board_state_[i][j] == kBlackPlayer) {
				//Renders a black stone
				ofSetColor(kBlackStoneRed, kBlackStoneGreen, kBlackStoneBlue);
				ofDrawCircle(kBoardXCoordinate + (i + 1) * kSquareSize, kBoardYCoordinate + (j + 1) * kSquareSize, kStoneSize);
			}
			else if (board_state_[i][j] == kWhitePlayer) {
				//Renders a white stone
				ofSetColor(kWhiteStoneRed, kWhiteStoneGreen, kWhiteStoneBlue);
				ofDrawCircle(kBoardXCoordinate + (i + 1) * kSquareSize, kBoardYCoordinate + (j + 1) * kSquareSize, kStoneSize);
			}
		}
	}
}

void ofApp::drawCapturedStones(int black_captures, int white_captures) {
	font.loadFont("vag.ttf", 30, true, true);
	ofSetColor(kBlackStoneRed, kBlackStoneGreen, kBlackStoneBlue);
	font.drawString("Black Captures: " + std::to_string(black_captures), 900, 250);
	font.drawString("White Captures: " + std::to_string(white_captures), 900, 300);
}

void ofApp::drawWinScreen(int winner) {
	font.loadFont("vag.ttf", 30, true, true);
	ofSetColor(kBlackStoneRed, kBlackStoneGreen, kBlackStoneBlue);
	if (winner == kBlackPlayer && player_resigned_ == false) {
		font.drawString("Black wins by " + std::to_string(score_difference_) +
			" points", 900, 250);
	}
	else if (winner == kWhitePlayer && player_resigned_ == false) {
		font.drawString("White wins by " + std::to_string(score_difference_) +
			" points", 900, 250);
	}
	else if (winner == kBlackPlayer && player_resigned_ == true) {
		font.drawString("Black wins by resign", 900, 250);
	}
	else if (winner == kWhitePlayer && player_resigned_ == true) {
		font.drawString("White wins by resign", 900, 250);
	}

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
