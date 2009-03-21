#include "BomTeams.h"
bool LoadTGA(Texture *, char *);
unsigned int BomTEXsNum[MAXBOMTEXS];
CBomTeams::CBomTeams(void)
: Num(0)
{
}

CBomTeams::~CBomTeams(void)
{
}

bool CBomTeams::LoadBomTeam(int BomTeamNum)
{
	
	FILE *File=NULL;
	char BomsIniName[64]={0};
	sprintf(BomsIniName,".\\Data\\Boms\\Bomini%d.ini",BomTeamNum);
	File=fopen(BomsIniName,"r");	
	if(File)
	{
		fclose(File);


			m_BomsNumber=GetPrivateProfileInt("MainSet","BomACTsMax",0,BomsIniName);
			if(m_BomsNumber>MAXBOMACTS)
			{
				m_BomsNumber=MAXBOMACTS;
				char WaringString[64]={0};
				sprintf(WaringString,"Bomini%d.ini BomACTsMax more than %d",BomTeamNum,MAXBOMACTS);
				::MessageBox(HWND_DESKTOP,WaringString,"Error",MB_OK | MB_ICONEXCLAMATION);
			}
			if(m_BomsNumber>0)
			{
				for(int i=0;i<m_BomsNumber;i++)
				{
					char BomsInilocalName[64]={0};
					sprintf(BomsInilocalName,"Bom%d",i);
					int Ploadnum=GetPrivateProfileInt(BomsInilocalName,"Pnum",-1,BomsIniName);
					if(Ploadnum>-1)
					{
						//unsigned int BomTEXsNum[MAXBOMTEXS];
						Bomini[i].Pnum=Ploadnum;
						if(Ploadnum<MAXBOMTEXS)
							Bomini[i].TEXNum=BomTEXsNum[Ploadnum];
						else
						{
							char WaringString[64]={0};
							sprintf(WaringString,"Bomini%d.ini Bom%d Pnum more than %d",BomTeamNum,i,MAXBOMTEXS);
							::MessageBox(HWND_DESKTOP,WaringString,"Error",MB_OK | MB_ICONEXCLAMATION);
							Bomini[i].TEXNum=0;
						}
						Bomini[i].SizeStart			= GetPrivateProfileInt( BomsInilocalName , "SizeStart"		, 0 , BomsIniName );
						Bomini[i].SizeEnd			= GetPrivateProfileInt( BomsInilocalName , "SizeEnd"		, 0 , BomsIniName );
						Bomini[i].ShowTimeStart		= GetPrivateProfileInt( BomsInilocalName , "ShowTimeStart"	, 0 , BomsIniName );
						Bomini[i].ShowTimeEnd		= GetPrivateProfileInt( BomsInilocalName , "ShowTimeEnd"	, 0 , BomsIniName );
						Bomini[i].ColorAlphaStart	= GetPrivateProfileInt( BomsInilocalName , "ColorAlphaStart", 0 , BomsIniName );
						Bomini[i].ColorAlphaEnd		= GetPrivateProfileInt( BomsInilocalName , "ColorAlphaEnd"	, 0 , BomsIniName );
						Bomini[i].AlpahType			= GetPrivateProfileInt( BomsInilocalName , "AlphaType"		, 0 , BomsIniName );
						AllFrame=Bomini[i].ShowTimeEnd;
					}
					
				}
				return true;
			}
			else
			{
				char WaringString[64]={0};
				sprintf(WaringString,"Bomini%d.ini BomACTsMax=0",BomTeamNum);
				::MessageBox(HWND_DESKTOP,WaringString,"Error",MB_OK | MB_ICONEXCLAMATION);
			}
		

	}
	else
	{
		/*
		char WaringString[64]={0};
		sprintf(WaringString,"There is no Bomini%d.ini",BomTeamNum);
		::MessageBox(HWND_DESKTOP,WaringString,"Error",MB_OK | MB_ICONEXCLAMATION);
*/
		WritePrivateProfileString("MainSet","BomACTsMax","0",BomsIniName);
		WritePrivateProfileString("Bom0","Pnum","0",BomsIniName);
		WritePrivateProfileString("Bom0","SizeStart","0",BomsIniName);
		WritePrivateProfileString("Bom0","SizeEnd","0",BomsIniName);
		WritePrivateProfileString("Bom0","ShowTimeStart","0",BomsIniName);
		WritePrivateProfileString("Bom0","ShowTimeEnd","0",BomsIniName);
		WritePrivateProfileString("Bom0","ColorAlphaStart","0",BomsIniName);
		WritePrivateProfileString("Bom0","ColorAlphaEnd","0",BomsIniName);
		WritePrivateProfileString("Bom0","AlphaType","0",BomsIniName);
	}
	return false;
	
}
int CBomTeams::DrawBomTeam(float posX, float posY, float posZ, int frame, unsigned int GLlistNum,float TeamSize)
{
	if(m_BomsNumber>MAXBOMACTS)
			{
				m_BomsNumber=MAXBOMACTS;
				char WaringString[64]={0};
				sprintf(WaringString,"m_BomsNumber in DrawBomTeam more than %d",MAXBOMACTS);
				::MessageBox(HWND_DESKTOP,WaringString,"Error",MB_OK | MB_ICONEXCLAMATION);
			}
	if(m_BomsNumber>0)
		if(frame<=Bomini[m_BomsNumber-1].ShowTimeEnd)
			for(int i=0;i<m_BomsNumber;i++)
			{
				if((Bomini[i].ShowTimeStart <= frame) && (Bomini[i].ShowTimeEnd >= frame))
				{
					int tmptime1=Bomini[i].ShowTimeEnd-Bomini[i].ShowTimeStart;
					int tmptime2=Bomini[i].ShowTimeEnd-frame;
					if(tmptime1<1)
						tmptime1=tmptime2;
					float tmpbili=(float)tmptime2/(float)tmptime1;

					int tmpsize1=Bomini[i].SizeEnd-Bomini[i].SizeStart;
					float tmpsize2=(float)Bomini[i].SizeEnd-(float)tmpsize1*tmpbili;

					int tmpalpha1=Bomini[i].ColorAlphaEnd-Bomini[i].ColorAlphaStart;
					float tmpalpha2=((float)Bomini[i].ColorAlphaEnd-(float)tmpalpha1*tmpbili)/255.0f;

					if(Bomini[i].SizeEnd==Bomini[i].SizeStart)
						tmpsize2=(float)Bomini[i].SizeEnd;
					tmpsize2=tmpsize2*TeamSize;
					if(Bomini[i].ColorAlphaEnd==Bomini[i].ColorAlphaStart)
						tmpalpha2=(float)Bomini[i].ColorAlphaEnd;

					if(Bomini[i].AlpahType==0)
						glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
					if(Bomini[i].AlpahType==1)
						glBlendFunc(GL_SRC_ALPHA,GL_ONE);

					//glPrintBom1((float)bompos(0),(float)bompos(1),(float)bompos(2),tmpsize2,tmpalpha2,Bomini[i].Pnum);
					glLoadIdentity();
					glBindTexture(GL_TEXTURE_2D, Bomini[i].TEXNum);
					glTranslated(posX,posY,posZ);
					glColor4f(tmpalpha2,tmpalpha2,tmpalpha2,tmpalpha2);
					glBegin(GL_QUADS);							// Use A Quad For Each Character
						glTexCoord2f(0.0f,0.0f);			// Texture Coord (Bottom Left)
						glVertex2f(-tmpsize2,-tmpsize2);						// Vertex Coord (Bottom Left)
						glTexCoord2f(1.0f,0.0f);	// Texture Coord (Bottom Right)
						glVertex2f(tmpsize2,-tmpsize2);						// Vertex Coord (Bottom Right)
						glTexCoord2f(1.0f,1.0f);			// Texture Coord (Top Right)
						glVertex2f(tmpsize2,tmpsize2);						// Vertex Coord (Top Right)
						glTexCoord2f(0.0f,1.0f);					// Texture Coord (Top Left)
						glVertex2f(-tmpsize2,tmpsize2);						// Vertex Coord (Top Left)
					glEnd();
					glColor4f(1.0f,1.0f,1.0f,1.0f);
				}
			}
	return 0;
}

