
#include <math.h>
#include <stdio.h>
#include <string.h>	
#include "Load3DS.h"

CLoad3DS::CLoad3DS(void)
: isRAM(false)
, isVRAM(false)
, VBOSupported(false)
, TotelVertices(0)
, TotelMeshs(0)
, VBOIDs(NULL)
, Error(0)
, MeshLoadNum(0)
{
}

CLoad3DS::~CLoad3DS(void)
{
	Del_RAM();
	Del_VRAM();
}

bool CLoad3DS::Loadfile(char * filename)
{
	if (glewIsSupported("GL_ARB_vertex_buffer_object"))
		VBOSupported=true;
	else
		VBOSupported=false;

	Model3ds=lib3ds_file_open(filename);
	if(!Model3ds)
	{
		Error=ERROR_NOT_OPEN_FILE;
		isRAM=false;
		return false;
	}
	TotelMeshs=Model3ds->nmeshes+2;
	if(!TotelMeshs)
	{
		Error=ERROR_NO_MESH;
		isRAM=false;
		return false;
	}
	if(VBOSupported)
	{
		VBOIDs = new tModelNodes[TotelMeshs];
		for(int i=0;i<TotelMeshs;i++)
		{
			VBOIDs[i].VerticeID=0;
			VBOIDs[i].ColorID=0;
			VBOIDs[i].TexCoordID=0;
			VBOIDs[i].NormalID=0;
			VBOIDs[i].TangentID=0;
		}
	}
	lib3ds_file_eval(Model3ds, 0.0f);
	isRAM=true;
	return true;
}

bool CLoad3DS::LoadToVRAM(void)
{
	if(!Model3ds)
	{
		isVRAM=false;
		return false;
	}
	if(Error)
	{
		isVRAM=false;
		return false;
	}
	Lib3dsNode *ThisNode=0;
	for(ThisNode=Model3ds->nodes;ThisNode!=NULL;ThisNode=ThisNode->next)
	{

		LoadNode(ThisNode);
	}
	isVRAM=true;
	return true;
}

void CLoad3DS::Del_RAM(void)
{
	lib3ds_file_free(Model3ds);
	Model3ds=NULL;
	isRAM=false;
}

void CLoad3DS::Del_VRAM(void)
{
	for(int i=0;i<TotelMeshs;i++)
	{
		if(VBOIDs[i].VerticeID)
			glDeleteBuffersARB(1,&VBOIDs[i].VerticeID);
		if(VBOIDs[i].ColorID)
			glDeleteBuffersARB(1,&VBOIDs[i].ColorID);
		if(VBOIDs[i].TexCoordID)
			glDeleteBuffersARB(1,&VBOIDs[i].TexCoordID);
		if(VBOIDs[i].NormalID)
			glDeleteBuffersARB(1,&VBOIDs[i].NormalID);
		if(VBOIDs[i].TangentID)
			glDeleteBuffersARB(1,&VBOIDs[i].TangentID);
	}
	delete[] VBOIDs;
	VBOIDs=NULL;
	isVRAM=false;
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
}
void CLoad3DS::RenderNode(Lib3dsNode *Node)
{
	if(!Node)
		return ;
	Lib3dsMeshInstanceNode * MeshData = (Lib3dsMeshInstanceNode *)Node;

	if(!MeshData)
		return ;
	glMultMatrixf(&Node->matrix[0][0]);  
	glTranslatef(-MeshData->pivot[0],-MeshData->pivot[1],-MeshData->pivot[2]);
	Lib3dsNode      *pNode; 
	for (pNode=Node->childs; pNode!=0; pNode=pNode->next){   
        RenderNode(pNode);   
    } 
	if(Node->type!=LIB3DS_NODE_MESH_INSTANCE)
		return ;
	if(strcmp(Node->name,"$$$DUMMY")==0)
		return ;

/*
	Lib3dsMesh *Mesh=0;
	Mesh=lib3ds_file_mesh_for_node(Model3ds,Node);
	float       M1[4][4]; 
	float       M2[4][4]; 
	lib3ds_matrix_copy(M1, Node->matrix);   
	lib3ds_matrix_inv(M1);   
	lib3ds_matrix_copy(M2, Mesh->matrix);   
	lib3ds_matrix_inv(M2); 
	
*/

	//glColor3f(float(VBOIDs[Node->user_id].VerticeNum%255)/255.0f,float(VBOIDs[Node->user_id].VerticeNum%255)/255.0f,float(VBOIDs[Node->user_id].VerticeNum%255)/255.0f);
	int i=Node->user_id;


	glMultMatrixf(&VBOIDs[i].MeshMatrix[0][0]); 

	glEnableClientState( GL_VERTEX_ARRAY );
	if(VBOIDs[i].NormalID)
		glEnableClientState( GL_NORMAL_ARRAY );
	if(VBOIDs[i].TexCoordID)
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	if(VBOIDs[i].ColorID)
		glEnableClientState( GL_COLOR_ARRAY );

	glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOIDs[i].VerticeID );
	glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );
	if(VBOIDs[i].NormalID)
	{
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOIDs[i].NormalID );
		glNormalPointer( GL_FLOAT, 0, (char *) NULL );
	}
	if(VBOIDs[i].TexCoordID)
	{
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOIDs[i].TexCoordID );
		glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );
	}
	if(VBOIDs[i].ColorID)
	{
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOIDs[i].ColorID );
		glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );
	}
	glDrawArrays( GL_TRIANGLES, 0, VBOIDs[i].VerticeNum );	

	glDisableClientState( GL_VERTEX_ARRAY );
	if(VBOIDs[i].NormalID)
		glDisableClientState( GL_NORMAL_ARRAY );
	if(VBOIDs[i].TexCoordID)
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	if(VBOIDs[i].ColorID)
		glDisableClientState( GL_COLOR_ARRAY );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );

}
void CLoad3DS::Render(float current_frame)
{
	lib3ds_file_eval(Model3ds, current_frame);
	if((TotelVertices<=0)||(TotelMeshs<=0)||(!isVRAM))
		return;
	Lib3dsNode *ThisNode=0;
	for(ThisNode=Model3ds->nodes;ThisNode!=NULL;ThisNode=ThisNode->next)
	{
		glPushMatrix();
			RenderNode(ThisNode);
		glPopMatrix();
	}
}

