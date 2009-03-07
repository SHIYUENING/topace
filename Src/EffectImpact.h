//#pragma once
#ifndef _EFFECTIMPACT_H
#define _EFFECTIMPACT_H
#include <windows.h>													// Header File For The Windows Library
#include <gl/gl.h>														// Header File For The OpenGL32 Library
#include <gl/glu.h>														// Header File For The GLu32 Library
#include <gl/glaux.h>
class CEffectImpact
{
public:
	CEffectImpact(void);
	~CEffectImpact(void);
	unsigned int EmptyTexture(int wh);
	bool IsSupportFBO;
	unsigned int TextureID;
	void EffectImpactDraw(bool DrawEffectImpact);
	int winW;
	int winH;
	int EffectImpactTextureSize;
	int Init(void);
	int EffectTime;
};
#endif