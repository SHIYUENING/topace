
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
//, GrassTexID(0)
//, DiffuseTexID(0)
, TextureMap(NULL)
, TextureMapNum(0)
, OmniLightNum(0)
, SpotLightNum(0)
, OmniLightNodes(NULL)
, SpotLightNodes(NULL)
, OnlySelfIllum(false)
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

	loadTex(filename);

	//if(Model3ds->nlights>0)
	//	OmniLightNodes = (tLightNodes *) _aligned_malloc (Model3ds->nlights*sizeof(tLightNodes),16);
		//OmniLightNodes = new tLightNodes[Model3ds->nlights];
	InitLight();

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
			VBOIDs[i].MaterialID=-1;
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
	if(!VBOSupported)
	{
		isVRAM=false;
		return false;
	}

	for(Lib3dsNode *ThisNode=Model3ds->nodes;ThisNode!=NULL;ThisNode=ThisNode->next)
		LoadNode(ThisNode);

	if(TextureMap)
	{
		for(int i=0;i<TextureMapNum;i++)
		{
			TextureMap[i].LoadToVRAM();
		}
	}
	isVRAM=true;
	return true;
}

void inline CLoad3DS::Del_RAM(void)
{
	if(OmniLightNodes)
	{
		_aligned_free(OmniLightNodes);
		//delete[] OmniLightNodes;
		OmniLightNodes = NULL;
		OmniLightNum = 0;
	}
	if(SpotLightNodes)
	{
		_aligned_free(SpotLightNodes);
		SpotLightNodes = NULL;
		SpotLightNum = 0;
	}
	if(Model3ds)
		lib3ds_file_free(Model3ds);
	Model3ds=NULL;
	if(TextureMap)
	{
		delete[] TextureMap;
		TextureMap=NULL;
		TextureMapNum=0;
	}
	isRAM=false;
}

void inline CLoad3DS::Del_VRAM(void)
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
			VBOIDs[i].MaterialID=-1;
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
	if(TextureMap)
	{
		for(int i=0;i<TextureMapNum;i++)
		{
			TextureMap[i].Del_VRAM();
		}
	}

	isVRAM=false;
	TotelVertices=0;
	MeshLoadNum=0;
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
}
bool CLoad3DS::LoadNode(Lib3dsNode *Node)
{
	if(!Node)
		return false;
	for (Lib3dsNode *pNode=Node->childs; pNode!=0; pNode=pNode->next)
		LoadNode(pNode);
	if(Node->type==LIB3DS_NODE_OMNILIGHT)
	{
		Lib3dsLight * TmpLight;
		for(int i=0;i<Model3ds->nlights;i++)
		{
			TmpLight = Model3ds->lights[i];
			if(!TmpLight->spot_light)
			{
				if(strcmp(Node->name,TmpLight->name)==0)
				{
					Node->user_id=TmpLight->user_id;
					break;
				}
			}
		}
//		Node->user_id=OmniLightLoaded;
//		OmniLightLoaded=OmniLightLoaded+1;
	}
	if(Node->type==LIB3DS_NODE_SPOTLIGHT)
	{
		Lib3dsLight * TmpLight;
		for(int i=0;i<Model3ds->nlights;i++)
		{
			TmpLight = Model3ds->lights[i];
			if(TmpLight->spot_light)
			{
				if(strcmp(Node->name,TmpLight->name)==0)
				{
					Node->user_id=TmpLight->user_id;
					//Easy_vector_copy(SpotLightNodes[Node->user_id].,
					break;
				}
			}
		}
	}
	if(Node->type==LIB3DS_NODE_SPOTLIGHT_TARGET)
	{
		Lib3dsLight * TmpLight;
		char ThisNodeName[64];
		strcpy(ThisNodeName,Node->name);
		for(int i=0;i<64;i++)
		{
			if(ThisNodeName[i]=='.')
				ThisNodeName[i]=0;
			if(ThisNodeName[i]==0)
				break;
		}
		for(int i=0;i<Model3ds->nlights;i++)
		{
			TmpLight = Model3ds->lights[i];
			if(TmpLight->spot_light)
			{
				if(strcmp(ThisNodeName,TmpLight->name)==0)
				{
					Node->user_id=TmpLight->user_id;
					break;
				}
			}
		}
	}
	if(Node->type!=LIB3DS_NODE_MESH_INSTANCE)
		return false;
	if(strcmp(Node->name,"$$$DUMMY")==0)
		return false;
	if(Node->user_id!=0)
		return false;

	Lib3dsMesh *Mesh=lib3ds_file_mesh_for_node(Model3ds,Node);

	if(!Mesh->vertices)
		return false;            //if no vertices ,Nothing to do.
	if(MeshLoadNum>=TotelMeshs)
		return false;  

	Node->user_id=MeshLoadNum;

	GetNodeType(Node->user_id,&Node->name[0]);

	if(VBOIDs[Node->user_id].NodeType[TYPE_3DS_NODE_DM])
	{
		VBOIDs[Node->user_id].ColorID=0;
		VBOIDs[Node->user_id].MaterialID=-1;
		VBOIDs[Node->user_id].NormalID=0;
		VBOIDs[Node->user_id].TangentID=0;
		VBOIDs[Node->user_id].TexCoordID=0;
		VBOIDs[Node->user_id].VerticeID=0;
		VBOIDs[Node->user_id].VerticeNum=0;
	}

	float * VBOverticesBuffer=new float[Mesh->nfaces*3*3*4];
	float (* VBONormalsBuffer)[3]=(float(*)[3])new float[Mesh->nfaces*3*3*4];
	float * VBOTexCoordBuffer=NULL;
	if(Mesh->texcos)
			VBOTexCoordBuffer=new float[Mesh->nfaces*3*2*4];

	lib3ds_mesh_calculate_vertex_normals(Mesh, VBONormalsBuffer); 

	
	VBOIDs[Node->user_id].VerticeNum=Mesh->nfaces*3;
	TotelVertices=TotelVertices+Mesh->nfaces*3;

	VBOIDs[Node->user_id].MaterialID=Mesh->faces[0].material;
	if(Mesh->faces[0].material>=0)
	{
		Lib3dsMaterial *Material = Model3ds->materials[Mesh->faces[0].material];
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
		//if(Material->self_illum_flag)
		//{
			VBOIDs[Node->user_id].mat_emission[0]=Material->diffuse[0]*Material->self_illum;
			VBOIDs[Node->user_id].mat_emission[1]=Material->diffuse[1]*Material->self_illum;
			VBOIDs[Node->user_id].mat_emission[2]=Material->diffuse[2]*Material->self_illum;
		//}
		//else
		//{
		//	VBOIDs[Node->user_id].mat_emission[0]=0.0f;
		//	VBOIDs[Node->user_id].mat_emission[1]=0.0f;
		//	VBOIDs[Node->user_id].mat_emission[2]=0.0f;
		//}
		VBOIDs[Node->user_id].mat_emission[3]=1.0f;
		VBOIDs[Node->user_id].mat_shininess=pow(2, 10 * Material->shininess - 1)*10.0f;
	}

	Lib3dsFace *Face=0;
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

	Easy_matrix_copy(VBOIDs[Node->user_id].MeshMatrix, Mesh->matrix);   
	Easy_matrix_inv(VBOIDs[Node->user_id].MeshMatrix); 
	
	MeshLoadNum=MeshLoadNum+1;
	return true;
}

