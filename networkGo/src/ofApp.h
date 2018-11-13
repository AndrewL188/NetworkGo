#pragma once

#include <cstdlib>
#include <utility>

#include "ofMain.h"
#include "ofxGui.h"
#include "C:/Users/Andrew Luo/Downloads/of_v0.10.0_vs2017_release/of_v0.10.0_vs2017_release/apps/myApps/finalproject-AndrewL188/networkGo/GoGameEngine.h"


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

	public:
		void setup();
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
		ofxPanel gui_;
		ofxButton pass_button_;
		ofxButton resign_button_;

		//Helper methods to render parts of the go game on screen

		//Draws the go board
		void drawGoBoard();
		//Renders black and white stones onto the board based on the board state of the game engine
		void drawBoardState();
		
};
