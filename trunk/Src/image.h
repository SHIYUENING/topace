#ifndef _image_H_
#define _image_H_

typedef struct __image {
    int             sizeX;
    int             sizeY;
    int             bitsPerPixel;
    int             bytesPerLine;
    unsigned char*  data;
} image_t;

#ifdef __cplusplus
extern "C" {
#endif

image_t* image_loadFromFile(const char* filename);
void     image_destroy(image_t* pImg);

void     image_scale(image_t* pImg, int x, int y);
void     image_scalep2(image_t* pImg);  // ��֤�߶ȺͿ�ȶ���2�������η������������Ŵ�ͼ��
void     image_toBGRA(image_t* pImg);
void     image_toAlpha(image_t* pImg);

void     image_loadAsTexture(const char* textureFile,
                             const char* alphamapFile,
                             void* texture);

#ifdef __cplusplus
}
#endif

#endif
