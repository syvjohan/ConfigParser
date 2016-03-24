#pragma once

#include <stdio.h>

class FileStream {
public:
	FileStream();
	FileStream(const char *path);
	~FileStream();
	char GetNextToken();
	bool IsOpen();
	bool EndOfStream();
	void Close();

private:
	FILE *f;
	int index = -1;

	void SetFileIndex(const int &index);
};

