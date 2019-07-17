#include "stdafx.h"
#include "musicData.h"

using std::vector;


musicData::musicData(vector<unsigned char> buff)
{
	this->crc = buff[1] & 0x01;
	this->channelMode = setChannelMode(buff);
	this->constant = this->channelMode == Mono ? 21 : 36;
	/* add two to the constant if the channel is cyclic*/
	if (crc == 0)
		this->constant += 2;
	this->mpegVersion = setMpegVersion(buff);
	this->layer = setLayer(buff[1]);
	this->bitRate = setBitRate(buff, this->mpegVersion, this->layer);

	/* constructing frame size for the object */
	/* REMEMBER LEIF YOU NEED TO WRITE A SETFRAME SIZE FUNCTION*/
	if (buff[0] == 0xFF && buff[1] >= 0xE0)
		this->frameSize = 0;
	
	/* constructing the logical frame and placing in buffer for use */
	/* dynamically allocation memory to the mp3MainData member in the musicData class before resizing */
	this->mp3MainData = vector<unsigned char>(buff.size());
	cout << "Printing parameters of this this obj as created" << endl;
	cout << this->mp3MainData.size() << endl;
	cout << this->frameSize << endl;
	cout << this->constant << endl;
	this->mp3MainData.resize(abs(this->frameSize - this->constant)); // giving abort() has been called on this line
	cout << this->mp3MainData.size();
	memcpy(&this->mp3MainData, &buff[constant], frameSize - constant); // giving some error here, should use getLastError() to check
}


musicData::ChannelMode musicData::setChannelMode(vector<unsigned char> buff)
{
	unsigned value = buff[3] >> 6;
	musicData::ChannelMode tmpChannel = static_cast<ChannelMode>(value);
	return tmpChannel;

}

float musicData::setMpegVersion(vector<unsigned char> buff)
{
	float mpegVersion = 0;
	if ((buff[1] & 0x10) == 0x10 && (buff[1] & 0x08) == 0x08)
		mpegVersion = 1;
	else if ((buff[1] & 0x10) == 0x10 && (buff[1] & 0x08) != 0x08)
		mpegVersion = 2;
	else if ((buff[1] & 0x10) != 0x10 && (buff[1] & 0x08) == 0x08)
		mpegVersion = 0;
	else if ((buff[1] & 0x10) != 0x10 && (buff[1] & 0x08) != 0x08)
		mpegVersion = 2.5;

	return mpegVersion;
}

unsigned musicData::setLayer(unsigned char byte)
{
	byte = byte << 5;
	byte = byte >> 6;

	return (4 - byte);
}


unsigned musicData::setBitRate(vector<unsigned char> buff, float mpegVersion, int layer)
{
	unsigned bitRate;
	if (mpegVersion == 1) {
		if (layer == 1) {
			bitRate = buff[2] * 32;
		}
		else if (layer == 2) {
			const int rates[14]{ 32, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384 };
			bitRate = rates[(buff[2] >> 4) - 1] * 1000;
		}
		else if (layer == 3) {
			const int rates[14]{ 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320 };
			bitRate = rates[(buff[2] >> 4) - 1] * 1000;
		}
		else
			return 0;
	}
	else {
		if (layer == 1) {
			const int rates[14]{ 32, 48, 56, 64, 80, 96, 112, 128, 144, 160, 176, 192, 224, 256 };
			bitRate = rates[(buff[2] >> 4) - 1] * 1000;
		}
		else if (layer < 4) {
			const int rates[14]{ 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160 };
			bitRate = rates[(buff[2] >> 4) - 1] * 1000;
		}
		else
			return 0;
	}
}

unsigned musicData::setSamplingRate(vector<unsigned char> buff, float mpegVersion)
{
	unsigned samplingRate = 0;
	int rates[3][3]{ 44100, 48000, 32000, 22050, 24000, 16000, 11025, 12000, 8000 };

	for (int version = 1; version <= 3; version++)
		if (mpegVersion == version) {
			if ((buff[2] & 0x08) != 0x08 && (buff[2] & 0x04) != 0x04) {
				samplingRate = rates[version - 1][0];
				break;
			}
			else if ((buff[2] & 0x08) != 0x08 && (buff[2] & 0x04) == 0x04) {
				samplingRate = rates[version - 1][1];
				break;
			}
			else if ((buff[2] & 0x08) == 0x08 && (buff[2] & 0x04) != 0x04) {
				samplingRate = rates[version - 1][2];
				break;
			}
		}
	return samplingRate;
}

