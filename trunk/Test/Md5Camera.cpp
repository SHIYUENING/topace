
#ifdef _WIN32
#include <windows.h> // yuck
#endif

#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <cstddef>
#include <cctype>

#include <GL/gl.h>

#include "Md5Camera.h"
#define IS_WHITESPACE(c) (' ' == c || '\t' == c || '\r' ==c || '\n' == c )
CMd5Camera::CMd5Camera(void)
: CameraFile(NULL)
, cameraFileSize(0)
, cameraFileAddress(0)
, MD5Version(0)
, numFrames(0)
, frameRate(0)
, cameraFrames(NULL)
, StartTime(0)
{
}

CMd5Camera::~CMd5Camera(void)
{
	Reset();
}
void CMd5Camera::Reset(void)
{
	if(CameraFile)
	{
		delete CameraFile;
		CameraFile=NULL;
	}
	cameraFileSize=0;
	cameraFileAddress=0;
	MD5Version=0;
	numFrames=0;
	frameRate=0;
	if(cameraFrames)
	{
		delete cameraFrames;
		cameraFrames=NULL;
	}
}

void CMd5Camera::LoadCamera(char *filename)
{
	Reset();
	if ( !filename )
		return;
	std::ifstream fin(filename, std::ifstream::in);
	if ( !fin.is_open() ) 
		return;
	std::string str;
	getNextToken(fin, &str);
	if ( str != "MD5Version" )
		return;
	MD5Version = readInt(fin);
	readElements(fin);
	/*
	if ( str != "MD5Version" )
	{
		MessageBox( NULL, "!MD5Version", "ERROR", MB_OK|MB_ICONEXCLAMATION );
		return;
	}
	else
		MessageBox( NULL, "MD5Version", "OK", MB_OK|MB_ICONEXCLAMATION );
	*/

}
// reads until first non-whitespace character
void CMd5Camera::skipWhitespace(std::ifstream &fin) {
  char c = '\0';
  while ( !fin.eof() ) {
    fin.get(c);

    if ( !IS_WHITESPACE(c) ) {
      fin.putback(c);
      break;
    }
  }
}


// reads in next token from file and matches it to a token type,
// if tokStr is non-NULL then it will be set to the text of the token
CMd5Camera::TOKEN CMd5Camera::getNextToken(std::ifstream &fin, std::string *tokStr) {
  skipWhitespace(fin);
  std::string str;

  TOKEN t = TOKEN_INVALID;

  while ( !fin.eof() ) {
    char c = '\0';
    fin.get(c);

    // single character tokens
    if ( '{' == c || '}' == c || '(' == c || ')' == c ) {
      // if already reading in a token, treat this as a delimiter
      if ( t != TOKEN_INVALID ) {
        fin.putback(c);
        if ( tokStr != NULL )
          (*tokStr) = str;
      }
 
      if ( '{' == c )
        t = TOKEN_LBRACE;
      if ( '}' == c )
        t = TOKEN_RBRACE;
      if ( '(' == c )
        t = TOKEN_LPAREN;
      if ( ')' == c )
        t = TOKEN_RPAREN;

      if ( tokStr) {
        (*tokStr) = std::string();
        (*tokStr) += c;
      }
      return t;
    }
    if ( isdigit(c) ) {
      str += c;
      if ( TOKEN_INVALID == t )
        t = TOKEN_INT;
      else if ( t != TOKEN_INT && t != TOKEN_FLOAT && t != TOKEN_KEYWORD ) {
        return TOKEN_INVALID;
      }
    }
    if ( '-' == c ) {
      str += c;
      if ( TOKEN_INVALID == t )
        t = TOKEN_INT;
      else {
        return TOKEN_INVALID;
      }
    }
    if ( isalpha(c) ) {
      str += c;
      if ( TOKEN_INVALID == t )
        t = TOKEN_KEYWORD;
      else if ( t != TOKEN_KEYWORD ) {
        return TOKEN_INVALID;
      }
    }
    if ( '"' == c ) {
      // treat as a delimeter if already reading in a token
      if ( t != TOKEN_INVALID ) {
        fin.putback(c);
        if ( tokStr != NULL )
          (*tokStr) = str;
        return t;
      }
      readString(fin, str);

      if ( tokStr != NULL )
        (*tokStr) = str;

      return TOKEN_STRING;
    }
    if ( '.' == c ) {
      str += c;
      if ( t != TOKEN_INT ) {
        return TOKEN_INVALID;
      }
      t = TOKEN_FLOAT;
    }
    if ( '/' == c ) {
      // treat as a delimeter if already reading in a token
      if ( t != TOKEN_INVALID ) {
        if ( tokStr != NULL )
          (*tokStr) = str;
        return t;
      }
      
      skipComments(fin);
      skipWhitespace(fin);
      continue;
    }

    // treat whitespace as a delimeter
    if ( IS_WHITESPACE(c) ) {
      if ( tokStr != NULL )
        (*tokStr) = str;
      return t;
    }

    // at this point token type should be set, if it hasn't been then
    // token is invalid
    if ( TOKEN_INVALID == t ) {
        return TOKEN_INVALID;
    }
  }

  return TOKEN_INVALID;
}


