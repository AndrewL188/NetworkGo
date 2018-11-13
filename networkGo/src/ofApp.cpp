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
	ofDrawRectangle(kSquareSize, kSquareSize, kSquareSize*(1 + game_engine.getBoardSize()), 
		kSquareSize*(1 + game_engine.getBoardSize()));
	
	//Draws grid
	ofSetColor(0, 0, 0);
	for (int i = 0; i < game_engine.getBoardSize(); i++) {
		ofDrawLine(kSquareSize + (i + 1) * kSquareSize, 2 * kSquareSize, 
			kSquareSize + (i + 1) * kSquareSize, (game_engine.getBoardSize() + 1) * kSquareSize);

		ofDrawLine(2 * kSquareSize, kSquareSize + (i + 1) * kSquareSize,
			(game_engine.getBoardSize() + 1) * kSquareSize, kSquareSize + (i + 1) * kSquareSize);
	}
}

void ofApp::drawBoardState()
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
