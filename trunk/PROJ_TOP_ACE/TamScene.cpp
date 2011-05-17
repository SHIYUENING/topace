#include "TamScene.h"
#include "Common.h"
WIN32_FIND_DATAW   filedata; 
wchar_t * FindFileWithExtName(wchar_t * ExtName)
{
	if(!ExtName) return 0;
	if(!GetCharLenth(ExtName)) return 0;
	HANDLE   filehandle;
	filehandle=FindFirstFileW(ExtName,&filedata);
	if(filehandle==INVALID_HANDLE_VALUE) 
	{
		FindClose(filehandle);
		return 0;
	}
	FindClose(filehandle);
	return filedata.cFileName;
}

CTamScene::CTamScene(void)
	:ModelNum(0)
{
}


CTamScene::~CTamScene(void)
{
	//ClearScene();
}


void CTamScene::LoadFile(wchar_t * ModelFolder)
{
	if(!ModelFolder) return;
	if(!GetCharLenth(ModelFolder)) return;
	TamList.clear(); 
	wstring ModelPath(ModelFolder),ModelFindName(L"*.*");
	ModelPath+=ModelFindName;
	HANDLE   filehandle;
	filehandle=FindFirstFileW(ModelPath.c_str(),&filedata);
	if(filehandle==INVALID_HANDLE_VALUE) 
	{
		FindClose(filehandle);
		return;
	}
	if(filedata.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
	if((wcscmp(filedata.cFileName,L".")!=0)&&(wcscmp(filedata.cFileName,L"..")!=0))
	{
		wstring ModelPathTMP(ModelFolder);
		ModelPathTMP+=filedata.cFileName;
		
		_TamUnit TamUnitTMP;
		if(AddUnit(ModelPathTMP,&TamUnitTMP))
			TamList.push_back(TamUnitTMP);
	}
	while(FindNextFileW(filehandle,&filedata))
	{
		if(filehandle==INVALID_HANDLE_VALUE)
			continue;
		if(filedata.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		if((wcscmp(filedata.cFileName,L".")!=0)&&(wcscmp(filedata.cFileName,L"..")!=0))
		{
			wstring ModelPathTMP(ModelFolder);
			ModelPathTMP+=filedata.cFileName;
			
			_TamUnit TamUnitTMP;
			if(AddUnit(ModelPathTMP,&TamUnitTMP))
				TamList.push_back(TamUnitTMP);
		}
	}
	FindClose(filehandle);
	if(TamList.empty()) return;
	ModelNum=TamList.size();
}


void CTamScene::ClearScene(void)
{
	for(unsigned int i=0;i<TamList.size();i++)
	{
		if(TamList[i].Model)
			delete TamList[i].Model;
	}
	TamList.clear();
}
inline float GetIniFloat(wchar_t * lpAppName,wchar_t * lpKeyName,const wchar_t * lpFileName)
{
	wchar_t ReadIniTMP[512];
	float IniFloat=0.0f;
	GetPrivateProfileStringW(lpAppName,lpKeyName,L"0",ReadIniTMP,512,lpFileName);
	swscanf_s(ReadIniTMP,L"%f",&IniFloat);
	return IniFloat;
}

bool CTamScene::AddUnit(wstring  ModelPath,_TamUnit * TamUnit)
{
	if(!TamUnit) return false;
	if(ModelPath.empty()) return false;
	HANDLE   filehandle;
	wstring ModelPathTMP(ModelPath);
	ModelPathTMP+=L"\\*.tam";
	filehandle=FindFirstFileW(ModelPathTMP.c_str(),&filedata);
	if(filehandle==INVALID_HANDLE_VALUE) 
	{
		FindClose(filehandle);
		return 0;
	}
	FindClose(filehandle);
	TamUnit->Model=new CTopAceModel;
	ModelPathTMP=ModelPath;
	ModelPathTMP+=L'\\';
	ModelPathTMP+=filedata.cFileName;
	TamUnit->Model->ReadTAMFile((wchar_t*)ModelPathTMP.c_str());
	ModelPathTMP=ModelPath;
	ModelPathTMP+=L"\\set.ini";
	GetPrivateProfileStringW(L"set",L"name",L"No Name",TamUnit->Name,64,ModelPathTMP.c_str());

	TamUnit->Pos[0]=GetIniFloat(L"pos",L"x",ModelPathTMP.c_str());
	TamUnit->Pos[1]=GetIniFloat(L"pos",L"y",ModelPathTMP.c_str());
	TamUnit->Pos[2]=GetIniFloat(L"pos",L"z",ModelPathTMP.c_str());
	TamUnit->scale[0]=GetIniFloat(L"scale",L"x",ModelPathTMP.c_str())*0.0001f;
	TamUnit->scale[1]=GetIniFloat(L"scale",L"y",ModelPathTMP.c_str())*0.0001f;
	TamUnit->scale[2]=GetIniFloat(L"scale",L"z",ModelPathTMP.c_str())*0.0001f;
	TamUnit->Limitfar=GetIniFloat(L"Limit",L"far",ModelPathTMP.c_str());
	TamUnit->Limitnear=GetIniFloat(L"Limit",L"near",ModelPathTMP.c_str());
	__m128 DrawMatrix[4];
	Easy_matrix_identity(DrawMatrix);
	Easy_matrix_scale(DrawMatrix,_mm_set_ps(1.0,TamUnit->scale[2],TamUnit->scale[1],TamUnit->scale[0]));
	Easy_matrix_translate_External(DrawMatrix,_mm_set_ps(1.0,TamUnit->Pos[2],TamUnit->Pos[1],TamUnit->Pos[0]));
	Easy_matrix_copy(TamUnit->Matrix,DrawMatrix);
	return true;
}


void CTamScene::ToVRAM(void)
{
	for(unsigned int i=0;i<TamList.size();i++)
	{
		if(TamList[i].Model)
			TamList[i].Model->LoadToVRAM();
	}
}


void CTamScene::Draw(bool Translucent,_TAM_Mesh_EXT_Type DrawType)
{
	for(unsigned int i=0;i<TamList.size();i++)
	{
		if(TamList[i].Model)
		{
			CommonMatrixs[CO_Matrix_World].Push();
			CommonMatrixs[CO_Matrix_World].MultF(TamList[i].Matrix);
			TamList[i].Model->Draw(Translucent,DrawType);
			CommonMatrixs[CO_Matrix_World].Pop();
		}
	}
}


void CTamScene::GetUnitWinPos(float * UnitWinPos,int UnitID)
{
	int viewports[]={0,0,GameSet.winW,GameSet.winH};
	double windowCoordinate[3];
	CommonMatrixs[CO_Matrix_ModelView].Push();
	CommonMatrixs[CO_Matrix_ModelView].MultD(CommonMatrixs[CO_Matrix_World].LinkList->Matrix);
	PointProjectD(
		TamList[UnitID].Pos[0],
		TamList[UnitID].Pos[1],
		TamList[UnitID].Pos[2],
		CommonMatrixs[CO_Matrix_ModelView].LinkList->Matrix,
		CommonMatrixs[CO_Matrix_Proj].LinkList->Matrix,
		viewports,
		windowCoordinate);
	CommonMatrixs[CO_Matrix_ModelView].Pop();
	UnitWinPos[0]=(float)windowCoordinate[0];
	UnitWinPos[1]=(float)windowCoordinate[1];
	UnitWinPos[2]=(float)windowCoordinate[2];
}


void CTamScene::DrawUnitLine(int UnitID,int winW,int winH)
{
	float LinePoss[6]={0.0f,0.0f,0.5f,float(winW/2),float(winH/2),0.5f};
	GetUnitWinPos(LinePoss,UnitID);
	LinePoss[2]=0.0f;
	glDisable( GL_CULL_FACE );
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,winW,0,winH,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, LinePoss );
	glDrawArrays(GL_LINES,0,2);
	glDisableClientState( GL_VERTEX_ARRAY );

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glEnable( GL_CULL_FACE );
	glEnable(GL_TEXTURE_2D);
}


void CTamScene::DrawUnitLineAll(int winW,int winH)
{
	for(unsigned int i=0;i<TamList.size();i++)
	{
		DrawUnitLine(i,winW,winH);
	}
}


void CTamScene::DrawUnitName(void)
{
	for(unsigned int i=0;i<TamList.size();i++)
	{
	}
}
