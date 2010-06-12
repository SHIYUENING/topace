//#pragma once
#ifndef _DDS_H
#define _DDS_H
//#ifdef _WIN32
//#include <windows.h>		// Header File For Windows
//#endif
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdlib.h>
#include <gl\glew.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library
#define DDS_NO_ERROR 0
#define DDS_ERROR_NOT_OPEN_FILE 1
#define DDS_ERROR_DDS_FORMAT 2
#define DDS_ERROR_DWLINEARSIZE 3 
#define DDS_ERROR_INIT 4 
#define DDS_ERROR_NO_SUPPOT 5


#ifndef DUMMYUNIONNAMEN
#if defined(__cplusplus) || !defined(NONAMELESSUNION)
#define DUMMYUNIONNAMEN(n)
#else
#define DUMMYUNIONNAMEN(n)      u##n
#endif
#endif

#ifndef MAKEFOURCC
    #define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
                ((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) |   \
                ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24 ))
#endif //defined(MAKEFOURCC)

/*
 * FOURCC codes for DX compressed-texture pixel formats
 */
#define FOURCC_DXT1  (MAKEFOURCC('D','X','T','1'))
#define FOURCC_DXT2  (MAKEFOURCC('D','X','T','2'))
#define FOURCC_DXT3  (MAKEFOURCC('D','X','T','3'))
#define FOURCC_DXT4  (MAKEFOURCC('D','X','T','4'))
#define FOURCC_DXT5  (MAKEFOURCC('D','X','T','5'))

typedef unsigned __int32 uint32;
typedef unsigned __int16 uint16;
typedef __int32 int32;
typedef struct _DDCOLORKEY
{
    uint32       dwColorSpaceLowvalue;   // low boundary of color space that is to
                                        // be treated as Color Key, inclusive
    uint32       dwColorSpaceHighvalue;  // high boundary of color space that is
                                        // to be treated as Color Key, inclusive
} DDCOLORKEY;

/*
 * DDSCAPS2
 */
typedef struct _DDSCAPS2
{
    uint32       dwCaps;         // capabilities of surface wanted
    uint32       dwCaps2;
    uint32       dwCaps3;
    union
	{
        uint32       dwCaps4;
        uint32       dwVolumeDepth;
	} DUMMYUNIONNAMEN(1);
} DDSCAPS2;

/*
 * DDPIXELFORMAT
 */
typedef struct _DDPIXELFORMAT
{
    uint32       dwSize;                 // size of structure
    uint32       dwFlags;                // pixel format flags
    uint32       dwFourCC;               // (FOURCC code)
    union
    {
        uint32   dwRGBBitCount;          // how many bits per pixel
        uint32   dwYUVBitCount;          // how many bits per pixel
        uint32   dwZBufferBitDepth;      // how many total bits/pixel in z buffer (including any stencil bits)
        uint32   dwAlphaBitDepth;        // how many bits for alpha channels
        uint32   dwLuminanceBitCount;    // how many bits per pixel
        uint32   dwBumpBitCount;         // how many bits per "buxel", total
        uint32   dwPrivateFormatBitCount;// Bits per pixel of private driver formats. Only valid in texture
                                        // format list and if DDPF_D3DFORMAT is set
	} DUMMYUNIONNAMEN(1);
    union
    {
        uint32   dwRBitMask;             // mask for red bit
        uint32   dwYBitMask;             // mask for Y bits
        uint32   dwStencilBitDepth;      // how many stencil bits (note: dwZBufferBitDepth-dwStencilBitDepth is total Z-only bits)
        uint32   dwLuminanceBitMask;     // mask for luminance bits
        uint32   dwBumpDuBitMask;        // mask for bump map U delta bits
        uint32   dwOperations;           // DDPF_D3DFORMAT Operations
	} DUMMYUNIONNAMEN(2);
    union
    {
        uint32   dwGBitMask;             // mask for green bits
        uint32   dwUBitMask;             // mask for U bits
        uint32   dwZBitMask;             // mask for Z bits
        uint32   dwBumpDvBitMask;        // mask for bump map V delta bits
        struct
        {
            uint16    wFlipMSTypes;       // Multisample methods supported via flip for this D3DFORMAT
            uint16    wBltMSTypes;        // Multisample methods supported via blt for this D3DFORMAT
        } MultiSampleCaps;

	} DUMMYUNIONNAMEN(3);
    union
    {
        uint32   dwBBitMask;             // mask for blue bits
        uint32   dwVBitMask;             // mask for V bits
        uint32   dwStencilBitMask;       // mask for stencil bits
        uint32   dwBumpLuminanceBitMask; // mask for luminance in bump map
	} DUMMYUNIONNAMEN(4);
    union
    {
        uint32   dwRGBAlphaBitMask;      // mask for alpha channel
        uint32   dwYUVAlphaBitMask;      // mask for alpha channel
        uint32   dwLuminanceAlphaBitMask;// mask for alpha channel
        uint32   dwRGBZBitMask;          // mask for Z channel
        uint32   dwYUVZBitMask;          // mask for Z channel
	} DUMMYUNIONNAMEN(5);
} DDPIXELFORMAT;