void CLoad3DS::Render()
{

	if(!Model3ds)
		return;
	if(!VBOSupported)
		return;
	//for(int i=0;i<MAX_TYPE_3DS_NODE;i++)
	//	TypeFrame[i]=NodesFrameIn[i];

	//if(float(Model3ds->frames)>=current_frame)
	//	lib3ds_file_eval(Model3ds, current_frame);
	if((TotelVertices<=0)||(TotelMeshs<=0)||(!isVRAM))
		return;

	
	//CameraMatrix();

	//Model3ds->nodes
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	for(Lib3dsNode *ThisNode=Model3ds->nodes;ThisNode!=NULL;ThisNode=ThisNode->next)
	{
		//glPushMatrix();
			RenderNode(ThisNode);
		//glPopMatrix();
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );
	glDepthMask(GL_FALSE);
	for(Lib3dsNode *ThisNode=Model3ds->nodes;ThisNode!=NULL;ThisNode=ThisNode->next)
	{
		//glPushMatrix();
			RenderNode(ThisNode,true);
		//glPopMatrix();
	}
	glDepthMask(GL_TRUE);
	glDisable(GL_CULL_FACE);
}

void CLoad3DS::RenderNoColor()
{
	if(!Model3ds)
		return;
	if(!VBOSupported)
		return;
	if((TotelVertices<=0)||(TotelMeshs<=0)||(!isVRAM))
		return;

	GLboolean UseGL_LIGHTING=false;
	glGetBooleanv(GL_LIGHTING,&UseGL_LIGHTING);
	glDisable( GL_TEXTURE_2D );
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	for(Lib3dsNode *ThisNode=Model3ds->nodes;ThisNode!=NULL;ThisNode=ThisNode->next)
	{
		RenderNodeNoColor(ThisNode);
	}
	if(UseGL_LIGHTING)
		glEnable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable( GL_TEXTURE_2D );
}

