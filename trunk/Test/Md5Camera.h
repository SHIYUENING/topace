//#pragma once
#ifndef _MD5CAMERA_H
#define _MD5CAMERA_H
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
};
#endif