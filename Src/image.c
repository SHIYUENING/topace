#include "image.h"

#include <stdlib.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

image_t* image_loadFromFile(const char* filename) {
    image_t* ret = 0;
    HBITMAP hBitmap = 0;
    BITMAP bitmap;

    hBitmap = LoadImageA(GetModuleHandle(0), filename, IMAGE_BITMAP,
        0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if( hBitmap == 0 )
        goto err;
    GetObject(hBitmap, sizeof(bitmap), &bitmap);

    ret = malloc(sizeof(image_t));
    if( ret == 0 )
        goto err;
    ret->data = malloc(bitmap.bmWidthBytes * bitmap.bmHeight);

    ret->sizeX = bitmap.bmWidth;
    ret->sizeY = bitmap.bmHeight;
    ret->bitsPerPixel = bitmap.bmBitsPixel;
    ret->bytesPerLine = bitmap.bmWidthBytes;
    memcpy(ret->data, bitmap.bmBits, bitmap.bmWidthBytes * bitmap.bmHeight);

    return ret;

err:
    if( hBitmap != 0 )
        DeleteObject(hBitmap);
    image_destroy(ret);
    return 0;
}

void image_destroy(image_t* pImg) {
    if( pImg ) {
        free(pImg->data);
        free(pImg);
    }
}

void image_scale(image_t* pImg, int x, int y) {
    void* pixels = 0;
    GLenum format, type;

    if( pImg->sizeX == x && pImg->sizeY == y )
        return;

    switch(pImg->bitsPerPixel) {
        case 8:
            format = GL_ALPHA;
            type = GL_UNSIGNED_BYTE;
            break;
        case 16:
            format = GL_COLOR_INDEX;
            type = GL_UNSIGNED_SHORT;
            break;
        case 24:
            format = GL_RGB;
            type = GL_UNSIGNED_BYTE;
            break;
        case 32:
            format = GL_RGBA;
            type = GL_UNSIGNED_BYTE;
            break;
        default:
            return;
    }

    pixels = malloc( (x * pImg->bitsPerPixel / 8 + 3)/4*4 * y );
    if( pixels == 0 )
        return;
    gluScaleImage(format,
        pImg->sizeX, pImg->sizeY, type, pImg->data,
        x, y, type, pixels);

    free(pImg->data);
    pImg->data = pixels;
    pImg->sizeX = x;
    pImg->sizeY = y;
    pImg->bytesPerLine = (x * pImg->bitsPerPixel / 8 + 3)/4*4;
}

void image_checkp2(image_t* pImg) {
    int x = 1;
    int y = 1;
    while(x < pImg->sizeX)
        x *= 2;
    while(y < pImg->sizeY)
        y *= 2;
    image_scale(pImg, x, y);
}

void image_toBGRA(image_t* pImg) {
    // 未实现……
}

void image_toAlpha(image_t* pImg) {
    // 未实现……
}

void image_loadAsTexture(const char* textureFile,
                         const char* alphamapFile,
                         void* texture) {
    image_t *tex, *alpha;

    tex = image_loadFromFile(textureFile);
    alpha = image_loadFromFile(alphamapFile);

    if( !tex && !alpha ) {
        *(GLuint*)texture = 0;
        return;
    }

    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *(GLuint*)texture);

    if( tex && !alpha ) {           // 有颜色，无alpha值
        image_toBGRA(tex);
        image_checkp2(tex);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA,
            tex->sizeX, tex->sizeY, GL_BGRA_EXT, GL_UNSIGNED_BYTE, tex->data);
    } else if( alpha && !tex ) {    // 有alpha值，无颜色
        image_toAlpha(alpha);
        image_checkp2(alpha);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_ALPHA,
            alpha->sizeX, alpha->sizeY, GL_ALPHA, GL_UNSIGNED_BYTE, alpha->data);
    } else {                        // 同时具有颜色和alpha值
        int i, j;
        image_toBGRA(tex);
        image_checkp2(tex);
        image_toAlpha(alpha);
        image_scale(alpha, tex->sizeX, tex->sizeY);

        for(i=0; i<tex->sizeY; ++i) {
            unsigned char* p = &tex->data[i*tex->bytesPerLine];
            for(j=0; j<tex->sizeX; ++j)
                p[j*4+3] = alpha->data[i*alpha->bytesPerLine+j];
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA,
            tex->sizeX, tex->sizeY, GL_BGRA_EXT, GL_UNSIGNED_BYTE, tex->data);
        }
    }

    image_destroy(tex);
    image_destroy(alpha);
}
