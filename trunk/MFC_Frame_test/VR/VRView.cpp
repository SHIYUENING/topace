// VRView.cpp : implementation of the CVRView class
//

#include "stdafx.h"
#include "VR.h"

#include "VRDoc.h"
#include "VRView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVRView

IMPLEMENT_DYNCREATE(CVRView, CView)

BEGIN_MESSAGE_MAP(CVRView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CVRView construction/destruction

CVRView::CVRView()
: m_pDC(NULL)
, turnX(0)
{
	// TODO: add construction code here

}

CVRView::~CVRView()
{
}

BOOL CVRView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CVRView drawing

void CVRView::OnDraw(CDC* /*pDC*/)
{
	CVRDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
//	this->UpdateWindow();
	// TODO: add draw code for native data here
	DrawScene();
	Invalidate(FALSE);
}


// CVRView printing

BOOL CVRView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVRView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVRView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CVRView diagnostics

#ifdef _DEBUG
void CVRView::AssertValid() const
{
	CView::AssertValid();
}

void CVRView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVRDoc* CVRView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVRDoc)));
	return (CVRDoc*)m_pDocument;
}
#endif //_DEBUG


// CVRView message handlers

bool CVRView::SetupPixFormat(CDC * pDC)
{
	static PIXELFORMATDESCRIPTOR pfd = //定义像素格式
	{
	   sizeof(PIXELFORMATDESCRIPTOR), // 上述格式描述符的大小
	   1,         // 版本号
	   PFD_DRAW_TO_WINDOW |    // 格式支持窗口
	   PFD_SUPPORT_OPENGL |    // 格式必须支持OpenGL
	   PFD_DOUBLEBUFFER,     // 必须支持双缓冲
	   PFD_TYPE_RGBA,      // 申请 RGBA 格式
	   24,         // 24位色彩深度，即1.67千万的真彩色
	   0, 0, 0, 0, 0, 0,     // 忽略的色彩位
	   0,         // 无Alpha缓存
	   0,         // 忽略Shift Bit
	   0,         // 无累加缓存
	   0, 0, 0, 0,       // 忽略聚集位
	   32,         // 32位 Z-缓存 (深度缓存)
	   0,         // 无蒙板缓存
	   0,         // 无辅助缓存
	   PFD_MAIN_PLANE,      // 主绘图层
	   0,         // Reserved
	   0, 0, 0        // 忽略层遮罩
	};

	int nIndex = ChoosePixelFormat(pDC->GetSafeHdc(), &pfd); //选择刚刚定义的像素格式
	if( nIndex == 0 ) return FALSE;

	return SetPixelFormat(pDC->GetSafeHdc(), nIndex, &pfd);   //设置像素格式
}

bool CVRView::InitialGL(void)
{
	glShadeModel(GL_SMOOTH);           // 启用阴影平滑
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);       // 黑色背景
	glClearDepth(1.0f);                            // 设置深度缓存
	glEnable(GL_DEPTH_TEST);             // 启用深度测试
	glDepthFunc(GL_LEQUAL);              // 所作深度测试的类型
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    // 告诉系统对透视进行修正
	return TRUE;
}

int CVRView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_pDC = new CClientDC(this);
	SetupPixFormat(m_pDC);

	HGLRC hrc = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(), hrc);

	InitialGL();
	return 0;
}

void CVRView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	HGLRC hrc = wglGetCurrentContext();
	wglMakeCurrent(NULL, 0);
	wglDeleteContext(hrc);
	delete m_pDC;
}

bool CVRView::DrawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // 清除屏幕和深度缓存
	glLoadIdentity();            // 重置当前的模型观察矩阵

	turnX=turnX+1.1f;
	glTranslatef(-1.5f,0.0f,-6.0f);       // 左移 1.5 单位，并移入屏幕 6.0
	glRotatef(turnX,1.0f,0.0f,0.0f);
	glBegin(GL_TRIANGLES);         // 绘制三角形
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f( 0.0f, 1.0f, 0.0f);       // 上顶点
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f,-1.0f, 0.0f);       // 左下
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f( 1.0f,-1.0f, 0.0f);       // 右下
	glEnd();            // 三角形绘制结束

	glTranslatef(3.0f,0.0f,0.0f);       // 右移3单位
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);          // 绘制正方形
	glVertex3f(-1.0f, 1.0f, 0.0f);       // 左上
	glVertex3f( 1.0f, 1.0f, 0.0f);       // 右上
	glVertex3f( 1.0f,-1.0f, 0.0f);       // 左下
	glVertex3f(-1.0f,-1.0f, 0.0f);       // 右下
	   glEnd();

	SwapBuffers(m_pDC->GetSafeHdc());        // 交换缓冲区
	return TRUE;
	}

void CVRView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (0 == cy)         // 防止被零除
	{
	   cy = 1;          // 将Height设为1
	}

	glViewport(0, 0, cx, cy);      // 重置当前的视口
	glMatrixMode(GL_PROJECTION);     // 选择投影矩阵
	glLoadIdentity();        // 重置投影矩阵

	// 设置视口的大小
	gluPerspective(45.0f,(GLfloat)cx/(GLfloat)cy,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);      // 选择模型观察矩阵
	glLoadIdentity();        // 重置模型观察矩阵
}
