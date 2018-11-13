#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
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
	/*ofSetColor(0, 0, 0);
	ofDrawCircle(160, 160, 30);*/
	/*for (int i = 0; i < game_engine_.getBoardSize(); i++) {
		for (int j = 0; j < game_engine_.getBoardSize(); j++) {
			if (game_engine_.getBoardState()[i][j] == kBlackPlayer) {
				ofDrawCircle(kSquareSize + (i + 1)*kSquareSize, kSquareSize + (j + 1)*kSquareSize, 30);
			}
		}
	}*/
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
