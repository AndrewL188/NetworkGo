#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//Adding listeners to buttons
	pass_button_.addListener(this, &ofApp::passButtonPressed);
	resign_button_.addListener(this, &ofApp::resignButtonPressed);
	
	gui_.setup();
	gui_.add(pass_button_.setup("Pass",200,40));
	gui_.add(resign_button_.setup("Resign",200,40));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	drawGoBoard();
	drawBoardState();
	gui_.draw();
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
}

void ofApp::resignButtonPressed() {

}

void ofApp::passButtonPressed() {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}


void ofApp::drawGoBoard()
{
	ofSetColor(kBoardColorRed, kBoardColorGreen, kBoardColorBlue);
	ofDrawRectangle(kSquareSize, kSquareSize, kSquareSize*(1 + game_engine_.getBoardSize()), 
		kSquareSize*(1 + game_engine_.getBoardSize()));
	
	//Draws grid
	ofSetColor(0, 0, 0);
	for (int i = 0; i < game_engine_.getBoardSize(); i++) {
		ofDrawLine(kBoardXCoordinate + (i + 1) * kSquareSize, kBoardYCoordinate + kSquareSize, 
			kBoardXCoordinate + (i + 1) * kSquareSize, kBoardYCoordinate + game_engine_.getBoardSize() * kSquareSize);

		ofDrawLine(kBoardXCoordinate + kSquareSize, kBoardYCoordinate + (i + 1) * kSquareSize,
			kBoardXCoordinate + game_engine_.getBoardSize() * kSquareSize, kBoardYCoordinate + (i + 1) * kSquareSize);
	}
}

void ofApp::drawBoardState()
{
	for (int i = 0; i < game_engine_.getBoardSize(); i++) {
		for (int j = 0; j < game_engine_.getBoardSize(); j++) {
			if (game_engine_.getBoardState()[i][j] == kBlackPlayer) {
				//Renders a black stone
				ofSetColor(kBlackStoneRed, kBlackStoneGreen, kBlackStoneBlue);
				ofDrawCircle(kBoardXCoordinate + (i + 1) * kSquareSize, kBoardYCoordinate + (j + 1) * kSquareSize, kStoneSize);
			}
			else if (game_engine_.getBoardState()[i][j] == kWhitePlayer) {
				//Renders a white stone
				ofSetColor(kWhiteStoneRed, kWhiteStoneGreen, kWhiteStoneBlue);
				ofDrawCircle(kBoardXCoordinate + (i + 1) * kSquareSize, kBoardYCoordinate + (j + 1) * kSquareSize, kStoneSize);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
