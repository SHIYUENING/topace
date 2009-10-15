/*
When creating your project, uncheck OWL,
uncheck Class Library, select Static
instead of Dynamic and change the target
model to Console from GUI.
Also link glut.lib to your project once its done.
*/
//#define STRICT
//#define DIRECTINPUT_VERSION 0x0800
#include <windows.h>   // Standard Header For Most Programs
#include <GL/glew.h>
#include <GL/gl.h>     // The GL Header File
#include <GL/freeglut.h>   // The GL Utility Toolkit (Glut) Header
#include <pthread.h>


//#include "GamePads.h"
//#include "dinputd.h"
//#include <commctrl.h>
//#pragma comment( lib, "dinput8.lib" )	
//#pragma comment( lib, "dxguid.lib" )	
//#pragma comment( lib, "comctl32.lib" )	
#pragma comment( lib, "pthreadVC2.lib" )	
#pragma comment( lib, "glew32.lib" )	
#pragma comment( lib, "glew32d.lib" )
float	rtri;						// Angle For The Triangle
float	rquad;						// Angle For The Quad
int winW=800;
int winH=600;
pthread_mutex_t mutex;
struct timespec delay;
bool ispad=true;
bool ispadEffect=true;
/*
//IDirectInput8 *g_pDI; // global DirectInput object
//IDirectInputDevice8 *pDIDevice;
//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

#define FEEDBACK_WINDOW_X       20
#define FEEDBACK_WINDOW_Y       60
#define FEEDBACK_WINDOW_WIDTH   200

LPDIRECTINPUT8          g_pDI = NULL;
LPDIRECTINPUTDEVICE8    g_pDevice = NULL;
LPDIRECTINPUTEFFECT     g_pEffect = NULL;
BOOL                    g_bActive = TRUE;
DWORD                   g_dwNumForceFeedbackAxis = 0;
INT                     g_nXForce = 0000;
INT                     g_nYForce = 5000;
DWORD                   g_dwLastEffectSet; // Time of the previous force feedback effect set


INT CoordToForce( INT x );
HRESULT SetDeviceForcesXY();
BOOL CALLBACK EnumFFDevicesCallback( const DIDEVICEINSTANCE* pInst, VOID* pContext );
BOOL CALLBACK EnumAxesCallback( const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext );
HRESULT InitDirectInput( HWND hDlg );
VOID FreeDirectInput();
//-----------------------------------------------------------------------------
// Name: InitDirectInput()
// Desc: Initialize the DirectInput variables.
//-----------------------------------------------------------------------------
HRESULT InitDirectInput( HWND hDlg )
{
    DIPROPDWORD dipdw;
    HRESULT hr;

    // Register with the DirectInput subsystem and get a pointer
    // to a IDirectInput interface we can use.
    if( FAILED( hr = DirectInput8Create( GetModuleHandle( NULL ), DIRECTINPUT_VERSION,
                                         IID_IDirectInput8, ( VOID** )&g_pDI, NULL ) ) )
    {
		ispad=false;
        return hr;
    }

    // Look for a force feedback device we can use
    if( FAILED( hr = g_pDI->EnumDevices( DI8DEVCLASS_GAMECTRL,
                                         EnumFFDevicesCallback, NULL,
                                         DIEDFL_ATTACHEDONLY | DIEDFL_FORCEFEEDBACK ) ) )
    {
		ispad=false;
        return hr;
    }

    if( NULL == g_pDevice )
    {
		ispad=false;
        MessageBox (HWND_DESKTOP, "Error DirectInput", "Error", MB_OK | MB_ICONEXCLAMATION);
        return S_OK;
    }

    // Set the data format to "simple joystick" - a predefined data format. A
    // data format specifies which controls on a device we are interested in,
    // and how they should be reported.
    //
    // This tells DirectInput that we will be passing a DIJOYSTATE structure to
    // IDirectInputDevice8::GetDeviceState(). Even though we won't actually do
    // it in this sample. But setting the data format is important so that the
    // DIJOFS_* values work properly.
    if( FAILED( hr = g_pDevice->SetDataFormat( &c_dfDIJoystick ) ) )
	{
		ispad=false;
        return hr;
	}

    // Set the cooperative level to let DInput know how this device should
    // interact with the system and with other DInput applications.
    // Exclusive access is required in order to perform force feedback.
    if( FAILED( hr = g_pDevice->SetCooperativeLevel( hDlg,
                                                     DISCL_EXCLUSIVE |
                                                     DISCL_FOREGROUND ) ) )
    {
		ispad=false;
        return hr;
    }

    // Since we will be playing force feedback effects, we should disable the
    // auto-centering spring.
    dipdw.diph.dwSize = sizeof( DIPROPDWORD );
    dipdw.diph.dwHeaderSize = sizeof( DIPROPHEADER );
    dipdw.diph.dwObj = 0;
    dipdw.diph.dwHow = DIPH_DEVICE;
    dipdw.dwData = FALSE;

    if( FAILED( hr = g_pDevice->SetProperty( DIPROP_AUTOCENTER, &dipdw.diph ) ) )
	{
		ispad=false;
        return hr;
	}

    // Enumerate and count the axes of the joystick 
    if( FAILED( hr = g_pDevice->EnumObjects( EnumAxesCallback,
                                             ( VOID* )&g_dwNumForceFeedbackAxis, DIDFT_AXIS ) ) )
	{
		ispad=false;
        return hr;
	}

    // This simple sample only supports one or two axis joysticks
    if( g_dwNumForceFeedbackAxis > 2 )
        g_dwNumForceFeedbackAxis = 2;

    // This application needs only one effect: Applying raw forces.
    DWORD rgdwAxes[2] = { DIJOFS_X, DIJOFS_Y };
    LONG rglDirection[2] = { 0, 0 };
    DICONSTANTFORCE cf = { 0 };

    DIEFFECT eff;
    ZeroMemory( &eff, sizeof( eff ) );
    eff.dwSize = sizeof( DIEFFECT );
    eff.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
    eff.dwDuration = INFINITE;
    eff.dwSamplePeriod = 0;
    eff.dwGain = DI_FFNOMINALMAX;
    eff.dwTriggerButton = DIEB_NOTRIGGER;
    eff.dwTriggerRepeatInterval = 0;
    eff.cAxes = g_dwNumForceFeedbackAxis;
    eff.rgdwAxes = rgdwAxes;
    eff.rglDirection = rglDirection;
    eff.lpEnvelope = 0;
    eff.cbTypeSpecificParams = sizeof( DICONSTANTFORCE );
    eff.lpvTypeSpecificParams = &cf;
    eff.dwStartDelay = 0;

    // Create the prepared effect
    if( FAILED( hr = g_pDevice->CreateEffect( GUID_ConstantForce,
                                              &eff, &g_pEffect, NULL ) ) )
    {
		ispad=false;
        return hr;
    }

    if( NULL == g_pEffect )
	{
		ispadEffect=false;
        return E_FAIL;
	}

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: EnumAxesCallback()
// Desc: Callback function for enumerating the axes on a joystick and counting
//       each force feedback enabled axis
//-----------------------------------------------------------------------------
BOOL CALLBACK EnumAxesCallback( const DIDEVICEOBJECTINSTANCE* pdidoi,
                                VOID* pContext )
{
    DWORD* pdwNumForceFeedbackAxis = ( DWORD* )pContext;

    if( ( pdidoi->dwFlags & DIDOI_FFACTUATOR ) != 0 )
        ( *pdwNumForceFeedbackAxis )++;

    return DIENUM_CONTINUE;
}




//-----------------------------------------------------------------------------
// Name: EnumFFDevicesCallback()
// Desc: Called once for each enumerated force feedback device. If we find
//       one, create a device interface on it so we can play with it.
//-----------------------------------------------------------------------------
BOOL CALLBACK EnumFFDevicesCallback( const DIDEVICEINSTANCE* pInst,
                                     VOID* pContext )
{
    LPDIRECTINPUTDEVICE8 pDevice;
    HRESULT hr;

    // Obtain an interface to the enumerated force feedback device.
    hr = g_pDI->CreateDevice( pInst->guidInstance, &pDevice, NULL );

    // If it failed, then we can't use this device for some
    // bizarre reason.  (Maybe the user unplugged it while we
    // were in the middle of enumerating it.)  So continue enumerating
    if( FAILED( hr ) )
        return DIENUM_CONTINUE;

    // We successfully created an IDirectInputDevice8.  So stop looking 
    // for another one.
    g_pDevice = pDevice;

    return DIENUM_STOP;
}




//-----------------------------------------------------------------------------
// Name: FreeDirectInput()
// Desc: Initialize the DirectInput variables.
//-----------------------------------------------------------------------------
VOID FreeDirectInput()
{
    // Unacquire the device one last time just in case 
    // the app tried to exit while the device is still acquired.
    if( g_pDevice )
        g_pDevice->Unacquire();

    // Release any DirectInput objects.
    SAFE_RELEASE( g_pEffect );
    SAFE_RELEASE( g_pDevice );
    SAFE_RELEASE( g_pDI );
}




*/
void* DataFream(void* Param)
{
	while(true)
	{
	 pthread_mutex_lock( &mutex );
   rtri+=0.2f;						// Increase The Rotation Variable For The Triangle ( NEW )
	rquad-=0.15f;						// Decrease The Rotation Variable For The Quad     ( NEW )
	pthread_mutex_unlock( &mutex );
/*	if(ispad&&ispadEffect)
	{
		g_pDevice->Acquire();

                if( g_pEffect )
                    g_pEffect->Start( 1, 0 ); // Start the effect
	}*/
	pthread_delay_np( &delay );
	}
	
	return NULL;
}
void InitGL ( GLvoid )     // Create Some Everyday Functions
{

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glEnable ( GL_COLOR_MATERIAL );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void display ( void )   // Create The Display Function
{
	float turn1,turn2;

	pthread_mutex_lock( &mutex );
	turn1=rtri;
	turn2=rquad;
	pthread_mutex_unlock( &mutex );
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
   glLoadIdentity();									// Reset The Current Modelview Matrix
   glPushMatrix();
	glTranslatef(-1.5f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
   glRotatef(turn1,0.0f,1.0f,0.0f);				// Rotate The Triangle On The Y axis
   glEnable(GL_MULTISAMPLE_ARB);
	glBegin(GL_TRIANGLES);								// Drawing Using Triangles
		glColor3f(1.0f,0.0f,0.0f);			// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Front)
		glColor3f(0.0f,1.0f,0.0f);			// Green
		glVertex3f(-1.0f,-1.0f, 1.0f);			// Left Of Triangle (Front)
		glColor3f(0.0f,0.0f,1.0f);			// Blue
		glVertex3f( 1.0f,-1.0f, 1.0f);			// Right Of Triangle (Front)
		glColor3f(1.0f,0.0f,0.0f);			// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Right)
		glColor3f(0.0f,0.0f,1.0f);			// Blue
		glVertex3f( 1.0f,-1.0f, 1.0f);			// Left Of Triangle (Right)
		glColor3f(0.0f,1.0f,0.0f);			// Green
		glVertex3f( 1.0f,-1.0f, -1.0f);			// Right Of Triangle (Right)
      glColor3f(1.0f,0.0f,0.0f);			// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Back)
		glColor3f(0.0f,1.0f,0.0f);			// Green
		glVertex3f( 1.0f,-1.0f, -1.0f);			// Left Of Triangle (Back)
		glColor3f(0.0f,0.0f,1.0f);			// Blue
		glVertex3f(-1.0f,-1.0f, -1.0f);			// Right Of Triangle (Back)
		glColor3f(1.0f,0.0f,0.0f);			// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Left)
		glColor3f(0.0f,0.0f,1.0f);			// Blue
		glVertex3f(-1.0f,-1.0f,-1.0f);			// Left Of Triangle (Left)
		glColor3f(0.0f,1.0f,0.0f);			// Green
		glVertex3f(-1.0f,-1.0f, 1.0f);			// Right Of Triangle (Left)
    glEnd();											// Finished Drawing The Triangle
glDisable(GL_MULTISAMPLE_ARB);
	glLoadIdentity();					// Reset The Current Modelview Matrix
    glTranslatef(1.5f,0.0f,-6.0f);				// Move Right 1.5 Units And Into The Screen 6.0
	glRotatef(turn2,1.0f,0.0f,0.0f);			// Rotate The Quad On The X axis
	glColor3f(0.5f,0.5f,1.0f);							// Set The Color To Blue One Time Only
	glBegin(GL_QUADS);									// Draw A Quad
		glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Blue
		glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f, 1.0f);			// Bottom Left Of The Quad (Top)
		glVertex3f( 1.0f, 1.0f, 1.0f);			// Bottom Right Of The Quad (Top)
		glColor3f(1.0f,0.5f,0.0f);			// Set The Color To Orange
		glVertex3f( 1.0f,-1.0f, 1.0f);			// Top Right Of The Quad (Bottom)
		glVertex3f(-1.0f,-1.0f, 1.0f);			// Top Left Of The Quad (Bottom)
		glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Bottom)
		glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Bottom)
		glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
		glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Front)
		glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Front)
		glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Front)
		glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Front)
		glColor3f(1.0f,1.0f,0.0f);			// Set The Color To Yellow
		glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Back)
		glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Back)
		glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Back)
		glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Back)
		glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Blue
		glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Left)
		glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Left)
		glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Left)
		glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Left)
		glColor3f(1.0f,0.0f,1.0f);			// Set The Color To Violet
		glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Right)
		glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Right)
		glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Right)
		glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Right)
	glEnd();						// Done Drawing The Quad
  												// Done Drawing The Quad
  glPopMatrix();
  // rtri+=0.2f;						// Increase The Rotation Variable For The Triangle ( NEW )
	//rquad-=0.15f;						// Decrease The Rotation Variable For The Quad     ( NEW )


  glutSwapBuffers ( );
  // Swap The Buffers To Not Be Left With A Clear Screen
}

