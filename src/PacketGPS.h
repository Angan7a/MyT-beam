#pragma once

class PacketGPS {
public:
	int h;
	int m;
	int s;

	float lng;
	float lat;
	int numSat;
	
	PacketGPS(int hh = 0, int mm = 0, int ss = 0,
			float lngG = 0, float latG = 0, int numSatG = 0);

};
