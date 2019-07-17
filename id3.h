#ifndef ID3_H
#define ID3_H



#include "stdafx.h"

using std::vector;
using std::string;

class id3 {
private:
	vector<unsigned char> findLength(vector<unsigned char> &);
	bool id3Identifier(vector<unsigned char>);
	vector<unsigned char> get_tags(vector<unsigned char> mp3Data);
	vector<unsigned char> id3Offset;
	unsigned int findOffset(vector<unsigned char>&);
	const int ID3HEADERLENGTH = 10;
	const int ID3FlAGLENGTH = 4;
	/* id3 tag values */
	string version;
	bool validity;
	
	
	

public:
	unsigned int offSet;
	bool unsynchronizationFlag;
	bool extendedHeaderFlag;
	bool experimentalHeaderFlag;
	bool footerFlag;
	id3(vector<unsigned char>);
	vector<unsigned char> findFlags(vector<unsigned char>);
	
	
};


#endif /* ID3_H */
