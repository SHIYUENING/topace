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
	static PIXELFORMATDESCRIPTOR pfd = //¶¨ÒåÏñËØ¸ñÊ½
	{
	   sizeof(PIXELFORMATDESCRIPTOR), // ÉÏÊö¸ñÊ½ÃèÊö·ûµÄ´óĞ¡
	   1,         // °æ±¾ºÅ
	   PFD_DRAW_TO_WINDOW |    // ¸ñÊ½Ö§³Ö´°¿Ú
	   PFD_SUPPORT_OPENGL |    // ¸ñÊ½±ØĞE§³ÖOpenGL
	   PFD_DOUBLEBUFFER,     // ±ØĞE§³ÖË«»º³E
	   PFD_TYPE_RGBA,      // ÉEERGBA ¸ñÊ½
	   24,         // 24Î»É«²ÊÉûÒÈ£¬¼´1.67Ç§ÍòµÄÕæ²ÊÉ«
	   0, 0, 0, 0, 0, 0,     // ºöÂÔµÄÉ«²ÊÎ»
	   0,         // ÎŞAlpha»º´E
	   0,         // ºöÂÔShift Bit
	   0,         // ÎŞÀÛ¼Ó»º´E
	   0, 0, 0, 0,       // ºöÂÔ¾Û¼¯Î»
	   32,         // 32Î» Z-»º´E(ÉûÒÈ»º´E
	   0,         // ÎŞÃÉ°å»º´E
	   0,         // ÎŞ¸¨Öú»º´E
	   PFD_MAIN_PLANE,      // Ö÷»æÍ¼²E
	   0,         // Reserved
	   0, 0, 0        // ºöÂÔ²ãÕÚÕÖ
	};

	int nIndex = ChoosePixelFormat(pDC->GetSafeHdc(), &pfd); //Ñ¡Ôñ¸Õ¸Õ¶¨ÒåµÄÏñËØ¸ñÊ½
	if( nIndex == 0 ) return FALSE;

	return SetPixelFormat(pDC->GetSafeHdc(), nIndex, &pfd);   //ÉèÖÃÏñËØ¸ñÊ½
}

bool CVRView::InitialGL(void)
{
	glShadeModel(GL_SMOOTH);           // ÆôÓÃÒõÓ°Æ½»¬
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);       // ºÚÉ«±³¾°
	glClearDepth(1.0f);                            // ÉèÖÃÉûÒÈ»º´E
	glEnable(GL_DEPTH_TEST);             // ÆôÓÃÉûÒÈ²âÊÔ
	glDepthFunc(GL_LEQUAL);              // Ëù×÷ÉûÒÈ²âÊÔµÄÀàĞÍ
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    // ¸æËßÏµÍ³¶ÔÍ¸ÊÓ½øĞĞĞŞÕı
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Çå³ıÆÁÄ»ºÍÉûÒÈ»º´E
	glLoadIdentity();            // ÖØÖÃµ±Ç°µÄÄ£ĞÍ¹Û²EØÕE

	turnX=turnX+1.1f;
	glTranslatef(-1.5f,0.0f,-6.0f);       // ×óÒÆ 1.5 µ¥Î»£¬²¢ÒÆÈEÁÄ» 6.0
	glRotatef(turnX,1.0f,0.0f,0.0f);
	glBegin(GL_TRIANGLES);         // »æÖÆÈı½ÇĞÎ
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f( 0.0f, 1.0f, 0.0f);       // ÉÏ¶¥µE
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f,-1.0f, 0.0f);       // ×óÏÂ
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f( 1.0f,-1.0f, 0.0f);       // ÓÒÏÂ
	glEnd();            // Èı½ÇĞÎ»æÖÆ½áÊE

	glTranslatef(3.0f,0.0f,0.0f);       // ÓÒÒÆ3µ¥Î»
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);          // »æÖÆÕı·½ĞÎ
	glVertex3f(-1.0f, 1.0f, 0.0f);       // ×óÉÏ
	glVertex3f( 1.0f, 1.0f, 0.0f);       // ÓÒÉÏ
	glVertex3f( 1.0f,-1.0f, 0.0f);       // ×óÏÂ
	glVertex3f(-1.0f,-1.0f, 0.0f);       // ÓÒÏÂ
	   glEnd();

	SwapBuffers(m_pDC->GetSafeHdc());        // ½»»»»º³åÇE
	return TRUE;
	}

void CVRView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (0 == cy)         // ·ÀÖ¹±»Áã³ı
	{
	   cy = 1;          // ½«HeightÉèÎª1
	}

	glViewport(0, 0, cx, cy);      // ÖØÖÃµ±Ç°µÄÊÓ¿Ú
	glMatrixMode(GL_PROJECTION);     // Ñ¡ÔñÍ¶Ó°¾ØÕE
	glLoadIdentity();        // ÖØÖÃÍ¶Ó°¾ØÕE

	// ÉèÖÃÊÓ¿ÚµÄ´óĞ¡
	gluPerspective(45.0f,(GLfloat)cx/(GLfloat)cy,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);      // Ñ¡ÔñÄ£ĞÍ¹Û²EØÕE
	glLoadIdentity();        // ÖØÖÃÄ£ĞÍ¹Û²EØÕE
}

void CVRView::OnAaaXxxx()
{
	MessageBox ( _T("xxx"), _T("xxx"), MB_OK | MB_ICONEXCLAMATION);
	// TODO: ‚±‚±‚ÉƒRƒ}ƒ“ƒh ƒnƒ“ƒhƒ‰ ƒR[ƒh‚ğ’Ç‰Á‚µ‚Ü‚·B
}
