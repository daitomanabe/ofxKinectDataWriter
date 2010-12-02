#pragma once
#include <sys/time.h>
#define DEPTH_LENGTH (640 * 480)
#define DISTANCE_LENGTH (640 * 480)
#define RGB_LENGTH (640 * 480 * 3)

class dataContainer {
public:
	double stamp;
	float distancePixels[DISTANCE_LENGTH];	
	unsigned char rgbPixels[RGB_LENGTH];
};

inline double get_stamp_sec() {
//	struct rusage t;
//	struct timeval tv;
//	getrusage(RUSAGE_SELF, &t);
//	tv = t.ru_utime;
//	return tv.tv_sec + (double)tv.tv_usec * 1e-6;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
}