//************************************************************************************************




CBomType::CBomType(void)
: loadBomTEXsNum(0)
, m_IsSupportFBO(false)
, BomType(0)
{
}
CBomType::~CBomType(void)
{
}
bool CBomType::LoadTypeIni(int TypeNum)
{
	FILE *File=NULL;
	char BomsIniName[64]={0};
	sprintf(BomsIniName,".\\Data\\Boms\\BomType%d.ini",TypeNum);
	File=fopen(BomsIniName,"r");	
	if(File)
	{
		fclose(File);


			m_AllBomTeamsNum=GetPrivateProfileInt("MainSet","BomTeamsMax",0,BomsIniName);
			if(m_AllBomTeamsNum>MAXBOMINIS)
			{
				m_AllBomTeamsNum=MAXBOMINIS;
				char WaringString[64]={0};
				sprintf(WaringString,"BomType%d.ini BomTeamsMax more than %d",TypeNum,MAXBOMINIS);
				::MessageBox(HWND_DESKTOP,WaringString,"Error",MB_OK | MB_ICONEXCLAMATION);
			}
			if(m_AllBomTeamsNum>0)
			{
				for(int i=0;i<m_AllBomTeamsNum;i++)
				{
					char BomsInilocalName[64]={0};
					sprintf(BomsInilocalName,"BomTeam%d",i);
					int Ploadnum=GetPrivateProfileInt(BomsInilocalName,"BomIniNum",-1,BomsIniName);
					if(Ploadnum>-1)
					{
						BomTeams[i].Num=Ploadnum;
						if(GetPrivateProfileInt( BomsInilocalName , "AutoGetPos", 0 , BomsIniName ) > 0)
							BomTeams[i].AutoGetPos=true;
						else
							BomTeams[i].AutoGetPos=false;
						BomTeams[i].RandomSizeMAX = GetPrivateProfileInt( BomsInilocalName , "RandomSizeMAX", 0 , BomsIniName );
						BomTeams[i].RandomSizeMIN = GetPrivateProfileInt( BomsInilocalName , "RandomSizeMIN", 0 , BomsIniName );
						BomTeams[i].RandomMoveMAX = GetPrivateProfileInt( BomsInilocalName , "RandomMoveMAX", 0 , BomsIniName );
						BomTeams[i].RandomMoveMIN = GetPrivateProfileInt( BomsInilocalName , "RandomMoveMIN", 0 , BomsIniName );
						

					}
				}
				return true;
			}
			else
			{
				char WaringString[64]={0};
				sprintf(WaringString,"BomType%d.ini PnumMax=0",TypeNum);
				::MessageBox(HWND_DESKTOP,WaringString,"Error",MB_OK | MB_ICONEXCLAMATION);
			}
		

	}
	else
	{

		WritePrivateProfileString("MainSet"	,"BomTeamsMax"	, "0" , BomsIniName);
		WritePrivateProfileString("BomTeam0","BomIniNum"	, "0" , BomsIniName);
		WritePrivateProfileString("BomTeam0","RandomSizeMAX", "0" , BomsIniName);
		WritePrivateProfileString("BomTeam0","RandomSizeMIN", "0" , BomsIniName);
		WritePrivateProfileString("BomTeam0","RandomMoveMAX", "0" , BomsIniName);
		WritePrivateProfileString("BomTeam0","RandomMoveMIN", "0" , BomsIniName);
		WritePrivateProfileString("BomTeam0","AutoGetPos"	, "0" , BomsIniName);
	}
	return false;
}