void CLoad3DS::RenderNode(Lib3dsNode *Node,bool isTranslucent)
{
	if(!Node)
		return ;
/*
	if(Node->type==LIB3DS_NODE_MESH_INSTANCE)
	{
		int TypeFrameID=MAX_TYPE_3DS_NODE-1;
		while(!VBOIDs[Node->user_id].NodeType[TypeFrameID])
		{
			TypeFrameID=TypeFrameID-1;
			if(TypeFrameID==0)
				break;
		}

		MeshNodeEval(Node,TypeFrame[TypeFrameID]);
		glMultMatrixf(&Node->matrix[0][0]); 
	}
 */
	for (Lib3dsNode * pNode=Node->childs; pNode!=0; pNode=pNode->next)
	{  
		//float ThisNodematrix[4][4];
		//glGetFloatv(GL_MODELVIEW_MATRIX,&ThisNodematrix[0][0]);
        RenderNode(pNode,isTranslucent);   
		//glLoadIdentity();
		//glLoadMatrixf(&ThisNodematrix[0][0]);
    } 

	if(strcmp(Node->name,"$$$DUMMY")==0)
		return ;
	if(Node->type!=LIB3DS_NODE_MESH_INSTANCE)
		return ;
	if(VBOIDs[Node->user_id].NodeType[TYPE_3DS_NODE_DM])
		return ;
	if(VBOIDs[Node->user_id].NodeType[TYPE_3DS_NODE_WW])
		return ;
	if(VBOIDs[Node->user_id].NodeType[TYPE_3DS_NODE_GR]!=isTranslucent)
		return ;
	Lib3dsMeshInstanceNode * MeshData = (Lib3dsMeshInstanceNode *)Node;
	if(!MeshData)
		return ;
	//glMultMatrixf(&Node->matrix[0][0]);  
	//glTranslatef(-MeshData->pivot[0],-MeshData->pivot[1],-MeshData->pivot[2]);
	//glMultMatrixf(&VBOIDs[Node->user_id].MeshMatrix[0][0]); 
	float ThisNodematrix[4][4];
	glGetFloatv(GL_MODELVIEW_MATRIX,&ThisNodematrix[0][0]);
	glMultMatrixf(&Node->matrix[0][0]);
	RenderNodeMesh(VBOIDs[Node->user_id]);
	glLoadMatrixf(&ThisNodematrix[0][0]);

}
void CLoad3DS::RenderNodeNoColor(Lib3dsNode *Node)
{
	if(!Node)
		return ;
	for (Lib3dsNode * pNode=Node->childs; pNode!=0; pNode=pNode->next)
	{
        RenderNodeNoColor(pNode);
    } 

	if(strcmp(Node->name,"$$$DUMMY")==0)
		return ;
	if(Node->type!=LIB3DS_NODE_MESH_INSTANCE)
		return ;
	if(VBOIDs[Node->user_id].NodeType[TYPE_3DS_NODE_DM])
		return ;
	if(VBOIDs[Node->user_id].NodeType[TYPE_3DS_NODE_WW])
		return ;
	if(VBOIDs[Node->user_id].NodeType[TYPE_3DS_NODE_GR])
		return ;
	Lib3dsMeshInstanceNode * MeshData = (Lib3dsMeshInstanceNode *)Node;
	if(!MeshData)
		return ; 
	float ThisNodematrix[4][4];
	glGetFloatv(GL_MODELVIEW_MATRIX,&ThisNodematrix[0][0]);
	glMultMatrixf(&Node->matrix[0][0]);
	RenderNodeMeshNoColor(VBOIDs[Node->user_id]);
	glLoadMatrixf(&ThisNodematrix[0][0]);

}
void inline CLoad3DS::MeshNodeEval(Lib3dsNode *Node,float Frame)
{

	Lib3dsMeshInstanceNode *n = (Lib3dsMeshInstanceNode*)Node;
	lib3ds_track_eval_vector(&n->pos_track, n->pos, Frame);
	lib3ds_track_eval_quat(&n->rot_track, n->rot, Frame);
	if (n->scl_track.nkeys) 
		lib3ds_track_eval_vector(&n->scl_track, n->scl, Frame);
	else 
		n->scl[0] = n->scl[1] = n->scl[2] = 1.0f;
	lib3ds_track_eval_bool(&n->hide_track, &n->hide, Frame);
	//lib3ds_matrix_identity(NodeMatrix);
	//Easy_matrix_identity(NodeMatrix);
	float NodeMatrix[4][4]={1.0f,0.0f,0.0f,0.0f,
							0.0f,1.0f,0.0f,0.0f,
							0.0f,0.0f,1.0f,0.0f,
							0.0f,0.0f,0.0f,1.0f};
	Easy_matrix_translate_Internal(NodeMatrix, n->pos[0], n->pos[1], n->pos[2]);
	Easy_matrix_rotate_quat(NodeMatrix, n->rot);
    Easy_matrix_scale(NodeMatrix, n->scl[0], n->scl[1], n->scl[2]);
	Easy_matrix_copy(Node->matrix, NodeMatrix);
}

void CLoad3DS::MultCameraMatrix()
{
	if(!Model3ds)
		return;
	if(!VBOSupported)
		return;
	if(!(Model3ds->cameras))
		return;
	if(Model3ds->ncameras<=0)
		return;
	Lib3dsCamera * TestCamera=Model3ds->cameras[0];
	/*for(Lib3dsNode *ThisNode=Model3ds->nodes;ThisNode!=NULL;ThisNode=ThisNode->next)
	{
		if(ThisNode->type==LIB3DS_NODE_CAMERA)
		{
			//MeshNodeEval(ThisNode,Frame);
			Lib3dsCameraNode *LCN = (Lib3dsCameraNode*)ThisNode;

			lib3ds_track_eval_vector(&LCN->pos_track, LCN->pos, Frame);
            lib3ds_track_eval_float(&LCN->roll_track, &LCN->roll, Frame);
			TestCamera->position[0]=LCN->pos[0];
			TestCamera->position[1]=LCN->pos[1];
			TestCamera->position[2]=LCN->pos[2];
			TestCamera->roll=LCN->roll;
		}
		if(ThisNode->type==LIB3DS_NODE_CAMERA_TARGET)
		{
			//MeshNodeEval(ThisNode,Frame);
			Lib3dsTargetNode *LCN = (Lib3dsTargetNode*)ThisNode;
			lib3ds_track_eval_vector(&LCN->pos_track, LCN->pos, Frame);
			TestCamera->target[0]=LCN->pos[0];
			TestCamera->target[1]=LCN->pos[1];
			TestCamera->target[2]=LCN->pos[2];
		}
	}
		*/
	float Test_matrix_camera[4][4];

	Easy_matrix_camera(Test_matrix_camera,TestCamera->position,TestCamera->target,TestCamera->roll);
	glMultMatrixf(&Test_matrix_camera[0][0]); 
	
}

