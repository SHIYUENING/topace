#ifndef HGL_XRAM_INCLUDE
#define HGL_XRAM_INCLUDE

#include<hgl/al/al.h>
namespace openal
{
	// XRAM Extension function pointer variables and enum values

	typedef ALboolean (__cdecl *LPEAXSETBUFFERMODE)(ALsizei n, ALuint *buffers, ALint value);
	typedef ALenum    (__cdecl *LPEAXGETBUFFERMODE)(ALuint buffer, ALint *value);

	extern LPEAXSETBUFFERMODE eaxSetBufferMode;
	extern LPEAXGETBUFFERMODE eaxGetBufferMode;

	// X-RAM Enum values
	extern ALenum eXRAMSize, eXRAMFree;
	extern ALenum eXRAMAuto, eXRAMHardware, eXRAMAccessible;
}
#endif//