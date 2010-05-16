fn yus a b=
(
	return a-(a/b)*b
)

fn expfile flip worldscale= 
(
--/*
out_name = GetSaveFileName \
	types:"TOP_ACE model|*.tam|other(*.*)|*.*|"
--*/

--out_name="L:\\TOP ACE\\Export\22.txt"
if out_name != undefined then
(
w = fopen out_name "w+"

(
	WriteString w "TAM"
	fseek w 4 #seek_set 
	filesize=ftell w
	WriteLong w 0
	WriteLong w 0
	WriteLong w 0
	
	WriteLong w 5	
	meshAddr=ftell w
	WriteLong w -1
	matsAddr=ftell w
	WriteLong w -1
	boneAddr=ftell w
	WriteLong w -1
	
	lghtAddr=ftell w
	WriteLong w -1
	cmerAddr=ftell w
	WriteLong w -1
	--WriteLong w 0
	--WriteLong w 0
	
	
)
sliderTime=0
(
	umeshs=#()
	--mats=#()
	ubones=#()
	ulights=#()
	ucameras=#()

	for g in Geometry where ((classof g == Editable_mesh or classof g == Editable_Poly) and classof g.baseObject != BoneGeometry ) do
	(
		append umeshs g
	)
	/*
	for g in Geometry where (classof g == Editable_mesh)
	(
		append mats g.name
	)
	*/
	for g in Geometry where (classof g.baseObject == BoneGeometry) do
	(
		append ubones g
	)
	--/*
	for g in Lights where (classof g.baseObject != Targetobject) do
	(
		append ulights g
	)
	--*/
	--/*
	for g in Cameras where (classof g.baseObject != Targetobject) do
	(
		append ucameras g
	)
	--*/
	
	WriteLong w umeshs.count
	WriteLong w sceneMaterials.count
	WriteLong w ubones.count
	WriteLong w ulights.count
	WriteLong w ucameras.count
	
	RootboneAddr=ftell w
	WriteLong w 0
)

--------/MESH--------------
if(umeshs.count>0) then
(
	nowaddr=ftell w
	
	fseek w meshAddr #seek_set
	WriteLong w nowaddr
	fseek w nowaddr #seek_set

	matidx=0

	--WriteLong w umeshs.count
	obj=#()
	for i=1 to umeshs.count do
	(
		append obj (ftell w)
		WriteLong w -1
	)
	
	i=0
	for i=1 to umeshs.count do
	(
		nowaddr=ftell w
		if((yus nowaddr 16)!=0) then
		(
			wnull=16-(yus nowaddr 16)
			for temnul= 1 to wnull do
			(
				WriteByte w -1
			)
		)
		nowaddr=ftell w
		local temmesh =snapshotAsMesh umeshs[i]
		fseek w obj[i] #seek_set
		WriteLong w nowaddr
		fseek w nowaddr #seek_set

		WriteLong w 0
		WriteLong w 0
		WriteLong w i
		if(umeshs[i].material!=undefined) then
		(
			WriteLong w (findItem sceneMaterials umeshs[i].material)
		)
		else
			WriteLong w 0
		
		bonnum=0
		if(umeshs[i].modifiers[#Skin]!=undefined) then
		(
			select umeshs[i]
			max modify mode
			bonnum=(skinOps.GetNumberBones umeshs[i].modifiers[#Skin])
			deselect umeshs[i]
		)


		--0x10---------------
		if(umeshs[i].parent!=undefined) then
		WriteByte w 1
		else
		WriteByte w bonnum
		if(bonnum>1) then
		(
			WriteByte w 1
		)
		else
		(
			WriteByte w 0
		)
		WriteByte w -1
		WriteByte w -1
		
		WriteLong w -1
		WriteLong w -1
		WriteLong w -1

		--0x20-------------------
		WriteLong w 4 --obj
		vptr=ftell w
		WriteLong w -1
		vnptr=ftell w
		WriteLong w -1
		vtptr=ftell w
		WriteLong w -1

		--0x30-------------------
		fptr=ftell w
		WriteLong w -1
		WriteLong w temmesh.numfaces
		WriteLong w (temmesh.numfaces*3)
		boneptr=ftell w
		WriteLong w -1

		--0x40-------------------
		nowaddr=ftell w
		WriteString w umeshs[i].name
		nowaddr=ftell w-nowaddr
		for j= nowaddr to 0x1f do
		(
			WriteByte w 0
		)

		nowaddr=ftell w
		if((yus nowaddr 16)!=0) then
		(
			wnull=16-(yus nowaddr 16)
			for temnul= 1 to wnull do
			(
				WriteByte w -1
			)
		)
		
		--0x60-------------------
		if ((isProperty umeshs[i] #castshadow)==false) then
		(
			WriteByte w 0
			WriteByte w 0
			WriteByte w 0
			WriteByte w 0
			
			WriteByte w 0
			WriteByte w 0
			WriteByte w 0
			
			WriteByte w -1
			
			WriteLong w -1
			WriteLong w -1
		)
		else
		(
			if (umeshs[i].castShadow) then
				WriteByte w 1
			else
				WriteByte w 0
			if (umeshs[i].ReceivingLight) then
				WriteByte w 1
			else
				WriteByte w 0
			if (umeshs[i].CanRender) then
				WriteByte w 1
			else
				WriteByte w 0
			if (umeshs[i].cartoon) then
				WriteByte w 1
			else
				WriteByte w 0
			if (umeshs[i].Wireframe) then
				WriteByte w 1
			else
				WriteByte w 0
			if (umeshs[i].OneSide) then
				WriteByte w 1
			else
				WriteByte w 0
			if (umeshs[i].translucented) then
				WriteByte w 1
			else
				WriteByte w 0	
				
			WriteByte w -1	
			WriteLong w -1
			WriteLong w -1
		)
		-------vert---------
		nowaddr=ftell w
		
		fseek w vptr #seek_set
		WriteLong w nowaddr
		fseek w nowaddr #seek_set

		
		if(flip) then
		(
			for v=1 to temmesh.numfaces do
			(
				WriteFloat w (getVert temmesh v)[1]
				WriteFloat w (getVert temmesh v)[3]
				WriteFloat w (0-(getVert temmesh v)[2])
				WriteFloat w 1.0
			)
		)
		else
		(
			for v=1 to temmesh.numfaces do
			(
				local faceidx=getface temmesh v
				WriteFloat w ((getVert temmesh faceidx[1])[1] * worldscale)
				WriteFloat w ((getVert temmesh faceidx[1])[2] * worldscale)
				WriteFloat w ((getVert temmesh faceidx[1])[3] * worldscale)
				WriteFloat w 1.0
				
				
				WriteFloat w ((getVert temmesh faceidx[2])[1] * worldscale)
				WriteFloat w ((getVert temmesh faceidx[2])[2] * worldscale)
				WriteFloat w ((getVert temmesh faceidx[2])[3] * worldscale)
				WriteFloat w 1.0
				
				
				WriteFloat w ((getVert temmesh faceidx[3])[1] * worldscale)
				WriteFloat w ((getVert temmesh faceidx[3])[2] * worldscale)
				WriteFloat w ((getVert temmesh faceidx[3])[3] * worldscale)
				WriteFloat w 1.0
			)
		)

		-------Normal---------
		nowaddr=ftell w
		
		fseek w vnptr #seek_set
		WriteLong w nowaddr
		fseek w nowaddr #seek_set

		local flipnormal=[1,1,1]
		if((in coordsys parent umeshs[i].scale.x)<0) then  flipnormal.x=1
		if((in coordsys parent umeshs[i].scale.y)<0) then  flipnormal.y=1
		if((in coordsys parent umeshs[i].scale.z)<0) then  flipnormal.z=1
		
		if(flip) then
		(
			for v=1 to temmesh.numfaces do
			(
				local faceidx=getface temmesh v
				WriteFloat w (getNormal temmesh faceidx[1])[1]
				WriteFloat w (getNormal temmesh faceidx[1])[3]
				WriteFloat w (0-(getNormal temmesh faceidx[1])[2])
				WriteFloat w 0.0
				
				WriteFloat w (getNormal temmesh faceidx[2])[1]
				WriteFloat w (getNormal temmesh faceidx[2])[3]
				WriteFloat w (0-(getNormal temmesh faceidx[2])[2])
				WriteFloat w 0.0
				
				WriteFloat w (getNormal temmesh faceidx[3])[1]
				WriteFloat w (getNormal temmesh faceidx[3])[3]
				WriteFloat w (0-(getNormal temmesh faceidx[3])[2])
				WriteFloat w 0.0
			)
		)
		else
		(
			--format "\n%\t\n" umeshs[i].name
			for v=1 to temmesh.numfaces do
			(
				local faceidx=meshop.getFaceRNormals temmesh v
				--local temnor=(normalize (in coordsys temmesh (getNormal temmesh faceidx[1])))
				WriteFloat w  (faceidx[1][1] * flipnormal.x)
				WriteFloat w  (faceidx[1][2] * flipnormal.y)
				WriteFloat w  (faceidx[1][3] * flipnormal.z)
				WriteFloat w 0.0
					
					--format "%\t%\t\n" faceidx[1] temnor
					
				--temnor=(normalize ((getNormal temmesh faceidx[2])))
				WriteFloat w  (faceidx[2][1] * flipnormal.x)
				WriteFloat w  (faceidx[2][2] * flipnormal.y)
				WriteFloat w  (faceidx[2][3] * flipnormal.z)
				WriteFloat w 0.0
					
					--format "%\t%\t\n" faceidx[2] temnor
					
				--temnor=(normalize ((getNormal temmesh faceidx[3])))
				WriteFloat w  (faceidx[3][1] * flipnormal.x)
				WriteFloat w  (faceidx[3][2] * flipnormal.y)
				WriteFloat w  (faceidx[3][3] * flipnormal.z)
				WriteFloat w 0.0
					
					--format "%\t%\t\n" faceidx[3] temnor
			)
		)
		
		-------tex---------
		nowaddr=ftell w
		
		fseek w vtptr #seek_set
		WriteLong w nowaddr
		fseek w nowaddr #seek_set
		/*
		local facelist=#()
		for v=1 to temmesh.numfaces do
		(
			append facelist ((getFace temmesh v)[1])
			append facelist ((getFace temmesh v)[2])
			append facelist ((getFace temmesh v)[3])
		)

		for v=1 to temmesh.numverts do
		(
			local faceidxs=(findItem facelist v)
			local vertinface=((mod (faceidxs-1) 3)+1) as integer
			faceidxs=((faceidxs-1)/3)+1
			local tvertidxs=(gettvFace temmesh faceidxs)[vertinface]
			WriteFloat w (getTVert temmesh tvertidxs)[1]
			WriteFloat w (getTVert temmesh tvertidxs)[2]
			
		)
		*/
		
		for v=1 to temmesh.numfaces do
		(
			try
			(
				local tvertidxs=(gettvFace temmesh v)
				WriteFloat w (getTVert temmesh tvertidxs[1])[1]
				WriteFloat w (getTVert temmesh tvertidxs[1])[2]
				
				
				WriteFloat w (getTVert temmesh tvertidxs[2])[1]
				WriteFloat w (getTVert temmesh tvertidxs[2])[2]
				
				
				WriteFloat w (getTVert temmesh tvertidxs[3])[1]
				WriteFloat w (getTVert temmesh tvertidxs[3])[2]
			)
			catch
			(
				WriteFloat w 0
				WriteFloat w 0
				
				WriteFloat w 0
				WriteFloat w 0
				
				WriteFloat w 0
				WriteFloat w 0
			)
			
		)
		

		-------face---------
		nowaddr=ftell w
		
		fseek w fptr #seek_set
		WriteLong w nowaddr
		fseek w nowaddr #seek_set

		for v=1 to temmesh.numfaces do
		(
			if(flipnormal.x<0) then
			(
				/*
			WriteLong w ((getFace temmesh v)[3]-1)	
			WriteLong w ((getFace temmesh v)[2]-1)
			WriteLong w ((getFace temmesh v)[1]-1)
			*/
			
				WriteLong w ((v-1)*3+2)
				WriteLong w ((v-1)*3+1)
				WriteLong w ((v-1)*3+0)
			)
			else
			(
				/*
			WriteLong w ((getFace temmesh v)[1]-1)
			WriteLong w ((getFace temmesh v)[2]-1)	
			WriteLong w ((getFace temmesh v)[3]-1)
				*/
				WriteLong w ((v-1)*3+0)
				WriteLong w ((v-1)*3+1)
				WriteLong w ((v-1)*3+2)
			)
		)
		
		-------bone---------
		local haspartbone=false
		local fatherid=0
		if(umeshs[i].parent!=undefined) then
		(
			local tbone=umeshs[i].parent
			while(tbone.parent!=undefined) do
			(
				
				if((findItem ubones tbone)==0)then
				append ubones tbone
				else
				break
				
				tbone=tbone.parent
			)
				haspartbone=true
				fatherid=(findItem ubones umeshs[i].parent)
		)
		
		 if(haspartbone==true) then
		(
			nowaddr=ftell w
			if((yus nowaddr 16)!=0) then
			(
				wnull=16-(yus nowaddr 16)
				for temnul= 1 to wnull do
				(
					WriteByte w -1
				)
			)
			nowaddr=ftell w
			
			fseek w boneptr #seek_set
			WriteLong w nowaddr
			fseek w nowaddr #seek_set
			
			bonnum=1
			for v=1 to umeshs[i].numfaces do
			(
				local j=1
				local k=1
				local tvertidxs=(getFace temmesh v)
				local boneidxs=#(fatherid,0,0,0)
				
				for vv=1 to 3 do
				(
					WriteFloat w 1
							
					for j = 2 to 4 do
					(
						WriteFloat w 0
					)
					for j = 1 to 4 do
					(
							WriteLong w boneidxs[j]
					)
				)
			)
		)
		else if(umeshs[i].modifiers[#Skin]!=undefined) then
		(
			nowaddr=ftell w
			if((yus nowaddr 16)!=0) then
			(
				wnull=16-(yus nowaddr 16)
				for temnul= 1 to wnull do
				(
					WriteByte w -1
				)
			)
			nowaddr=ftell w
			
			fseek w boneptr #seek_set
			WriteLong w nowaddr
			fseek w nowaddr #seek_set
		
			select umeshs[i]
			max modify mode
			bonnum=(skinOps.GetNumberBones umeshs[i].modifiers[#Skin])
			for v=1 to umeshs[i].numfaces do
			(
				local tvertidxs=(getFace temmesh v)
				for vv=1 to 3 do
				(
					local j=1
					local k=1
					local l=1
					local boneidxs=#(0,0,0,0)
					while j<=bonnum and k<=4 do
					(
						try
						(
							local wegs=(skinOps.GetVertexWeight umeshs[i].modifiers[#Skin] tvertidxs[vv] j)
							if (wegs!=0) then 
							(
							WriteFloat w wegs
							boneidxs[k]=(findItem ubones (getNodeByName (skinOps.GetBoneName umeshs[i].modifiers[#Skin] (skinOps.GetVertexWeightBoneID umeshs[i].modifiers[#Skin] tvertidxs[vv] j) 1)))
							k=k+1
								if(j<bonnum and k ==5) then
									format "too many weight in : % -- %" umeshs[i].name tvertidxs[vv]
							)
						)
						catch
						(
							--skip
						)
						j=j+1
					)
					for j = k to 4 do
					(
						WriteFloat w 0
					)
					for j = 1 to 4 do
					(
							WriteLong w boneidxs[j]
					)
				)
			)
			deselect umeshs[i]
		)
	)
)

--------------MATS------------/
if(sceneMaterials.count>0) then
(
	nowaddr=ftell w
		if((yus nowaddr 16)!=0) then
		(
			wnull=16-(yus nowaddr 16)
			for temnul= 1 to wnull do
			(
				WriteByte w -1
			)
		)
	nowaddr=ftell w
	
	fseek w matsAddr #seek_set
	WriteLong w nowaddr
	fseek w nowaddr #seek_set

	for i=1 to sceneMaterials.count do
	(
		nowaddr=ftell w
		if((yus nowaddr 16)!=0) then
		(
			wnull=16-(yus nowaddr 16)
			for temnul= 1 to wnull do
			(
				WriteByte w -1
			)
		)
		WriteLong w 0
		WriteLong w 0
		WriteLong w i
		WriteLong w 0

		
		nowaddr=ftell w
		WriteString w sceneMaterials[i].name
		nowaddr=ftell w-nowaddr
		for j= nowaddr to 0x1f do
		(
			WriteByte w 0
		)
	
		if((classof sceneMaterials[i])!=Standardmaterial) then
		(
			WriteFloat w 1
			WriteFloat w 1
			WriteFloat w 1
			WriteFloat w 1 
	
			WriteFloat w 1
			WriteFloat w 1
			WriteFloat w 1
			WriteFloat w 1 

			WriteFloat w 1
			WriteFloat w 1
			WriteFloat w 1
			WriteFloat w 1 

			WriteFloat w 1
			WriteFloat w 1
			WriteFloat w 1
			WriteFloat w 1 

			WriteFloat w 0
			WriteFloat w 0
			WriteFloat w 0
			WriteFloat w 0.0 

			for j=1 to 0x40 do
			(
				WriteByte w 0
			)


			for j=1 to 0x40 do
			(
				WriteByte w 0
			)


			for j=1 to 0x40 do
			(
				WriteByte w 0
			)


			for j=1 to 0x40 do
			(
				WriteByte w 0
			)
		)
		else
		(
		WriteFloat w (sceneMaterials[i].ambient.r/255.0)
		WriteFloat w (sceneMaterials[i].ambient.g/255.0)
		WriteFloat w (sceneMaterials[i].ambient.b/255.0)
		WriteFloat w 0.0
		
		WriteFloat w (sceneMaterials[i].diffuse.r/255.0)
		WriteFloat w (sceneMaterials[i].diffuse.g/255.0)
		WriteFloat w (sceneMaterials[i].diffuse.b/255.0)
		WriteFloat w 0.0 

		WriteFloat w (sceneMaterials[i].specular.r/255.0)
		WriteFloat w (sceneMaterials[i].specular.g/255.0)
		WriteFloat w (sceneMaterials[i].specular.b/255.0)
		WriteFloat w 0.0 

		WriteFloat w (sceneMaterials[i].selfIllumColor.r/255.0)
		WriteFloat w (sceneMaterials[i].selfIllumColor.g/255.0)
		WriteFloat w (sceneMaterials[i].selfIllumColor.b/255.0)
		WriteFloat w 0.0 

		WriteFloat w sceneMaterials[i].specularLevel
		WriteFloat w sceneMaterials[i].Glossiness
		WriteFloat w sceneMaterials[i].opacity
		WriteFloat w 0.0 

		if((classof sceneMaterials[i].diffusemap)==Bitmaptexture) then
		(
			WriteString w (filenameFromPath sceneMaterials[i].diffusemap.fileName)
			for j=(filenameFromPath sceneMaterials[i].diffusemap.fileName).count to 0x3e do
			(
				WriteByte w 0
			)
		)
		else
		(
			for j=1 to 0x40 do
			(
				WriteByte w 0
			)
		)

		if((classof sceneMaterials[i].specularMap)==Bitmaptexture) then
		(
			WriteString w (filenameFromPath sceneMaterials[i].specularMap.fileName)
			for j=(filenameFromPath sceneMaterials[i].specularMap.fileName).count to 0x3e do
			(
				WriteByte w 0
			)
		)
		else
		(
			for j=1 to 0x40 do
			(
				WriteByte w 0
			)
		)

		if((classof sceneMaterials[i].reflectionMap)==Bitmaptexture) then
		(
			WriteString w (filenameFromPath sceneMaterials[i].reflectionMap.fileName)
			for j=(filenameFromPath sceneMaterials[i].reflectionMap.fileName).count to 0x3e do
			(
				WriteByte w 0
			)
		)
		else
		(
			for j=1 to 0x40 do
			(
				WriteByte w 0
			)
		)

		if((classof sceneMaterials[i].bumpMap)==Normal_Bump) then
		(
			if((classof sceneMaterials[i].bumpMap.normal_map)==Bitmaptexture) then
			(
				WriteString w (filenameFromPath sceneMaterials[i].bumpMap.normal_map.fileName)
				for j=(filenameFromPath sceneMaterials[i].bumpMap.normal_map.fileName).count to 0x3e do
				(
					WriteByte w 0
				)
			)
			else
			(
				for j=1 to 0x40 do
				(
					WriteByte w 0
				)
			)
		)
		else
		(
			for j=1 to 0x40 do
			(
				WriteByte w 0
			)
		)
		)

	)
)

nowaddr=ftell w
	
	fseek w 0x30 #seek_set
	WriteLong w ubones.count
	fseek w nowaddr #seek_set
------------BONE------------/

if(ubones.count>0) then
(
	nowaddr=ftell w
		if((yus nowaddr 16)!=0) then
		(
			wnull=16-(yus nowaddr 16)
			for temnul= 1 to wnull do
			(
				WriteByte w -1
			)
		)
	nowaddr=ftell w
	
	fseek w boneAddr #seek_set
	WriteLong w nowaddr
	fseek w nowaddr #seek_set

	--WriteLong w ubones.count
	rootboneidx=#()
	baddr=#()
	for i=1 to ubones.count do
	(
		append baddr (ftell w)
		WriteLong w -1
		if(ubones[i].parent==undefined) then
		(
			append rootboneidx i
		)
	)
	
	nowaddr=ftell w
	fseek w RootboneAddr #seek_set
	WriteLong w rootboneidx[1]
	fseek w nowaddr #seek_set


	
	for i=1 to ubones.count do
	(
		nowaddr=ftell w
		if((yus nowaddr 16)!=0) then
		(
			wnull=16-(yus nowaddr 16)
			for temnul= 1 to wnull do
			(
				WriteByte w -1
			)
		)
		nowaddr=ftell w
		
		fseek w baddr[i] #seek_set
		WriteLong w nowaddr
		fseek w nowaddr #seek_set

		--0x0
		WriteLong w 0
		WriteLong w 0
		WriteLong w i
		if(ubones[i].parent==undefined) then
		(
			tidx=findItem rootboneidx i
			if(tidx==rootboneidx.count) then
			(
				/*
				if(tidx!=1) then
					WriteLong w rootboneidx[1]
				else  */
					WriteLong w 0
			)
			else
			(
				WriteLong w  rootboneidx[(tidx+1)]
			)
		)
		else
		(
			tidx=findItem ubones[i].parent.children ubones[i]
			if(tidx==ubones[i].parent.children.count) then
			(
				/*
				if(tidx!=1) then
					WriteLong w  (findItem ubones ubones[i].parent.children[1])
				else*/
					WriteLong w 0
			)
			else
			(
				WriteLong w  (findItem ubones ubones[i].parent.children[(tidx+1)])
			)
		)


		--0x10
		if(ubones[i].children.count==0) then
		(
			WriteLong w 0
		)
		else
		(
			WriteLong w (findItem ubones ubones[i].children[1])
		)
		
		
			cpos=in coordsys parent ubones[i].pos
			cpos=cpos * worldscale
			if(ubones[i].parent!=undefined	) then
			(
			crotation=normalize ((at time 0 animate on ubones[i].rotation.controller.value))
				/*
				if(in coordsys parent ubones[i].scale.x<0) then
				(
					local trots=crotation
					crotation.w=-trots.x
					crotation.z=-trots.y
					crotation.y=trots.w
					crotation.x=trots.z
				)
				--*/
			)
			else
			(
			crotation=normalize ((ubones[i].transform.rotation))
			)
			cscale=in coordsys parent ubones[i].scale
		
		----------------------------------------------------------------------
		local localboneTM=matrix3 0
		local tmrot=crotation
		local tttpos=cpos
		if(flip) then
		(
			teule=(quatToEuler crotation)
			tmrot=(eulerToQuat (EulerAngles teule.x teule.z teule.y))
			
			tttpos.y=cpos.z
			tttpos.z=0-cpos.y
		)
		
		localboneTM+=tmrot as matrix3
		localboneTM.row4+=tttpos
		localboneTM=scale localboneTM cscale
		
		
		if(ubones[i].parent==undefined) then
			WriteLong w 0
		else
			WriteLong w (findItem ubones ubones[i].parent)
		WriteLong w -1
		WriteLong w -1
		
		--0x20
		WriteFloat w cpos[1]
		if(flip) then
		(
		WriteFloat w cpos[3]
		WriteFloat w (0-cpos[2])
		)
		else
		(
		WriteFloat w cpos[2]
		WriteFloat w cpos[3]
		)
		WriteFloat w 1
		
		--0x30
		WriteFloat w crotation.x
		if(flip) then
		(
			WriteFloat w tmrot.y
			WriteFloat w tmrot.z
		)
		else
		(
			WriteFloat w crotation.y
			WriteFloat w crotation.z
		)
		WriteFloat w crotation.w
		
		--0x40
		WriteFloat w cscale[1]
		if(flip) then
		(
		WriteFloat w cscale[3]
		WriteFloat w cscale[2]
		)
		else
		(
		WriteFloat w cscale[2]
		WriteFloat w cscale[3]
		)
		WriteFloat w 1
		
		--0x50
		WriteLong w 3
		poskeyaddr=ftell w
		WriteLong w -1
		rotkeyaddr=ftell w
		WriteLong w -1
		sclkeyaddr=ftell w
		WriteLong w -1
		
		--0x60
		
		nowaddr=ftell w
		WriteString w ubones[i].name
		nowaddr=ftell w-nowaddr
		for j= nowaddr to 0x1f do
		(
			WriteByte w 0
		)
		
		--0x80
		if ((isProperty ubones[i] #Pitch)==false) then
		(
			WriteByte w 0
			WriteByte w 0
			WriteByte w 0
			WriteByte w 0
			
			WriteByte w 0
			WriteByte w 0
			WriteByte w 0
			WriteByte w 0
			
			WriteByte w 0
			WriteByte w 0
			
			WriteByte w -1
			WriteByte w -1
			
			WriteLong w -1
		)
		else
		(
			if (ubones[i].Pitch) then
				WriteByte w 1
			else
				WriteByte w 0
			if (ubones[i].Yaw) then
				WriteByte w 1
			else
				WriteByte w 0
			if (ubones[i].Roll) then
				WriteByte w 1
			else
				WriteByte w 0
			if (ubones[i].Enginethrust) then
				WriteByte w 1
			else
				WriteByte w 0
			if (ubones[i].speedbrake) then
				WriteByte w 1
			else
				WriteByte w 0
			if (ubones[i].gear) then
				WriteByte w 1
			else
				WriteByte w 0
			if (ubones[i].gearcap) then
				WriteByte w 1
			else
				WriteByte w 0
			if (ubones[i].missile) then
				WriteByte w 1
			else
				WriteByte w 0
			if (ubones[i].missiledoor) then
				WriteByte w 1
			else
				WriteByte w 0	
			if (ubones[i].special) then
				WriteByte w 1
			else
				WriteByte w 0	
				
			
			WriteByte w -1
			WriteByte w -1
			
			WriteLong w -1
		)
		
		--0x90
		localboneTM=inverse localboneTM
		
		WriteFloat w localboneTM.row1[1]
		WriteFloat w localboneTM.row2[1]
		WriteFloat w localboneTM.row3[1]
		WriteFloat w localboneTM.row4[1]
		
		WriteFloat w localboneTM.row1[2]
		WriteFloat w localboneTM.row2[2]
		WriteFloat w localboneTM.row3[2]
		WriteFloat w localboneTM.row4[2]
		
		WriteFloat w localboneTM.row1[3]
		WriteFloat w localboneTM.row2[3]
		WriteFloat w localboneTM.row3[3]
		WriteFloat w localboneTM.row4[3]
		
		WriteFloat w 0
		WriteFloat w 0
		WriteFloat w 0
		WriteFloat w 1

	--pos
		--donghua	
		nowaddr=ftell w
		if(ubones[i].Position.controller.keys.count==0) then
		(
			addNewKey ubones[i].Position.controller.keys 0
		)
		if(ubones[i].Position.controller.keys.count>0) then
		(
		
			fseek w poskeyaddr #seek_set
			WriteLong w nowaddr
			fseek w nowaddr #seek_set

			maxidx=ubones[i].Position.controller.keys.count
			WriteLong w maxidx
			posfaddr=#()
			if(maxidx!=0) then
			(
				WriteLong w ubones[i].Position.controller.keys[maxidx].time
				for j=1 to (int)(ubones[i].Position.controller.keys[maxidx].time+1) do
				(
					posfaddr[j]= (ftell w)
					WriteLong w -1
				)
			)
			else
			(
				WriteLong w 0
			)
			nowaddr=(ftell w)
			if((yus nowaddr 16)!=0) then
			(
				wnull=16-(yus nowaddr 16)
				for temnul= 1 to wnull do
				(
					WriteByte w -1
				)
			)
			--frame
			lastaddr=#(-1)
			for j=1 to maxidx do
			(
				nowaddr=(ftell w)+8
				if((yus nowaddr 16)!=0) then
				(
					wnull=16-(yus nowaddr 16)
					for temnul= 1 to wnull do
					(
						WriteByte w -1
					)
				)
				nowaddr=ftell w
			append lastaddr (nowaddr-8)

				if(j==1) then
				(
					fseek w posfaddr[1] #seek_set
					if(ubones[i].Position.controller.keys[j].time!=0) then
					(
						for ti=0 to (int)(ubones[i].Position.controller.keys[j].time) do
						(
							WriteLong w (nowaddr-8)
						)
					)
					else
					(
						WriteLong w (nowaddr-8)
					)
					fseek w nowaddr #seek_set

					WriteLong w lastaddr[j]
				)
				else
				(
					fseek w posfaddr[(int)(ubones[i].Position.controller.keys[j-1].time+2)] #seek_set
					--tmpadr=ReadLong w
					for ti=(int)(ubones[i].Position.controller.keys[j-1].time+1) to (int)(ubones[i].Position.controller.keys[j].time) do
					(
						WriteLong w (nowaddr-8)
					)
					fseek w nowaddr #seek_set
	
					WriteLong w lastaddr[j]
				)
				WriteLong w ubones[i].Position.controller.keys[j].time
				WriteFloat w ((at time ubones[i].Position.controller.keys[j].time animate on ubones[i].position.controller.x_position) * worldscale)
				if(flip) then
				(
					WriteFloat w ((at time ubones[i].Position.controller.keys[j].time animate on ubones[i].position.controller.z_position) * worldscale)
					WriteFloat w ((0-(at time ubones[i].Position.controller.keys[j].time animate on ubones[i].position.controller.y_position)) * worldscale)
				)
				else
				(
					WriteFloat w ((at time ubones[i].Position.controller.keys[j].time animate on ubones[i].position.controller.y_position) * worldscale)
					WriteFloat w ((at time ubones[i].Position.controller.keys[j].time animate on ubones[i].position.controller.z_position) * worldscale)
				)
				WriteFloat w 0.0
			)
		)
		else
		(
		)
		
	--rot
		--donghua	
		nowaddr=ftell w
		if(ubones[i].rotation.controller.keys.count==0) then
		(
			addNewKey ubones[i].rotation.controller.keys 0
		)
		if(ubones[i].rotation.controller.keys.count>0) then
		(
		
		fseek w rotkeyaddr #seek_set
		WriteLong w nowaddr
		fseek w nowaddr #seek_set

		maxidx=ubones[i].rotation.controller.keys.count
		WriteLong w maxidx
		rotfaddr=#()
		if(maxidx!=0) then
		(
			WriteLong w ubones[i].rotation.controller.keys[maxidx].time
			for j=1 to (int)(ubones[i].rotation.controller.keys[maxidx].time+1) do
			(
				rotfaddr[j]=ftell w
				WriteLong w -1
			)
		)
		else
		(
			WriteLong w 0
		)
		nowaddr=(ftell w)
			if((yus nowaddr 16)!=0) then
			(
				wnull=16-(yus nowaddr 16)
				for temnul= 1 to wnull do
				(
					WriteByte w -1
				)
			)
		--frame
		lastaddr=#(-1)
		for j=1 to maxidx do
		(
			nowaddr=(ftell w)+8
			if((yus nowaddr 16)!=0) then
			(
				wnull=16-(yus nowaddr 16)
				for temnul= 1 to wnull do
				(
					WriteByte w -1
				)
			)
			nowaddr=ftell w
			append lastaddr (nowaddr-8)

			if(j==1) then
			(
				fseek w rotfaddr[1] #seek_set
				if(ubones[i].rotation.controller.keys[j].time!=0) then
				(
					for ti=0 to (int)(ubones[i].rotation.controller.keys[j].time) do
					(
						WriteLong w (nowaddr-8)
					)
				)
				else
				(
					WriteLong w (nowaddr-8)
				)
				fseek w nowaddr #seek_set

				WriteLong w lastaddr[j]
			)
			else
			(
				fseek w rotfaddr[(int)(ubones[i].rotation.controller.keys[j-1].time+2)] #seek_set
				--tmpadr=ReadLong w
				for ti=(int)(ubones[i].rotation.controller.keys[j-1].time+1) to (int)(ubones[i].rotation.controller.keys[j].time) do
				(
					WriteLong w (nowaddr-8)
				)
				fseek w nowaddr #seek_set

				WriteLong w lastaddr[j]
			)
			local tempt=ubones[i].rotation.controller.keys[j].time
			WriteLong w tempt
			local tmprr=inverse (at time tempt animate on ubones[i].rotation.controller.value)

			if(in coordsys parent ubones[i].scale.x<0) then
				(
					/*
					local trots=tmprr
					tmprr.w=-trots.x
					tmprr.z=-trots.y
					tmprr.y=trots.w
					tmprr.x=trots.z
					--*/
				)
			WriteFloat w tmprr.x
			if(flip) then
			(
				local teule=(quatToEuler tmprr)
				local tqat=(eulerToQuat (EulerAngles teule.x teule.z teule.y))
				WriteFloat w tqat.y
				WriteFloat w tqat.z
			)
			else
			(
				WriteFloat w tmprr.y
				WriteFloat w tmprr.z
			)
			WriteFloat w tmprr.w
		)
		)

	--scl
		--donghua
		nowaddr=ftell w
		if(ubones[i].scale.controller.keys.count==0) then
		(
			addNewKey ubones[i].scale.controller.keys 0
		)
		if(ubones[i].scale.controller.keys.count>0) then
		(
		
		fseek w sclkeyaddr #seek_set
		WriteLong w nowaddr
		fseek w nowaddr #seek_set

		maxidx=ubones[i].scale.controller.keys.count
		WriteLong w maxidx
		sclfaddr=#()
		if(maxidx!=0) then
		(
			WriteLong w ubones[i].scale.controller.keys[maxidx].time
			for j=1 to (int)(ubones[i].scale.controller.keys[maxidx].time+1) do
			(
				sclfaddr[j]=ftell w
				WriteLong w -1
			)
		)
		else
		(
			WriteLong w 0
		)
			nowaddr=(ftell w)
			if((yus nowaddr 16)!=0) then
			(
				wnull=16-(yus nowaddr 16)
				for temnul= 1 to wnull do
				(
					WriteByte w -1
				)
			)
		
		--frame
		lastaddr=#(-1)
		for j=1 to maxidx do
		(
			nowaddr=(ftell w)+8
			if((yus nowaddr 16)!=0) then
			(
				wnull=16-(yus nowaddr 16)
				for temnul= 1 to wnull do
				(
					WriteByte w -1
				)
			)
			nowaddr=ftell w
			append lastaddr (nowaddr-8)

			if(j==1) then
			(
				fseek w sclfaddr[1] #seek_set
				if(ubones[i].scale.controller.keys[j].time!=0) then
				(
					for ti=0 to (int)(ubones[i].scale.controller.keys[j].time) do
					(
						WriteLong w (nowaddr-8)
					)
				)
				else
				(
					WriteLong w (nowaddr-8)
				)
				fseek w nowaddr #seek_set

				WriteLong w lastaddr[j]
			)
			else
			(
				fseek w sclfaddr[(int)(ubones[i].scale.controller.keys[j-1].time+2)] #seek_set
				--tmpadr=ReadLong w
				for ti=(int)(ubones[i].scale.controller.keys[j-1].time+1) to (int)(ubones[i].scale.controller.keys[j].time) do
				(
					WriteLong w (nowaddr-8)
				)
				fseek w nowaddr #seek_set

				WriteLong w lastaddr[j]
			)
			WriteLong w ubones[i].scale.controller.keys[j].time
			tmprr=ubones[i].scale.controller.keys[j].value
			WriteFloat w tmprr[1]
			if(flip) then
			(
				WriteFloat w tmprr[3]
				WriteFloat w tmprr[2]
			)
			else
			(
				WriteFloat w tmprr[2]
				WriteFloat w tmprr[3]
			)
			WriteFloat w 1.0
		)
		)

	)
)

--------/LIGHT--------------
if(ulights.count>0) then
(
	nowaddr=ftell w
		if((yus nowaddr 16)!=0) then
		(
			wnull=16-(yus nowaddr 16)
			for temnul= 1 to wnull do
			(
				WriteByte w -1
			)
		)
	lighttype=#(#omni,#freeSpot,#targetSpot,#freeDirect,#targetDirect)
	nowaddr=ftell w
	
	fseek w lghtAddr #seek_set
	WriteLong w nowaddr
	fseek w nowaddr #seek_set

	--WriteLong w ulights.count
	lgtaddrs=#()
	for i=1 to ulights.count do
	(
		append lgtaddrs (ftell w)
		WriteLong w -1
	)

	for i=1 to ulights.count do
	(
		nowaddr=ftell w
		if((yus nowaddr 16)!=0) then
		(
			wnull=16-(yus nowaddr 16)
			for temnul= 1 to wnull do
			(
				WriteByte w -1
			)
		)
		nowaddr=ftell w
		
		fseek w lgtaddrs[i] #seek_set
		WriteLong w nowaddr
		fseek w nowaddr #seek_set

		WriteLong w 0
		WriteLong w 0
		WriteLong w i
		WriteLong w 0

		--0x10
		WriteLong w (findItem lighttype ulights[i].type)
		WriteByte w ulights[i].color.r
		WriteByte w ulights[i].color.g
		WriteByte w ulights[i].color.b
		WriteByte w 255
		WriteLong w ulights[i].attenDecay
		if(ulights[i].type==#targetSpot or ulights[i].type==#freeSpot) then
			WriteFloat w ulights[i].hotspot
		else
			WriteFloat w 0

		--0x20
		if(ulights[i].parent!=undefined) then
			WriteLong w (findItem ubones ulights[i].parent)
		else
			WriteLong w 0
		if(ulights[i].target!=undefined) then
		(
			if(ulights[i].target.parent!=undefined) then
				WriteLong w (findItem ubones ulights[i].target.parent)
			else
				WriteLong w 0
		)
		else
			WriteLong w 0
		WriteLong w 0
		WriteLong w 0

		--0x30
		
		nowaddr=ftell w
		WriteString w ulights[i].name
		nowaddr=ftell w-nowaddr
		for j= nowaddr to 0x1f do
		(
			WriteByte w 0
		)

		--0x40
		colorkeyaddr=ftell w
		WriteLong w -1
		falloffaddr=ftell w
		WriteLong w -1
		hotspotaddr=ftell w
		WriteLong w -1
		WriteLong w -1
		
		--0x50
		lpos=ulights[i].pos * worldscale
		--lrotation=ulights[i].rotation
		lrotation=normalize (inverse ulights[i].transform.rotation)
		
		--pos
		WriteFloat w lpos[1]
		if(flip) then
		(
			WriteFloat w lpos[3]
			WriteFloat w (0-lpos[2])
		)
		else
		(
			WriteFloat w lpos[2]
			WriteFloat w lpos[3]
		)
		WriteFloat w 0
		
		--0x60
		--rot
		WriteFloat w lrotation.x
		if(flip) then
		(
			local teule=(quatToEuler lrotation)
			local tqat=(eulerToQuat (EulerAngles teule.x teule.z teule.y))
			WriteFloat w tqat.y
			WriteFloat w tqat.z
		)
		else
		(
			WriteFloat w lrotation.y
			WriteFloat w lrotation.z
		)
		WriteFloat w lrotation.w
		

	--color
		--donghua
		nowaddr=ftell w
		if(ulights[i].RGB.controller!=undefined) then
		(
		
		fseek w colorkeyaddr #seek_set
		WriteLong w nowaddr
		fseek w nowaddr #seek_set

		maxidx=ulights[i].RGB.controller.keys.count
		WriteLong w maxidx
		colorfaddr=#()
		if(maxidx!=0) then
		(
			WriteLong w ulights[i].RGB.controller.keys[maxidx].time
			for j=1 to (int)(ulights[i].RGB.controller.keys[maxidx].time+1) do
			(
				colorfaddr[j]=ftell w
				WriteLong w -1
			)
		)
		else
		(
			WriteLong w 0
		)
		/*
			nowaddr=(ftell w)
			if((yus nowaddr 16)!=0) then
			(
				wnull=16-(yus nowaddr 16)
				for temnul= 1 to wnull do
				(
					WriteByte w -1
				)
			)
		--*/
		--frame
		lastaddr=#(-1)
		for j=1 to maxidx do
		(
			nowaddr=ftell w
			append lastaddr nowaddr

			if(j==1) then
			(
				fseek w colorfaddr[1] #seek_set
				if(ulights[i].RGB.controller.keys[j].time!=0) then
				(
					for ti=0 to (int)(ulights[i].RGB.controller.keys[j].time) do
					(
						WriteLong w nowaddr
					)
				)
				else
				(
					WriteLong w nowaddr
				)
				fseek w nowaddr #seek_set
				WriteLong w lastaddr[j]
			)
			else
			(
				fseek w colorfaddr[(int)(ulights[i].RGB.controller.keys[j-1].time+2)] #seek_set
				--format "seekaddr=%\n" colorfaddr[(int)(ulights[i].RGB.controller.keys[j-1].time+1)]
				--tmpadr=ReadLong w
				for ti=(int)(ulights[i].RGB.controller.keys[j-1].time+1) to (int)(ulights[i].RGB.controller.keys[j].time) do
				(
					WriteLong w nowaddr
				)
				fseek w nowaddr #seek_set

				WriteLong w lastaddr[j]
			)
			WriteLong w ulights[i].RGB.controller.keys[j].time
			WriteByte w (at time ulights[i].RGB.controller.keys[j].time animate on ulights[i].RGB.controller.r)
			WriteByte w (at time ulights[i].RGB.controller.keys[j].time animate on ulights[i].RGB.controller.g)
			WriteByte w (at time ulights[i].RGB.controller.keys[j].time animate on ulights[i].RGB.controller.b)
			WriteByte w 0
		)
		)

	--hotspotaddr
		--donghua
		nowaddr=ftell w
		if(ulights[i].type==#targetSpot or ulights[i].type==#freeSpot) then
		(
		if(ulights[i].hotspot.controller!=undefined) then
		(
		
		fseek w hotspotaddr #seek_set
		WriteLong w nowaddr
		fseek w nowaddr #seek_set

		maxidx=ulights[i].hotspot.controller.keys.count
		WriteLong w maxidx
		hotfaddr=#()
		if(maxidx!=0) then
		(
			WriteLong w ulights[i].hotspot.controller.keys[maxidx].time
			for j=1 to (int)(ulights[i].hotspot.controller.keys[maxidx].time+1) do
			(
				hotfaddr[j]=ftell w
				WriteLong w -1
			)
		)
		else
		(
			WriteLong w 0
		)
		
		/*
		
			nowaddr=(ftell w)
			if((yus nowaddr 16)!=0) then
			(
				wnull=16-(yus nowaddr 16)
				for temnul= 1 to wnull do
				(
					WriteByte w -1
				)
			)
		--*/
		--frame
		lastaddr=#(-1)
		for j=1 to maxidx do
		(
			nowaddr=ftell w
			append lastaddr nowaddr

			if(j==1) then
			(
				fseek w hotfaddr[1] #seek_set
				if(ulights[i].hotspot.controller.keys[j].time!=0) then
				(
					for ti=0 to (int)(ulights[i].hotspot.controller.keys[j].time) do
					(
						WriteLong w nowaddr
					)
				)
				else
				(
					WriteLong w nowaddr
				)
				fseek w nowaddr #seek_set

				WriteLong w lastaddr[j]
			)
			else
			(
				fseek w hotfaddr[(int)(ulights[i].hotspot.controller.keys[j-1].time+2)] #seek_set
				--tmpadr=ReadLong w
				for ti=(int)(ulights[i].hotspot.controller.keys[j-1].time+1) to (int)(ulights[i].hotspot.controller.keys[j].time) do
				(
					WriteLong w nowaddr
				)
				fseek w nowaddr #seek_set

				WriteLong w lastaddr[j]
			)
			WriteLong w ulights[i].hotspot.controller.keys[j].time
			WriteFloat w ulights[i].hotspot.controller.keys[j].value
		)
		)
		)
	)
)

--------/CAMERA--------------
if(ucameras.count>0) then
(
	nowaddr=ftell w
		if((yus nowaddr 16)!=0) then
		(
			wnull=16-(yus nowaddr 16)
			for temnul= 1 to wnull do
			(
				WriteByte w -1
			)
		)
	cameratype=#(#target,#free)
	nowaddr=ftell w
	
	fseek w cmerAddr #seek_set
	WriteLong w nowaddr
	fseek w nowaddr #seek_set

	/*
	WriteLong w ucameras.count
	cmaaddrs=#()
	for i=1 to ucameras.count do
	(
		append cmaaddrs i
		WriteLong w 0
	)
	--*/

	for i=1 to ucameras.count do
	(
		nowaddr=ftell w
		if((yus nowaddr 16)!=0) then
		(
			wnull=16-(yus nowaddr 16)
			for temnul= 1 to wnull do
			(
				WriteByte w -1
			)
		)
		/*
		nowaddr=ftell w
		
		fseek w cmaaddrs[i] #seek_set
		WriteLong w nowaddr
		fseek w nowaddr #seek_set
		--*/

		WriteLong w 0
		WriteLong w 0
		WriteLong w i
		WriteLong w 0

		--0x10
		WriteLong w (findItem cameratype ucameras[i].type)
		WriteFloat w ucameras[i].fov
		if(ucameras[i].parent!=undefined) then
			WriteLong w (findItem ubones ucameras[i].parent)
		else
			WriteLong w 0
		if(ucameras[i].target!=undefined) then
		(
			if(ucameras[i].target.parent!=undefined) then
				WriteLong w (findItem ubones ucameras[i].target.parent)
			else
				WriteLong w 0
		)
		else
			WriteLong w 0

		--0x20
		nowaddr=ftell w
		WriteString w ucameras[i].name
		nowaddr=ftell w-nowaddr
		for j= nowaddr to 0x1f do
		(
			WriteByte w 0
		)
		
		--0x40
		lpos=ucameras[i].pos * worldscale
		lrotation=normalize (inverse ucameras[i].transform.rotation)
		
		--pos
		WriteFloat w lpos[1]
		if(flip) then
		(
		WriteFloat w lpos[3]
		WriteFloat w (0-lpos[2])
		)
		else
		(
		WriteFloat w lpos[2]
		WriteFloat w lpos[3]
		)
		WriteFloat w 0
		
		--0x50
		--rot
		WriteFloat w lrotation.x
		if(flip) then
		(
			local teule=(quatToEuler lrotation)
			local tqat=(eulerToQuat (EulerAngles teule.x teule.z teule.y))
			WriteFloat w tqat.y
			WriteFloat w tqat.z
		)
		else
		(
			WriteFloat w lrotation.y
			WriteFloat w lrotation.z
		)
		WriteFloat w lrotation.w
	)
)
nowaddr=ftell w
fseek w 4 #seek_set
WriteLong w nowaddr
fflush w
FClose w
return true
)
else
return false
)


rollout TOP_ACE_MODEL_Exporter "TOP ACE Model" 

(
label lab1 "TOP ACE Model(TEST)" height:17
button theButton "exporter" width:77 height:25
spinner worldscale "Scale:" range:[0,5555,1] type:#float pos:[27,64]
checkbox flipyz "flip YZ"  enabled:false
	
	--worldscale.pos=[0,0]
	--flipyz.enabled=false
on theButton pressed do 
(
	local ret=expfile false worldscale.value
	if(ret) then
	Messagebox "Finished"
	else
	Messagebox "No File Out"
)

)



createDialog TOP_ACE_MODEL_Exporter 170 100