void inline CLoad3DS::RenderNodeMesh(tModelNodes ModelNode)
{

	if((ModelNode.MaterialID>=0)&&(Model3ds->nmaterials>ModelNode.MaterialID))
	{
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,ModelNode.mat_specular);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ModelNode.mat_ambient);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,ModelNode.mat_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,ModelNode.mat_emission);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,&ModelNode.mat_shininess);

		Lib3dsMaterial *Material = Model3ds->materials[ModelNode.MaterialID];
		if(OnlySelfIllum&&(Material->self_illum<0.85f))
			return;
		//Material->self_illum
		if(Material->two_sided)
			glDisable(GL_CULL_FACE);
		else
			glEnable(GL_CULL_FACE);

		if(Material->use_wire)
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

		glBindTexture(GL_TEXTURE_2D, 0);
		if(TextureMap)
		{
			if(Material->texture1_map.user_id<(unsigned int)TextureMapNum)
				glBindTexture(GL_TEXTURE_2D, TextureMap[Material->texture1_map.user_id].TexID);

				glMatrixMode(GL_TEXTURE);
				if(TextureMap[Material->texture1_map.user_id].TexType==IS_DDS)
				{
					//float textureMatrix[4][4];
					//Easy_matrix_identity(textureMatrix);
					//textureMatrix[1][1]=-1.0f;
					glLoadMatrixf(&IdentityDDSTexMatrix[0][0]);
				}
				else
					glLoadIdentity();
				glMatrixMode(GL_MODELVIEW);
		}
		
	}
	glEnableClientState( GL_VERTEX_ARRAY );
	if(ModelNode.NormalID)		glEnableClientState( GL_NORMAL_ARRAY );
	if(ModelNode.TexCoordID)	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	if(ModelNode.ColorID)		glEnableClientState( GL_COLOR_ARRAY );

	glBindBufferARB( GL_ARRAY_BUFFER_ARB, ModelNode.VerticeID );
	glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );
	if(ModelNode.NormalID)
	{
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, ModelNode.NormalID );
		glNormalPointer( GL_FLOAT, 0, (char *) NULL );
	}
	if(ModelNode.TexCoordID)
	{
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, ModelNode.TexCoordID );
		glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );
	}
	if(ModelNode.ColorID)
	{
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, ModelNode.ColorID );
		glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );
	}
	glDrawArrays( GL_TRIANGLES, 0, ModelNode.VerticeNum );	

	glDisableClientState( GL_VERTEX_ARRAY );
	if(ModelNode.NormalID)		glDisableClientState( GL_NORMAL_ARRAY );
	if(ModelNode.TexCoordID)	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	if(ModelNode.ColorID)		glDisableClientState( GL_COLOR_ARRAY );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
}

void inline CLoad3DS::RenderNodeMeshNoColor(tModelNodes ModelNode)
{
	glEnableClientState( GL_VERTEX_ARRAY );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, ModelNode.VerticeID );
	glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );
	glDrawArrays( GL_TRIANGLES, 0, ModelNode.VerticeNum );	
	glDisableClientState( GL_VERTEX_ARRAY );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
}

void inline CLoad3DS::Clear3DSIDs(Lib3dsNode *Node)
{
	if(!Node)
		return ;
	Lib3dsNode      *pNode; 
	for (pNode=Node->childs; pNode!=0; pNode=pNode->next)
		Clear3DSIDs(pNode);

	if(Node->type!=LIB3DS_NODE_MESH_INSTANCE)
		return ;
	if(strcmp(Node->name,"$$$DUMMY")==0)
		return ;

	Node->user_id=0;

	return ;
}
void inline CLoad3DS::GetNodeType(int NodeID,const char * NodeName)
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
		if((NodeName[i]=='D')&&(NodeName[i+1]=='M'))
			VBOIDs[NodeID].NodeType[TYPE_3DS_NODE_DM]=true;
	}
	if(firstFlagLen+4>=NodeNameLen)
		return;
	if((NodeName[firstFlagLen+1]=='D')&&(NodeName[firstFlagLen+2]=='M')&&(NodeName[firstFlagLen+3]=='_'))
		VBOIDs[NodeID].NodeType[TYPE_3DS_NODE_DM]=true;

}
void inline CLoad3DS::LoadTexToRam(int TexID,char * FilePath)
{
	int TexNameLen=64;
	if(!(Model3ds->materials[TexID]->texture1_map.name))
		return;
	for(int i=0;i<TexID;i++)
	{
		if(stricmp(Model3ds->materials[TexID]->texture1_map.name,Model3ds->materials[i]->texture1_map.name)==0)
		{
			Model3ds->materials[TexID]->texture1_map.user_id=Model3ds->materials[i]->texture1_map.user_id;
			return;
		}
	}
	char TexName[64]={0};
	while(Model3ds->materials[TexID]->texture1_map.name[TexNameLen]!='.')
	{
		TexNameLen=TexNameLen-1;
		if(TexNameLen<=0)
			break;
	}
	for(int i=TexNameLen;i>0;i--)
	{
		TexName[i-1]=Model3ds->materials[TexID]->texture1_map.name[i-1];
	}
	char * TexNameFull = new char [strlen(TexName)+strlen(FilePath)+4];
	sprintf(TexNameFull,"%s/%s",FilePath,TexName);

	TextureMap[TextureMapNum].loadfile(&TexNameFull[0]);
	Model3ds->materials[TexID]->texture1_map.user_id=TextureMapNum;
	TextureMapNum=TextureMapNum+1;
	delete[] TexNameFull;
}

