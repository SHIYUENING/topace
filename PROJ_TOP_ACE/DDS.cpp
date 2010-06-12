#include "DDS.h"
GLfloat CDDS::AFNum=1.0f;
CDDS::CDDS(void)
:g_compressedTextureID(0)
,pDDSImageData(NULL)
,DDSerror(0)
,isRAM(false)
,isVRAM(false)
,UseAlpha(false)
{
}

CDDS::~CDDS(void)
{
	DelDDS_RAM();
	DelDDS_VRAM();
}
void CDDS::loadDDSTextureFile( const char *filename )
{

	if(!glewIsSupported("GL_EXT_texture_compression_s3tc"))
	{
		DDSerror=DDS_ERROR_NO_SUPPOT;
		return;
	}
   // DDS_IMAGE_DATA *pDDSImageData;
    DDSURFACEDESC2 ddsd;

    char filecode[4];
    FILE *pFile;
    int factor;
    int bufferSize; 

    // Open the file
    fopen_s(&pFile, filename, "rb" ); 

    if( pFile == NULL )
    {
       // char str[255];
       // sprintf( str, "loadDDSTextureFile couldn't find, or failed to load \"%s\"", filename );
       // MessageBox( NULL, str, "ERROR", MB_OK|MB_ICONEXCLAMATION );
		DDSerror=DDS_ERROR_NOT_OPEN_FILE;
        return ;
    } 

    // Verify the file is a true .dds file
    fread( filecode, 1, 4, pFile ); 

    if( strncmp( filecode, "DDS ", 4 ) != 0 )
    {

      //  char str[255];
     //   sprintf( str, "The file \"%s\" doesn't appear to be a valid .dds file!", filename );
    //    MessageBox( NULL, str, "ERROR", MB_OK|MB_ICONEXCLAMATION );

		DDSerror=DDS_ERROR_NOT_OPEN_FILE;
        fclose( pFile );
        return ;
    } 

    // Get the surface descriptor
    fread( &ddsd, sizeof(ddsd), 1, pFile ); 

    pDDSImageData = (DDS_IMAGE_DATA*) malloc(sizeof(DDS_IMAGE_DATA)); 

    memset( pDDSImageData, 0, sizeof(DDS_IMAGE_DATA) ); 

    //
    // This .dds loader supports the loading of compressed formats DXT1, DXT3 
    // and DXT5.
    // 

    switch( ddsd.ddpfPixelFormat.dwFourCC )
    {
        case FOURCC_DXT1:
            // DXT1's compression ratio is 8:1
            pDDSImageData->format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            factor = 2;
			UseAlpha=false;
            break; 

        case FOURCC_DXT3:
            // DXT3's compression ratio is 4:1
            pDDSImageData->format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            factor = 4;
			UseAlpha=true;
            break; 

        case FOURCC_DXT5:
            // DXT5's compression ratio is 4:1
            pDDSImageData->format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            factor = 4;
			UseAlpha=true;
            break; 

        default:
//#ifdef _WIN32
//            char str[255];
//            sprintf( str, "The file \"%s\" doesn't appear to be compressed "
//                "using DXT1, DXT3, or DXT5!", filename );
//            MessageBox( NULL, str, "ERROR", MB_OK|MB_ICONEXCLAMATION );
//#endif
			DDSerror=DDS_ERROR_DDS_FORMAT;
            return ;
    } 

    //
    // How big will the buffer need to be to load all of the pixel data 
    // including mip-maps?
    // 

    if( ddsd.dwLinearSize == 0 )
    {
//#ifdef _WIN32
//        MessageBox( NULL, "dwLinearSize is 0!","ERROR",
//            MB_OK|MB_ICONEXCLAMATION);
//#endif
		DDSerror=DDS_ERROR_DDS_FORMAT;
		return ;
    } 

    if( ddsd.dwMipMapCount > 1 )
        bufferSize = ddsd.dwLinearSize * factor;
    else
        bufferSize = ddsd.dwLinearSize; 

    pDDSImageData->pixels = (unsigned char*)malloc(bufferSize * sizeof(unsigned char)); 

    fread( pDDSImageData->pixels, 1, bufferSize, pFile ); 

    // Close the file
    fclose( pFile ); 

    pDDSImageData->width      = ddsd.dwWidth;
    pDDSImageData->height     = ddsd.dwHeight;
    pDDSImageData->numMipMaps = ddsd.dwMipMapCount; 

    if( ddsd.ddpfPixelFormat.dwFourCC == FOURCC_DXT1 )
        pDDSImageData->components = 3;
    else
        pDDSImageData->components = 4; 

	isRAM=true;
    //return pDDSImageData;
}
void CDDS::loadDDSTextureFile( const wchar_t *filename )
{

	if(!glewIsSupported("GL_EXT_texture_compression_s3tc"))
	{
		DDSerror=DDS_ERROR_NO_SUPPOT;
		return;
	}
   // DDS_IMAGE_DATA *pDDSImageData;
    DDSURFACEDESC2 ddsd;

    char filecode[4];
    FILE *pFile;
    int factor;
    int bufferSize; 

    // Open the file
    _wfopen_s(&pFile, filename, L"rb" ); 

    if( pFile == NULL )
    {
       // char str[255];
       // sprintf( str, "loadDDSTextureFile couldn't find, or failed to load \"%s\"", filename );
       // MessageBox( NULL, str, "ERROR", MB_OK|MB_ICONEXCLAMATION );
		DDSerror=DDS_ERROR_NOT_OPEN_FILE;
        return ;
    } 

    // Verify the file is a true .dds file
    fread( filecode, 1, 4, pFile ); 

    if( strncmp( filecode, "DDS ", 4 ) != 0 )
    {

      //  char str[255];
     //   sprintf( str, "The file \"%s\" doesn't appear to be a valid .dds file!", filename );
    //    MessageBox( NULL, str, "ERROR", MB_OK|MB_ICONEXCLAMATION );

		DDSerror=DDS_ERROR_NOT_OPEN_FILE;
        fclose( pFile );
        return ;
    } 

    // Get the surface descriptor
    fread( &ddsd, sizeof(ddsd), 1, pFile ); 

    pDDSImageData = (DDS_IMAGE_DATA*) malloc(sizeof(DDS_IMAGE_DATA)); 

    memset( pDDSImageData, 0, sizeof(DDS_IMAGE_DATA) ); 

    //
    // This .dds loader supports the loading of compressed formats DXT1, DXT3 
    // and DXT5.
    // 

    switch( ddsd.ddpfPixelFormat.dwFourCC )
    {
        case FOURCC_DXT1:
            // DXT1's compression ratio is 8:1
            pDDSImageData->format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            factor = 2;
			UseAlpha=false;
            break; 

        case FOURCC_DXT3:
            // DXT3's compression ratio is 4:1
            pDDSImageData->format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            factor = 4;
			UseAlpha=true;
            break; 

        case FOURCC_DXT5:
            // DXT5's compression ratio is 4:1
            pDDSImageData->format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            factor = 4;
			UseAlpha=true;
            break; 

        default:
//#ifdef _WIN32
//            char str[255];
//            sprintf( str, "The file \"%s\" doesn't appear to be compressed "
//                "using DXT1, DXT3, or DXT5!", filename );
//            MessageBox( NULL, str, "ERROR", MB_OK|MB_ICONEXCLAMATION );
//#endif
			DDSerror=DDS_ERROR_DDS_FORMAT;
            return ;
    } 

    //
    // How big will the buffer need to be to load all of the pixel data 
    // including mip-maps?
    // 

    if( ddsd.dwLinearSize == 0 )
    {
//#ifdef _WIN32
//        MessageBox( NULL, "dwLinearSize is 0!","ERROR",
//            MB_OK|MB_ICONEXCLAMATION);
//#endif
		DDSerror=DDS_ERROR_DDS_FORMAT;
		return ;
    } 

    if( ddsd.dwMipMapCount > 1 )
        bufferSize = ddsd.dwLinearSize * factor;
    else
        bufferSize = ddsd.dwLinearSize; 

    pDDSImageData->pixels = (unsigned char*)malloc(bufferSize * sizeof(unsigned char)); 

    fread( pDDSImageData->pixels, 1, bufferSize, pFile ); 

    // Close the file
    fclose( pFile ); 

    pDDSImageData->width      = ddsd.dwWidth;
    pDDSImageData->height     = ddsd.dwHeight;
    pDDSImageData->numMipMaps = ddsd.dwMipMapCount; 

    if( ddsd.ddpfPixelFormat.dwFourCC == FOURCC_DXT1 )
        pDDSImageData->components = 3;
    else
        pDDSImageData->components = 4; 

	isRAM=true;
    //return pDDSImageData;
}
//-----------------------------------------------------------------------------
// Name: loadCompressedTexture()
// Desc: 
//-----------------------------------------------------------------------------
unsigned int CDDS::loadCompressedTexture( GLint TexParameter)
{
    // NOTE: Unlike "lena.bmp", "lena.dds" actually contains its own mip-map 
    // levels, which are also compressed.
	//g_compressedTextureID=0;
    //DDS_IMAGE_DATA *pDDSImageData = 
	//loadDDSTextureFile( filename ); 
	if(g_compressedTextureID!=0)
		return g_compressedTextureID;

	if((void *)glCompressedTexImage2DARB==NULL)
	{
		DDSerror=DDS_ERROR_INIT;
		return 0;
	}
    if( pDDSImageData != NULL )
    {
        int nHeight     = pDDSImageData->height;
        int nWidth      = pDDSImageData->width;
        int nNumMipMaps = pDDSImageData->numMipMaps; 

        int nBlockSize; 

        if( pDDSImageData->format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT )
            nBlockSize = 8;
        else
            nBlockSize = 16; 

        glGenTextures( 1, &g_compressedTextureID );
        glBindTexture( GL_TEXTURE_2D, g_compressedTextureID ); 

		if(TexParameter!=0)
		{
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TexParameter );
		}
		else
		{
			if(nNumMipMaps>1)
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
			else
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

		}
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); 
		if(((TexParameter==GL_LINEAR_MIPMAP_LINEAR)||(TexParameter==0))&&(nNumMipMaps>1))
			if(CDDS::AFNum>1.0f)
				glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, CDDS::AFNum ); 

        int nSize;
        int nOffset = 0; 

        // Load the mip-map levels 

        for( int i = 0; i < nNumMipMaps; ++i )
        {
            if( nWidth  == 0 ) nWidth  = 1;
            if( nHeight == 0 ) nHeight = 1; 

            nSize = ((nWidth+3)/4) * ((nHeight+3)/4) * nBlockSize; 

            glCompressedTexImage2DARB( GL_TEXTURE_2D,
                                       i,
                                       pDDSImageData->format,
                                       nWidth,
                                       nHeight,
                                       0,
                                       nSize,
                                       pDDSImageData->pixels + nOffset ); 

            nOffset += nSize; 

            // Half the image size for the next mip-map level...
            nWidth  = (nWidth  / 2);
            nHeight = (nHeight / 2);
        }
		isVRAM=true;
    } 

	
	return g_compressedTextureID;
} 
void CDDS::DelDDS_RAM()
{
	if( pDDSImageData != NULL )
    {
        if( pDDSImageData->pixels != NULL )
		{
            free( pDDSImageData->pixels ); 
			pDDSImageData->pixels=NULL;
		}

        free( pDDSImageData );
		pDDSImageData = NULL;
    }
	isRAM=false;
}
void CDDS::DelDDS_VRAM()
{
	if(g_compressedTextureID!=0)
		glDeleteTextures(1, &g_compressedTextureID);
	g_compressedTextureID=0;
	isVRAM=false;
}
void CDDS::SetAFNum(GLfloat AFSet)
{
	if (!glewIsSupported("GL_EXT_texture_filter_anisotropic"))
		return;
	GLfloat AFMAX=1.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT,&AFMAX);
	CDDS::AFNum=max(1.0f,min(AFSet,AFMAX));
}