void CMd5Camera::skipComments(std::ifstream &fin) {
  char c;
  fin.get(c);

  if ( c != '/' )
    return ;

  while ( !fin.eof() && c != '\n' )
    fin.get(c);

  // put back last character read
  fin.putback(c);
}


void CMd5Camera::readString(std::ifstream &fin, std::string &str) {
  str = std::string();

  // read characters until closing " is found
  char c = '\0';
  do {
    fin.get(c);

    if ( fin.eof() )
      return;

    if ( c != '"')
      str += c;
  } while ( c != '"' );
}


// reads in an integer terminal and returns its value
int CMd5Camera::readInt(std::ifstream &fin) {
  std::string str;
  TOKEN t = getNextToken(fin, &str);

  if ( t != TOKEN_INT )
    return 0;

  return atoi( str.c_str() );
}


// reads in a float terminal and returns its value
float CMd5Camera::readFloat(std::ifstream &fin) {
  std::string str;
  TOKEN t = getNextToken(fin, &str);

  // integer tokens are just numbers with out a decimal point, so they'll
  // suffice here as well
  while ( t != TOKEN_FLOAT && t != TOKEN_INT )
  {
	  if(fin.eof())
		  return 0.0f;
	  t = getNextToken(fin, &str);
  }
    

  float f = 0.0f;
  sscanf(str.c_str(), "%f", &f);

  return f;
}


void CMd5Camera::readElements(std::ifstream &fin) {
  while ( !fin.eof() ) {
    std::string str;
    TOKEN tok = getNextToken(fin, &str);
  
    // token is TOKEN_INVALID when end of file is reached
    if ( TOKEN_INVALID == tok )
      break;
  
    if ( str == "commandline" )
      getNextToken(fin);
    else if ( str == "numFrames" )
      numFrames = readInt(fin);
    else if ( str == "frameRate" )
      frameRate = readInt(fin);
    else if ( str == "numCuts" )
      getNextToken(fin);
    else if ( str == "camera" )
      ReadFrames(fin);
  } // while ( not EOF )
}



void CMd5Camera::ReadFrames(std::ifstream &fin)
{
	int tmp=0;
	if(numFrames<=0)
		return;
	cameraFrames=new float[numFrames*7];

	while ( !fin.eof() ) 
	{
		if(tmp==numFrames*7)
			return;
		std::string str;
		TOKEN t = getNextToken(fin, &str);
		if( t == TOKEN_FLOAT || t == TOKEN_INT )
		{
			float f = 0.0f;
			sscanf(str.c_str(), "%f", &f);
			cameraFrames[tmp]=f;
			tmp=tmp+1;
		}
	}
}


void CMd5Camera::Play(double timeNow)
{
	if(numFrames==0)
		return;
	float PlayTime=float(timeNow-StartTime)*float(frameRate);
	if(PlayTime<0.0f)
		return;
	while(PlayTime>(numFrames-1))
		PlayTime=PlayTime-(numFrames-1);

	int FrameNum=int(PlayTime);
	float FrameIn= PlayTime-FrameNum;
	CameraPos[0]=ReadOneFrameUnit(FrameNum,0,FrameIn);
	CameraPos[1]=ReadOneFrameUnit(FrameNum,1,FrameIn);
	CameraPos[2]=ReadOneFrameUnit(FrameNum,2,FrameIn);
	CameraView[0]=ReadOneFrameUnit(FrameNum,3,FrameIn);
	CameraView[1]=ReadOneFrameUnit(FrameNum,4,FrameIn);
	CameraView[2]=ReadOneFrameUnit(FrameNum,5,FrameIn);
	CameraFOV=ReadOneFrameUnit(FrameNum,6,FrameIn);
}
float CMd5Camera::ReadOneFrameUnit(int FrameNum,int UnitNum,float FrameIn)
{
	return cameraFrames[FrameNum*7+UnitNum]+(cameraFrames[(FrameNum+1)*7+UnitNum]-cameraFrames[FrameNum*7+UnitNum])*FrameIn;
}