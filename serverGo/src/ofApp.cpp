#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	server_.setup(kPortNumber);
	if (server_.isConnected()) {
		std::cout << "Connected" << endl;
	}
}

//--------------------------------------------------------------
void ofApp::update(){	
	//Only two players should be able to play the go game
	if (server_.getNumClients() != 2) {
		return;
	}



	for (int i = 0; i < server_.getLastID(); i++) {
		if (server_.isClientConnected(i)) {
			string input = server_.receive(i);
			
			if (input == "pass" && i == player_turn_) {
				game_engine_.pass();
				player_turn_ = (player_turn_ == kBlackClientNumber) ? kWhiteClientNumber : kBlackClientNumber;
			}
			else if (input == "resign" && i == player_turn_) {
				game_engine_.resign();
				player_resigned_ = true;
				player_turn_ = (player_turn_ == kBlackClientNumber) ? kWhiteClientNumber : kBlackClientNumber;
			}
			//Player tries to play a move
			else if (input.find(",") != string::npos && i == player_turn_){
				int comma_index = input.find(",");
				int x_coord = std::stoi(input.substr(0, comma_index));
				int y_coord = std::stoi(input.substr(comma_index + 1, input.length() - 1 - comma_index));
				game_engine_.playMove(x_coord, y_coord);
				player_turn_ = (player_turn_ == kBlackClientNumber) ? kWhiteClientNumber : kBlackClientNumber;
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

	std::string string_to_send = "\# ";
	for (int i = 0; i < game_engine_.getBoardSize(); i++) {
		for (int j = 0; j < game_engine_.getBoardSize(); j++) {
			string_to_send += std::to_string(game_engine_.getBoardState()[i][j]) + " ";
		}
	}

	string_to_send += std::to_string(game_engine_.getBlackCaptures()) + " ";
	string_to_send += std::to_string(game_engine_.getWhiteCaptures()) + " ";

	string_to_send += std::to_string(game_engine_.getWinner()) + " ";

	if (player_resigned_) {
		string_to_send += "1 ";
	}
	else {
		string_to_send += "0 ";
	}
	string_to_send += std::to_string(game_engine_.getScoreDifference()) + " @";
	

	server_.send(client_number, string_to_send);

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
