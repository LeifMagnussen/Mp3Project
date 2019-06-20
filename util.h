#ifndef UTIL_H
#define	UTIL_H

#include "stdafx.h"


extern std::vector<unsigned char> get_file(const char *dir);

std::vector<unsigned char> get_file(const char *dir)
{
	std::ifstream file(dir, std::ios::in | std::ios::binary | std::ios::ate);
	std::streamoff fileSize = file.tellg();
	std::vector<unsigned char> buffer(file.tellg());
	file.seekg(0, std::ios::beg);
	file.read((char *)buffer.data(), buffer.size());
	file.close();
	return std::move(buffer);
};

#endif	/* UTIL_H */