void inline CLoad3DS::loadTex(char * filename)
{
	if(Model3ds->nmaterials<=0)
		return;
	char * FilePath = new char[strlen(filename)+1];
	sprintf(FilePath,"%s",filename);
	for(int i=strlen(filename)-1;i>0;i--)
	{
		if(filename[i]=='/')
		{
			FilePath[i]=0;
			break;
		}
	}
	if(Model3ds->nmaterials>0)
	{
		TextureMap=new Textures[Model3ds->nmaterials];
		for(int i=0;i<Model3ds->nmaterials;i++)
		{
			LoadTexToRam(i,FilePath);
		}
	}
	delete[] FilePath;
}

void CLoad3DS::ModelMatrix(float NodesFrameIn[MAX_TYPE_3DS_NODE],float test_frame)
{
	if(!Model3ds)
		return;
	if(!VBOSupported)
		return;
	for(int i=0;i<MAX_TYPE_3DS_NODE;i++)
	{
		if(TypeFrame[i]==NodesFrameIn[i])
			TypeFrameStats[i]=false;
		else
		{
			TypeFrameStats[i]=true;
			TypeFrame[i]=NodesFrameIn[i];
		}
	}
	float ThisNodematrix[4][4];
	glGetFloatv(GL_MODELVIEW_MATRIX,&ThisNodematrix[0][0]);
	glLoadIdentity();
	Easy_matrix_identity(ModelRootMatrix);
	//CameraMatrix(test_frame);
	for(Lib3dsNode *ThisNode=Model3ds->nodes;ThisNode!=NULL;ThisNode=ThisNode->next)
	{
		float ThisNodematrix[4][4];
		glGetFloatv(GL_MODELVIEW_MATRIX,&ThisNodematrix[0][0]);
		NodeMatrix(ThisNode);
		glLoadMatrixf(&ThisNodematrix[0][0]);
	}
	glLoadMatrixf(&ThisNodematrix[0][0]);
}

void CLoad3DS::NodeMatrix(Lib3dsNode *Node)
{
	if(Node->type==LIB3DS_NODE_MESH_INSTANCE)
	{
		int TypeFrameID=MAX_TYPE_3DS_NODE-1;
		while(!VBOIDs[Node->user_id].NodeType[TypeFrameID])
		{
			TypeFrameID=TypeFrameID-1;
			if(TypeFrameID==0)
				break;
		}
		MeshNodeEval(Node,TypeFrame[TypeFrameID]);
		//glMultMatrixf(&Node->matrix[0][0]); 
	}
	if(Node->type==LIB3DS_NODE_CAMERA)
	{
		CameraNodeEval(Node,TypeFrame[0]);
		//glMultMatrixf(&Node->matrix[0][0]); 
		//glGetFloatv(GL_MODELVIEW_MATRIX,&Node->matrix[0][0]); 
	}
	if(Node->type==LIB3DS_NODE_CAMERA_TARGET)
	{
		CameraTGTNodeEval(Node,TypeFrame[0]);
		//glMultMatrixf(&Node->matrix[0][0]);  
		//glGetFloatv(GL_MODELVIEW_MATRIX,&Node->matrix[0][0]);
	}
	if(Node->type==LIB3DS_NODE_OMNILIGHT)
	{
		OmniLightNodeEval(Node,TypeFrame[0]);
		//glMultMatrixf(&Node->matrix[0][0]);  
		//glGetFloatv(GL_MODELVIEW_MATRIX,&Node->matrix[0][0]);
	}
	if(Node->type==LIB3DS_NODE_SPOTLIGHT)
	{
		SpotLightNodeEval(Node,TypeFrame[0]);
		//glMultMatrixf(&Node->matrix[0][0]);  
		//glGetFloatv(GL_MODELVIEW_MATRIX,&Node->matrix[0][0]);
	}
	if(Node->type==LIB3DS_NODE_SPOTLIGHT_TARGET)
	{
		SpotLightTGTNodeEval(Node,TypeFrame[0]);
	}
	
	glMultMatrixf(&Node->matrix[0][0]); 
	glGetFloatv(GL_MODELVIEW_MATRIX,&Node->matrix[0][0]); 
	for (Lib3dsNode * pNode=Node->childs; pNode!=0; pNode=pNode->next)
	{  
		float ThisNodematrix[4][4];
		glGetFloatv(GL_MODELVIEW_MATRIX,&ThisNodematrix[0][0]);
        NodeMatrix(pNode); 
		glLoadMatrixf(&ThisNodematrix[0][0]);
    } 

	if(strcmp(Node->name,"$$$DUMMY")==0)
		return ;
	if(Node->type!=LIB3DS_NODE_MESH_INSTANCE)
		return ;
	Lib3dsMeshInstanceNode * MeshData = (Lib3dsMeshInstanceNode *)Node;
	if(!MeshData)
		return ; 
	glTranslatef(-MeshData->pivot[0],-MeshData->pivot[1],-MeshData->pivot[2]);
	glMultMatrixf(&VBOIDs[Node->user_id].MeshMatrix[0][0]); 
	glGetFloatv(GL_MODELVIEW_MATRIX,&Node->matrix[0][0]);
}

