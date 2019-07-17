#ifndef MUSICDATA
#define MUSICDATA

#include "stdafx.h"



using namespace std;

class musicData
{
	/* musicData will construct an object holding the physical frame from the mp3 data, this is where sample manipulation will occur*/
	public:
		/* taken from Floris Crey's mp3Decoder*/
		enum ChannelMode {
			Stereo = 0,
			JointStereo = 1,
			DualChannel = 2,
			Mono = 3
		};

		musicData(vector<unsigned char>);
		vector<unsigned char> mp3MainData;

	private:
		bool crc;
		int constant;
		ChannelMode channelMode;
		int frameSize;
		float mpegVersion;
		unsigned layer;
		unsigned bitRate;
		unsigned samplingRate;

		/* forward private function decls */
		ChannelMode setChannelMode(vector<unsigned char>);
		float setMpegVersion(vector<unsigned char>);
		unsigned setLayer(unsigned char byte);
		unsigned setBitRate(vector<unsigned char>, float, int);
		unsigned setSamplingRate(vector<unsigned char>, float);

};

#endif /* MUSICDATA */