void reshape ( int width , int height )   // Create The Reshape Function (the viewport)
{
  if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
  switch ( key ) {
    case 27:        // When Escape Is Pressed...
      exit ( 0 );   // Exit The Program
      break;        // Ready For Next Case
    default:        // Now Wrap It Up
      break;
  }
}

void arrow_keys ( int a_keys, int x, int y )  // Create Special Function (required for arrow keys)
{
  switch ( a_keys ) {
    case GLUT_KEY_UP:     // When Up Arrow Is Pressed...
      glutFullScreen ( ); // Go Into Full Screen Mode
      break;
    case GLUT_KEY_DOWN:               // When Down Arrow Is Pressed...
		glutFullScreen();
		glutPositionWindow((GetSystemMetrics(SM_CXFULLSCREEN)-winW)/2,(GetSystemMetrics(SM_CYFULLSCREEN)-winH)/2);
      glutReshapeWindow ( winW, winH ); // Go Into A 500 By 500 Window
	  
      break;
    default:
      break;
  }
}


//void main ( int argc, char** argv )   // Create Main Function For Bringing It All Together
/*
BOOL CALLBACK EnumDevices(LPCDIDEVICEINSTANCE pdInst, LPVOID pvRef)
{
    int Result;
 // Display a message box with name of device found
    Result = MessageBox(HWND_DESKTOP, pdInst->tszInstanceName,
            pdInst->tszProductName, MB_OKCANCEL);
	
    // Tell it to continue enumeration if OK pressed
    if(Result == IDOK)
        return DIENUM_CONTINUE;
    // Stop enumeration
    return DIENUM_STOP;
}
*/
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
/*	 HRESULT hr;
	 hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, \
              IID_IDirectInput8, (void**)&g_pDI, NULL);
	if(FAILED(hr))
	{
		MessageBox (HWND_DESKTOP, "Error DirectInput", "Error", MB_OK | MB_ICONEXCLAMATION);
	}
	else
	{
		g_pDI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumDevices,(LPVOID)hInstance, DIEDFL_ALLDEVICES);
	}
*/

	char path[_MAX_PATH];
    GetModuleFileName(hInstance, path, _MAX_PATH);
	char* argv=(char *)path;

	glutInit            ( &nCmdShow, &argv ); // Erm Just Write It =)
