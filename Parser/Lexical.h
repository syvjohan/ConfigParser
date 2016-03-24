#pragma once

#include <string>
#include <vector>
#include <map>

enum TokenType {
	TOKEN_NONE = 0,
	TOKEN_NAME,
	TOKEN_STRING,
	TOKEN_INT,
	TOKEN_DECIMAL,
	TOKEN_BOOL,
	TOKEN_EQUALS,
	TOKEN_REGION
};

enum CVarType {
	CVAR_BOOL,
	CVAR_FLOAT,
	CVAR_INT,
	CVAR_STRING,
};

//const char *TokenTypeStrings[] = {
//	"Name",
//	"Constant",
//	"String",
//	"Int",
//	"decimal",
//	"Bool",
//	"Equals",
//	"Region",
//};

class Lexical {
public:
	Lexical();
	~Lexical();
	
	void Initialize( const char *path );

private:
	struct Token {
		TokenType           m_Type;
		std::string         m_String;
	};

	struct CVar {
		union {
			bool        m_Bool;
			int         m_Int;
			float       m_Float;
			char       *m_String;
		};
		CVarType m_Type;
	};

	struct Region {
		std::map<std::string, CVar> m_CVars;
	};

	std::map<std::string, Region> m_Regions;

	void EvalTokens( const char *path );
	bool IsNum( const char &ch );
	bool IsBool( const char &ch );
};

