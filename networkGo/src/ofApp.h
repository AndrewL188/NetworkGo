#pragma once

#include <cstdlib>
#include <utility>

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxNetwork.h"
#include "GoGameEngine.h"


class ofApp : public ofBaseApp{
	private:
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
		GoGameEngine game_engine_;

		enum GameState {
			IN_PROGRESS,
			GAME_OVER
		};

		GameState current_state_ = IN_PROGRESS;
		bool player_resigned_ = false;

		//Client instance variable
		ofxTCPClient client;


	public:
		void setup();
		/*
		Called whenever the user performs an action (clicks a button or a part of the board)
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
		Renders black and white stones onto the board based on the board state of the game engine
		*/
		void drawBoardState(int board_size, std::string board_state);
		/*
		Renders display that shows captures stones for both players
		*/
		void drawCapturedStones(int black_captures, int white_captures);
		/*
		Renders win screen
		*/
		void drawWinScreen(int winner);
		
};
