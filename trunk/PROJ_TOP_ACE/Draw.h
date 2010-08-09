#ifndef _DRAW_H
#define _DRAW_H

void InitDraw();
void DeinitDraw();
void ClearVRAM();
void Draw(float oneframetimepointCPUSYS=0.0f,float oneframetimepointGPU=0.0f);
void InitTestModel();
void DrawTestModel();
void DeinitTestModel();
#endif