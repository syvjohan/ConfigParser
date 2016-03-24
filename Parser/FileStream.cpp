#include "FileStream.h"
#include <stdio.h>

FileStream::FileStream() {}

FileStream::FileStream( const char *path ) {
	f = fopen( path, "r" );
}

FileStream::~FileStream() {}

char FileStream::GetNextToken() {
	SetFileIndex( ++index );
	return fgetc( f );
}

bool FileStream::IsOpen() {
	if ( f == NULL ) {
		return false;
	}
	return true;
}

bool FileStream::EndOfStream() {
	char c;
	if ( c = fgetc( f ) == EOF ) {
		return true;
	}
	return false;
}

void FileStream::Close() {
	fclose( f );
}

void FileStream::SetFileIndex(const int &index) {
	fseek( f, index, SEEK_SET);
}

