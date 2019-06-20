#include "id3.h"
#include "stdafx.h"


std::vector<unsigned char> id3::get_tags(std::vector<unsigned char> mp3Data)
{
	std::vector<unsigned char> id3Data;
	for (int i = 0; i < mp3Data.size(); i += 3)
	{
		if (mp3Data[i] == 'I' && mp3Data[i + 1] == 'D' && mp3Data[i + 2] == '3')
		{
			id3Data = findLength(mp3Data);
			break;
		}
	}

	// call buffer modifier to shape the mp3 data


	return id3Data;
}


vector<unsigned char> id3::findLength(std::vector<unsigned char> &mp3Data)
{
	std::vector<unsigned char> id3Tags;
	for (int i = 0; i < 20; i++)
	{
		id3Tags.push_back(mp3Data[i]);
	}
	return id3Tags;
}


std::vector<unsigned char> id3::alterTest(std::vector<unsigned char> mp3Data)
{
	char testString = '0a67';
	for (int i = 100; i < mp3Data.size() - 300; i++)
	{
		if (mp3Data[i] == testString)
		{
			mp3Data[i] = '0a00';
		}
	}

	return mp3Data;
}
