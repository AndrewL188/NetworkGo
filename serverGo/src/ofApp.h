#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "GoGameEngine.h"

class ofApp : public ofBaseApp{
private:
	ofxTCPServer server_;
	GoGameEngine game_engine_;
	bool player_resigned_ = false;
	const int kPortNumber = 1000;
	const int kBlackClientNumber = 0;
	const int kWhiteClientNumber = 1;
	int player_turn_ = kBlackClientNumber;

	public:
		void setup();
		/*
		Method that is called every frame that attempt to receive messages from clients that are connected 
		to the server. Will modify the state of the game engine depending on what message is received from 
		the client.
		*/
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		/*
			Method that generates and sends the message that the server sends back to the client. Called 
			every time update() is run. The message is sent in the following format:
			<board_state>,<black captures>,<white captures>,<winner>,<resignation boolean>,
			<score difference>
			Each aspect of the game is represented as a string, and are separated by spaces.
		*/
		void createServerMessage(int client_number);
		
};
