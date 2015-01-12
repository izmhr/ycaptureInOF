#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "CaptureSender.h"
#include "ycapture.h"

#include "ofxOsc.h"
#define PORT 3333

enum EffectType {
	NONE = 0,
	CANNY,
	BLUR
};

class ofApp : public ofBaseApp{

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
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	ofVideoGrabber cam;
	ofImage raw;
	ofPixels gray;
	ofImage edge;
	ofImage edgeFull;
	ofImage blur;
	int cannyThresh1;
	int cannyThresh2;
	int blurSize;

	CaptureSender *sender;
	int counter;

	ofxOscReceiver oscReceiver;
	EffectType effectType;
		
};
