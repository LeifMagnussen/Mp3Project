#include "util.h"]
#include "stdafx.h"

using std::vector;

vector<unsigned char> util::get_file(const char* dir)
{
	std::ifstream file(dir, std::ios::in | std::ios::binary | std::ios::ate);
	std::streamoff fileSize = file.tellg();
	vector<unsigned char> buffer(file.tellg());
	file.seekg(0, std::ios::beg);
	file.read((char*)buffer.data(), buffer.size());
	file.close();
	return std::move(buffer);
};

int util::convertChar(unsigned char* buff)
{
	unsigned num = 0x00;

	// converting single byte char to integer
	for (int i = 0; i < 4; i++)
		num = (num << 7) + buff[i];

	return num;
}