
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
	TotelMeshs=Model3ds->nmeshes;
	if(!TotelMeshs)
	{
		Error=ERROR_NO_MESH;
		isRAM=false;
		return false;
	}
	if(VBOSupported)
	{
		VBOIDs = new tVBOIDs[TotelMeshs+1];
		for(int i=0;i<TotelMeshs;i++)
		{
			VBOIDs[i].VerticeID=0;
			VBOIDs[i].ColorID=0;
			VBOIDs[i].TexCoordID=0;
			VBOIDs[i].NormalID=0;
			VBOIDs[i].TangentID=0;
		}
	}
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
		LoadNode(ThisNode);
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
	delete VBOIDs;
	VBOIDs=NULL;
	isVRAM=false;
}

void CLoad3DS::Render(void)
{
}

bool CLoad3DS::LoadNode(Lib3dsNode *Node)
{

	if(Node->type!=LIB3DS_NODE_MESH_INSTANCE)
		return false;
	if(strcmp(Node->name,"$$$DUMMY")==0)
		return false;
	if(!Node)
		return false;

	Lib3dsMesh *Mesh=0;
	Mesh=lib3ds_file_mesh_for_node(Model3ds,Node);
	if(!Mesh->vertices)
		return false;            //if no vertices ,Nothing to do.
	float * VBOverticesBuffer=new float[Mesh->nvertices*3];
	float * VBONormalsBuffer=new float[Mesh->nvertices*3];
	Lib3dsFace *Face=0;
	for(int i=0;i<Mesh->nfaces;i++)
	{
		Face=&(Mesh->faces[i]);
		for(int j=0;j<3;j++)
			for(int k=0;k<3;k++)
			{
				VBOverticesBuffer[i*3*3+j*3+k]=Mesh->vertices[Face->index[j]][k];
			}
	}
	glGenBuffersARB( 1,&VBOIDs[Node->node_id].VerticeID);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOIDs[Node->node_id].VerticeID );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, Mesh->nvertices*3*sizeof(float), VBOverticesBuffer, GL_STATIC_DRAW_ARB );
	delete VBOverticesBuffer;
	VBOverticesBuffer=NULL;

	delete VBONormalsBuffer;
	VBONormalsBuffer=NULL;
	
	return false;
}
