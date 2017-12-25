#pragma once

#include "ofMain.h"
#include "dot.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void draw();

	vector<Dot> dots;
	ofEasyCam cam;
	float anglePhase = 0;

	float dt = 0.03;
	float tFireworks = 0;
	float tCamPosition = 0;
	float tRadius = 0;
	float tWait = 0;
	float tStar = 0;
	float tStarWait = 0;
	float tFadeOut = 0;

	float maxRadius;
	float height;
	int numPoints;
	int numLaps;
	ofVec3f initCamPosition = ofVec3f(0, -280, 0);
	ofVec3f finalCamPosition = ofVec3f(0, height / 2 + 50, 1.6 * 240);
	ofVec3f camPosition = initCamPosition;

	ofPath star;

	enum State
	{
		FIREWORKS,
		START_EXPLOSION,
		EXPLOSION_WAIT,
		ROTATING,
		STAR,
		STAR_WAIT,
		FADE_OUT
	};

	State state;

private:
	float easeOut(float);
	float easeBounce(float);
	float easeInOut(float);

	void drawStar();
	void drawTree();
};