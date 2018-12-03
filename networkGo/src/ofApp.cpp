#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//client.setup("10.194.209.87", 1000);

	//Adding listeners to buttons
	pass_button_.addListener(this, &ofApp::passButtonPressed);
	resign_button_.addListener(this, &ofApp::resignButtonPressed);
	
	gui_.setup();
	gui_.add(pass_button_.setup("Pass",200,40));
	gui_.add(resign_button_.setup("Resign",200,40));
}

//--------------------------------------------------------------
void ofApp::update(){
	if (game_engine_.getWinner() != GoGameEngine::NOPLAYER) {
		current_state_ = GAME_OVER;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	int board_size = game_engine_.getBoardSize();
	string board_state;
	for (int i = 0; i < board_size * board_size; i++) {
		board_state += to_string(game_engine_.getFlatBoardState()[i]);
	}
	int black_captures = game_engine_.getBlackCaptures();
	int white_captures = game_engine_.getWhiteCaptures();
	int winner = game_engine_.getWinner();

	if (current_state_ == IN_PROGRESS) {
		drawGoBoard(game_engine_.getBoardSize());
		drawBoardState(board_size, board_state);
		drawCapturedStones(black_captures, white_captures);
		gui_.draw();
	}
	else if (current_state_ == GAME_OVER) {
		drawGoBoard(game_engine_.getBoardSize());
		drawBoardState(board_size, board_state);
		drawWinScreen(winner);
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
	if (x < kBoardXCoordinate + kSquareSize / 2 || x > kBoardXCoordinate + game_engine_.getBoardSize() * kSquareSize + kSquareSize / 2 ||
y < kBoardYCoordinate + kSquareSize / 2 || y > kBoardYCoordinate + game_engine_.getBoardSize() * kSquareSize + kSquareSize / 2) {
return;
	}
	//Calculates the indicies of where user wants to play on the board
	double board_coord_x = ((double)(x - kBoardXCoordinate - kSquareSize)) / kSquareSize;
	double board_coord_y = ((double)(y - kBoardXCoordinate - kSquareSize)) / kSquareSize;
	int board_coord_x_int = (int)round(board_coord_x);
	int board_coord_y_int = (int)round(board_coord_y);


	game_engine_.playMove(board_coord_x_int, board_coord_y_int);
	update();
}

void ofApp::resignButtonPressed() {
	//client.send("resign");
	update();
}

void ofApp::passButtonPressed() {
	//client.send("pass");
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

void ofApp::drawBoardState(int board_size, string board_state)
{
	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
			if (stoi(board_state.substr(i*board_size + j, 1)) == kBlackPlayer) {
				//Renders a black stone
				ofSetColor(kBlackStoneRed, kBlackStoneGreen, kBlackStoneBlue);
				ofDrawCircle(kBoardXCoordinate + (i + 1) * kSquareSize, kBoardYCoordinate + (j + 1) * kSquareSize, kStoneSize);
			}
			else if (stoi(board_state.substr(i*board_size + j, 1)) == kWhitePlayer) {
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
		font.drawString("Black wins by " + std::to_string(game_engine_.getScoreDifference()) +
			" points", 900, 250);
	}
	else if (winner == kWhitePlayer && player_resigned_ == false) {
		font.drawString("White wins by " + std::to_string(game_engine_.getScoreDifference()) +
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
