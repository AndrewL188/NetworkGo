#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	server_.setup(1000);
}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < server_.getLastID(); i++) {
		if (server_.isClientConnected(i)) {
			string input = server_.receive(i);
			if (input == "pass") {
				game_engine_.pass();
			}
			else if (input == "resign") {
				game_engine_.resign();
				player_resigned_ = true;
			}
			//Player tries to play a move
			else {
				int comma_index = input.find(",");
				int x_coord = std::stoi(input.substr(0, comma_index));
				int y_coord = std::stoi(input.substr(comma_index + 1, input.length() - 1 - comma_index));
				game_engine_.playMove(x_coord, y_coord);
			}
			createServerMessage(i);
			
		}
	}

	
	

}

//--------------------------------------------------------------
void ofApp::draw(){

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

void ofApp::createServerMessage(int client_number) {
	server_.send(client_number, std::to_string(game_engine_.getBoardSize()));

	std::string board_state;
	for (int i = 0; i < game_engine_.getBoardSize() * game_engine_.getBoardSize(); i++) {
		board_state += std::to_string(game_engine_.getFlatBoardState()[i]) + " ";
	}
	server_.send(client_number, board_state);

	server_.send(client_number, std::to_string(game_engine_.getBlackCaptures()));
	server_.send(client_number, std::to_string(game_engine_.getWhiteCaptures()));

	server_.send(client_number, std::to_string(game_engine_.getWinner()));

	if (player_resigned_) {
		server_.send(client_number, "true");
	}
	else {
		server_.send(client_number, "false");
	}
	server_.send(client_number, std::to_string(game_engine_.getScoreDifference()));

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
