#ifndef ID3_H
#define ID3_H



#include "stdafx.h"

using std::vector;

class id3 {
private:
	vector<unsigned char> findLength(vector<unsigned char> &);
	vector<unsigned char> alterTest(vector<unsigned char> );

public:
	vector<unsigned char> get_tags(vector<unsigned char> mp3Data);
	
};


#endif /* ID3_H */
