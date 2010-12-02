#ifndef _TEST_APP
#define _TEST_APP

#include "ofxKinectDataWriter.h"
#include <time.h>
#include "ofxKinect.h"
#include "dataContainer.h"

#include "ofMain.h"

class testApp : public ofBaseApp{
private:
	ofTrueTypeFont _font;
	ofxKinectDataWriter *dataWriter;
	
public:
	int frameRecording;
	double timeStampRecording;
	bool bRecording;
	int countRecording;
	vector <string> filenames;
	
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

	ofxKinect kinect;
	dataContainer container;
	inline double getrusage_sec() {
		struct rusage t;
		struct timeval tv;
		getrusage(RUSAGE_SELF, &t);
		tv = t.ru_utime;
		return tv.tv_sec + (double)tv.tv_usec * 1e-6;
	}
	
	
};

#endif