bool CLoad3DS::LoadNode(Lib3dsNode *Node)
{
	if(!Node)
		return false;
	Lib3dsNode      *pNode; 
	for (pNode=Node->childs; pNode!=0; pNode=pNode->next)
		LoadNode(pNode);

	if(Node->type!=LIB3DS_NODE_MESH_INSTANCE)
		return false;
	if(strcmp(Node->name,"$$$DUMMY")==0)
		return false;
	//if(strcmp(Node->name,"Box01")==0)
	//	return false;

	if(Node->user_id!=0)
		return false;

	Lib3dsMesh *Mesh=0;
	Mesh=lib3ds_file_mesh_for_node(Model3ds,Node);
	if(!Mesh->vertices)
		return false;            //if no vertices ,Nothing to do.
	if(MeshLoadNum>=TotelMeshs)
		return false;  
	Node->user_id=MeshLoadNum;
	float * VBOverticesBuffer=new float[Mesh->nfaces*3*3*4];
	float (* VBONormalsBuffer)[3]=(float(*)[3])new float[Mesh->nfaces*3*3*4];
	
	float * VBOTexCoordBuffer=NULL;
	if(Mesh->texcos)
			VBOTexCoordBuffer=new float[Mesh->nfaces*3*2*4];

	lib3ds_mesh_calculate_vertex_normals(Mesh, VBONormalsBuffer); 

	Lib3dsFace *Face=0;
	VBOIDs[Node->user_id].VerticeNum=Mesh->nfaces*3;
	TotelVertices=TotelVertices+Mesh->nfaces*3;

	for(int i=0;i<Mesh->nfaces;i++)
	{
		Face=&(Mesh->faces[i]);
		for(int j=0;j<3;j++)
		{
			VBOverticesBuffer[i*3*3+j*3+0]=Mesh->vertices[Face->index[j]][0];
			VBOverticesBuffer[i*3*3+j*3+1]=Mesh->vertices[Face->index[j]][1];
			VBOverticesBuffer[i*3*3+j*3+2]=Mesh->vertices[Face->index[j]][2];

			if(Mesh->texcos)
			{
				VBOTexCoordBuffer[i*3*2+j*2+0]=Mesh->texcos[Face->index[j]][0];
				VBOTexCoordBuffer[i*3*2+j*2+1]=Mesh->texcos[Face->index[j]][1];
			}
		}
	}
	glGenBuffersARB( 1,&VBOIDs[Node->user_id].VerticeID);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOIDs[Node->user_id].VerticeID );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, Mesh->nfaces*3*3*sizeof(float), VBOverticesBuffer, GL_STATIC_DRAW_ARB );
	delete[] VBOverticesBuffer;
	VBOverticesBuffer=NULL;

	glGenBuffersARB( 1,&VBOIDs[Node->user_id].NormalID);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOIDs[Node->user_id].NormalID );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, Mesh->nfaces*3*3*sizeof(float), VBONormalsBuffer, GL_STATIC_DRAW_ARB );
	delete[] VBONormalsBuffer;
	VBONormalsBuffer=NULL;

	if(Mesh->texcos)
	{
		glGenBuffersARB( 1,&VBOIDs[Node->user_id].TexCoordID);
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOIDs[Node->user_id].TexCoordID );
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, Mesh->nfaces*3*2*sizeof(float), VBOTexCoordBuffer, GL_STATIC_DRAW_ARB );
		delete[] VBOTexCoordBuffer;
		VBOTexCoordBuffer=NULL;
	}

	lib3ds_matrix_copy(VBOIDs[Node->user_id].MeshMatrix, Mesh->matrix);   
	lib3ds_matrix_inv(VBOIDs[Node->user_id].MeshMatrix); 
	
	MeshLoadNum=MeshLoadNum+1;
	return true;
}
