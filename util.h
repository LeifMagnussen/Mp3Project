#ifndef UTIL_H
#define	UTIL_H

#include "stdafx.h"

class util {
	public:
		std::vector<unsigned char> get_file(const char* dir);
		int convertChar(unsigned char* buff);

};

#endif	/* UTIL_H */
