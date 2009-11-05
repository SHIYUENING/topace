#include "LoadData_thread.h"
#include <stdio.h>	
#include <pthread.h>

extern pthread_mutex_t mutex_LoadData;
extern pthread_cond_t cond_LoadData;
extern tLoadDataList * LoadDataList;
void Initthread_LoadData()
{
	LoadDataList = new tLoadDataList;
	LoadDataList->Data=NULL;
	LoadDataList->DataPath[0]=0;
	LoadDataList->DataPointer=NULL;
	LoadDataList->DataType=0;
	LoadDataList->NextNode=NULL;
	LoadDataList->DataSet=NULL;

	pthread_attr_t attr_LoadData; 
	pthread_attr_init(&attr_LoadData); 
	pthread_attr_setscope(&attr_LoadData, PTHREAD_SCOPE_PROCESS);
    pthread_attr_setdetachstate(&attr_LoadData, PTHREAD_CREATE_DETACHED);
	pthread_t threadID_LoadData;
	pthread_mutex_init(&mutex_LoadData, NULL);
	pthread_cond_init(&cond_LoadData,NULL);
	pthread_create( &threadID_LoadData, &attr_LoadData, LoadData, NULL);
}
void* LoadData(void* Param)
{
	while(true)
	{
		pthread_mutex_lock( &mutex_LoadData );
		pthread_cond_wait( &cond_LoadData ,&mutex_LoadData);
		tLoadDataList * loadnod=LoadDataList;
		while(loadnod)
		{
			switch(loadnod->DataType)
			{
				case DATATYPE_TEXTURE: Textures * pLoadTexture;
					pLoadTexture = new Textures;
					pLoadTexture->loadfile(loadnod->DataPath);
					loadnod->Data = pLoadTexture;
					loadnod = loadnod->NextNode;
					break;

				case DATATYPE_FONT2D: CFont2D * pLoadFont2D;
					pLoadFont2D = new CFont2D;
					
					if(loadnod->DataSet)
					{
						tFont2Dset * Font2Dset = (tFont2Dset *)loadnod->DataSet;
						pLoadFont2D->LoadFont(
						loadnod->DataPath,
						Font2Dset->FontSizeW,
						Font2Dset->FontSizeH,
						Font2Dset->FontW,
						Font2Dset->FontH,
						Font2Dset->CHARSET
						);
					}
					else
						pLoadFont2D->LoadFont(loadnod->DataPath,0,0);
					loadnod->Data = pLoadFont2D;
					loadnod = loadnod->NextNode;
					break;

				case DATATYPE_FONT3D: CFont3D * pLoadFont3D;
					pLoadFont3D = new CFont3D;
					if(loadnod->DataSet)
						pLoadFont3D->LoadFont(loadnod->DataPath,*(int*)loadnod->DataSet);
					else
						pLoadFont3D->LoadFont(loadnod->DataPath);
					loadnod->Data = pLoadFont3D;
					loadnod = loadnod->NextNode;
					break;

			}
		
		}
		pthread_mutex_unlock( &mutex_LoadData );
	}
	return NULL;
}