//	glutInitDisplayMode ( GLUT_RGBA | GLUT_DOUBLE|GLUT_DEPTH|GLUT_MULTISAMPLE ); // Display Mode
	glutInitDisplayString("rgba double depth>=24 samples alpha");
	glutSetOption(GLUT_MULTISAMPLE,2);
	glutInitWindowPosition((GetSystemMetrics(SM_CXFULLSCREEN)-winW)/2,(GetSystemMetrics(SM_CYFULLSCREEN)-winH)/2);
	glutInitWindowSize  ( winW, winH ); // If glutFullScreen wasn't called this is the window size
	glutCreateWindow    ( "TOP_ACE" ); // Window Title (argv[0] for current directory as title)
//	glutFullScreen      ( );          // Put Into Full Screen
	InitGL ();
	HWND hDlg;
	hDlg=*(HWND *) glutGetWindowData();
/*	if( FAILED( InitDirectInput( hDlg ) ) )
	{
		MessageBox (HWND_DESKTOP, "Error DirectInput", "Error", MB_OK | MB_ICONEXCLAMATION);
		ispad=false;
	}
	if(ispad&&ispadEffect)
	SetDeviceForcesXY();

*/
	delay.tv_nsec=10000000;
	delay.tv_sec=0;
//     pthread_t pid;
     pthread_attr_t attr;
     pthread_attr_init(&attr);
     pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
     pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_t reader;
	pthread_mutex_init(&mutex, NULL);
    pthread_create( &reader, &attr, DataFream,
                    NULL);
	glutDisplayFunc     ( display );  // Matching Earlier Functions To Their Counterparts
	glutReshapeFunc     ( reshape );
	glutKeyboardFunc    ( keyboard );
	glutSpecialFunc     ( arrow_keys );
	glutIdleFunc		  ( display );
	glutMainLoop        ( );          // Initialize The Main Loop
	//FreeDirectInput();
	return 0;
}
/*
//-----------------------------------------------------------------------------
// Name: SetDeviceForcesXY()
// Desc: Apply the X and Y forces to the effect we prepared.
//-----------------------------------------------------------------------------
HRESULT SetDeviceForcesXY()
{
    // Modifying an effect is basically the same as creating a new one, except
    // you need only specify the parameters you are modifying
    LONG rglDirection[2] = { 0, 0 };

    DICONSTANTFORCE cf;

    if( g_dwNumForceFeedbackAxis == 1 )
    {
        // If only one force feedback axis, then apply only one direction and 
        // keep the direction at zero
        cf.lMagnitude = g_nXForce;
        rglDirection[0] = 0;
    }
    else
    {
        // If two force feedback axis, then apply magnitude from both directions 
        rglDirection[0] = g_nXForce;
        rglDirection[1] = g_nYForce;
        cf.lMagnitude = ( DWORD )sqrt( ( double )g_nXForce * ( double )g_nXForce +
                                       ( double )g_nYForce * ( double )g_nYForce );
    }

    DIEFFECT eff;
    ZeroMemory( &eff, sizeof( eff ) );
    eff.dwSize = sizeof( DIEFFECT );
    eff.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
    eff.cAxes = g_dwNumForceFeedbackAxis;
    eff.rglDirection = rglDirection;
    eff.lpEnvelope = 0;
    eff.cbTypeSpecificParams = sizeof( DICONSTANTFORCE );
    eff.lpvTypeSpecificParams = &cf;
    eff.dwStartDelay = 0;

    // Now set the new parameters and start the effect immediately.
    return g_pEffect->SetParameters( &eff, DIEP_DIRECTION |
                                     DIEP_TYPESPECIFICPARAMS |
                                     DIEP_START );
}


*/
