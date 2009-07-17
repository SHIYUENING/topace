//#pragma once
#ifndef _MD5CAMERA_H
#define _MD5CAMERA_H
#include <string>
#include <stdexcept>
#include <vector>
#include <fstream>
class CMd5Camera
{
public:
	CMd5Camera(void);
	~CMd5Camera(void);
	char * CameraFile;
	unsigned int cameraFileSize;
	unsigned int cameraFileAddress;
	unsigned int MD5Version;
	unsigned int numFrames;
	unsigned int frameRate;
	void LoadCamera(char *filename);
	  // methods for lexer
	void  readElements(std::ifstream &fin);
	void readString(std::ifstream &fin, std::string &str);
	void skipComments(std::ifstream &fin);
	void skipWhitespace(std::ifstream &fin);
	int   readInt(std::ifstream &fin);
	float readFloat(std::ifstream &fin);
	
protected:
	enum TOKEN { TOKEN_KEYWORD,
				TOKEN_INT,
				TOKEN_FLOAT,
				TOKEN_STRING,
				TOKEN_LBRACE,
				TOKEN_RBRACE,
				TOKEN_LPAREN,
				TOKEN_RPAREN,
				TOKEN_INVALID };
	TOKEN getNextToken(std::ifstream &fin, std::string *tokStr=NULL);
public:
	void ReadFrames(std::ifstream &fin);
	float* cameraFrames;
	void Reset(void);
	void Play(float timeNow);
	float StartTime;
};
#endif