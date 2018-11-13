#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(2048, 1024, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

	/*GoGameEngine game_engine;
	for (int i = 0; i < game_engine.getBoardSize(); i++) {
		std::cout << game_engine.getBoardState()[0][i] << "a ";
	}*/



}
