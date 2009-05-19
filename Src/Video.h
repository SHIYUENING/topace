//#pragma once
#ifndef _VIDEO_H
#define _VIDEO_H
#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library
#include "ffmpeg\avformat.h"		// Header File For The Glaux Library
#include "ffmpeg\avcodec.h"		// Header File For The Glaux Library
#pragma comment( lib, "avcodec.lib" )
#pragma comment( lib, "avformat.lib" )
#pragma comment( lib, "avutil.lib" )
class CVideo
{
public:
	CVideo(void);
	~CVideo(void);
	AVPicture * TTTTT;
	AVPacket  packet;
	AVFrame *pFrame,*pFrameRGB;
	AVFormatContext *pFormatCtx;
	AVCodecContext *pCodecCtx;
	int	isend;
	int ww,hh;
	int frameFinished;
	int	videoStream;
	void InitVideo(unsigned int VideoTexSize=512);
	bool LoadVideo(const char *filename);
	void DrawVideo(void);
	GLuint VideoTexID;

};
#endif