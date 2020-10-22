#pragma once

class PacketGPS {
public:
	int h;
	int m;
	int s;

	double lng;
	double lat;
	int numSat;
	
	PacketGPS(int hh = 0, int mm = 0, int ss = 0,
			double lngG = 0, double latG = 0, int numSatG = 0);

	double getLng() const;

	double getLat() const;
};
