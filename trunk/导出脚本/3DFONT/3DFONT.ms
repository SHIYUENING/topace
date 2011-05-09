rollout Gen3DFONT "Gen 3D FONT"
(
button genfont "Gen FONT" 
	spinner fontheight "Font Height:" range:[0,0.2,0.07] type:#float scale:0.01
progressbar font_prog color:red 
label Info1 "0/0"
label Info2 ""	

	
on genfont pressed do -- when the button is pressed...
(
local x=0
local y=0
local debugon=false
	timcount=0
	DotNet.loadAssembly @"F:\lotsbiss\TOPACE\导出脚本\3DFONT\FONT3D\FONT3D\bin\Release\FONT3D.dll"
	local FontGener =  DotNetObject "FONT3D.Font3D" @"F:\lotsbiss\TOPACE\导出脚本\3DFONT\unicode.txt" 1200
	--ttcharcount = dotNetObject "System.Int32" FontGener.CharCount
	local charcount=FontGener.CharCount
	local tcont=charcount as integer
	Info1.text="0/"+(tcont as string)
	local timebuf=getLocalTime()
	local curtime=timebuf[5]*3600+timebuf[6]*60+timebuf[7]
	local lastime=curtime
	
	local temw=fopen @"F:\lotsbiss\TOPACE\导出脚本\3DFONT\test.fnt.tmp" "wb"
	WriteLong temw charcount
	
	for i = 1 to charcount do
	(
		font_prog.value = 100.*i/tcont
		Info1.text=(i as string)+"/"+ (tcont as string)
		if((mod i 100)==0) then
		(			
			timebuf=getLocalTime()
			curtime=timebuf[5]*3600+timebuf[6]*60+timebuf[7]
			Info2.text=(i/(curtime-lastime)) as string + " chars per sec"
			--lastime=curtime
		)
		
		tch=FontGener.GetChar (i-1)
		--tch="啊"
		tchmesh=text size:1 kerning:0 leading:0 pos:[0.5,0.257,0] isSelected:off steps:2 text:tch font:"微软雅黑"
		convertToMesh tchmesh
		if(fontheight.value>0) then
		(
			addModifier tchmesh (Shell ())
			tchmesh.modifiers[1].outerAmount = fontheight.value
			tchmesh.modifiers[1].autoSmoothAngle = 37
			maxOps.CollapseNode tchmesh true
			meshop.explodeAllFaces tchmesh 1.344
		)
		deselect tchmesh
			
		--local vtArray = dotNetObject "System.Single[]" (tchmesh.numverts*3)
		--local vnArray = dotNetObject "System.Single[]" (tchmesh.numverts*3)
		--local fArray = dotNetObject "System.Int32[]" (tchmesh.numfaces*3)
		
		WriteLong temw tchmesh.numverts
		WriteLong temw tchmesh.numfaces
		for vtidx = 1 to tchmesh.numverts do
		(	
			--local vts=getFace tchmesh fidx
			local temvvt=getVert tchmesh vtidx
				for xyz= 1 to 3 do
				(
					WriteFloat temw temvvt[xyz]
					--local vtValue = dotNetObject "System.Single" (temvvt[xyz])	
					--local vtIndex = dotNetObject "System.Int32"((vtidx-1)*3+xyz-1)	
					--vtArray.SetValue vtValue vtIndex
				)
		)
		
		for vtidx = 1 to tchmesh.numverts do
		(	
			--local vts=getFace tchmesh fidx
			local temvvt=getNormal tchmesh vtidx
				for xyz= 1 to 3 do
				(
					WriteFloat temw temvvt[xyz]
					--local vtValue = dotNetObject "System.Single" ((getNormal tchmesh vtidx)[xyz])	
					--local vtIndex = dotNetObject "System.Int32"((vtidx-1)*3+xyz-1)	
					--vnArray.SetValue vtValue vtIndex
				)
		)
		
		
		for fidx = 1 to tchmesh.numfaces do
		(	
			local vts=getFace tchmesh fidx
				for xyz= 1 to 3 do
				(
					WriteLong temw (vts[xyz]-1)
					--local vtValue = dotNetObject "System.Int32" (vts[xyz]-1)	
					--local vtIndex = dotNetObject "System.Int32"((fidx-1)*3+xyz-1)	
					--fArray.SetValue vtValue vtIndex
				)
		)
		--FontGener.SetCharVert (i-1) vtArray
		--FontGener.SetCharNormal (i-1) vtArray
		--FontGener.SetCharFace (i-1) fArray
		if(debugon) then
		(
			local ss=text size:10 kerning:0 leading:0 pos:[x*10,-y*10,0] isSelected:off steps:2 text:tch font:"微软雅黑"
			convertToMesh ss
		)
		delete tchmesh

		x+=1
		if(x>32)then
		(
			y+=1
			x=0
		)
	)
	fflush temw
	fclose temw
	FontGener.GetTmpFile @"F:\lotsbiss\TOPACE\导出脚本\3DFONT\test.fnt.tmp"
	FontGener.savefile @"F:\lotsbiss\TOPACE\导出脚本\3DFONT\test.fnt"
	font_prog.value=0
	Info1.text="0/"+(tcont as string)
)
)

createDialog Gen3DFONT 170 127