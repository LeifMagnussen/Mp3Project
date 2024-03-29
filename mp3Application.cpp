// mp3Application.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "util.h"
#include "id3.h"
#include "musicData.h"


using namespace std;

int main(int argc, char **argv) 
{

	if (argc > 2) {
		printf("Unexpected number of arguments.\n");
		return -1;
	}
	else if (argc == 1) {
		printf("No directory specified.\n");
		return -1;
	}

	try {
		util utilObj;
		vector<unsigned char> buffer = utilObj.get_file(argv[1]);

		id3 id3Object(buffer);

		ofstream logStream;
		logStream.open("C:\\Users\\Leif\\Desktop\\mp3Logs.txt");

		cout << id3Object.offSet << '\n';
		cout << buffer.size() << '\n';
		/* shifting buffer size to match the offset found in the id3 tags */
		buffer.resize(static_cast<int>(buffer.size()) - id3Object.offSet);
		/* creating musicData object starting at the offset found in the id3 tags */
		musicData musicObj(buffer);
		cout << "this is the error code: ";
		cout << GetLastError() << endl;

		/* printing out the frame */
		for (int i = 0; i < musicObj.mp3MainData.size(); i++)
		{
			char k_temp = musicObj.mp3MainData[i];
			logStream << k_temp;
		}
		/* closing log file after writing */
		logStream.close();
	}
	catch (bad_alloc) {
		printf("File does not exist.\n");
		return -1;
	}

	return 0;
}

