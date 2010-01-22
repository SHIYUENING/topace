
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
, GrassTexID(0)
, DiffuseTexID(0)
{
}

CLoad3DS::~CLoad3DS(void)
{
	
	Del_VRAM();
	Del_RAM();
	delete[] VBOIDs;
	VBOIDs=NULL;
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
	for(int i=0;i<MAX_TYPE_3DS_NODE;i++)
		TypeFrame[i]=0.0f;
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
			VBOIDs[i].VerticeNum=0;
			VBOIDs[i].UseMaterial=false;
			for(int j=0;j<MAX_TYPE_3DS_NODE;j++)
				VBOIDs[i].NodeType[j]=false;
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
	if(Model3ds)
		lib3ds_file_free(Model3ds);
	Model3ds=NULL;
	isRAM=false;
}

void CLoad3DS::Del_VRAM(void)
{

	if(Model3ds)
	{
		Lib3dsNode *ThisNode=0;
		for(ThisNode=Model3ds->nodes;ThisNode!=NULL;ThisNode=ThisNode->next)
		{

			Clear3DSIDs(ThisNode);
		}
	}
	if(VBOIDs)
	{
		for(int i=0;i<TotelMeshs;i++)
		{
			VBOIDs[i].VerticeID=0;
			VBOIDs[i].ColorID=0;
			VBOIDs[i].TexCoordID=0;
			VBOIDs[i].NormalID=0;
			VBOIDs[i].TangentID=0;
			VBOIDs[i].VerticeNum=0;
			VBOIDs[i].UseMaterial=false;
			for(int j=0;j<MAX_TYPE_3DS_NODE;j++)
				VBOIDs[i].NodeType[j]=false;
		}
	}
	if((!VBOIDs)||(!isVRAM))
		return;
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

	isVRAM=false;
	TotelVertices=0;
	MeshLoadNum=0;
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
}
void CLoad3DS::RenderNode(Lib3dsNode *Node,bool isTranslucent)
{
	if(!Node)
		return ;
	Lib3dsMeshInstanceNode * MeshData = (Lib3dsMeshInstanceNode *)Node;

	if(!MeshData)
		return ;

	float ThisNodematrix[4][4];
	Lib3dsNode      *pNode; 
	for (pNode=Node->childs; pNode!=0; pNode=pNode->next){  
		//glPushMatrix();
		glGetFloatv(GL_MODELVIEW_MATRIX,&ThisNodematrix[0][0]);
        RenderNode(pNode,isTranslucent);   
		//glPopMatrix();
		glLoadIdentity();
		glLoadMatrixf(&ThisNodematrix[0][0]);
    } 
	if(VBOIDs[Node->user_id].NodeType[TYPE_3DS_NODE_DM])
		return;
	glMultMatrixf(&Node->matrix[0][0]);  
	glTranslatef(-MeshData->pivot[0],-MeshData->pivot[1],-MeshData->pivot[2]);
	if(Node->type!=LIB3DS_NODE_MESH_INSTANCE)
		return ;
	if(strcmp(Node->name,"$$$DUMMY")==0)
		return ;
	//if((Node->name[0]=='W')&&(Node->name[1]=='W'))
	if(VBOIDs[Node->user_id].NodeType[TYPE_3DS_NODE_WW])
		return ;
	
	//if(((Node->name[0]=='G')&&(Node->name[1]=='R'))!=isTranslucent)
	if(VBOIDs[Node->user_id].NodeType[TYPE_3DS_NODE_GR]!=isTranslucent)
		return ;
/*
	if((Node->name[0]=='G')&&(Node->name[1]=='R'))
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );
		glDepthMask(GL_FALSE);
		glBindTexture(GL_TEXTURE_2D, GrassTexID);
	}
	else
	{
		glDisable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D, DiffuseTexID);
	}
*/
		
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
	//Lib3dsMaterial *m = Model3ds->materials[i];
/*
	GLfloat mat_specular[]={1.0f,1.0f,1.0f,1.0f};
	GLfloat mat_ambient[]={0.5f,0.5f,0.5f,1.0f};
	GLfloat mat_diffuse[]={0.5f,0.5f,0.5f,1.0f};
	GLfloat mat_shininess[]={100.0f};*/
	if(VBOIDs[i].UseMaterial)
	{
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,VBOIDs[i].mat_specular);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,VBOIDs[i].mat_ambient);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,VBOIDs[i].mat_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,&VBOIDs[i].mat_shininess);
	}


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
	if(!Model3ds)
		return;
	if(float(Model3ds->frames)>=current_frame)
		lib3ds_file_eval(Model3ds, current_frame);
	if((TotelVertices<=0)||(TotelMeshs<=0)||(!isVRAM))
		return;
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, DiffuseTexID);
	Lib3dsNode *ThisNode=0;
	for(ThisNode=Model3ds->nodes;ThisNode!=NULL;ThisNode=ThisNode->next)
	{
		glPushMatrix();
			RenderNode(ThisNode);
		glPopMatrix();
	}

	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );
	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, GrassTexID);
	for(ThisNode=Model3ds->nodes;ThisNode!=NULL;ThisNode=ThisNode->next)
	{
		glPushMatrix();
			RenderNode(ThisNode,true);
		glPopMatrix();
	}
	glDepthMask(GL_TRUE);
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
	GetNodeType(Node->user_id,&Node->name[0]);
	float * VBOverticesBuffer=new float[Mesh->nfaces*3*3*4];
	float (* VBONormalsBuffer)[3]=(float(*)[3])new float[Mesh->nfaces*3*3*4];
	
	float * VBOTexCoordBuffer=NULL;
	if(Mesh->texcos)
			VBOTexCoordBuffer=new float[Mesh->nfaces*3*2*4];

	lib3ds_mesh_calculate_vertex_normals(Mesh, VBONormalsBuffer); 

	Lib3dsFace *Face=0;
	VBOIDs[Node->user_id].VerticeNum=Mesh->nfaces*3;
	TotelVertices=TotelVertices+Mesh->nfaces*3;

	if(Mesh->faces[0].material>=0)
	{
		Lib3dsMaterial *Material = Model3ds->materials[Mesh->faces[0].material];

		VBOIDs[Node->user_id].UseMaterial=true;
		VBOIDs[Node->user_id].mat_ambient[0]=Material->ambient[0];
		VBOIDs[Node->user_id].mat_ambient[1]=Material->ambient[1];
		VBOIDs[Node->user_id].mat_ambient[2]=Material->ambient[2];
		VBOIDs[Node->user_id].mat_ambient[3]=1.0f;
		VBOIDs[Node->user_id].mat_diffuse[0]=Material->diffuse[0];
		VBOIDs[Node->user_id].mat_diffuse[1]=Material->diffuse[1];
		VBOIDs[Node->user_id].mat_diffuse[2]=Material->diffuse[2];
		VBOIDs[Node->user_id].mat_diffuse[3]=1.0f;
		VBOIDs[Node->user_id].mat_specular[0]=Material->specular[0];
		VBOIDs[Node->user_id].mat_specular[1]=Material->specular[1];
		VBOIDs[Node->user_id].mat_specular[2]=Material->specular[2];
		VBOIDs[Node->user_id].mat_specular[3]=1.0f;
		VBOIDs[Node->user_id].mat_shininess=pow(2, 10 * Material->shininess - 1)*10.0f;
	}
	else
		VBOIDs[Node->user_id].UseMaterial=false;
	//VBOIDs[Node->user_id].mat_shininess=Material->shininess*128.0f;

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