/*
 * DDSURFACEDESC2
 */
typedef struct _DDSURFACEDESC2
{
    uint32               dwSize;                 // size of the DDSURFACEDESC structure
    uint32               dwFlags;                // determines what fields are valid
    uint32               dwHeight;               // height of surface to be created
    uint32               dwWidth;                // width of input surface
    union
    {
        int32            lPitch;                 // distance to start of next line (return value only)
        uint32           dwLinearSize;           // Formless late-allocated optimized surface size
	} DUMMYUNIONNAMEN(1);
    union
    {
        uint32           dwBackBufferCount;      // number of back buffers requested
        uint32           dwDepth;                // the depth if this is a volume texture 
	} DUMMYUNIONNAMEN(5);
    union
    {
        uint32           dwMipMapCount;          // number of mip-map levels requestde
                                                // dwZBufferBitDepth removed, use ddpfPixelFormat one instead
        uint32           dwRefreshRate;          // refresh rate (used when display mode is described)
        uint32           dwSrcVBHandle;          // The source used in VB::Optimize
	} DUMMYUNIONNAMEN(2);
    uint32               dwAlphaBitDepth;        // depth of alpha buffer requested
    uint32               dwReserved;             // reserved
    void*              lpSurface;              // pointer to the associated surface memory
    union
    {
        DDCOLORKEY      ddckCKDestOverlay;      // color key for destination overlay use
        uint32           dwEmptyFaceColor;       // Physical color for empty cubemap faces
	} DUMMYUNIONNAMEN(3);
    DDCOLORKEY          ddckCKDestBlt;          // color key for destination blt use
    DDCOLORKEY          ddckCKSrcOverlay;       // color key for source overlay use
    DDCOLORKEY          ddckCKSrcBlt;           // color key for source blt use
    union
    {
        DDPIXELFORMAT   ddpfPixelFormat;        // pixel format description of the surface
        uint32           dwFVF;                  // vertex format description of vertex buffers
	} DUMMYUNIONNAMEN(4);
    DDSCAPS2            ddsCaps;                // direct draw surface capabilities
    uint32               dwTextureStage;         // stage in multitexture cascade
} DDSURFACEDESC2;

struct DDS_IMAGE_DATA
{
    int  width;
    int  height;
    int    components;
    unsigned int   format;
    int      numMipMaps;
    unsigned char *pixels;
};


class CDDS
{
public:
	CDDS(void);
	~CDDS(void);
	DDS_IMAGE_DATA *pDDSImageData;
	void loadDDSTextureFile( const char *filename );
	void loadDDSTextureFile( const wchar_t *filename );
	unsigned int loadCompressedTexture( GLint TexParameter=0 );
	unsigned int g_compressedTextureID;
	int DDSerror;
	void DelDDS_RAM();
	void DelDDS_VRAM();
	bool isRAM;
	bool isVRAM;
	bool UseAlpha;

	static GLfloat AFNum;
	static void SetAFNum(GLfloat AFSet=1.0f);
};


#endif