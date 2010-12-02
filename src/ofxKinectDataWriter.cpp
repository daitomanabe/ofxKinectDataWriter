#include "ofxKinectDataWriter.h"

ofxKinectDataWriter::ofxKinectDataWriter(char *_filename) {
	containers = new dataContainer[MAX_RECORDING_TIME];
	strncpy(filename, _filename, 256);
	item_count = 1;
	frame = 0;
	open = false;
}

string ofxKinectDataWriter::startRecording() {
	if(open) {
		stopRecording();
	}
	char _filename[128];
	sprintf(_filename, "%s-%d.knct", filename, item_count);
	
	char buf[256];
	sprintf(buf, "%s%s", ofToDataPath("./").c_str(), _filename, item_count);
	outFile = fopen(buf, "wb");
	if(outFile != NULL) {
		startClock = get_stamp_sec();
		open = true;
		cout << "ofxKinectDataWriter::startRecording() | file open success. : create file " << buf << " ..." << endl;
		cout << "ofxKinectDataWriter::startRecording() | start recording..." << endl;
		string outName = _filename;
		return outName;
	} else {
		cout << "ofxKinectDataWriter::startRecording() | file open error. : failed to open " << buf << " ..." << endl;
		return NULL;
	}
}

bool ofxKinectDataWriter::update(dataContainer *buffer) {
	if(open) {
		if(frame < MAX_RECORDING_TIME) {
			memcpy(&(containers[frame]), buffer, sizeof(dataContainer));
			containers[frame].stamp = get_stamp_sec() - startClock;
			
			frame++;
			return true;
		} else {
			stopRecording();
			return false;
		}
	}
	return false;
}

void ofxKinectDataWriter::stopRecording() {
	if(open) {
		int count = fwrite(containers, sizeof(dataContainer), frame, outFile);
		fclose(outFile);
		open = false;
		frame = 0;
		cout << "ofxKinectDataWriter::stopRecording() | stop recording #" << item_count << " ... " << count << " frame write." << endl;
		cout << "ofxKinectDataWriter::stopRecording() | " << containers[count - 1].stamp << "sec." << endl;
		item_count++;
	} else {
		cout << "ofxKinectDataWriter::stopRecording() | waiting. press '!' to start recording" << endl;
	}
}
