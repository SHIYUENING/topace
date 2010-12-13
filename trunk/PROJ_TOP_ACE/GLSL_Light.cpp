#include "GLSL_Light.h"
#include "FileSysBace.h"
#include "CharSysBace.h"
GLhandleARB GH_VS[2][3];
GLhandleARB GH_TC;
GLhandleARB GH_TE;
GLhandleARB GH_GS[3];
GLhandleARB GH_PS[3];
GLhandleARB GH_PO[2][3];
void Init_GLSL_light(int LightSet)
{
	if(LightSet<2) return;
	GH_VS[SINGLBONE][GLSL120]=CompileShader(L"data/shader/GLSL/Light/VS_120_SINGLBONE.glsl",GL_VERTEX_SHADER);
	GH_VS[MULTIBONE][GLSL120]=CompileShader(L"data/shader/GLSL/Light/VS_120_MULTIBONE.glsl",GL_VERTEX_SHADER);
	GH_PS			[GLSL120]=CompileShader(L"data/shader/GLSL/Light/PS_120.glsl",			GL_FRAGMENT_SHADER);
	GH_PO[SINGLBONE][GLSL120]=glCreateProgramObjectARB();
	GH_PO[MULTIBONE][GLSL120]=glCreateProgramObjectARB();
	if(LightSet<3) return;
	GH_VS[SINGLBONE][GLSL150]=CompileShader(L"data/shader/GLSL/Light/VS_150_SINGLBONE.glsl",GL_VERTEX_SHADER);
	GH_VS[MULTIBONE][GLSL150]=CompileShader(L"data/shader/GLSL/Light/VS_150_MULTIBONE.glsl",GL_VERTEX_SHADER);
	GH_GS			[GLSL150]=CompileShader(L"data/shader/GLSL/Light/PS_150.glsl",			GL_GEOMETRY_SHADER);
	GH_PS			[GLSL150]=CompileShader(L"data/shader/GLSL/Light/PS_150.glsl",			GL_FRAGMENT_SHADER);
	GH_PO[SINGLBONE][GLSL150]=glCreateProgramObjectARB();
	GH_PO[MULTIBONE][GLSL150]=glCreateProgramObjectARB();
	if(LightSet<4) return;
	GH_VS[SINGLBONE][GLSL400]=CompileShader(L"data/shader/GLSL/Light/VS_400_SINGLBONE.glsl",GL_VERTEX_SHADER);
	GH_VS[MULTIBONE][GLSL400]=CompileShader(L"data/shader/GLSL/Light/VS_400_MULTIBONE.glsl",GL_VERTEX_SHADER);
	GH_TC					 =CompileShader(L"data/shader/GLSL/Light/VS_400_MULTIBONE.glsl",GL_TESS_CONTROL_SHADER);
	GH_TE					 =CompileShader(L"data/shader/GLSL/Light/VS_400_MULTIBONE.glsl",GL_TESS_EVALUATION_SHADER);
	GH_GS			[GLSL400]=CompileShader(L"data/shader/GLSL/Light/PS_400.glsl",			GL_GEOMETRY_SHADER);
	GH_PS			[GLSL400]=CompileShader(L"data/shader/GLSL/Light/PS_400.glsl",			GL_FRAGMENT_SHADER);
	GH_PO[SINGLBONE][GLSL400]=glCreateProgramObjectARB();
	GH_PO[MULTIBONE][GLSL400]=glCreateProgramObjectARB();
}
CGLSL_Light::CGLSL_Light(void)
{
}


CGLSL_Light::~CGLSL_Light(void)
{
}
