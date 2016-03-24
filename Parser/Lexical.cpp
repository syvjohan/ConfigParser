#include "Lexical.h"
#include "FileStream.h"

Lexical::Lexical() {}

Lexical::~Lexical() {}

void Lexical::Initialize( const char *path ) {
	EvalTokens( path );
}

void Lexical::EvalTokens( const char *path ) {
	std::vector<Token> tokens; //Store currentToken.
	//std::vector<char>  currentTokenData; //store data.
	Token              currentToken; //Store currentTokenData.
	currentToken.m_Type = TOKEN_NONE;

	int currentRow = 1;
	int currentColumn = 1;

	FileStream stream( path );
	if ( stream.IsOpen() ) {
		while ( !stream.EndOfStream() ) {
			char token = stream.GetNextToken();

			if ( token == '\n' ) {
				//++currentRow;
				//currentColumn  = 1;

				//Store information.
				if ( currentToken.m_Type != TOKEN_NONE ) {
					tokens.push_back( currentToken );
					currentToken.m_Type = TOKEN_NONE;
					currentToken.m_String = "\0";
				}

			} else if ( token == '\r' ) {
				if ( currentToken.m_Type == TOKEN_STRING ) {
					currentToken.m_String.push_back( token );
				}
			} else if ( token == '\t' ) {
				if ( currentToken.m_Type == TOKEN_STRING ) {
					currentToken.m_String.push_back( token );
				}
			} else if ( token == ' ' ) {
				if ( currentToken.m_Type == TOKEN_NONE ) {

				} else if ( currentToken.m_Type == TOKEN_STRING ) {
					currentToken.m_String.push_back( token );

				} else {
					tokens.push_back( currentToken );
					currentToken.m_String = "\0";
						currentToken.m_Type = TOKEN_NONE;
				}
			} else if ( token == '\"' ) {
				currentToken.m_Type = TOKEN_STRING;

			} else if ( token == '=' ) {

			} else if ( token == '[' ) {
				currentToken.m_Type = TOKEN_REGION;

			} else if ( token == ']' ) {
				tokens.push_back( currentToken );
				currentToken.m_Type = TOKEN_NONE;
				currentToken.m_String = "\0";

			} else if ( token == '@' ) {
				if ( token = stream.GetNextToken() == '@' ) {
					//Is block comment.
					do {
						token = stream.GetNextToken();
						// Stop when terminating block comment.
						if ( token == '@' && stream.GetNextToken() == '@' ) {
							break;
						}
					} while ( !stream.EndOfStream() );
				} else {
					//Is line comment.
					while ( token = stream.GetNextToken() != '\n' && !stream.EndOfStream() ) {
						;
					}
				}

			} else if ( IsNum(token) ) {
				currentToken.m_Type = TOKEN_INT;
				currentToken.m_String.push_back( token );				
				int counterDots = 0;
				do {
					token = stream.GetNextToken();
					if ( IsNum( token ) ) {
						currentToken.m_String.push_back( token );
					} else if ( token == '.' ) {
						if ( counterDots > 1 ) {
							printf( "To many dots in decimal number!" );
						} else {
							++counterDots;
							currentToken.m_Type = TOKEN_DECIMAL;
							currentToken.m_String.push_back( token );
						}
					} else {
						break;
					}
				} while ( !stream.EndOfStream() );
			
			} else if ( IsBool( token ) && currentToken.m_Type == TOKEN_NONE || currentToken.m_Type == TOKEN_BOOL ) {
				currentToken.m_String.push_back( token );
				currentToken.m_Type = TOKEN_BOOL;
			
			} else {
				currentToken.m_String.push_back( token );
				if ( currentToken.m_Type == TOKEN_NONE ) {
					currentToken.m_Type = TOKEN_NAME;
				}
			}
		}
	} else {
		printf( "Stream could not be open, check file path!" );
	}
}

bool Lexical::IsNum( const char &ch ) {
	return ( ch >= '0' && ch <= '9' );
}

bool Lexical::IsBool( const char &ch ) {
	return
		ch == 't' || ch == 'T' ||
		ch == 'r' || ch == 'R' ||
		ch == 'u' || ch == 'U' ||
		ch == 'e' || ch == 'E' ||
		ch == 'f' || ch == 'F' ||
		ch == 'a' || ch == 'A' ||
		ch == 'l' || ch == 'L' ||
		ch == 's' || ch == 'S';
}