#include "id3.h"
#include "stdafx.h"




id3::id3(std::vector<unsigned char> mp3Data)
{
	/* setting id3 data upon construction*/
	this->version = mp3Data[3] + mp3Data[4];
	id3Identifier(mp3Data) ? this->validity = true : this->validity = false;
	this->offSet = findOffset(mp3Data);

	/* checking id3 flags */
	std::vector<unsigned char> tmpBuff = findFlags(mp3Data);

	/* constructing the id3 object with flags */
	this->unsynchronizationFlag = tmpBuff[0];
	this->extendedHeaderFlag = tmpBuff[1];
	this->experimentalHeaderFlag = tmpBuff[2];
	this->footerFlag = tmpBuff[3];

}

std::vector<unsigned char> id3::get_tags(std::vector<unsigned char> mp3Data)
{
	for (int i = 0; i < ID3HEADERLENGTH; i ++)
	{
		id3::id3Offset.push_back(mp3Data[i]);
	}

	return id3::id3Offset;
}


std::vector<unsigned char> id3::findLength(std::vector<unsigned char> &mp3Data)
{
	std::vector<unsigned char> id3Tags;
	for (int i = 0; i < 10; i++)
	{
		id3Tags.push_back(mp3Data[i]);
	}
	return id3Tags;
}

unsigned int id3::findOffset(vector<unsigned char>& buffer)
{
	util utilObj;
	int convertedOffset = utilObj.convertChar(&buffer[6]);

	return convertedOffset;
}

bool id3::id3Identifier(vector<unsigned char> buff)
{
	if (buff[0] == 'I' && buff[1] == 'D' && buff[2] == '3')
		return true;

	return false;
}

std::vector<unsigned char> id3::findFlags(vector<unsigned char> buff)
{
	std::vector<unsigned char> tmpVec(4);
	for (int i = 0; i < tmpVec.size(); i++)
		tmpVec[i] = buff[i];

	return tmpVec;
}

