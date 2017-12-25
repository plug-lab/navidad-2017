#include "ofMain.h"
#include "ofApp.h"

int main()
{
	// ofAppGlutWindow window;
	// window.setGlutDisplayString("rgba double depth alpha samples>=4");
	// ofSetupOpenGL(&window, 600, 600, OF_WINDOW);
	// ofSetFrameRate(60);
	// ofRunApp(new ofApp());

	ofSetupOpenGL(1024, 1024, OF_WINDOW); // <-------- setup the GL context
	ofRunApp(new ofApp());
}
