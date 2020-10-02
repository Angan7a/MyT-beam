#include "PacketGPS.h"

PacketGPS::PacketGPS(int hh, int mm, int ss,
			float lngG, float latG, int numSatG) :
	h(hh), m(mm), s(ss), lng(lngG), lat(latG), numSat(numSatG) {}
