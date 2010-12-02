#pragma once

#include "ofMain.h"
#include "dataContainer.h"
#include "ofxThread.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_RECORDING_TIME_SECOND (20)
#define RECORDING_FPS 30
#define MAX_RECORDING_TIME (MAX_RECORDING_TIME_SECOND * RECORDING_FPS)

class ofxKinectDataWriter : protected ofxThread {
private:
	FILE *outFile;
	char filename[256];
	bool open;
	int item_count;
	dataContainer * containers;
	double startClock;
	
public:
	int frame;
	ofxKinectDataWriter(char *_filename);
	string startRecording();
	bool update(dataContainer *buffer);
	void stopRecording();
};