#ifndef _TGA_H
#define _TGA_H
#include <string.h>	
#include <stdio.h>										// Standard I/O header 
#include <gl\glew.h>
#include <gl\gl.h>	
#define TGA_NO_ERROR 0
#define TGA_ERROR_NOT_OPEN_FILE 1
#define TGA_ERROR_NOT_READ_FILE_HEADER 2
#define TGA_ERROR_FILE_HEADER_TYPE 3 //TGA file be type 2 or type 10
#define TGA_ERROR_NOT_READ_INFO_HEADER 4
#define TGA_ERROR_TEX_INFO 5 //Invalid texture information
#define TGA_ERROR_NOT_ALLOCAT_RAM 6 //Could not allocate memory for image
#define TGA_ERROR_NOT_READ_IMAGE_DATA 7
/*
typedef	struct									
{
	GLubyte	* imageData;									// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
	GLuint	type;											// Image Type (GL_RGB, GL_RGBA)
} Texture;	
*/
struct TGAHeader
{
	GLubyte Header[12];									// TGA File Header
} ;


struct sTGA
{
	GLubyte		header[6];								// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;							// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;								// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;									// Temporary Variable
	GLuint		type;	
	GLuint		Height;									//Height of Image
	GLuint		Width;									//Width ofImage
	GLuint		Bpp;									// Bits Per Pixel
} ;

class TGA
{
	public:
		TGA(void);
		~TGA(void);
		void DelTGA_RAM();
		void DelTGA_VRAM();
		GLuint LoadTGA_RAMtoVRAM(int TexParameter = GL_LINEAR);
		GLubyte	* imageData;									// Image Data (Up To 32 Bits)
		GLuint	bpp;											// Image Color Depth In Bits Per Pixel
		GLuint	width;											// Image Width
		GLuint	height;											// Image Height
		GLuint	texID;											// Texture ID Used To Select A Texture
		GLuint	type;
		int TGAerror;
		bool isRAM;
		bool isVRAM;
		bool UseAlpha;

		bool LoadTGA(char * filename);
		bool LoadTGA(wchar_t * filename);
		bool LoadUncompressedTGA(FILE * fTGA);
		//bool LoadCompressedTGA(char * filename, FILE * fTGA);
		TGAHeader tgaheader;									// TGA header
		sTGA tga;	

};
#endif