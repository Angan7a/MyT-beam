#include "PacketGPS.h"

PacketGPS::PacketGPS(int hh, int mm, int ss,
			double lngG, double latG, int numSatG) :
	h(hh), m(mm), s(ss), lng(lngG), lat(latG), numSat(numSatG) {}