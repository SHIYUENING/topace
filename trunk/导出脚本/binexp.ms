fn yus a b=
(
	return a-(a/b)*b
)

fn expfile debugon = 
(
--/*
out_name = GetSaveFileName \
	types:"TOP_ACE模型文件|*.tam|其他类型(*.*)|*.*|"
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
	WriteLong w 0
	WriteLong w 0
	
	
)

(
	umeshs=#()
	--mats=#()
	ubones=#()
	ulights=#()
	ucameras=#()

	for g in Geometry where (classof g == Editable_mesh) do
	(
		append umeshs g
	)
	/*
	for g in Geometry where (classof g == Editable_mesh)
	(
		append mats g.name
	)
	*/
	for g in Geometry where (classof g == BoneGeometry) do
	(
		append ubones g
	)
	--/*
	for g in Lights where (classof g != Targetobject) do
	(
		append ulights g
	)
	--*/
	--/*
	for g in Cameras where (classof g != Targetobject) do
	(
		append ucameras g
	)
	--*/
)

--------/MESH--------------
if(umeshs.count>0) then
(
	nowaddr=ftell w
	
	fseek w meshAddr #seek_set
	WriteLong w nowaddr
	fseek w nowaddr #seek_set

	matidx=0

	WriteLong w umeshs.count
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

		if(umeshs[i].modifiers[#Skin]!=undefined) then
		(
			select umeshs[i]
			max modify mode
			bonnum=(skinOps.GetNumberBones umeshs[i].modifiers[#Skin])
			for j = 1 to 4 do
			(
				if(j<=bonnum) then
				(
					try
						WriteFloat w (skinOps.GetVertexWeight umeshs[i].modifiers[#Skin] 1 j)
					catch
						WriteFloat w 0
				)
				else
				(
					WriteFloat w 0
				)
			)
			for j = 1 to 4 do
			(
				if(j<=bonnum) then
				(
					WriteLong w (findItem ubones (skinOps.GetBoneName umeshs[i].modifiers[#Skin] j 1))
				)
				else
				(
					WriteLong w 0
				)
			)
			deselect umeshs[i]
		)
		else
		(
			for j = 1 to 8 do
			(
				WriteLong w 0
			)
		)

		for j = 1 to 4 do
		(
			WriteLong w 0
		)

		------------------------
		WriteLong w 4 --obj内数据数量?
		vptr=ftell w
		WriteLong w -1
		vnptr=ftell w
		WriteLong w -1
		vtptr=ftell w
		WriteLong w -1

		fptr=ftell w
		WriteLong w -1
		WriteLong w umeshs[i].numfaces
		WriteLong w 0
		WriteLong w 0

		WriteString w umeshs[i].name
		for j= umeshs[i].name.count to 0x1e do
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
		-------vert---------
		nowaddr=ftell w
		
		fseek w vptr #seek_set
		WriteLong w nowaddr
		fseek w nowaddr #seek_set

		for v=1 to umeshs[i].numverts do
		(
			WriteFloat w (getVert umeshs[i] v)[1]
			WriteFloat w (getVert umeshs[i] v)[2]
			WriteFloat w (getVert umeshs[i] v)[3]
			WriteFloat w 1.0
		)

		-------Normal---------
		nowaddr=ftell w
		
		fseek w vnptr #seek_set
		WriteLong w nowaddr
		fseek w nowaddr #seek_set

		for v=1 to umeshs[i].numverts do
		(
			WriteFloat w (getNormal umeshs[i] v)[1]
			WriteFloat w (getNormal umeshs[i] v)[2]
			WriteFloat w (getNormal umeshs[i] v)[3]
			WriteFloat w 0.0
		)
		
		-------tex---------
		nowaddr=ftell w
		
		fseek w vtptr #seek_set
		WriteLong w nowaddr
		fseek w nowaddr #seek_set

		for v=1 to umeshs[i].numverts do
		(
			try
			(
				WriteFloat w (getTVert umeshs[i] v)[1]
				WriteFloat w (getTVert umeshs[i] v)[2]
			)
			catch
			(
				WriteFloat w 0.0
				WriteFloat w 0.0
				if(debugon) then
				(
					format "%:贴图坐标 % 错误，已跳过\n" umeshs[i].name v
				)
				--
			)
		)

		-------face---------
		nowaddr=ftell w
		
		fseek w fptr #seek_set
		WriteLong w nowaddr
		fseek w nowaddr #seek_set

		for v=1 to umeshs[i].numfaces do
		(
			WriteLong w (getFace umeshs[i] v)[1]
			WriteLong w (getFace umeshs[i] v)[2]
			WriteLong w (getFace umeshs[i] v)[3]
		)
	)
)

--------------MATS------------/
if(sceneMaterials.count>0) then
(
	nowaddr=ftell w
	
	fseek w matsAddr #seek_set
	WriteLong w nowaddr
	fseek w nowaddr #seek_set

	for i=1 to sceneMaterials.count do
	(
		WriteLong w 0
		WriteLong w 0
		WriteLong w i
		WriteLong w 0

		WriteString w sceneMaterials[i].name
		for j= sceneMaterials[i].name.count to 0x1e do
		(
			WriteByte w 0
		)

		WriteByte w sceneMaterials[i].ambient.r
		WriteByte w sceneMaterials[i].ambient.g
		WriteByte w sceneMaterials[i].ambient.b
		WriteByte w 255 

		WriteByte w sceneMaterials[i].diffuse.r
		WriteByte w sceneMaterials[i].diffuse.g
		WriteByte w sceneMaterials[i].diffuse.b
		WriteByte w 255 

		WriteByte w sceneMaterials[i].specular.r
		WriteByte w sceneMaterials[i].specular.g
		WriteByte w sceneMaterials[i].specular.b
		WriteByte w 255 

		WriteByte w sceneMaterials[i].selfIllumColor.r
		WriteByte w sceneMaterials[i].selfIllumColor.g
		WriteByte w sceneMaterials[i].selfIllumColor.b
		WriteByte w 255 

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

------------BONE------------/
sliderTime=0
if(ubones.count>0) then
(
	nowaddr=ftell w
	
	fseek w boneAddr #seek_set
	WriteLong w nowaddr
	fseek w nowaddr #seek_set

	WriteLong w ubones.count
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
	for i=1 to ubones.count do
	(
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
				if(tidx!=1) then
					WriteLong w rootboneidx[1]
				else
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
				if(tidx!=1) then
					WriteLong w  (findItem ubones ubones[i].parent.children[1])
				else
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
		
		if(ubones[i].parent==undefined) then
		(
			cpos=ubones[i].pos
			crotation=ubones[i].rotation
			cscale=ubones[i].scale
		)
		else
		(
			cpos=ubones[i].parent.pos - ubones[i].pos
			crotation=ubones[i].parent.rotation - ubones[i].rotation
			cscale=ubones[i].scale
		)
		WriteLong w -1
		WriteLong w -1
		WriteLong w -1
		
		--0x20
		--位置
		WriteFloat w cpos[1]
		WriteFloat w cpos[2]
		WriteFloat w cpos[3]
		WriteFloat w 0
		
		--0x30
		--旋转
		WriteFloat w crotation.x
		WriteFloat w crotation.y
		WriteFloat w crotation.z
		WriteFloat w crotation.w
		
		--0x40
		--缩放
		WriteFloat w cscale[1]
		WriteFloat w cscale[2]
		WriteFloat w cscale[3]
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
		WriteString w ubones[i].name
		for j=ubones[i].name.count to 0x1e do
		(
			WriteByte w 0
		)

	--pos
		--动画	
		nowaddr=ftell w
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
					posfaddr[j]=ftell w
					WriteLong w -1
				)
			)
			else
			(
				WriteLong w 0
			)
		
			--帧
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
			append lastaddr nowaddr

				if(j==1) then
				(
					fseek w posfaddr[1] #seek_set
					if(ubones[i].Position.controller.keys[j].time!=0) then
					(
						for ti=0 to (int)(ubones[i].Position.controller.keys[j].time) do
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
					fseek w posfaddr[(int)(ubones[i].Position.controller.keys[j-1].time+2)] #seek_set
					--tmpadr=ReadLong w
					for ti=(int)(ubones[i].Position.controller.keys[j-1].time+1) to (int)(ubones[i].Position.controller.keys[j].time) do
					(
						WriteLong w nowaddr
					)
					fseek w nowaddr #seek_set
	
					WriteLong w lastaddr[j]
				)
				WriteLong w ubones[i].Position.controller.keys[j].time
				WriteFloat w (at time ubones[i].Position.controller.keys[j].time animate on ubones[i].position.controller.x_position)
				WriteFloat w (at time ubones[i].Position.controller.keys[j].time animate on ubones[i].position.controller.y_position)
				WriteFloat w (at time ubones[i].Position.controller.keys[j].time animate on ubones[i].position.controller.z_position)
				WriteFloat w 0.0
			)
		)
		else
		(
		)
		
	--rot
		--动画	
		nowaddr=ftell w
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
		
		--帧
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
			append lastaddr nowaddr

			if(j==1) then
			(
				fseek w rotfaddr[1] #seek_set
				if(ubones[i].rotation.controller.keys[j].time!=0) then
				(
					for ti=0 to (int)(ubones[i].rotation.controller.keys[j].time) do
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
				fseek w rotfaddr[(int)(ubones[i].rotation.controller.keys[j-1].time+2)] #seek_set
				--tmpadr=ReadLong w
				for ti=(int)(ubones[i].rotation.controller.keys[j-1].time+1) to (int)(ubones[i].rotation.controller.keys[j].time) do
				(
					WriteLong w nowaddr
				)
				fseek w nowaddr #seek_set

				WriteLong w lastaddr[j]
			)
			tempt=ubones[i].rotation.controller.keys[j].time
			WriteLong w tempt
			tmprr=((EulerAngles (at time tempt animate on ubones[i].rotation.controller.x_rotation) (at time tempt animate on ubones[i].rotation.controller.y_rotation) (at time tempt animate on ubones[i].rotation.controller.z_rotation)) as quat)
			WriteFloat w tmprr.x
			WriteFloat w tmprr.y
			WriteFloat w tmprr.z
			WriteFloat w tmprr.w
		)
		)

	--scl
		--动画	
		nowaddr=ftell w
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
		
		--帧
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
			append lastaddr nowaddr

			if(j==1) then
			(
				fseek w sclfaddr[1] #seek_set
				if(ubones[i].scale.controller.keys[j].time!=0) then
				(
					for ti=0 to (int)(ubones[i].scale.controller.keys[j].time) do
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
				fseek w sclfaddr[(int)(ubones[i].scale.controller.keys[j-1].time+2)] #seek_set
				--tmpadr=ReadLong w
				for ti=(int)(ubones[i].scale.controller.keys[j-1].time+1) to (int)(ubones[i].scale.controller.keys[j].time) do
				(
					WriteLong w nowaddr
				)
				fseek w nowaddr #seek_set

				WriteLong w lastaddr[j]
			)
			WriteLong w ubones[i].scale.controller.keys[j].time
			tmprr=ubones[i].scale.controller.keys[j].value
			WriteFloat w tmprr[1]
			WriteFloat w tmprr[2]
			WriteFloat w tmprr[3]
			WriteFloat w 0.0
		)
		)

	)
)

--------/LIGHT--------------
if(ulights.count>0) then
(
	lighttype=#(#omni,#freeSpot,#targetSpot,#freeDirect,#targetDirect)
	nowaddr=ftell w
	
	fseek w lghtAddr #seek_set
	WriteLong w nowaddr
	fseek w nowaddr #seek_set

	WriteLong w ulights.count
	lgtaddrs=#()
	for i=1 to ulights.count do
	(
		append lgtaddrs (ftell w)
		WriteLong w -1
	)

	for i=1 to ulights.count do
	(
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
		WriteString w ulights[i].name
		for temi= ulights[i].name.count to 0x1e do
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

	--color
		--动画
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
		
		--帧
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
		--动画
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
		
		--帧
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
		WriteString w ucameras[i].name
		for temi= ucameras[i].name.count to 0x1e do
		(
			WriteByte w 0
		)
	)
)
nowaddr=ftell w
fseek w 4 #seek_set
WriteLong w nowaddr
fflush w
FClose w
)
)


rollout TOP_ACE_MODEL_Exporter "TOP ACE 模型导出器" 

(
label lab1 "TOP ACE 模型导出器(测试)" height:17
button theButton "导出" width:77 height:25
checkbox debugon "显示贴图坐标错误信息" 
on theButton pressed do 
(
	expfile debugon.checked
	Messagebox "完成"
)

)



createDialog TOP_ACE_MODEL_Exporter 170 80