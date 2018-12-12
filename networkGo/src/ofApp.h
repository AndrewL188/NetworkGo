#pragma once

#include <cstdlib>
#include <utility>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxNetwork.h"

class ofApp : public ofBaseApp{
	private:
		const int kNoPlayer = 0;
		const int kBlackPlayer = 1;
		const int kWhitePlayer = 2;
		const int kBoardColorRed = 210;
		const int kBoardColorGreen = 180;
		const int kBoardColorBlue = 135;
		const int kBlackStoneRed = 0;
		const int kBlackStoneGreen = 0;
		const int kBlackStoneBlue = 0;
		const int kWhiteStoneRed = 255;
		const int kWhiteStoneGreen = 255;
		const int kWhiteStoneBlue = 255;

		const int kBoardXCoordinate = 80;
		const int kBoardYCoordinate = 80;
		const int kSquareSize = 80;
		const int kStoneSize = 27;

		enum GameState {
			IN_PROGRESS,
			GAME_OVER
		};

		GameState current_state_ = IN_PROGRESS;
	
		int board_size_ = 9;
		std::vector<std::vector<int> > board_state_;
		int black_captures_ = 0;
		int white_captures_ = 0;
		int winner_ = 0;
		bool player_resigned_ = false;
		double score_difference_ = 0.0;

		//Client instance variable
		ofxTCPClient client_;
	


	public:
		/*
		Called whenever an open frameworks project is run. Sets up a client, adds listeners to buttons,
		adds buttons to a panel.
		*/
		void setup();
		/*
		Called every time the frame updates. Attempts to receive a message in the form of a string from
		a server. Parses the string into segments that represent various aspects of the game.
		*/
		void update();
		/*
		Draws components in the window, using the helper draw methods below. What this method draws is based
		on the game state enum, current_state_
		*/
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

		//GUI elements
		ofTrueTypeFont font;
		ofxPanel gui_;
		ofxButton pass_button_;
		ofxButton resign_button_;


		/*
		Method that runs when the resign button is pressed. Will end the game and indicate the winner
		*/
		void resignButtonPressed();

		/*
		Method that runs when the pass button is pressed. Passes the player's turn to the other player without making
		a move
		*/
		void passButtonPressed();


		//Helper methods to render parts of the go game on screen
		/*
		//Draws the go board
		*/
		void drawGoBoard(int size);
		/*
		Renders black and white stones onto the board based on the board state received from the server
		*/
		void drawBoardState(int board_size);
		/*
		Renders display that shows captures stones for both players
		*/
		void drawCapturedStones(int black_captures, int white_captures);
		/*
		Renders win screen. Shows the winner of the game and the number of points he/she won by
		*/
		void drawWinScreen(int winner);
		
};
