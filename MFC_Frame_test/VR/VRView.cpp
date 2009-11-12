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
	ON_COMMAND(ID_AAA_XXXX, &CVRView::OnAaaXxxx)
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
	//Invalidate(FALSE);
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
	static PIXELFORMATDESCRIPTOR pfd = //�������ظ�ʽ
	{
	   sizeof(PIXELFORMATDESCRIPTOR), // ������ʽ�������Ĵ�С
	   1,         // �汾��
	   PFD_DRAW_TO_WINDOW |    // ��ʽ֧�ִ���
	   PFD_SUPPORT_OPENGL |    // ��ʽ��ЁE���OpenGL
	   PFD_DOUBLEBUFFER,     // ��ЁE���˫����E
	   PFD_TYPE_RGBA,      // ɁE�ERGBA ��ʽ
	   24,         // 24λɫ�����ȣ���1.67ǧ������ɫ
	   0, 0, 0, 0, 0, 0,     // ���Ե�ɫ��λ
	   0,         // ��Alpha����E
	   0,         // ����Shift Bit
	   0,         // ���ۼӻ���E
	   0, 0, 0, 0,       // ���Ծۼ�λ
	   32,         // 32λ Z-����E(���Ȼ���E
	   0,         // ���ɰ建��E
	   0,         // �޸�������E
	   PFD_MAIN_PLANE,      // ����ͼ��E
	   0,         // Reserved
	   0, 0, 0        // ���Բ�����
	};

	int nIndex = ChoosePixelFormat(pDC->GetSafeHdc(), &pfd); //ѡ��ոն�������ظ�ʽ
	if( nIndex == 0 ) return FALSE;

	return SetPixelFormat(pDC->GetSafeHdc(), nIndex, &pfd);   //�������ظ�ʽ
}

bool CVRView::InitialGL(void)
{
	glShadeModel(GL_SMOOTH);           // ������Ӱƽ��
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);       // ��ɫ����
	glClearDepth(1.0f);                            // �������Ȼ���E
	glEnable(GL_DEPTH_TEST);             // �������Ȳ���
	glDepthFunc(GL_LEQUAL);              // �������Ȳ��Ե�����
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    // ����ϵͳ��͸�ӽ�������
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // �����Ļ�����Ȼ���E
	glLoadIdentity();            // ���õ�ǰ��ģ�͹۲�E�ՁE

	turnX=turnX+1.1f;
	glTranslatef(-1.5f,0.0f,-6.0f);       // ���� 1.5 ��λ������ȁE�Ļ 6.0
	glRotatef(turnX,1.0f,0.0f,0.0f);
	glBegin(GL_TRIANGLES);         // ����������
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f( 0.0f, 1.0f, 0.0f);       // �϶���E
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f,-1.0f, 0.0f);       // ����
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f( 1.0f,-1.0f, 0.0f);       // ����
	glEnd();            // �����λ��ƽ�ʁE

	glTranslatef(3.0f,0.0f,0.0f);       // ����3��λ
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);          // ����������
	glVertex3f(-1.0f, 1.0f, 0.0f);       // ����
	glVertex3f( 1.0f, 1.0f, 0.0f);       // ����
	glVertex3f( 1.0f,-1.0f, 0.0f);       // ����
	glVertex3f(-1.0f,-1.0f, 0.0f);       // ����
	   glEnd();

	SwapBuffers(m_pDC->GetSafeHdc());        // ��������ǁE
	return TRUE;
	}

void CVRView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (0 == cy)         // ��ֹ�����
	{
	   cy = 1;          // ��Height��Ϊ1
	}

	glViewport(0, 0, cx, cy);      // ���õ�ǰ���ӿ�
	glMatrixMode(GL_PROJECTION);     // ѡ��ͶӰ��ՁE
	glLoadIdentity();        // ����ͶӰ��ՁE

	// �����ӿڵĴ�С
	gluPerspective(45.0f,(GLfloat)cx/(GLfloat)cy,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);      // ѡ��ģ�͹۲�E�ՁE
	glLoadIdentity();        // ����ģ�͹۲�E�ՁE
}

void CVRView::OnAaaXxxx()
{
	MessageBox ( _T("xxx"), _T("xxx"), MB_OK | MB_ICONEXCLAMATION);
	// TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
}
