#include "Md5Camera.h"

CMd5Camera::CMd5Camera(void)
: CameraFile(NULL)
, cameraFileSize(0)
, cameraFileAddress(0)
, MD5Version(0)
, numFrames(0)
, frameRate(0)
{
}

CMd5Camera::~CMd5Camera(void)
{
}

void CMd5Camera::LoadCamera(char *filename)
{
}
