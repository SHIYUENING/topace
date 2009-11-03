#ifndef  _LOADDATA_THREAD_H
#define  _LOADDATA_THREAD_H
#define DATATYPE_ERROR 0
#define DATATYPE_TEXTURE 1
#define DATATYPE_FONT2D 2
#define DATATYPE_FONT3D 3
#include"Textures.h"
#include "Font2D.h"
#include "Font3D.h"
struct tLoadDataList
{
	tLoadDataList* NextNode;
	char DataPath[255];
	int DataType;
	void * Data;
	void ** DataPointer;
	void * DataSet;
};
void* LoadData(void* Param);
#endif