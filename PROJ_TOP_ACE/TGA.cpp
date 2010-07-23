#include "tga.h"


//GLubyte cTGAcompare[12] = {0,0,10,0,0,0,0,0,0,0,0,0};	// Compressed TGA Header
TGA::TGA(void)
:imageData(0)
,bpp(0)
,width(0)
,height(0)
,texID(0)
,type(0)
,isRAM(false)
,isVRAM(false)
,TGAerror(0)
,UseAlpha(false)
{
}
TGA::~TGA(void)
{
	DelTGA_VRAM();
	DelTGA_RAM();
}
GLuint TGA::LoadTGA_RAMtoVRAM(int TexParameter)
{
	if(this->texID)
		return this->texID;
	if(!imageData)
		return 0;
	
		glGenTextures(1, &this->texID);
		glBindTexture(GL_TEXTURE_2D, this->texID);
		glTexImage2D(GL_TEXTURE_2D, 0, this->bpp / 8, this->width, this->height, 0, this->type, GL_UNSIGNED_BYTE, this->imageData);
		if((GL_LINEAR!=TexParameter)&&(0!=TexParameter))
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}
	isVRAM=true;

	return this->texID;
}

bool TGA::LoadFile(char * filename)				// Load a TGA file
{
	FILE * fTGA;												// File pointer to texture file
	fopen_s(&fTGA,filename, "rb");								// Open file for reading

	if(fTGA == NULL)											// If it didn't open....
	{
		//MessageBox(NULL, "Could not open texture file", "ERROR", MB_OK);	// Display an error message
		TGAerror=TGA_ERROR_NOT_OPEN_FILE;
		return false;														// Exit function
	}

	if(fread(&tgaheader, sizeof(TGAHeader), 1, fTGA) == 0)					// Attempt to read 12 byte header from file
	{
		//MessageBox(NULL, "Could not read file header", "ERROR", MB_OK);		// If it fails, display an error message 
		TGAerror=TGA_ERROR_NOT_READ_FILE_HEADER;
		if(fTGA != NULL)													// Check to seeiffile is still open
		{
			fclose(fTGA);													// If it is, close it
		}
		return false;														// Exit function
	}

	GLubyte uTGAcompare[12] = {0,0,2, 0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
	if(memcmp(uTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)				// See if header matches the predefined header of 
	{																		// an Uncompressed TGA image
		isRAM=LoadUncompressedTGA(fTGA);						// If so, jump to Uncompressed TGA loading code
	}
/*	else if(memcmp(cTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)		// See if header matches the predefined header of
	{																		// an RLE compressed TGA image
		LoadCompressedTGA(filename, fTGA);							// If so, jump to Compressed TGA loading code
	}*/
	else																	// If header matches neither type
	{
		//MessageBox(NULL, "TGA file be type 2 or type 10 ", "Invalid Image", MB_OK);	// Display an error
		TGAerror=TGA_ERROR_FILE_HEADER_TYPE;
		fclose(fTGA);
		return false;																// Exit function
	}
	return true;															// All went well, continue on
}
bool TGA::LoadFile(wchar_t * filename)				// Load a TGA file
{
	FILE * fTGA;												// File pointer to texture file
	_wfopen_s(&fTGA,filename, L"rb");									// Open file for reading

	if(fTGA == NULL)											// If it didn't open....
	{
		//MessageBox(NULL, "Could not open texture file", "ERROR", MB_OK);	// Display an error message
		TGAerror=TGA_ERROR_NOT_OPEN_FILE;
		return false;														// Exit function
	}

	if(fread(&tgaheader, sizeof(TGAHeader), 1, fTGA) == 0)					// Attempt to read 12 byte header from file
	{
		//MessageBox(NULL, "Could not read file header", "ERROR", MB_OK);		// If it fails, display an error message 
		TGAerror=TGA_ERROR_NOT_READ_FILE_HEADER;
		if(fTGA != NULL)													// Check to seeiffile is still open
		{
			fclose(fTGA);													// If it is, close it
		}
		return false;														// Exit function
	}

	GLubyte uTGAcompare[12] = {0,0,2, 0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
	if(memcmp(uTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)				// See if header matches the predefined header of 
	{																		// an Uncompressed TGA image
		isRAM=LoadUncompressedTGA(fTGA);						// If so, jump to Uncompressed TGA loading code
	}
/*	else if(memcmp(cTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)		// See if header matches the predefined header of
	{																		// an RLE compressed TGA image
		LoadCompressedTGA(filename, fTGA);							// If so, jump to Compressed TGA loading code
	}*/
	else																	// If header matches neither type
	{
		//MessageBox(NULL, "TGA file be type 2 or type 10 ", "Invalid Image", MB_OK);	// Display an error
		TGAerror=TGA_ERROR_FILE_HEADER_TYPE;
		fclose(fTGA);
		return false;																// Exit function
	}
	return true;															// All went well, continue on
}
bool TGA::LoadUncompressedTGA(FILE * fTGA)	// Load an uncompressed TGA (note, much of this code is based on NeHe's 
{																			// TGA Loading code nehe.gamedev.net)
	if(fread(tga.header, sizeof(tga.header), 1, fTGA) == 0)					// Read TGA header
	{										
		//MessageBox(NULL, "Could not read info header", "ERROR", MB_OK);		// Display error
		TGAerror=TGA_ERROR_NOT_READ_INFO_HEADER;
		if(fTGA != NULL)													// if file is still open
		{
			fclose(fTGA);													// Close it
		}
		return false;														// Return failular
	}	

	this->width  = tga.header[1] * 256 + tga.header[0];					// Determine The TGA Width	(highbyte*256+lowbyte)
	this->height = tga.header[3] * 256 + tga.header[2];					// Determine The TGA Height	(highbyte*256+lowbyte)
	this->bpp	= tga.header[4];										// Determine the bits per pixel
	tga.Width		= this->width;										// Copy width into local structure						
	tga.Height		= this->height;										// Copy height into local structure
	tga.Bpp			= this->bpp;											// Copy BPP into local structure

	if((this->width <= 0) || (this->height <= 0) || ((this->bpp != 24) && (this->bpp !=32)))	// Make sure all information is valid
	{
		//MessageBox(NULL, "Invalid texture information", "ERROR", MB_OK);	// Display Error
		TGAerror=TGA_ERROR_TEX_INFO;
		if(fTGA != NULL)													// Check if file is still open
		{
			fclose(fTGA);													// If so, close it
		}
		return false;														// Return failed
	}

	if(this->bpp == 24)													// If the BPP of the image is 24...
	{
		this->type	= GL_RGB;											// Set Image type to GL_RGB
		UseAlpha=false;
	}
	else																	// Else if its 32 BPP
	{
		this->type	= GL_RGBA;											// Set image type to GL_RGBA
		UseAlpha=true;
	}

	tga.bytesPerPixel	= (tga.Bpp / 8);									// Compute the number of BYTES per pixel
	tga.imageSize		= (tga.bytesPerPixel * tga.Width * tga.Height);		// Compute the total amout ofmemory needed to store data
	this->imageData	= new GLubyte[tga.imageSize];					// Allocate that much memory

	if(this->imageData == NULL)											// If no space was allocated
	{
		//MessageBox(NULL, "Could not allocate memory for image", "ERROR", MB_OK);	// Display Error
		TGAerror=TGA_ERROR_NOT_ALLOCAT_RAM;
		fclose(fTGA);														// Close the file
		return false;														// Return failed
	}

	if(fread(this->imageData, 1, tga.imageSize, fTGA) != tga.imageSize)	// Attempt to read image data
	{
		//MessageBox(NULL, "Could not read image data", "ERROR", MB_OK);		// Display Error
		TGAerror=TGA_ERROR_NOT_READ_IMAGE_DATA;
		if(this->imageData != NULL)										// If imagedata has data in it
		{
			delete [] this->imageData;										// Delete data from memory
			this->imageData=NULL;
		}
		fclose(fTGA);														// Close file
		return false;														// Return failed
	}

	// Byte Swapping Optimized By Steve Thomas
	for(GLuint cswap = 0; cswap < (int)tga.imageSize; cswap += tga.bytesPerPixel)
	{
		this->imageData[cswap] ^= this->imageData[cswap+2] ^=
		this->imageData[cswap] ^= this->imageData[cswap+2];
	}

	fclose(fTGA);															// Close file
	return true;															// Return success
}
void TGA::DelTGA_RAM()
{
	if(imageData)
		delete [] this->imageData ;
	isRAM=false;
	this->imageData=NULL;
}
void TGA::DelTGA_VRAM()
{
	if(this->texID)
		glDeleteTextures(1, &this->texID);
	isVRAM=false;
	this->texID=0;
}