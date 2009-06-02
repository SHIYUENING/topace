#ifndef _ms3d_H_
#define _ms3d_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void* ms3d_t;

ms3d_t ms3d_loadFromFile(const char* filename,int UserTexID);
ms3d_t ms3d_loadFromMemory(const void* pData, unsigned int size,int UserTexID);
void   ms3d_destroy(ms3d_t ms3d);

float  ms3d_totalTime(ms3d_t ms3d);
void   ms3d_range(ms3d_t ms3d, float minXYZ[3], float maxXYZ[3]);

void   ms3d_drawStatic(ms3d_t ms3d);
void   ms3d_drawAnimation(ms3d_t ms3d, float time);

#ifdef __cplusplus
}
#endif

#endif