unsigned int CBomType::loadBomTEXs(int BomsNum)
{
	Texture LoadBomTexture;
	char BomsFileName[64]={0};
	sprintf(BomsFileName,"Data/Boms/Bom%d.tga",BomsNum);
	FILE	*m_Filefighter;
	if ((m_Filefighter=fopen(BomsFileName,"rb"))==NULL)
		return 0;
	if (LoadTGA(&LoadBomTexture, BomsFileName))
	{
		glGenTextures(1, &LoadBomTexture.texID);
		glBindTexture(GL_TEXTURE_2D, LoadBomTexture.texID);
		glTexImage2D(GL_TEXTURE_2D, 0, LoadBomTexture.bpp / 8, LoadBomTexture.width, LoadBomTexture.height, 0, LoadBomTexture.type, GL_UNSIGNED_BYTE, LoadBomTexture.imageData);
		if(m_IsSupportFBO)
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		}
		if (LoadBomTexture.imageData)						// If Texture Image Exists ( CHANGE )
		{
			free(LoadBomTexture.imageData);					// Free The Texture Image Memory ( CHANGE )
		}
		BomTEXsNum[BomsNum]=LoadBomTexture.texID;
		if(BomsNum==MAXBOMTEXS)
			return 0;
		return LoadBomTexture.texID;

	}
	return 0;
}
bool CBomType::InitBomType(int TypeNum)
{
	BomType=TypeNum;
	while(loadBomTEXs(loadBomTEXsNum)>0)
	{
		loadBomTEXsNum=loadBomTEXsNum+1;
	}

	return LoadTypeIni(TypeNum)&&InitBomTeams();
}

