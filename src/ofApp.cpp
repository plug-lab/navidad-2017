#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetCircleResolution(50);
	ofEnableDepthTest();
	ofSetVerticalSync(true);
	ofEnableAntiAliasing();
	ofEnableSmoothing();
	ofSetFrameRate(30);

	ofBackground(23, 21, 20);

	state = FIREWORKS;
}

//--------------------------------------------------------------
void ofApp::draw()
{
	switch (state)
	{
		case FIREWORKS:
		{
			maxRadius = 130;
			height = 240;
			numPoints = 497;
			numLaps = 12;

			tFireworks += dt / 4;

			if (tFireworks > 0.5)
			{
				tFireworks = 0.5;
				state = START_EXPLOSION;
			}

			float posX = 0;
			float posY = 200 * easeOut(tFireworks) - 200;

			cam.begin();
			ofSetColor(255);
			ofDrawBox(posX, 0, posY, 1, 50, 1);
			cam.end();
			break;
		}

		case START_EXPLOSION:
		{
			maxRadius = 100 * easeOut(tRadius);

			tRadius += dt / 3;

			if (tRadius > 0.5)
			{
				tRadius = 0.5;
				state = EXPLOSION_WAIT;
			}

			cam.begin();
			drawTree();
			cam.end();

			break;
		}

		case EXPLOSION_WAIT:
		{
			tWait += dt;

			if (tWait >= 1.0)
			{
				tWait = 0;
				state = ROTATING;
			}

			cam.begin();
			drawTree();
			cam.end();

			break;
		}

		case ROTATING:
		{
			float t = easeInOut(tCamPosition);
			camPosition = finalCamPosition * t + initCamPosition * (1 - t);
			tCamPosition += dt / 2;

			if (tCamPosition > 1)
			{
				tCamPosition = 0;
				state = STAR;
			}

			cam.begin();
			drawTree();
			cam.end();

			break;
		}

		case STAR:
		{
			tStar += dt * 1.5;

			if (tStar > 1)
			{
				tStar = 1;
				state = STAR_WAIT;
			}

			cam.begin();
			drawTree();
			drawStar();
			cam.end();

			break;
		}

		case STAR_WAIT:
		{
			tStarWait += dt;

			if (tStarWait > 2)
			{
				tStarWait = 0;
				state = FADE_OUT;
			}

			cam.begin();
			drawTree();
			drawStar();
			cam.end();

			break;
		}

		case FADE_OUT:
		{
			tFadeOut += dt;

			if (tFadeOut > 1)
			{
				tFadeOut = 0;
				tFireworks = 0;
				tStar = 0;
				tRadius = 0;
				camPosition = initCamPosition;
				state = FIREWORKS;

				std::exit(0);
				break;
			}

			cam.begin();
			drawTree();
			drawStar();
			cam.end();

			ofSetColor(23, 21, 20, 255 * tFadeOut);
			ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
		}
	}

	cam.setPosition(camPosition);
	cam.setTarget(ofVec3f(0, height / 2, 0));

	if (ofGetFrameNum() > 1) ofSaveScreen("frames/" + ofToString(ofGetFrameNum()) + ".png");
}

void ofApp::drawTree()
{
	anglePhase += dt / 2;

	if (anglePhase >= 2 * PI * numLaps / numPoints)
	{
		anglePhase = 0;
	}

	dots.clear();

	for (float angle = 0; angle < numLaps * 2 * PI; angle += 2 * PI * numLaps / numPoints)
	{
		Dot dot;
		float radius = maxRadius - maxRadius * angle / (2 * PI * numLaps);
		dot.x = radius * cos(angle + anglePhase);
		dot.y = (angle + anglePhase) * height / (2 * PI * numLaps);
		dot.z = radius * sin(angle + anglePhase);
		dots.push_back(dot);
	}

	float r = 1.3;
	ofColor color;

	for (int i = 0; i < dots.size(); i++)
	{
		if (i % 5 == 0)
		{
			color = ofColor(253, 226, 10);
		}
		else if (i % 5 == 1)
		{
			color = ofColor(251, 50, 7);
		}
		else if (i % 5 == 2)
		{
			color = ofColor(90, 240, 218);
		}
		else if (i % 5 == 3)
		{
			color = ofColor(253, 226, 167);
		}
		else
		{
			color = ofColor(253, 122, 87);
		}

		int biasLeft = 100;
		int biasRight = 20;

		if (i < biasRight)
		{
			ofSetColor(color, 255 * i / biasRight);
		}
		else if (i > numPoints - biasLeft)
		{
			ofSetColor(color, 255 * (numPoints - i) / biasLeft);
		}
		else
		{
			ofSetColor(color, 255);
		}

		ofDrawSphere(dots[i].x, dots[i].y, dots[i].z, r);
	}
}

void ofApp::drawStar()
{
	ofSetPolyMode(OF_POLY_WINDING_NONZERO);
	ofBeginShape();

	ofSetColor(255, 200, 0);

	float angle;
	int outSize = 14;
	int inSize = 7;

	for (int i = 0; i < 5; i++)
	{
		angle = i * 2 * PI / 5 + PI / 2;
		ofPoint p;
		p.x = outSize * easeBounce(tStar) * cos(angle);
		p.y = outSize * easeBounce(tStar) * sin(angle) + height + 10;
		p.z = 10;
		ofVertex(p);

		angle = angle + 36 * PI / 180;
		p.x = inSize * easeBounce(tStar) * cos(angle);
		p.y = inSize * easeBounce(tStar) * sin(angle) + height + 10;
		p.z = 10;
		ofVertex(p);
	}
	
	ofEndShape();
}

float ofApp::easeOut(float t)
{
	return 4 * t - 4 * t * t;
}

float ofApp::easeBounce(float t)
{
	return 3 * t - 2 * t * t;
}

float ofApp::easeInOut(float t)
{
	return 3 * t * t - 2 * t * t * t;
}