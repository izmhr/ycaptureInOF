#include "ofApp.h"

int CAM_WIDTH = 640;
int CAM_HEIGHT = 480;
unsigned long avgTimePF = 1000 / 30;	// 30fps

//--------------------------------------------------------------
void ofApp::setup(){
	cam.initGrabber(CAM_WIDTH, CAM_HEIGHT);
	sender = new CaptureSender(CS_SHARED_PATH, CS_EVENT_WRITE, CS_EVENT_READ);
	counter = 0;

	cannyThresh1 = 100;
	cannyThresh2 = 300;
	blurSize = 51;
	effectType = EffectType::NONE;

	oscReceiver.setup(PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
	cam.update();

	while(oscReceiver.hasWaitingMessages()){
		ofxOscMessage m;
		oscReceiver.getNextMessage(&m);

		std::string oscaddress = m.getAddress();

		if(oscaddress == "/changeeffect"){
			std::string typeStr = m.getArgAsString(0);
			if(typeStr == "non") {
				effectType = EffectType::NONE;
			} else if(typeStr == "canny" ) {
				effectType = EffectType::CANNY;
			} else if(typeStr == "blur" ) {
				effectType = EffectType::BLUR;
			} else {

			}
		} else if(oscaddress == "/cannythresh/1") {
			//std::cout << oscaddress << ": " << m.getArgAsInt32(0) << std::endl;
			cannyThresh1 = m.getArgAsInt32(0);
		} else if(oscaddress == "/cannythresh/2") {
			//std::cout << oscaddress << ": " << m.getArgAsInt32(0) << std::endl;
			cannyThresh2 = m.getArgAsInt32(0);
		} else if(oscaddress == "/blursize") {
			//std::cout << oscaddress << ": " << m.getArgAsInt32(0) << std::endl;
			blurSize = m.getArgAsInt32(0);
		}
	}

	if(cam.isFrameNew()){
		counter++;

		raw.setFromPixels(cam.getPixels(), CAM_WIDTH, CAM_HEIGHT, OF_IMAGE_COLOR);
		raw.mirror(1, 0);

		HRESULT hr;

		switch(effectType) {
		case EffectType::NONE:
			hr = sender->Send(counter * avgTimePF, CAM_WIDTH, CAM_HEIGHT, raw.getPixels() );
			break;
		case EffectType::CANNY:
			ofxCv::convertColor(raw, gray, CV_RGB2GRAY);
			ofxCv::Canny(gray, edge, cannyThresh1, cannyThresh2, 3);
			edge.update();
			ofxCv::convertColor(edge, edgeFull, CV_GRAY2RGB);

			hr = sender->Send(counter * avgTimePF, CAM_WIDTH, CAM_HEIGHT, edgeFull.getPixels() );
			break;
		case EffectType::BLUR:
			ofxCv::blur(raw, blur, blurSize);
			hr = sender->Send(counter * avgTimePF, CAM_WIDTH, CAM_HEIGHT, blur.getPixels() );
			break;
		}

		
		if(FAILED(hr)) {
			// エラー: 続行しない
			fprintf(stderr, "Error: 0x%08x\n", hr);
		} else if(hr == S_OK) {
			// 送信成功
			printf("Sent\n");
		} else {
			// フィルタ未起動。無視
			printf("Ignored\n");
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.draw(0, 0);
	//edge.draw(640, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
