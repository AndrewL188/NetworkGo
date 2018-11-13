#pragma once

#include "ofMain.h"
#include "C:/Users/Andrew Luo/Downloads/of_v0.10.0_vs2017_release/of_v0.10.0_vs2017_release/apps/myApps/finalproject-AndrewL188/networkGo/GoGameEngine.h"

class ofApp : public ofBaseApp{
	private:
		const int kBoardColorRed = 210;
		const int kBoardColorGreen = 180;
		const int kBoardColorBlue = 135;
		const int kSquareSize = 80;
		GoGameEngine game_engine;

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

		//Helper methods to render parts of the go game on screen
		void drawGoBoard();
		void drawBoardState();
		
};