void CLoad3DS::CameraNodeEval(Lib3dsNode *Node,float Frame)
{
	if(!(Model3ds->cameras))
		return;
	if(Model3ds->ncameras<=0)
		return;
	Lib3dsCamera * TestCamera=Model3ds->cameras[0];
	Lib3dsCameraNode *LCN = (Lib3dsCameraNode*)Node;
    lib3ds_track_eval_vector(&LCN->pos_track, LCN->pos, Frame);
	lib3ds_track_eval_float(&LCN->fov_track, &LCN->fov, Frame);
	lib3ds_track_eval_float(&LCN->roll_track, &LCN->roll, Frame);
	TestCamera->roll=LCN->roll;
	TestCamera->fov=LCN->fov;
	glGetFloatv(GL_MODELVIEW_MATRIX,&Node->matrix[0][0]);
	float Test_matrix_camera[3];
	Easy_matrix_mult_vector3X3(Test_matrix_camera,&Node->matrix[0][0],LCN->pos);
	TestCamera->position[0]=Test_matrix_camera[0];
	TestCamera->position[1]=Test_matrix_camera[1];
	TestCamera->position[2]=Test_matrix_camera[2];
	Easy_matrix_identity(Node->matrix);
	Easy_matrix_translate_Internal(Node->matrix, LCN->pos[0], LCN->pos[1], LCN->pos[2]);
}
void CLoad3DS::CameraTGTNodeEval(Lib3dsNode *Node,float Frame)
{
	if(!(Model3ds->cameras))
		return;
	if(Model3ds->ncameras<=0)
		return;	
	Lib3dsCamera * TestCamera=Model3ds->cameras[0];
	Lib3dsTargetNode *LCN = (Lib3dsTargetNode*)Node;
	lib3ds_track_eval_vector(&LCN->pos_track, LCN->pos, Frame);
	glGetFloatv(GL_MODELVIEW_MATRIX,&Node->matrix[0][0]);
	float Test_matrix_camera_Tgt[3];
	Easy_matrix_mult_vector3X3(Test_matrix_camera_Tgt,&Node->matrix[0][0],LCN->pos);
	TestCamera->target[0]=Test_matrix_camera_Tgt[0];
	TestCamera->target[1]=Test_matrix_camera_Tgt[1];
	TestCamera->target[2]=Test_matrix_camera_Tgt[2];
	Easy_matrix_identity(Node->matrix);
	Easy_matrix_translate_Internal(Node->matrix, LCN->pos[0], LCN->pos[1], LCN->pos[2]);
}
void CLoad3DS::OmniLightNodeEval(Lib3dsNode *Node,float Frame)
{
	if(!(Model3ds->lights))
		return;
	if(Model3ds->nlights<=0)
		return;	
	Lib3dsOmnilightNode *LCN = (Lib3dsOmnilightNode*)Node;
	lib3ds_track_eval_vector(&LCN->pos_track, LCN->pos, Frame);
	lib3ds_track_eval_vector(&LCN->color_track, LCN->color, Frame);
	glGetFloatv(GL_MODELVIEW_MATRIX,&Node->matrix[0][0]);
	float matrix_OmniLightPos[3];
	Easy_matrix_mult_vector3X3(matrix_OmniLightPos,&Node->matrix[0][0],LCN->pos);
	Easy_matrix_translate_Internal(Node->matrix, LCN->pos[0], LCN->pos[1], LCN->pos[2]);
	if(OmniLightNodes&&((int)Node->user_id<Model3ds->nlights))
	{
		Easy_vector_copy(&OmniLightNodes[Node->user_id].LightWorldPos,matrix_OmniLightPos);
		//OmniLightNodes[Node->user_id].LightWorldPos.m128_f32[0]=matrix_OmniLightPos[0];
		//OmniLightNodes[Node->user_id].LightWorldPos.m128_f32[1]=matrix_OmniLightPos[1];
		//OmniLightNodes[Node->user_id].LightWorldPos.m128_f32[2]=matrix_OmniLightPos[2];
		//OmniLightNodes[Node->user_id].LightWorldPos.m128_f32[3]=1.0f;
		//Easy_vector_copy(OmniLightNodes[Node->user_id].LightColor,
		OmniLightNodes[Node->user_id].LightColor.m128_f32[0]=LCN->color[0]*0.3f;
		OmniLightNodes[Node->user_id].LightColor.m128_f32[1]=LCN->color[1]*0.3f;
		OmniLightNodes[Node->user_id].LightColor.m128_f32[2]=LCN->color[2]*0.3f;
		OmniLightNodes[Node->user_id].LightColor.m128_f32[3]=1.0f;

	}
	/*if(strcmp(Node->name,"Omni01")==0)
	{

		OmniLightPos[0].m128_f32[0]=matrix_OmniLightPos[0];
		OmniLightPos[0].m128_f32[1]=matrix_OmniLightPos[1];
		OmniLightPos[0].m128_f32[2]=matrix_OmniLightPos[2];
		OmniLightPos[0].m128_f32[3]=0.0f;
		glEnable(GL_LIGHT0);
		GLfloat mat_specular[]={0.5f*LCN->color[0],0.5f*LCN->color[1],0.5f*LCN->color[2],1.0f};
		GLfloat mat_ambient[]={0.1f,0.1f,0.1f,1.0f};
		GLfloat mat_diffuse[]={0.7f*LCN->color[0],0.7f*LCN->color[1],0.7f*LCN->color[2],1.0f};
		GLfloat mat_shininess[]={100.0f};
		glLightfv(GL_LIGHT0,GL_SPECULAR,mat_specular);
		glLightfv(GL_LIGHT0,GL_AMBIENT,mat_ambient);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,mat_diffuse);
		glLightfv(GL_LIGHT0,GL_SHININESS,mat_shininess);
	}
	if(strcmp(Node->name,"Omni02")==0)
	{
		OmniLightPos[1].m128_f32[0]=matrix_OmniLightPos[0];
		OmniLightPos[1].m128_f32[1]=matrix_OmniLightPos[1];
		OmniLightPos[1].m128_f32[2]=matrix_OmniLightPos[2];
		OmniLightPos[1].m128_f32[3]=0.0f;
		glEnable(GL_LIGHT1);
		GLfloat mat_specular[]={0.5f*LCN->color[0],0.5f*LCN->color[1],0.5f*LCN->color[2],1.0f};
		GLfloat mat_ambient[]={0.1f,0.1f,0.1f,1.0f};
		GLfloat mat_diffuse[]={0.7f*LCN->color[0],0.7f*LCN->color[1],0.7f*LCN->color[2],1.0f};
		GLfloat mat_shininess[]={100.0f};
		glLightfv(GL_LIGHT1,GL_SPECULAR,mat_specular);
		glLightfv(GL_LIGHT1,GL_AMBIENT,mat_ambient);
		glLightfv(GL_LIGHT1,GL_DIFFUSE,mat_diffuse);
		glLightfv(GL_LIGHT1,GL_SHININESS,mat_shininess);
	}*/
}
void CLoad3DS::SpotLightNodeEval(Lib3dsNode *Node,float Frame)
{
	if(!(Model3ds->lights))
		return;
	if(Model3ds->nlights<=0)
		return;
	Lib3dsSpotlightNode *LCN = (Lib3dsSpotlightNode*)Node;
	lib3ds_track_eval_vector(&LCN->pos_track, LCN->pos, Frame);
	lib3ds_track_eval_vector(&LCN->color_track, LCN->color, Frame);
	lib3ds_track_eval_float(&LCN->hotspot_track, &LCN->hotspot, Frame);
	lib3ds_track_eval_float(&LCN->falloff_track, &LCN->falloff, Frame);
	lib3ds_track_eval_float(&LCN->roll_track, &LCN->roll, Frame);
	glGetFloatv(GL_MODELVIEW_MATRIX,&Node->matrix[0][0]);
	float LCN_SpotLightPos[3];
	Easy_matrix_mult_vector3X3(LCN_SpotLightPos,&Node->matrix[0][0],LCN->pos);
	Easy_vector_copy(&SpotLightNodes[Node->user_id].LightWorldPos,LCN_SpotLightPos);

	Easy_matrix_identity(Node->matrix);
	Easy_matrix_translate_Internal(Node->matrix, LCN->pos[0], LCN->pos[1], LCN->pos[2]);
	Easy_vector_copy(&SpotLightNodes[Node->user_id].LightColor,LCN->color);
	//float CutOff=(LCN->hotspot+LCN->falloff)/2.0f;
	SpotLightNodes[Node->user_id].SpotSet.m128_f32[0]=LCN->hotspot;
	SpotLightNodes[Node->user_id].SpotSet.m128_f32[1]=LCN->hotspot;
	SpotLightNodes[Node->user_id].SpotSet.m128_f32[2]=LCN->falloff;
	SpotLightNodes[Node->user_id].SpotSet.m128_f32[3]=LCN->falloff/1.5f;

	

}
void CLoad3DS::SpotLightTGTNodeEval(Lib3dsNode *Node,float Frame)
{
	if(!(Model3ds->lights))
		return;
	if(Model3ds->nlights<=0)
		return;
	Lib3dsSpotlightNode *LCN = (Lib3dsSpotlightNode*)Node;
	lib3ds_track_eval_vector(&LCN->pos_track, LCN->pos, Frame);
	glGetFloatv(GL_MODELVIEW_MATRIX,&Node->matrix[0][0]);
	float LCN_SpotLightTGTPos[3];
	Easy_matrix_mult_vector3X3(LCN_SpotLightTGTPos,&Node->matrix[0][0],LCN->pos);
	Easy_vector_copy(&SpotLightNodes[Node->user_id].SpotTGTWorldPos,LCN_SpotLightTGTPos);
	Easy_matrix_identity(Node->matrix);
	Easy_matrix_translate_Internal(Node->matrix, LCN->pos[0], LCN->pos[1], LCN->pos[2]);

}
void CLoad3DS::SetLightsPos(int lightBase)
{
	Easy_vector_copy(&ModelAmbientLightColot,Model3ds->ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,(float *)&ModelAmbientLightColot);

//	float LightPosWorld[4],LightPosEye[4],ThisNodematrix[4][4];
	__m128 ThisNodematrixM[4];
	//glGetFloatv(GL_MODELVIEW_MATRIX,ThisNodematrix[0]);
	glGetFloatv(GL_MODELVIEW_MATRIX,(float *)&ThisNodematrixM[0]);
	glLoadIdentity();

	for(int i=0;i<OmniLightNum;i++)
	{
		Easy_matrix_mult_vector3X3(&OmniLightNodes[i].LightEyePos,ThisNodematrixM,OmniLightNodes[i].LightWorldPos);
		OmniLightNodes[i].LightEyePos.m128_f32[3]=1.0f;

		if((i+lightBase)<8)
		{
			glEnable(GL_LIGHT0+i+lightBase);
			glLightfv(GL_LIGHT0+i+lightBase,GL_POSITION,(float *)&OmniLightNodes[i].LightEyePos);
			glLightfv(GL_LIGHT0+i+lightBase,GL_SPECULAR,(float *)&OmniLightNodes[i].LightColor);
			glLightfv(GL_LIGHT0+i+lightBase,GL_DIFFUSE,(float *)&OmniLightNodes[i].LightColor);
		}
		
	}
	for(int i=0;i<SpotLightNum;i++)
	{
		Easy_matrix_mult_vector3X3(&SpotLightNodes[i].LightEyePos,ThisNodematrixM,SpotLightNodes[i].LightWorldPos);
		Easy_matrix_mult_vector3X3(&SpotLightNodes[i].SpotTGTEyePos,ThisNodematrixM,SpotLightNodes[i].SpotTGTWorldPos);
		SpotLightNodes[i].LightEyePos.m128_f32[3]=1.0f;
		SpotLightNodes[i].SpotTGTEyePos.m128_f32[3]=1.0f;
		Easy_vector_sub(&SpotLightNodes[i].SpotEyeDirection,SpotLightNodes[i].SpotTGTEyePos,SpotLightNodes[i].LightEyePos);
		Easy_vector_normalize(&SpotLightNodes[i].SpotEyeDirection,SpotLightNodes[i].SpotEyeDirection);
//		glLineWidth(7.0);
//		glBegin(GL_LINES);
//		glVertex3fv((float *)&SpotLightNodes[i].LightEyePos);
//		glVertex3fv((float *)&SpotLightNodes[i].SpotTGTEyePos);
//		glEnd();

		if((i+lightBase+OmniLightNum)<8)
		{
			glEnable(GL_LIGHT0+i+lightBase+OmniLightNum);
			glLightfv(GL_LIGHT0+i+lightBase+OmniLightNum,GL_POSITION,(float *)&SpotLightNodes[i].LightEyePos);
			glLightfv(GL_LIGHT0+i+lightBase+OmniLightNum,GL_SPECULAR,(float *)&SpotLightNodes[i].LightColor);
			glLightfv(GL_LIGHT0+i+lightBase+OmniLightNum,GL_DIFFUSE,(float *)&SpotLightNodes[i].LightColor);
			glLightfv(GL_LIGHT0+i+lightBase+OmniLightNum,GL_SPOT_DIRECTION,(float *)&SpotLightNodes[i].SpotEyeDirection);
			glLightfv(GL_LIGHT0+i+lightBase+OmniLightNum,GL_SPOT_EXPONENT,(float *)&SpotLightNodes[i].SpotSet.m128_f32[3]);
			glLightf(GL_LIGHT0+i+lightBase+OmniLightNum,GL_SPOT_CUTOFF,SpotLightNodes[i].SpotSet.m128_f32[0]);
		}
		
	}
	/*
	Easy_vector_copy(LightPosWorld,OmniLightPos[0]);
	LightPosWorld[3]=1.0f;
	Easy_matrix_mult_vector3X3(LightPosEye,&ThisNodematrix[0][0],LightPosWorld);
	LightPosEye[3]=1.0f;

	if(!UseShader)
	glLightfv(GL_LIGHT0,GL_POSITION,LightPosEye);

	Easy_vector_copy(LightPosWorld,OmniLightPos[1]);
	LightPosWorld[3]=1.0f;
	Easy_matrix_mult_vector3X3(LightPosEye,&ThisNodematrix[0][0],LightPosWorld);
	LightPosEye[3]=1.0f;

	if(!UseShader)
	glLightfv(GL_LIGHT1,GL_POSITION,LightPosEye);*/
	glLoadMatrixf((float *)&ThisNodematrixM[0]);
}

void CLoad3DS::InitLight(void)
{
	if(!Model3ds)
		return;
	if(Model3ds->nlights<=0)
		return;

	Lib3dsLight * TmpLight;
	for(int i=0;i<Model3ds->nlights;i++)
	{
		TmpLight = Model3ds->lights[i];
		if(TmpLight->spot_light)
		{
			TmpLight->user_id=SpotLightNum;
			SpotLightNum=SpotLightNum+1;
		}
		else
		{
			TmpLight->user_id=OmniLightNum;
			OmniLightNum=OmniLightNum+1;
		}
	}
	
	OmniLightNodes = (tLightNodes *) _aligned_malloc (OmniLightNum*sizeof(tLightNodes),16);
	SpotLightNodes = (tLightNodes *) _aligned_malloc (SpotLightNum*sizeof(tLightNodes),16);
	
}

