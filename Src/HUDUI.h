#pragma once

unsigned int EmptyTexture(int wh=256,bool isGL_LINEAR=true)	;
void LoadGLTextures();
void DrawUI1totexture(double latitude);
void DrawUI2totexture(double speed);
void DrawUI3totexture(double ATL);
void DrawUI1(double rotation);
void DrawUI2();
void DrawUI3();
void DrawUI4(float turnX=0.0f,float turnY=0.0f,float turnZ=0.0f);
void DrawTex(unsigned int PTexID,int posx,int posy,int SizeW,int SizeH,int winW,int winH,float colorR,float colorG,float ColorB,float ColorA);
void DrawBlackBack(int Size);
void DrawRedarToTexture();
void DrawMAP();
void DrawAREARedarToTexture(float turn=0.0f);
void DrawRedar(float ne=0.0);
void glPrint(int x, int y, char *string, int set,bool isover800_600=false);
void glPrints(int x, int y, int winW,int winH,char *string);
void glPrintW(float HUDx=0.0,float HUDy=0.0, bool locked=false);
void glPrintRedar(float Rx=0.0,float Ry=0.0, int TGTflag=0,float Renge=10000.0f);
void glPrintAREARedar(float Rx=0.0,float Ry=0.0, int TGTflag=0,float Renge=100000.0f,float turn=0.0f);
void BuildFont();