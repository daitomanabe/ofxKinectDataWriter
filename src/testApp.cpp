#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	kinect.init();
	kinect.setVerbose(false);
	kinect.open();

	char buf[256];
	time_t timer;
	time(&timer);
	struct tm *t_st;
	t_st = localtime(&timer);
	
	sprintf(buf, "rec%dfps_%02d_%02d_%02d-%02d-%02d", RECORDING_FPS, t_st->tm_mon+1, t_st->tm_mday, t_st->tm_hour, t_st->tm_min, t_st->tm_sec);
	dataWriter = new ofxKinectDataWriter(buf);	
	countRecording = 0;
	bRecording = false;
	frameRecording = 0;
	
	ofSetFrameRate(RECORDING_FPS);
	
}


//--------------------------------------------------------------
void testApp::update(){
	kinect.update();	
	if(bRecording) {
		char buf[512];
		double rec = (get_stamp_sec() - timeStampRecording);
		sprintf(buf, "now recording : %04d:%02d, %05d frame,", (int)rec / 60, (int)rec % 60, frameRecording);
		string str = buf;
		ofSetWindowTitle(str);
		frameRecording++;
		
		float * kinectDistancePixels = kinect.getDistancePixels();
		//		unsigned char * kinectRgbPixels = kinect.getPixels();
		unsigned char * kinectRgbPixels = kinect.getCalibratedRGBPixels();		
		for (int i=0; i<kinect.width; i++) {
			for (int j=0; j<kinect.height; j++) {
				int n = i + j * kinect.width;
				container.distancePixels[n] = kinectDistancePixels[n];
				container.rgbPixels[n * 3] = kinectRgbPixels[n * 3];
				container.rgbPixels[n * 3 + 1] = kinectRgbPixels[n * 3 + 1];
				container.rgbPixels[n * 3 + 2] = kinectRgbPixels[n * 3 + 2];				
			}
		}
		bRecording = dataWriter->update( &container );		
	} else {
		ofSetWindowTitle("waiting, press ! to start rec");
	}
	ofBackground(110, 110, 110);
	
}

//--------------------------------------------------------------
void testApp::draw(){
	char buf[32];
	sprintf(buf, "%05d", dataWriter->frame);
	ofSetColor(255, 255, 255);
	_font.drawString(buf, 100, 100);
	if (dataWriter->frame==0) {
		float * kinectDistancePixels = kinect.getDistancePixels();
		unsigned char * kinectRgbPixels = kinect.getCalibratedRGBPixels();		
		for (int i=0; i<kinect.width; i++) {
			for (int j=0; j<kinect.height; j++) {
				int n = i + j * kinect.width;
				ofSetColor(kinectRgbPixels[n * 3],kinectRgbPixels[n * 3 + 1],kinectRgbPixels[n * 3 + 2]);
				glVertex3f(i, j, kinectDistancePixels[n]);
			}
		}
		ofSetColor(255, 255, 255);
		kinect.drawDepth(10, 10, 400, 300);
		kinect.draw(450, 10, 400, 300);					
	}	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == '!') {
		filenames.push_back(dataWriter->startRecording());
		frameRecording	= 0;
		timeStampRecording	= get_stamp_sec();
		bRecording	= true;
	} else if(key == '"') {
		dataWriter->stopRecording();
		bRecording = false;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

