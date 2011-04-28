#include "TAMTEX.h"


CTAMTEX::CTAMTEX(void)
{
}


CTAMTEX::~CTAMTEX(void)
{
}




void CTAMTEX::Init(void)
{
	Init_One_TAM_TEX(CTAMTEX::pTAM_TEXs);
}


void CTAMTEX::Deinit(void)
{
	_TAM_TEX * TAM_TEX_TMP=NULL;
	while(CTAMTEX::pTAM_TEXs->pNext)
	{
		Clear_One_TAM_TEX(CTAMTEX::pTAM_TEXs);
		TAM_TEX_TMP=CTAMTEX::pTAM_TEXs->pNext;
		CTAMTEX::pTAM_TEXs=CTAMTEX::pTAM_TEXs->pNext;
		delete TAM_TEX_TMP;
	}
}
