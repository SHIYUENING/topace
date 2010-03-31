meshdef = attributes "TOP ACE Mesh Data"
(
	parameters main rollout:topaceattr
	(
		castShadow type:#Boolean ui:castShadow default:true
		ReceivingLight type:#Boolean ui:ReceivingLight default:true 
		CanRender type:#Boolean  ui:CanRender default:true 
		cartoon type:#Boolean  ui:cartoon default:false 
		Wireframe type:#Boolean  ui:Wireframe default:false 
		OneSide  type:#Boolean  ui:OneSide default:true 
		translucented type:#Boolean  ui:translucented default:false 
	)
	rollout topaceattr "TOP ACE Attributes"
	(
		checkbox castShadow "Cast Shadow" checked:true 
		checkbox ReceivingLight "Receiving Light" checked:true 
		checkbox CanRender "Render" checked:true 
		checkbox cartoon "Cartoon Render" checked:false 
		checkbox Wireframe "Render Wireframe" checked:false 
		checkbox OneSide "One Side" checked:true 
		checkbox translucented "translucent" checked:false 
	)
)


bonedef = attributes "TOP ACE Bone Data"
(
	parameters main rollout:topaceattr
	(
		Pitch type:#Boolean ui:Pitch default:false
		Yaw type:#Boolean ui:Yaw default:false 
		Roll type:#Boolean  ui:Roll default:false 
		Enginethrust type:#Boolean  ui:Enginethrust default:false 
		speedbrake type:#Boolean  ui:speedbrake default:false 
		gear  type:#Boolean  ui:gear default:false 
		gearcap type:#Boolean  ui:gearcap default:false 
		missile type:#Boolean  ui:missile default:false 
		missiledoor type:#Boolean  ui:missiledoor default:false 
		special type:#Boolean  ui:special default:false 
	)
	rollout topaceattr "TOP ACE Attributes"
	(
		checkbox Pitch "Pitch" checked:true 
		checkbox Yaw "Yaw" checked:true 
		checkbox Roll "Roll" checked:true 
		checkbox Enginethrust "Engine thrust" checked:false 
		checkbox speedbrake "speed brake" checked:false 
		checkbox gear "gear" checked:true 
		checkbox gearcap "gear cap" checked:false 
		checkbox missile "missile" checked:false 
		checkbox missiledoor "missile door" checked:false 
		checkbox special "special" checked:false 
	)
)

fn addall= 
(
	count=#(0,0)
	for g in Geometry where (classof g == Editable_mesh) do
	(
		if ((isProperty g #castshadow)==false) then
		(
			custAttributes.add g meshdef
			count[1]=count[1]+1
		)
	)
	
	for g in Geometry where (classof g == BoneGeometry) do
	(
		if ((isProperty g #Pitch)==false) then
		(
			custAttributes.add g bonedef
			count[2]=count[2]+1
		)
	)
	return count
)

rollout AddAttrib "Add Attributes" 

(
--label lab1 "Add Attributes" height:17
button theButton "Add ALL" width:77 height:25
on theButton pressed do 
(
	ss = stringstream ""
	count=addall()
	format "Add % Meshs\nAdd % Bones" count[1] count[2] to:ss
	Messagebox (ss as string) title:"Result"
	DestroyDialog AddAttrib
)

)

rollout getTopAceAttrib "Get Attributes" 

(
	button Getatt "GET" width:77 height:25
	on Getatt pressed do 
	(
		if (selection.count >0) then
		(
			if ((isProperty selection[1] #castshadow)==true) then
			(
				tmpedt =newRolloutFloater selection[1].name 350 200
				addRollout selection[1].topaceattr tmpedt
			)
			else if ((isProperty selection[1] #Pitch)==true) then
			(
				tmpedt =newRolloutFloater selection[1].name 350 200
				addRollout selection[1].topaceattr tmpedt
			)
		)
	)
)


createDialog AddAttrib 157 37
createDialog getTopAceAttrib 157 37