bool CLoad3DS::Clear3DSIDs(Lib3dsNode *Node)
{
	if(!Node)
		return false;
	Lib3dsNode      *pNode; 
	for (pNode=Node->childs; pNode!=0; pNode=pNode->next)
		Clear3DSIDs(pNode);

	if(Node->type!=LIB3DS_NODE_MESH_INSTANCE)
		return false;
	if(strcmp(Node->name,"$$$DUMMY")==0)
		return false;

	Node->user_id=0;

	return true;
}
void CLoad3DS::GetNodeType(int NodeID,const char * NodeName)
{
	int NodeNameLen=strlen(NodeName);
	if(NodeNameLen>=4)
	{
		if(((NodeName[0]=='B')&&(NodeName[1]=='o'))&&((NodeName[2]=='n')&&(NodeName[3]=='e')))
			VBOIDs[NodeID].NodeType[TYPE_3DS_NODE_DM]=true;
	}
	int firstFlagLen=0;
	while((firstFlagLen<NodeNameLen)&&(NodeName[firstFlagLen]!='_'))
		firstFlagLen=firstFlagLen+1;
	for(int i=0;i<firstFlagLen;i=i+2)
	{
		if(NodeName[i]=='C')
		{
			if(NodeName[i+1]=='X')
				VBOIDs[NodeID].NodeType[TYPE_3DS_NODE_CX]=true;
			if(NodeName[i+1]=='Y')
				VBOIDs[NodeID].NodeType[TYPE_3DS_NODE_CY]=true;
			if(NodeName[i+1]=='Z')
				VBOIDs[NodeID].NodeType[TYPE_3DS_NODE_CZ]=true;
		}
		if((NodeName[i]=='E')&&(NodeName[i+1]=='N'))
			VBOIDs[NodeID].NodeType[TYPE_3DS_NODE_EN]=true;
		if((NodeName[i]=='A')&&(NodeName[i+1]=='B'))
			VBOIDs[NodeID].NodeType[TYPE_3DS_NODE_AB]=true;
		if((NodeName[i]=='W')&&(NodeName[i+1]=='P'))
			VBOIDs[NodeID].NodeType[TYPE_3DS_NODE_WP]=true;
		if((NodeName[i]=='W')&&(NodeName[i+1]=='W'))
			VBOIDs[NodeID].NodeType[TYPE_3DS_NODE_WW]=true;
		if((NodeName[i]=='S')&&(NodeName[i+1]=='P'))
			VBOIDs[NodeID].NodeType[TYPE_3DS_NODE_SP]=true;
		if((NodeName[i]=='G')&&(NodeName[i+1]=='R'))
			VBOIDs[NodeID].NodeType[TYPE_3DS_NODE_GR]=true;
		if((NodeName[i]=='M')&&(NodeName[i+1]=='H'))
			VBOIDs[NodeID].NodeType[TYPE_3DS_NODE_MH]=true;
	}
	if(firstFlagLen+4>=NodeNameLen)
		return;
	if((NodeName[firstFlagLen+1]=='D')&&(NodeName[firstFlagLen+2]=='M')&&(NodeName[firstFlagLen+3]=='_'))
		VBOIDs[NodeID].NodeType[TYPE_3DS_NODE_DM]=true;

}