// mp3Application.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "util.h"
#include "id3.h"


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
		vector<unsigned char> buffer = get_file(argv[1]);

		id3 id3Object;

		vector<unsigned char> id3Data = id3Object.get_tags(buffer);
		
		ofstream logStream;
		logStream.open("C:\\Users\\Leifm\\Desktop\\mp3Logs.mp3");

		// printing out the buffer
		for (int i = 0; i < id3Data.size(); i++)
		{
			char k_temp = id3Data[i];
			logStream << k_temp;
		}

		if (&id3Data)
		{
			cout << "GOT ID3 TAGS";
		}
	}
	catch (bad_alloc) {
		printf("File does not exist.\n");
		return -1;
	}

	return 0;
}

