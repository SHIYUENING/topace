
#include <math.h>
#include <stdio.h>
#include <string.h>	
#include "Load3DS.h"

CLoad3DS::CLoad3DS(void)
: isRAM(false)
, isVRAM(false)
, Model3ds(NULL)
, VBOVerticeID(0)
, VBOTexCoordID(0)
, VBONormalID(0)
, VBOColorID(0)
, VBOTangentID(0)
{
}

CLoad3DS::~CLoad3DS(void)
{
	Del_RAM();
	Del_VRAM();
}

bool CLoad3DS::Loadfile(char * filename)
{
	return false;
}

unsigned int CLoad3DS::LoadToVRAM(void)
{
	return 0;
}

void CLoad3DS::Del_RAM(void)
{
}

void CLoad3DS::Del_VRAM(void)
{
}