bool CBomType::InitBomTeams(void)
{
	
	bool IsLoadOK=false;
	for(int i=0;i<m_AllBomTeamsNum;i++)
	{
		IsLoadOK=BomTeams[i].LoadBomTeam(i);
	}
	return IsLoadOK;
}

//*****************************************************

CBom::CBom(void)
: Frame(0)
, life(0)
, m_Timer(0)
, x(0)
, y(0)
, z(0)
, Movex(0)
, Movey(0)
, Movez(0)
, BomType(0)
, BomTeam(0)
, RandomSize(0)
{
}
CBom::~CBom(void)
{
}
int CBom::NewBom(float posx, float posy, float posz, CBomType * m_pBom)
{

	BomType=m_pBom->BomType;
	Frame=0;
	life=100;
	m_Timer=0;
	BomTeam=rand()%(m_pBom->m_AllBomTeamsNum);
	if(BomTeam>(m_pBom->m_AllBomTeamsNum-1))
		BomTeam=m_pBom->m_AllBomTeamsNum-1;
	if(BomTeam<0)
		BomTeam=0;
	x=posx;
	y=posy;
	z=posz;
	AutoGetPos=m_pBom->BomTeams[BomTeam].AutoGetPos;
	int MoveTMP=m_pBom->BomTeams[BomTeam].RandomMoveMAX-m_pBom->BomTeams[BomTeam].RandomMoveMIN;
	int TPMmin=m_pBom->BomTeams[BomTeam].RandomMoveMIN;
	if(MoveTMP!=0)
	{

		Movex=rand()%(MoveTMP*2)-MoveTMP;
		if(Movex>0)
			Movex=Movex+TPMmin;
		else
			Movex=Movex-TPMmin;

		Movey=rand()%(MoveTMP*2)-MoveTMP;
		if(Movey>0)
			Movey=Movey+TPMmin;
		else
			Movey=Movey-TPMmin;

		Movez=rand()%(MoveTMP*2)-MoveTMP;
		if(Movez>0)
			Movez=Movez+TPMmin;
		else
			Movez=Movez-TPMmin;
	}
	else
	{
		Movex=(rand()%2-1)*TPMmin;
		Movey=(rand()%2-1)*TPMmin;
		Movez=(rand()%2-1)*TPMmin;
		//Movex=Movey=Movez=m_pBom->BomTeams[BomTeam].RandomMoveMIN;
	}
	RandomSize=m_pBom->BomTeams[BomTeam].RandomSizeMAX-m_pBom->BomTeams[BomTeam].RandomSizeMIN;
	if(RandomSize!=0)
		RandomSize=rand()%RandomSize+m_pBom->BomTeams[BomTeam].RandomSizeMIN;
	else
		RandomSize=m_pBom->BomTeams[BomTeam].RandomSizeMIN;
		
	
	return 0;
}

int CBom::DrawBom(float posx, float posy, float posz, CBomType * m_pBom)
{
	x=x+(float)Movex*0.01f;
	y=y+(float)Movey*0.01f;
	z=z+(float)Movez*0.01f;
	if((BomTeam<0)||(BomTeam>=MAXBOMINIS))
		return 0;
	m_pBom->BomTeams[BomTeam].DrawBomTeam(posx,posy,posz,Frame,0,(float)RandomSize/100.0f);
	Frame=Frame+1;
	if(Frame>m_pBom->BomTeams[BomTeam].AllFrame)
		this->life=0;
	return 0;
}
