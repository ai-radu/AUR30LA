# 0 "/home/ai/AUR30LA/src/aur/view/VAO.cpp"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "/home/ai/AUR30LA/src/aur/view/VAO.cpp"
# 1 "/home/ai/AUR30LA/src/aur/view/VAO.h" 1
       
# 1 "/home/ai/AUR30LA/includes/glad/glad.h" 1
# 47 "/home/ai/AUR30LA/includes/glad/glad.h"
extern "C" {


struct gladGLversionStruct {
    int major;
    int minor;
};

typedef void* (* GLADloadproc)(const char *name);
# 83 "/home/ai/AUR30LA/includes/glad/glad.h"
extern struct gladGLversionStruct GLVersion;

extern int gladLoadGL(void);

extern int gladLoadGLLoader(GLADloadproc);

# 1 "/usr/include/KHR/khrplatform.h" 1 3 4
# 149 "/usr/include/KHR/khrplatform.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/15/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/x86_64-linux-gnu/15/include/stdint.h" 3 4
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
# 1 "/usr/include/stdint.h" 1 3 4
# 26 "/usr/include/stdint.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 33 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 431 "/usr/include/features.h" 3 4
# 1 "/usr/include/features-time64.h" 1 3 4
# 20 "/usr/include/features-time64.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 21 "/usr/include/features-time64.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 1 3 4
# 19 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 20 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 2 3 4
# 22 "/usr/include/features-time64.h" 2 3 4
# 432 "/usr/include/features.h" 2 3 4
# 539 "/usr/include/features.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 1 3 4
# 730 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 731 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/long-double.h" 1 3 4
# 732 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 2 3 4
# 540 "/usr/include/features.h" 2 3 4
# 563 "/usr/include/features.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 1 3 4
# 10 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/gnu/stubs-64.h" 1 3 4
# 11 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 2 3 4
# 564 "/usr/include/features.h" 2 3 4
# 34 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 2 3 4
# 27 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types.h" 1 3 4
# 27 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 28 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 1 3 4
# 19 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 20 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 2 3 4
# 29 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;






typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;



typedef long int __quad_t;
typedef unsigned long int __u_quad_t;







typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;
# 141 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/typesizes.h" 1 3 4
# 142 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/time64.h" 1 3 4
# 143 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef long int __suseconds64_t;

typedef int __daddr_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;


typedef long int __fsword_t;

typedef long int __ssize_t;


typedef long int __syscall_slong_t;

typedef unsigned long int __syscall_ulong_t;



typedef __off64_t __loff_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;




typedef int __sig_atomic_t;
# 28 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wchar.h" 1 3 4
# 29 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 30 "/usr/include/stdint.h" 2 3 4
# 38 "/usr/include/stdint.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/stdint-intn.h" 1 3 4
# 24 "/usr/include/x86_64-linux-gnu/bits/stdint-intn.h" 3 4
typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
# 39 "/usr/include/stdint.h" 2 3 4


# 1 "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h" 1 3 4
# 24 "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h" 3 4
typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;
# 42 "/usr/include/stdint.h" 2 3 4



# 1 "/usr/include/x86_64-linux-gnu/bits/stdint-least.h" 1 3 4
# 25 "/usr/include/x86_64-linux-gnu/bits/stdint-least.h" 3 4
typedef __int_least8_t int_least8_t;
typedef __int_least16_t int_least16_t;
typedef __int_least32_t int_least32_t;
typedef __int_least64_t int_least64_t;


typedef __uint_least8_t uint_least8_t;
typedef __uint_least16_t uint_least16_t;
typedef __uint_least32_t uint_least32_t;
typedef __uint_least64_t uint_least64_t;
# 46 "/usr/include/stdint.h" 2 3 4





typedef signed char int_fast8_t;

typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
# 64 "/usr/include/stdint.h" 3 4
typedef unsigned char uint_fast8_t;

typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
# 80 "/usr/include/stdint.h" 3 4
typedef long int intptr_t;


typedef unsigned long int uintptr_t;
# 94 "/usr/include/stdint.h" 3 4
typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;
# 12 "/usr/lib/gcc/x86_64-linux-gnu/15/include/stdint.h" 2 3 4
#pragma GCC diagnostic pop
# 150 "/usr/include/KHR/khrplatform.h" 2 3 4
typedef int32_t khronos_int32_t;
typedef uint32_t khronos_uint32_t;
typedef int64_t khronos_int64_t;
typedef uint64_t khronos_uint64_t;
# 242 "/usr/include/KHR/khrplatform.h" 3 4
typedef signed char khronos_int8_t;
typedef unsigned char khronos_uint8_t;
typedef signed short int khronos_int16_t;
typedef unsigned short int khronos_uint16_t;
# 259 "/usr/include/KHR/khrplatform.h" 3 4
typedef signed long int khronos_intptr_t;
typedef unsigned long int khronos_uintptr_t;






typedef signed long int khronos_ssize_t;
typedef unsigned long int khronos_usize_t;






typedef float khronos_float_t;
# 288 "/usr/include/KHR/khrplatform.h" 3 4
typedef khronos_uint64_t khronos_utime_nanoseconds_t;
typedef khronos_int64_t khronos_stime_nanoseconds_t;
# 305 "/usr/include/KHR/khrplatform.h" 3 4
typedef enum {
    KHRONOS_FALSE = 0,
    KHRONOS_TRUE = 1,
    KHRONOS_BOOLEAN_ENUM_FORCE_SIZE = 0x7FFFFFFF
} khronos_boolean_enum_t;
# 90 "/home/ai/AUR30LA/includes/glad/glad.h" 2

# 90 "/home/ai/AUR30LA/includes/glad/glad.h"
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
typedef khronos_int8_t GLbyte;
typedef khronos_uint8_t GLubyte;
typedef khronos_int16_t GLshort;
typedef khronos_uint16_t GLushort;
typedef int GLint;
typedef unsigned int GLuint;
typedef khronos_int32_t GLclampx;
typedef int GLsizei;
typedef khronos_float_t GLfloat;
typedef khronos_float_t GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void *GLeglClientBufferEXT;
typedef void *GLeglImageOES;
typedef char GLchar;
typedef char GLcharARB;



typedef unsigned int GLhandleARB;

typedef khronos_uint16_t GLhalf;
typedef khronos_uint16_t GLhalfARB;
typedef khronos_int32_t GLfixed;
typedef khronos_intptr_t GLintptr;
typedef khronos_intptr_t GLintptrARB;
typedef khronos_ssize_t GLsizeiptr;
typedef khronos_ssize_t GLsizeiptrARB;
typedef khronos_int64_t GLint64;
typedef khronos_int64_t GLint64EXT;
typedef khronos_uint64_t GLuint64;
typedef khronos_uint64_t GLuint64EXT;
typedef struct __GLsync *GLsync;
struct _cl_context;
struct _cl_event;
typedef void ( *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void ( *GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void ( *GLDEBUGPROCKHR)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void ( *GLDEBUGPROCAMD)(GLuint id,GLenum category,GLenum severity,GLsizei length,const GLchar *message,void *userParam);
typedef unsigned short GLhalfNV;
typedef GLintptr GLvdpauSurfaceNV;
typedef void ( *GLVULKANPROCNV)(void);
# 1946 "/home/ai/AUR30LA/includes/glad/glad.h"
extern int GLAD_GL_VERSION_1_0;
typedef void ( * PFNGLCULLFACEPROC)(GLenum mode);
extern PFNGLCULLFACEPROC glad_glCullFace;

typedef void ( * PFNGLFRONTFACEPROC)(GLenum mode);
extern PFNGLFRONTFACEPROC glad_glFrontFace;

typedef void ( * PFNGLHINTPROC)(GLenum target, GLenum mode);
extern PFNGLHINTPROC glad_glHint;

typedef void ( * PFNGLLINEWIDTHPROC)(GLfloat width);
extern PFNGLLINEWIDTHPROC glad_glLineWidth;

typedef void ( * PFNGLPOINTSIZEPROC)(GLfloat size);
extern PFNGLPOINTSIZEPROC glad_glPointSize;

typedef void ( * PFNGLPOLYGONMODEPROC)(GLenum face, GLenum mode);
extern PFNGLPOLYGONMODEPROC glad_glPolygonMode;

typedef void ( * PFNGLSCISSORPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
extern PFNGLSCISSORPROC glad_glScissor;

typedef void ( * PFNGLTEXPARAMETERFPROC)(GLenum target, GLenum pname, GLfloat param);
extern PFNGLTEXPARAMETERFPROC glad_glTexParameterf;

typedef void ( * PFNGLTEXPARAMETERFVPROC)(GLenum target, GLenum pname, const GLfloat *params);
extern PFNGLTEXPARAMETERFVPROC glad_glTexParameterfv;

typedef void ( * PFNGLTEXPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
extern PFNGLTEXPARAMETERIPROC glad_glTexParameteri;

typedef void ( * PFNGLTEXPARAMETERIVPROC)(GLenum target, GLenum pname, const GLint *params);
extern PFNGLTEXPARAMETERIVPROC glad_glTexParameteriv;

typedef void ( * PFNGLTEXIMAGE1DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels);
extern PFNGLTEXIMAGE1DPROC glad_glTexImage1D;

typedef void ( * PFNGLTEXIMAGE2DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
extern PFNGLTEXIMAGE2DPROC glad_glTexImage2D;

typedef void ( * PFNGLDRAWBUFFERPROC)(GLenum buf);
extern PFNGLDRAWBUFFERPROC glad_glDrawBuffer;

typedef void ( * PFNGLCLEARPROC)(GLbitfield mask);
extern PFNGLCLEARPROC glad_glClear;

typedef void ( * PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern PFNGLCLEARCOLORPROC glad_glClearColor;

typedef void ( * PFNGLCLEARSTENCILPROC)(GLint s);
extern PFNGLCLEARSTENCILPROC glad_glClearStencil;

typedef void ( * PFNGLCLEARDEPTHPROC)(GLdouble depth);
extern PFNGLCLEARDEPTHPROC glad_glClearDepth;

typedef void ( * PFNGLSTENCILMASKPROC)(GLuint mask);
extern PFNGLSTENCILMASKPROC glad_glStencilMask;

typedef void ( * PFNGLCOLORMASKPROC)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
extern PFNGLCOLORMASKPROC glad_glColorMask;

typedef void ( * PFNGLDEPTHMASKPROC)(GLboolean flag);
extern PFNGLDEPTHMASKPROC glad_glDepthMask;

typedef void ( * PFNGLDISABLEPROC)(GLenum cap);
extern PFNGLDISABLEPROC glad_glDisable;

typedef void ( * PFNGLENABLEPROC)(GLenum cap);
extern PFNGLENABLEPROC glad_glEnable;

typedef void ( * PFNGLFINISHPROC)(void);
extern PFNGLFINISHPROC glad_glFinish;

typedef void ( * PFNGLFLUSHPROC)(void);
extern PFNGLFLUSHPROC glad_glFlush;

typedef void ( * PFNGLBLENDFUNCPROC)(GLenum sfactor, GLenum dfactor);
extern PFNGLBLENDFUNCPROC glad_glBlendFunc;

typedef void ( * PFNGLLOGICOPPROC)(GLenum opcode);
extern PFNGLLOGICOPPROC glad_glLogicOp;

typedef void ( * PFNGLSTENCILFUNCPROC)(GLenum func, GLint ref, GLuint mask);
extern PFNGLSTENCILFUNCPROC glad_glStencilFunc;

typedef void ( * PFNGLSTENCILOPPROC)(GLenum fail, GLenum zfail, GLenum zpass);
extern PFNGLSTENCILOPPROC glad_glStencilOp;

typedef void ( * PFNGLDEPTHFUNCPROC)(GLenum func);
extern PFNGLDEPTHFUNCPROC glad_glDepthFunc;

typedef void ( * PFNGLPIXELSTOREFPROC)(GLenum pname, GLfloat param);
extern PFNGLPIXELSTOREFPROC glad_glPixelStoref;

typedef void ( * PFNGLPIXELSTOREIPROC)(GLenum pname, GLint param);
extern PFNGLPIXELSTOREIPROC glad_glPixelStorei;

typedef void ( * PFNGLREADBUFFERPROC)(GLenum src);
extern PFNGLREADBUFFERPROC glad_glReadBuffer;

typedef void ( * PFNGLREADPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels);
extern PFNGLREADPIXELSPROC glad_glReadPixels;

typedef void ( * PFNGLGETBOOLEANVPROC)(GLenum pname, GLboolean *data);
extern PFNGLGETBOOLEANVPROC glad_glGetBooleanv;

typedef void ( * PFNGLGETDOUBLEVPROC)(GLenum pname, GLdouble *data);
extern PFNGLGETDOUBLEVPROC glad_glGetDoublev;

typedef GLenum ( * PFNGLGETERRORPROC)(void);
extern PFNGLGETERRORPROC glad_glGetError;

typedef void ( * PFNGLGETFLOATVPROC)(GLenum pname, GLfloat *data);
extern PFNGLGETFLOATVPROC glad_glGetFloatv;

typedef void ( * PFNGLGETINTEGERVPROC)(GLenum pname, GLint *data);
extern PFNGLGETINTEGERVPROC glad_glGetIntegerv;

typedef const GLubyte * ( * PFNGLGETSTRINGPROC)(GLenum name);
extern PFNGLGETSTRINGPROC glad_glGetString;

typedef void ( * PFNGLGETTEXIMAGEPROC)(GLenum target, GLint level, GLenum format, GLenum type, void *pixels);
extern PFNGLGETTEXIMAGEPROC glad_glGetTexImage;

typedef void ( * PFNGLGETTEXPARAMETERFVPROC)(GLenum target, GLenum pname, GLfloat *params);
extern PFNGLGETTEXPARAMETERFVPROC glad_glGetTexParameterfv;

typedef void ( * PFNGLGETTEXPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
extern PFNGLGETTEXPARAMETERIVPROC glad_glGetTexParameteriv;

typedef void ( * PFNGLGETTEXLEVELPARAMETERFVPROC)(GLenum target, GLint level, GLenum pname, GLfloat *params);
extern PFNGLGETTEXLEVELPARAMETERFVPROC glad_glGetTexLevelParameterfv;

typedef void ( * PFNGLGETTEXLEVELPARAMETERIVPROC)(GLenum target, GLint level, GLenum pname, GLint *params);
extern PFNGLGETTEXLEVELPARAMETERIVPROC glad_glGetTexLevelParameteriv;

typedef GLboolean ( * PFNGLISENABLEDPROC)(GLenum cap);
extern PFNGLISENABLEDPROC glad_glIsEnabled;

typedef void ( * PFNGLDEPTHRANGEPROC)(GLdouble n, GLdouble f);
extern PFNGLDEPTHRANGEPROC glad_glDepthRange;

typedef void ( * PFNGLVIEWPORTPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
extern PFNGLVIEWPORTPROC glad_glViewport;

typedef void ( * PFNGLNEWLISTPROC)(GLuint list, GLenum mode);
extern PFNGLNEWLISTPROC glad_glNewList;

typedef void ( * PFNGLENDLISTPROC)(void);
extern PFNGLENDLISTPROC glad_glEndList;

typedef void ( * PFNGLCALLLISTPROC)(GLuint list);
extern PFNGLCALLLISTPROC glad_glCallList;

typedef void ( * PFNGLCALLLISTSPROC)(GLsizei n, GLenum type, const void *lists);
extern PFNGLCALLLISTSPROC glad_glCallLists;

typedef void ( * PFNGLDELETELISTSPROC)(GLuint list, GLsizei range);
extern PFNGLDELETELISTSPROC glad_glDeleteLists;

typedef GLuint ( * PFNGLGENLISTSPROC)(GLsizei range);
extern PFNGLGENLISTSPROC glad_glGenLists;

typedef void ( * PFNGLLISTBASEPROC)(GLuint base);
extern PFNGLLISTBASEPROC glad_glListBase;

typedef void ( * PFNGLBEGINPROC)(GLenum mode);
extern PFNGLBEGINPROC glad_glBegin;

typedef void ( * PFNGLBITMAPPROC)(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap);
extern PFNGLBITMAPPROC glad_glBitmap;

typedef void ( * PFNGLCOLOR3BPROC)(GLbyte red, GLbyte green, GLbyte blue);
extern PFNGLCOLOR3BPROC glad_glColor3b;

typedef void ( * PFNGLCOLOR3BVPROC)(const GLbyte *v);
extern PFNGLCOLOR3BVPROC glad_glColor3bv;

typedef void ( * PFNGLCOLOR3DPROC)(GLdouble red, GLdouble green, GLdouble blue);
extern PFNGLCOLOR3DPROC glad_glColor3d;

typedef void ( * PFNGLCOLOR3DVPROC)(const GLdouble *v);
extern PFNGLCOLOR3DVPROC glad_glColor3dv;

typedef void ( * PFNGLCOLOR3FPROC)(GLfloat red, GLfloat green, GLfloat blue);
extern PFNGLCOLOR3FPROC glad_glColor3f;

typedef void ( * PFNGLCOLOR3FVPROC)(const GLfloat *v);
extern PFNGLCOLOR3FVPROC glad_glColor3fv;

typedef void ( * PFNGLCOLOR3IPROC)(GLint red, GLint green, GLint blue);
extern PFNGLCOLOR3IPROC glad_glColor3i;

typedef void ( * PFNGLCOLOR3IVPROC)(const GLint *v);
extern PFNGLCOLOR3IVPROC glad_glColor3iv;

typedef void ( * PFNGLCOLOR3SPROC)(GLshort red, GLshort green, GLshort blue);
extern PFNGLCOLOR3SPROC glad_glColor3s;

typedef void ( * PFNGLCOLOR3SVPROC)(const GLshort *v);
extern PFNGLCOLOR3SVPROC glad_glColor3sv;

typedef void ( * PFNGLCOLOR3UBPROC)(GLubyte red, GLubyte green, GLubyte blue);
extern PFNGLCOLOR3UBPROC glad_glColor3ub;

typedef void ( * PFNGLCOLOR3UBVPROC)(const GLubyte *v);
extern PFNGLCOLOR3UBVPROC glad_glColor3ubv;

typedef void ( * PFNGLCOLOR3UIPROC)(GLuint red, GLuint green, GLuint blue);
extern PFNGLCOLOR3UIPROC glad_glColor3ui;

typedef void ( * PFNGLCOLOR3UIVPROC)(const GLuint *v);
extern PFNGLCOLOR3UIVPROC glad_glColor3uiv;

typedef void ( * PFNGLCOLOR3USPROC)(GLushort red, GLushort green, GLushort blue);
extern PFNGLCOLOR3USPROC glad_glColor3us;

typedef void ( * PFNGLCOLOR3USVPROC)(const GLushort *v);
extern PFNGLCOLOR3USVPROC glad_glColor3usv;

typedef void ( * PFNGLCOLOR4BPROC)(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
extern PFNGLCOLOR4BPROC glad_glColor4b;

typedef void ( * PFNGLCOLOR4BVPROC)(const GLbyte *v);
extern PFNGLCOLOR4BVPROC glad_glColor4bv;

typedef void ( * PFNGLCOLOR4DPROC)(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
extern PFNGLCOLOR4DPROC glad_glColor4d;

typedef void ( * PFNGLCOLOR4DVPROC)(const GLdouble *v);
extern PFNGLCOLOR4DVPROC glad_glColor4dv;

typedef void ( * PFNGLCOLOR4FPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern PFNGLCOLOR4FPROC glad_glColor4f;

typedef void ( * PFNGLCOLOR4FVPROC)(const GLfloat *v);
extern PFNGLCOLOR4FVPROC glad_glColor4fv;

typedef void ( * PFNGLCOLOR4IPROC)(GLint red, GLint green, GLint blue, GLint alpha);
extern PFNGLCOLOR4IPROC glad_glColor4i;

typedef void ( * PFNGLCOLOR4IVPROC)(const GLint *v);
extern PFNGLCOLOR4IVPROC glad_glColor4iv;

typedef void ( * PFNGLCOLOR4SPROC)(GLshort red, GLshort green, GLshort blue, GLshort alpha);
extern PFNGLCOLOR4SPROC glad_glColor4s;

typedef void ( * PFNGLCOLOR4SVPROC)(const GLshort *v);
extern PFNGLCOLOR4SVPROC glad_glColor4sv;

typedef void ( * PFNGLCOLOR4UBPROC)(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
extern PFNGLCOLOR4UBPROC glad_glColor4ub;

typedef void ( * PFNGLCOLOR4UBVPROC)(const GLubyte *v);
extern PFNGLCOLOR4UBVPROC glad_glColor4ubv;

typedef void ( * PFNGLCOLOR4UIPROC)(GLuint red, GLuint green, GLuint blue, GLuint alpha);
extern PFNGLCOLOR4UIPROC glad_glColor4ui;

typedef void ( * PFNGLCOLOR4UIVPROC)(const GLuint *v);
extern PFNGLCOLOR4UIVPROC glad_glColor4uiv;

typedef void ( * PFNGLCOLOR4USPROC)(GLushort red, GLushort green, GLushort blue, GLushort alpha);
extern PFNGLCOLOR4USPROC glad_glColor4us;

typedef void ( * PFNGLCOLOR4USVPROC)(const GLushort *v);
extern PFNGLCOLOR4USVPROC glad_glColor4usv;

typedef void ( * PFNGLEDGEFLAGPROC)(GLboolean flag);
extern PFNGLEDGEFLAGPROC glad_glEdgeFlag;

typedef void ( * PFNGLEDGEFLAGVPROC)(const GLboolean *flag);
extern PFNGLEDGEFLAGVPROC glad_glEdgeFlagv;

typedef void ( * PFNGLENDPROC)(void);
extern PFNGLENDPROC glad_glEnd;

typedef void ( * PFNGLINDEXDPROC)(GLdouble c);
extern PFNGLINDEXDPROC glad_glIndexd;

typedef void ( * PFNGLINDEXDVPROC)(const GLdouble *c);
extern PFNGLINDEXDVPROC glad_glIndexdv;

typedef void ( * PFNGLINDEXFPROC)(GLfloat c);
extern PFNGLINDEXFPROC glad_glIndexf;

typedef void ( * PFNGLINDEXFVPROC)(const GLfloat *c);
extern PFNGLINDEXFVPROC glad_glIndexfv;

typedef void ( * PFNGLINDEXIPROC)(GLint c);
extern PFNGLINDEXIPROC glad_glIndexi;

typedef void ( * PFNGLINDEXIVPROC)(const GLint *c);
extern PFNGLINDEXIVPROC glad_glIndexiv;

typedef void ( * PFNGLINDEXSPROC)(GLshort c);
extern PFNGLINDEXSPROC glad_glIndexs;

typedef void ( * PFNGLINDEXSVPROC)(const GLshort *c);
extern PFNGLINDEXSVPROC glad_glIndexsv;

typedef void ( * PFNGLNORMAL3BPROC)(GLbyte nx, GLbyte ny, GLbyte nz);
extern PFNGLNORMAL3BPROC glad_glNormal3b;

typedef void ( * PFNGLNORMAL3BVPROC)(const GLbyte *v);
extern PFNGLNORMAL3BVPROC glad_glNormal3bv;

typedef void ( * PFNGLNORMAL3DPROC)(GLdouble nx, GLdouble ny, GLdouble nz);
extern PFNGLNORMAL3DPROC glad_glNormal3d;

typedef void ( * PFNGLNORMAL3DVPROC)(const GLdouble *v);
extern PFNGLNORMAL3DVPROC glad_glNormal3dv;

typedef void ( * PFNGLNORMAL3FPROC)(GLfloat nx, GLfloat ny, GLfloat nz);
extern PFNGLNORMAL3FPROC glad_glNormal3f;

typedef void ( * PFNGLNORMAL3FVPROC)(const GLfloat *v);
extern PFNGLNORMAL3FVPROC glad_glNormal3fv;

typedef void ( * PFNGLNORMAL3IPROC)(GLint nx, GLint ny, GLint nz);
extern PFNGLNORMAL3IPROC glad_glNormal3i;

typedef void ( * PFNGLNORMAL3IVPROC)(const GLint *v);
extern PFNGLNORMAL3IVPROC glad_glNormal3iv;

typedef void ( * PFNGLNORMAL3SPROC)(GLshort nx, GLshort ny, GLshort nz);
extern PFNGLNORMAL3SPROC glad_glNormal3s;

typedef void ( * PFNGLNORMAL3SVPROC)(const GLshort *v);
extern PFNGLNORMAL3SVPROC glad_glNormal3sv;

typedef void ( * PFNGLRASTERPOS2DPROC)(GLdouble x, GLdouble y);
extern PFNGLRASTERPOS2DPROC glad_glRasterPos2d;

typedef void ( * PFNGLRASTERPOS2DVPROC)(const GLdouble *v);
extern PFNGLRASTERPOS2DVPROC glad_glRasterPos2dv;

typedef void ( * PFNGLRASTERPOS2FPROC)(GLfloat x, GLfloat y);
extern PFNGLRASTERPOS2FPROC glad_glRasterPos2f;

typedef void ( * PFNGLRASTERPOS2FVPROC)(const GLfloat *v);
extern PFNGLRASTERPOS2FVPROC glad_glRasterPos2fv;

typedef void ( * PFNGLRASTERPOS2IPROC)(GLint x, GLint y);
extern PFNGLRASTERPOS2IPROC glad_glRasterPos2i;

typedef void ( * PFNGLRASTERPOS2IVPROC)(const GLint *v);
extern PFNGLRASTERPOS2IVPROC glad_glRasterPos2iv;

typedef void ( * PFNGLRASTERPOS2SPROC)(GLshort x, GLshort y);
extern PFNGLRASTERPOS2SPROC glad_glRasterPos2s;

typedef void ( * PFNGLRASTERPOS2SVPROC)(const GLshort *v);
extern PFNGLRASTERPOS2SVPROC glad_glRasterPos2sv;

typedef void ( * PFNGLRASTERPOS3DPROC)(GLdouble x, GLdouble y, GLdouble z);
extern PFNGLRASTERPOS3DPROC glad_glRasterPos3d;

typedef void ( * PFNGLRASTERPOS3DVPROC)(const GLdouble *v);
extern PFNGLRASTERPOS3DVPROC glad_glRasterPos3dv;

typedef void ( * PFNGLRASTERPOS3FPROC)(GLfloat x, GLfloat y, GLfloat z);
extern PFNGLRASTERPOS3FPROC glad_glRasterPos3f;

typedef void ( * PFNGLRASTERPOS3FVPROC)(const GLfloat *v);
extern PFNGLRASTERPOS3FVPROC glad_glRasterPos3fv;

typedef void ( * PFNGLRASTERPOS3IPROC)(GLint x, GLint y, GLint z);
extern PFNGLRASTERPOS3IPROC glad_glRasterPos3i;

typedef void ( * PFNGLRASTERPOS3IVPROC)(const GLint *v);
extern PFNGLRASTERPOS3IVPROC glad_glRasterPos3iv;

typedef void ( * PFNGLRASTERPOS3SPROC)(GLshort x, GLshort y, GLshort z);
extern PFNGLRASTERPOS3SPROC glad_glRasterPos3s;

typedef void ( * PFNGLRASTERPOS3SVPROC)(const GLshort *v);
extern PFNGLRASTERPOS3SVPROC glad_glRasterPos3sv;

typedef void ( * PFNGLRASTERPOS4DPROC)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
extern PFNGLRASTERPOS4DPROC glad_glRasterPos4d;

typedef void ( * PFNGLRASTERPOS4DVPROC)(const GLdouble *v);
extern PFNGLRASTERPOS4DVPROC glad_glRasterPos4dv;

typedef void ( * PFNGLRASTERPOS4FPROC)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
extern PFNGLRASTERPOS4FPROC glad_glRasterPos4f;

typedef void ( * PFNGLRASTERPOS4FVPROC)(const GLfloat *v);
extern PFNGLRASTERPOS4FVPROC glad_glRasterPos4fv;

typedef void ( * PFNGLRASTERPOS4IPROC)(GLint x, GLint y, GLint z, GLint w);
extern PFNGLRASTERPOS4IPROC glad_glRasterPos4i;

typedef void ( * PFNGLRASTERPOS4IVPROC)(const GLint *v);
extern PFNGLRASTERPOS4IVPROC glad_glRasterPos4iv;

typedef void ( * PFNGLRASTERPOS4SPROC)(GLshort x, GLshort y, GLshort z, GLshort w);
extern PFNGLRASTERPOS4SPROC glad_glRasterPos4s;

typedef void ( * PFNGLRASTERPOS4SVPROC)(const GLshort *v);
extern PFNGLRASTERPOS4SVPROC glad_glRasterPos4sv;

typedef void ( * PFNGLRECTDPROC)(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
extern PFNGLRECTDPROC glad_glRectd;

typedef void ( * PFNGLRECTDVPROC)(const GLdouble *v1, const GLdouble *v2);
extern PFNGLRECTDVPROC glad_glRectdv;

typedef void ( * PFNGLRECTFPROC)(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
extern PFNGLRECTFPROC glad_glRectf;

typedef void ( * PFNGLRECTFVPROC)(const GLfloat *v1, const GLfloat *v2);
extern PFNGLRECTFVPROC glad_glRectfv;

typedef void ( * PFNGLRECTIPROC)(GLint x1, GLint y1, GLint x2, GLint y2);
extern PFNGLRECTIPROC glad_glRecti;

typedef void ( * PFNGLRECTIVPROC)(const GLint *v1, const GLint *v2);
extern PFNGLRECTIVPROC glad_glRectiv;

typedef void ( * PFNGLRECTSPROC)(GLshort x1, GLshort y1, GLshort x2, GLshort y2);
extern PFNGLRECTSPROC glad_glRects;

typedef void ( * PFNGLRECTSVPROC)(const GLshort *v1, const GLshort *v2);
extern PFNGLRECTSVPROC glad_glRectsv;

typedef void ( * PFNGLTEXCOORD1DPROC)(GLdouble s);
extern PFNGLTEXCOORD1DPROC glad_glTexCoord1d;

typedef void ( * PFNGLTEXCOORD1DVPROC)(const GLdouble *v);
extern PFNGLTEXCOORD1DVPROC glad_glTexCoord1dv;

typedef void ( * PFNGLTEXCOORD1FPROC)(GLfloat s);
extern PFNGLTEXCOORD1FPROC glad_glTexCoord1f;

typedef void ( * PFNGLTEXCOORD1FVPROC)(const GLfloat *v);
extern PFNGLTEXCOORD1FVPROC glad_glTexCoord1fv;

typedef void ( * PFNGLTEXCOORD1IPROC)(GLint s);
extern PFNGLTEXCOORD1IPROC glad_glTexCoord1i;

typedef void ( * PFNGLTEXCOORD1IVPROC)(const GLint *v);
extern PFNGLTEXCOORD1IVPROC glad_glTexCoord1iv;

typedef void ( * PFNGLTEXCOORD1SPROC)(GLshort s);
extern PFNGLTEXCOORD1SPROC glad_glTexCoord1s;

typedef void ( * PFNGLTEXCOORD1SVPROC)(const GLshort *v);
extern PFNGLTEXCOORD1SVPROC glad_glTexCoord1sv;

typedef void ( * PFNGLTEXCOORD2DPROC)(GLdouble s, GLdouble t);
extern PFNGLTEXCOORD2DPROC glad_glTexCoord2d;

typedef void ( * PFNGLTEXCOORD2DVPROC)(const GLdouble *v);
extern PFNGLTEXCOORD2DVPROC glad_glTexCoord2dv;

typedef void ( * PFNGLTEXCOORD2FPROC)(GLfloat s, GLfloat t);
extern PFNGLTEXCOORD2FPROC glad_glTexCoord2f;

typedef void ( * PFNGLTEXCOORD2FVPROC)(const GLfloat *v);
extern PFNGLTEXCOORD2FVPROC glad_glTexCoord2fv;

typedef void ( * PFNGLTEXCOORD2IPROC)(GLint s, GLint t);
extern PFNGLTEXCOORD2IPROC glad_glTexCoord2i;

typedef void ( * PFNGLTEXCOORD2IVPROC)(const GLint *v);
extern PFNGLTEXCOORD2IVPROC glad_glTexCoord2iv;

typedef void ( * PFNGLTEXCOORD2SPROC)(GLshort s, GLshort t);
extern PFNGLTEXCOORD2SPROC glad_glTexCoord2s;

typedef void ( * PFNGLTEXCOORD2SVPROC)(const GLshort *v);
extern PFNGLTEXCOORD2SVPROC glad_glTexCoord2sv;

typedef void ( * PFNGLTEXCOORD3DPROC)(GLdouble s, GLdouble t, GLdouble r);
extern PFNGLTEXCOORD3DPROC glad_glTexCoord3d;

typedef void ( * PFNGLTEXCOORD3DVPROC)(const GLdouble *v);
extern PFNGLTEXCOORD3DVPROC glad_glTexCoord3dv;

typedef void ( * PFNGLTEXCOORD3FPROC)(GLfloat s, GLfloat t, GLfloat r);
extern PFNGLTEXCOORD3FPROC glad_glTexCoord3f;

typedef void ( * PFNGLTEXCOORD3FVPROC)(const GLfloat *v);
extern PFNGLTEXCOORD3FVPROC glad_glTexCoord3fv;

typedef void ( * PFNGLTEXCOORD3IPROC)(GLint s, GLint t, GLint r);
extern PFNGLTEXCOORD3IPROC glad_glTexCoord3i;

typedef void ( * PFNGLTEXCOORD3IVPROC)(const GLint *v);
extern PFNGLTEXCOORD3IVPROC glad_glTexCoord3iv;

typedef void ( * PFNGLTEXCOORD3SPROC)(GLshort s, GLshort t, GLshort r);
extern PFNGLTEXCOORD3SPROC glad_glTexCoord3s;

typedef void ( * PFNGLTEXCOORD3SVPROC)(const GLshort *v);
extern PFNGLTEXCOORD3SVPROC glad_glTexCoord3sv;

typedef void ( * PFNGLTEXCOORD4DPROC)(GLdouble s, GLdouble t, GLdouble r, GLdouble q);
extern PFNGLTEXCOORD4DPROC glad_glTexCoord4d;

typedef void ( * PFNGLTEXCOORD4DVPROC)(const GLdouble *v);
extern PFNGLTEXCOORD4DVPROC glad_glTexCoord4dv;

typedef void ( * PFNGLTEXCOORD4FPROC)(GLfloat s, GLfloat t, GLfloat r, GLfloat q);
extern PFNGLTEXCOORD4FPROC glad_glTexCoord4f;

typedef void ( * PFNGLTEXCOORD4FVPROC)(const GLfloat *v);
extern PFNGLTEXCOORD4FVPROC glad_glTexCoord4fv;

typedef void ( * PFNGLTEXCOORD4IPROC)(GLint s, GLint t, GLint r, GLint q);
extern PFNGLTEXCOORD4IPROC glad_glTexCoord4i;

typedef void ( * PFNGLTEXCOORD4IVPROC)(const GLint *v);
extern PFNGLTEXCOORD4IVPROC glad_glTexCoord4iv;

typedef void ( * PFNGLTEXCOORD4SPROC)(GLshort s, GLshort t, GLshort r, GLshort q);
extern PFNGLTEXCOORD4SPROC glad_glTexCoord4s;

typedef void ( * PFNGLTEXCOORD4SVPROC)(const GLshort *v);
extern PFNGLTEXCOORD4SVPROC glad_glTexCoord4sv;

typedef void ( * PFNGLVERTEX2DPROC)(GLdouble x, GLdouble y);
extern PFNGLVERTEX2DPROC glad_glVertex2d;

typedef void ( * PFNGLVERTEX2DVPROC)(const GLdouble *v);
extern PFNGLVERTEX2DVPROC glad_glVertex2dv;

typedef void ( * PFNGLVERTEX2FPROC)(GLfloat x, GLfloat y);
extern PFNGLVERTEX2FPROC glad_glVertex2f;

typedef void ( * PFNGLVERTEX2FVPROC)(const GLfloat *v);
extern PFNGLVERTEX2FVPROC glad_glVertex2fv;

typedef void ( * PFNGLVERTEX2IPROC)(GLint x, GLint y);
extern PFNGLVERTEX2IPROC glad_glVertex2i;

typedef void ( * PFNGLVERTEX2IVPROC)(const GLint *v);
extern PFNGLVERTEX2IVPROC glad_glVertex2iv;

typedef void ( * PFNGLVERTEX2SPROC)(GLshort x, GLshort y);
extern PFNGLVERTEX2SPROC glad_glVertex2s;

typedef void ( * PFNGLVERTEX2SVPROC)(const GLshort *v);
extern PFNGLVERTEX2SVPROC glad_glVertex2sv;

typedef void ( * PFNGLVERTEX3DPROC)(GLdouble x, GLdouble y, GLdouble z);
extern PFNGLVERTEX3DPROC glad_glVertex3d;

typedef void ( * PFNGLVERTEX3DVPROC)(const GLdouble *v);
extern PFNGLVERTEX3DVPROC glad_glVertex3dv;

typedef void ( * PFNGLVERTEX3FPROC)(GLfloat x, GLfloat y, GLfloat z);
extern PFNGLVERTEX3FPROC glad_glVertex3f;

typedef void ( * PFNGLVERTEX3FVPROC)(const GLfloat *v);
extern PFNGLVERTEX3FVPROC glad_glVertex3fv;

typedef void ( * PFNGLVERTEX3IPROC)(GLint x, GLint y, GLint z);
extern PFNGLVERTEX3IPROC glad_glVertex3i;

typedef void ( * PFNGLVERTEX3IVPROC)(const GLint *v);
extern PFNGLVERTEX3IVPROC glad_glVertex3iv;

typedef void ( * PFNGLVERTEX3SPROC)(GLshort x, GLshort y, GLshort z);
extern PFNGLVERTEX3SPROC glad_glVertex3s;

typedef void ( * PFNGLVERTEX3SVPROC)(const GLshort *v);
extern PFNGLVERTEX3SVPROC glad_glVertex3sv;

typedef void ( * PFNGLVERTEX4DPROC)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
extern PFNGLVERTEX4DPROC glad_glVertex4d;

typedef void ( * PFNGLVERTEX4DVPROC)(const GLdouble *v);
extern PFNGLVERTEX4DVPROC glad_glVertex4dv;

typedef void ( * PFNGLVERTEX4FPROC)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
extern PFNGLVERTEX4FPROC glad_glVertex4f;

typedef void ( * PFNGLVERTEX4FVPROC)(const GLfloat *v);
extern PFNGLVERTEX4FVPROC glad_glVertex4fv;

typedef void ( * PFNGLVERTEX4IPROC)(GLint x, GLint y, GLint z, GLint w);
extern PFNGLVERTEX4IPROC glad_glVertex4i;

typedef void ( * PFNGLVERTEX4IVPROC)(const GLint *v);
extern PFNGLVERTEX4IVPROC glad_glVertex4iv;

typedef void ( * PFNGLVERTEX4SPROC)(GLshort x, GLshort y, GLshort z, GLshort w);
extern PFNGLVERTEX4SPROC glad_glVertex4s;

typedef void ( * PFNGLVERTEX4SVPROC)(const GLshort *v);
extern PFNGLVERTEX4SVPROC glad_glVertex4sv;

typedef void ( * PFNGLCLIPPLANEPROC)(GLenum plane, const GLdouble *equation);
extern PFNGLCLIPPLANEPROC glad_glClipPlane;

typedef void ( * PFNGLCOLORMATERIALPROC)(GLenum face, GLenum mode);
extern PFNGLCOLORMATERIALPROC glad_glColorMaterial;

typedef void ( * PFNGLFOGFPROC)(GLenum pname, GLfloat param);
extern PFNGLFOGFPROC glad_glFogf;

typedef void ( * PFNGLFOGFVPROC)(GLenum pname, const GLfloat *params);
extern PFNGLFOGFVPROC glad_glFogfv;

typedef void ( * PFNGLFOGIPROC)(GLenum pname, GLint param);
extern PFNGLFOGIPROC glad_glFogi;

typedef void ( * PFNGLFOGIVPROC)(GLenum pname, const GLint *params);
extern PFNGLFOGIVPROC glad_glFogiv;

typedef void ( * PFNGLLIGHTFPROC)(GLenum light, GLenum pname, GLfloat param);
extern PFNGLLIGHTFPROC glad_glLightf;

typedef void ( * PFNGLLIGHTFVPROC)(GLenum light, GLenum pname, const GLfloat *params);
extern PFNGLLIGHTFVPROC glad_glLightfv;

typedef void ( * PFNGLLIGHTIPROC)(GLenum light, GLenum pname, GLint param);
extern PFNGLLIGHTIPROC glad_glLighti;

typedef void ( * PFNGLLIGHTIVPROC)(GLenum light, GLenum pname, const GLint *params);
extern PFNGLLIGHTIVPROC glad_glLightiv;

typedef void ( * PFNGLLIGHTMODELFPROC)(GLenum pname, GLfloat param);
extern PFNGLLIGHTMODELFPROC glad_glLightModelf;

typedef void ( * PFNGLLIGHTMODELFVPROC)(GLenum pname, const GLfloat *params);
extern PFNGLLIGHTMODELFVPROC glad_glLightModelfv;

typedef void ( * PFNGLLIGHTMODELIPROC)(GLenum pname, GLint param);
extern PFNGLLIGHTMODELIPROC glad_glLightModeli;

typedef void ( * PFNGLLIGHTMODELIVPROC)(GLenum pname, const GLint *params);
extern PFNGLLIGHTMODELIVPROC glad_glLightModeliv;

typedef void ( * PFNGLLINESTIPPLEPROC)(GLint factor, GLushort pattern);
extern PFNGLLINESTIPPLEPROC glad_glLineStipple;

typedef void ( * PFNGLMATERIALFPROC)(GLenum face, GLenum pname, GLfloat param);
extern PFNGLMATERIALFPROC glad_glMaterialf;

typedef void ( * PFNGLMATERIALFVPROC)(GLenum face, GLenum pname, const GLfloat *params);
extern PFNGLMATERIALFVPROC glad_glMaterialfv;

typedef void ( * PFNGLMATERIALIPROC)(GLenum face, GLenum pname, GLint param);
extern PFNGLMATERIALIPROC glad_glMateriali;

typedef void ( * PFNGLMATERIALIVPROC)(GLenum face, GLenum pname, const GLint *params);
extern PFNGLMATERIALIVPROC glad_glMaterialiv;

typedef void ( * PFNGLPOLYGONSTIPPLEPROC)(const GLubyte *mask);
extern PFNGLPOLYGONSTIPPLEPROC glad_glPolygonStipple;

typedef void ( * PFNGLSHADEMODELPROC)(GLenum mode);
extern PFNGLSHADEMODELPROC glad_glShadeModel;

typedef void ( * PFNGLTEXENVFPROC)(GLenum target, GLenum pname, GLfloat param);
extern PFNGLTEXENVFPROC glad_glTexEnvf;

typedef void ( * PFNGLTEXENVFVPROC)(GLenum target, GLenum pname, const GLfloat *params);
extern PFNGLTEXENVFVPROC glad_glTexEnvfv;

typedef void ( * PFNGLTEXENVIPROC)(GLenum target, GLenum pname, GLint param);
extern PFNGLTEXENVIPROC glad_glTexEnvi;

typedef void ( * PFNGLTEXENVIVPROC)(GLenum target, GLenum pname, const GLint *params);
extern PFNGLTEXENVIVPROC glad_glTexEnviv;

typedef void ( * PFNGLTEXGENDPROC)(GLenum coord, GLenum pname, GLdouble param);
extern PFNGLTEXGENDPROC glad_glTexGend;

typedef void ( * PFNGLTEXGENDVPROC)(GLenum coord, GLenum pname, const GLdouble *params);
extern PFNGLTEXGENDVPROC glad_glTexGendv;

typedef void ( * PFNGLTEXGENFPROC)(GLenum coord, GLenum pname, GLfloat param);
extern PFNGLTEXGENFPROC glad_glTexGenf;

typedef void ( * PFNGLTEXGENFVPROC)(GLenum coord, GLenum pname, const GLfloat *params);
extern PFNGLTEXGENFVPROC glad_glTexGenfv;

typedef void ( * PFNGLTEXGENIPROC)(GLenum coord, GLenum pname, GLint param);
extern PFNGLTEXGENIPROC glad_glTexGeni;

typedef void ( * PFNGLTEXGENIVPROC)(GLenum coord, GLenum pname, const GLint *params);
extern PFNGLTEXGENIVPROC glad_glTexGeniv;

typedef void ( * PFNGLFEEDBACKBUFFERPROC)(GLsizei size, GLenum type, GLfloat *buffer);
extern PFNGLFEEDBACKBUFFERPROC glad_glFeedbackBuffer;

typedef void ( * PFNGLSELECTBUFFERPROC)(GLsizei size, GLuint *buffer);
extern PFNGLSELECTBUFFERPROC glad_glSelectBuffer;

typedef GLint ( * PFNGLRENDERMODEPROC)(GLenum mode);
extern PFNGLRENDERMODEPROC glad_glRenderMode;

typedef void ( * PFNGLINITNAMESPROC)(void);
extern PFNGLINITNAMESPROC glad_glInitNames;

typedef void ( * PFNGLLOADNAMEPROC)(GLuint name);
extern PFNGLLOADNAMEPROC glad_glLoadName;

typedef void ( * PFNGLPASSTHROUGHPROC)(GLfloat token);
extern PFNGLPASSTHROUGHPROC glad_glPassThrough;

typedef void ( * PFNGLPOPNAMEPROC)(void);
extern PFNGLPOPNAMEPROC glad_glPopName;

typedef void ( * PFNGLPUSHNAMEPROC)(GLuint name);
extern PFNGLPUSHNAMEPROC glad_glPushName;

typedef void ( * PFNGLCLEARACCUMPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern PFNGLCLEARACCUMPROC glad_glClearAccum;

typedef void ( * PFNGLCLEARINDEXPROC)(GLfloat c);
extern PFNGLCLEARINDEXPROC glad_glClearIndex;

typedef void ( * PFNGLINDEXMASKPROC)(GLuint mask);
extern PFNGLINDEXMASKPROC glad_glIndexMask;

typedef void ( * PFNGLACCUMPROC)(GLenum op, GLfloat value);
extern PFNGLACCUMPROC glad_glAccum;

typedef void ( * PFNGLPOPATTRIBPROC)(void);
extern PFNGLPOPATTRIBPROC glad_glPopAttrib;

typedef void ( * PFNGLPUSHATTRIBPROC)(GLbitfield mask);
extern PFNGLPUSHATTRIBPROC glad_glPushAttrib;

typedef void ( * PFNGLMAP1DPROC)(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points);
extern PFNGLMAP1DPROC glad_glMap1d;

typedef void ( * PFNGLMAP1FPROC)(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
extern PFNGLMAP1FPROC glad_glMap1f;

typedef void ( * PFNGLMAP2DPROC)(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points);
extern PFNGLMAP2DPROC glad_glMap2d;

typedef void ( * PFNGLMAP2FPROC)(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points);
extern PFNGLMAP2FPROC glad_glMap2f;

typedef void ( * PFNGLMAPGRID1DPROC)(GLint un, GLdouble u1, GLdouble u2);
extern PFNGLMAPGRID1DPROC glad_glMapGrid1d;

typedef void ( * PFNGLMAPGRID1FPROC)(GLint un, GLfloat u1, GLfloat u2);
extern PFNGLMAPGRID1FPROC glad_glMapGrid1f;

typedef void ( * PFNGLMAPGRID2DPROC)(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
extern PFNGLMAPGRID2DPROC glad_glMapGrid2d;

typedef void ( * PFNGLMAPGRID2FPROC)(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
extern PFNGLMAPGRID2FPROC glad_glMapGrid2f;

typedef void ( * PFNGLEVALCOORD1DPROC)(GLdouble u);
extern PFNGLEVALCOORD1DPROC glad_glEvalCoord1d;

typedef void ( * PFNGLEVALCOORD1DVPROC)(const GLdouble *u);
extern PFNGLEVALCOORD1DVPROC glad_glEvalCoord1dv;

typedef void ( * PFNGLEVALCOORD1FPROC)(GLfloat u);
extern PFNGLEVALCOORD1FPROC glad_glEvalCoord1f;

typedef void ( * PFNGLEVALCOORD1FVPROC)(const GLfloat *u);
extern PFNGLEVALCOORD1FVPROC glad_glEvalCoord1fv;

typedef void ( * PFNGLEVALCOORD2DPROC)(GLdouble u, GLdouble v);
extern PFNGLEVALCOORD2DPROC glad_glEvalCoord2d;

typedef void ( * PFNGLEVALCOORD2DVPROC)(const GLdouble *u);
extern PFNGLEVALCOORD2DVPROC glad_glEvalCoord2dv;

typedef void ( * PFNGLEVALCOORD2FPROC)(GLfloat u, GLfloat v);
extern PFNGLEVALCOORD2FPROC glad_glEvalCoord2f;

typedef void ( * PFNGLEVALCOORD2FVPROC)(const GLfloat *u);
extern PFNGLEVALCOORD2FVPROC glad_glEvalCoord2fv;

typedef void ( * PFNGLEVALMESH1PROC)(GLenum mode, GLint i1, GLint i2);
extern PFNGLEVALMESH1PROC glad_glEvalMesh1;

typedef void ( * PFNGLEVALPOINT1PROC)(GLint i);
extern PFNGLEVALPOINT1PROC glad_glEvalPoint1;

typedef void ( * PFNGLEVALMESH2PROC)(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
extern PFNGLEVALMESH2PROC glad_glEvalMesh2;

typedef void ( * PFNGLEVALPOINT2PROC)(GLint i, GLint j);
extern PFNGLEVALPOINT2PROC glad_glEvalPoint2;

typedef void ( * PFNGLALPHAFUNCPROC)(GLenum func, GLfloat ref);
extern PFNGLALPHAFUNCPROC glad_glAlphaFunc;

typedef void ( * PFNGLPIXELZOOMPROC)(GLfloat xfactor, GLfloat yfactor);
extern PFNGLPIXELZOOMPROC glad_glPixelZoom;

typedef void ( * PFNGLPIXELTRANSFERFPROC)(GLenum pname, GLfloat param);
extern PFNGLPIXELTRANSFERFPROC glad_glPixelTransferf;

typedef void ( * PFNGLPIXELTRANSFERIPROC)(GLenum pname, GLint param);
extern PFNGLPIXELTRANSFERIPROC glad_glPixelTransferi;

typedef void ( * PFNGLPIXELMAPFVPROC)(GLenum map, GLsizei mapsize, const GLfloat *values);
extern PFNGLPIXELMAPFVPROC glad_glPixelMapfv;

typedef void ( * PFNGLPIXELMAPUIVPROC)(GLenum map, GLsizei mapsize, const GLuint *values);
extern PFNGLPIXELMAPUIVPROC glad_glPixelMapuiv;

typedef void ( * PFNGLPIXELMAPUSVPROC)(GLenum map, GLsizei mapsize, const GLushort *values);
extern PFNGLPIXELMAPUSVPROC glad_glPixelMapusv;

typedef void ( * PFNGLCOPYPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
extern PFNGLCOPYPIXELSPROC glad_glCopyPixels;

typedef void ( * PFNGLDRAWPIXELSPROC)(GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
extern PFNGLDRAWPIXELSPROC glad_glDrawPixels;

typedef void ( * PFNGLGETCLIPPLANEPROC)(GLenum plane, GLdouble *equation);
extern PFNGLGETCLIPPLANEPROC glad_glGetClipPlane;

typedef void ( * PFNGLGETLIGHTFVPROC)(GLenum light, GLenum pname, GLfloat *params);
extern PFNGLGETLIGHTFVPROC glad_glGetLightfv;

typedef void ( * PFNGLGETLIGHTIVPROC)(GLenum light, GLenum pname, GLint *params);
extern PFNGLGETLIGHTIVPROC glad_glGetLightiv;

typedef void ( * PFNGLGETMAPDVPROC)(GLenum target, GLenum query, GLdouble *v);
extern PFNGLGETMAPDVPROC glad_glGetMapdv;

typedef void ( * PFNGLGETMAPFVPROC)(GLenum target, GLenum query, GLfloat *v);
extern PFNGLGETMAPFVPROC glad_glGetMapfv;

typedef void ( * PFNGLGETMAPIVPROC)(GLenum target, GLenum query, GLint *v);
extern PFNGLGETMAPIVPROC glad_glGetMapiv;

typedef void ( * PFNGLGETMATERIALFVPROC)(GLenum face, GLenum pname, GLfloat *params);
extern PFNGLGETMATERIALFVPROC glad_glGetMaterialfv;

typedef void ( * PFNGLGETMATERIALIVPROC)(GLenum face, GLenum pname, GLint *params);
extern PFNGLGETMATERIALIVPROC glad_glGetMaterialiv;

typedef void ( * PFNGLGETPIXELMAPFVPROC)(GLenum map, GLfloat *values);
extern PFNGLGETPIXELMAPFVPROC glad_glGetPixelMapfv;

typedef void ( * PFNGLGETPIXELMAPUIVPROC)(GLenum map, GLuint *values);
extern PFNGLGETPIXELMAPUIVPROC glad_glGetPixelMapuiv;

typedef void ( * PFNGLGETPIXELMAPUSVPROC)(GLenum map, GLushort *values);
extern PFNGLGETPIXELMAPUSVPROC glad_glGetPixelMapusv;

typedef void ( * PFNGLGETPOLYGONSTIPPLEPROC)(GLubyte *mask);
extern PFNGLGETPOLYGONSTIPPLEPROC glad_glGetPolygonStipple;

typedef void ( * PFNGLGETTEXENVFVPROC)(GLenum target, GLenum pname, GLfloat *params);
extern PFNGLGETTEXENVFVPROC glad_glGetTexEnvfv;

typedef void ( * PFNGLGETTEXENVIVPROC)(GLenum target, GLenum pname, GLint *params);
extern PFNGLGETTEXENVIVPROC glad_glGetTexEnviv;

typedef void ( * PFNGLGETTEXGENDVPROC)(GLenum coord, GLenum pname, GLdouble *params);
extern PFNGLGETTEXGENDVPROC glad_glGetTexGendv;

typedef void ( * PFNGLGETTEXGENFVPROC)(GLenum coord, GLenum pname, GLfloat *params);
extern PFNGLGETTEXGENFVPROC glad_glGetTexGenfv;

typedef void ( * PFNGLGETTEXGENIVPROC)(GLenum coord, GLenum pname, GLint *params);
extern PFNGLGETTEXGENIVPROC glad_glGetTexGeniv;

typedef GLboolean ( * PFNGLISLISTPROC)(GLuint list);
extern PFNGLISLISTPROC glad_glIsList;

typedef void ( * PFNGLFRUSTUMPROC)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
extern PFNGLFRUSTUMPROC glad_glFrustum;

typedef void ( * PFNGLLOADIDENTITYPROC)(void);
extern PFNGLLOADIDENTITYPROC glad_glLoadIdentity;

typedef void ( * PFNGLLOADMATRIXFPROC)(const GLfloat *m);
extern PFNGLLOADMATRIXFPROC glad_glLoadMatrixf;

typedef void ( * PFNGLLOADMATRIXDPROC)(const GLdouble *m);
extern PFNGLLOADMATRIXDPROC glad_glLoadMatrixd;

typedef void ( * PFNGLMATRIXMODEPROC)(GLenum mode);
extern PFNGLMATRIXMODEPROC glad_glMatrixMode;

typedef void ( * PFNGLMULTMATRIXFPROC)(const GLfloat *m);
extern PFNGLMULTMATRIXFPROC glad_glMultMatrixf;

typedef void ( * PFNGLMULTMATRIXDPROC)(const GLdouble *m);
extern PFNGLMULTMATRIXDPROC glad_glMultMatrixd;

typedef void ( * PFNGLORTHOPROC)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
extern PFNGLORTHOPROC glad_glOrtho;

typedef void ( * PFNGLPOPMATRIXPROC)(void);
extern PFNGLPOPMATRIXPROC glad_glPopMatrix;

typedef void ( * PFNGLPUSHMATRIXPROC)(void);
extern PFNGLPUSHMATRIXPROC glad_glPushMatrix;

typedef void ( * PFNGLROTATEDPROC)(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
extern PFNGLROTATEDPROC glad_glRotated;

typedef void ( * PFNGLROTATEFPROC)(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
extern PFNGLROTATEFPROC glad_glRotatef;

typedef void ( * PFNGLSCALEDPROC)(GLdouble x, GLdouble y, GLdouble z);
extern PFNGLSCALEDPROC glad_glScaled;

typedef void ( * PFNGLSCALEFPROC)(GLfloat x, GLfloat y, GLfloat z);
extern PFNGLSCALEFPROC glad_glScalef;

typedef void ( * PFNGLTRANSLATEDPROC)(GLdouble x, GLdouble y, GLdouble z);
extern PFNGLTRANSLATEDPROC glad_glTranslated;

typedef void ( * PFNGLTRANSLATEFPROC)(GLfloat x, GLfloat y, GLfloat z);
extern PFNGLTRANSLATEFPROC glad_glTranslatef;




extern int GLAD_GL_VERSION_1_1;
typedef void ( * PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);
extern PFNGLDRAWARRAYSPROC glad_glDrawArrays;

typedef void ( * PFNGLDRAWELEMENTSPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices);
extern PFNGLDRAWELEMENTSPROC glad_glDrawElements;

typedef void ( * PFNGLGETPOINTERVPROC)(GLenum pname, void **params);
extern PFNGLGETPOINTERVPROC glad_glGetPointerv;

typedef void ( * PFNGLPOLYGONOFFSETPROC)(GLfloat factor, GLfloat units);
extern PFNGLPOLYGONOFFSETPROC glad_glPolygonOffset;

typedef void ( * PFNGLCOPYTEXIMAGE1DPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
extern PFNGLCOPYTEXIMAGE1DPROC glad_glCopyTexImage1D;

typedef void ( * PFNGLCOPYTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
extern PFNGLCOPYTEXIMAGE2DPROC glad_glCopyTexImage2D;

typedef void ( * PFNGLCOPYTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
extern PFNGLCOPYTEXSUBIMAGE1DPROC glad_glCopyTexSubImage1D;

typedef void ( * PFNGLCOPYTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
extern PFNGLCOPYTEXSUBIMAGE2DPROC glad_glCopyTexSubImage2D;

typedef void ( * PFNGLTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
extern PFNGLTEXSUBIMAGE1DPROC glad_glTexSubImage1D;

typedef void ( * PFNGLTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
extern PFNGLTEXSUBIMAGE2DPROC glad_glTexSubImage2D;

typedef void ( * PFNGLBINDTEXTUREPROC)(GLenum target, GLuint texture);
extern PFNGLBINDTEXTUREPROC glad_glBindTexture;

typedef void ( * PFNGLDELETETEXTURESPROC)(GLsizei n, const GLuint *textures);
extern PFNGLDELETETEXTURESPROC glad_glDeleteTextures;

typedef void ( * PFNGLGENTEXTURESPROC)(GLsizei n, GLuint *textures);
extern PFNGLGENTEXTURESPROC glad_glGenTextures;

typedef GLboolean ( * PFNGLISTEXTUREPROC)(GLuint texture);
extern PFNGLISTEXTUREPROC glad_glIsTexture;

typedef void ( * PFNGLARRAYELEMENTPROC)(GLint i);
extern PFNGLARRAYELEMENTPROC glad_glArrayElement;

typedef void ( * PFNGLCOLORPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const void *pointer);
extern PFNGLCOLORPOINTERPROC glad_glColorPointer;

typedef void ( * PFNGLDISABLECLIENTSTATEPROC)(GLenum array);
extern PFNGLDISABLECLIENTSTATEPROC glad_glDisableClientState;

typedef void ( * PFNGLEDGEFLAGPOINTERPROC)(GLsizei stride, const void *pointer);
extern PFNGLEDGEFLAGPOINTERPROC glad_glEdgeFlagPointer;

typedef void ( * PFNGLENABLECLIENTSTATEPROC)(GLenum array);
extern PFNGLENABLECLIENTSTATEPROC glad_glEnableClientState;

typedef void ( * PFNGLINDEXPOINTERPROC)(GLenum type, GLsizei stride, const void *pointer);
extern PFNGLINDEXPOINTERPROC glad_glIndexPointer;

typedef void ( * PFNGLINTERLEAVEDARRAYSPROC)(GLenum format, GLsizei stride, const void *pointer);
extern PFNGLINTERLEAVEDARRAYSPROC glad_glInterleavedArrays;

typedef void ( * PFNGLNORMALPOINTERPROC)(GLenum type, GLsizei stride, const void *pointer);
extern PFNGLNORMALPOINTERPROC glad_glNormalPointer;

typedef void ( * PFNGLTEXCOORDPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const void *pointer);
extern PFNGLTEXCOORDPOINTERPROC glad_glTexCoordPointer;

typedef void ( * PFNGLVERTEXPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const void *pointer);
extern PFNGLVERTEXPOINTERPROC glad_glVertexPointer;

typedef GLboolean ( * PFNGLARETEXTURESRESIDENTPROC)(GLsizei n, const GLuint *textures, GLboolean *residences);
extern PFNGLARETEXTURESRESIDENTPROC glad_glAreTexturesResident;

typedef void ( * PFNGLPRIORITIZETEXTURESPROC)(GLsizei n, const GLuint *textures, const GLfloat *priorities);
extern PFNGLPRIORITIZETEXTURESPROC glad_glPrioritizeTextures;

typedef void ( * PFNGLINDEXUBPROC)(GLubyte c);
extern PFNGLINDEXUBPROC glad_glIndexub;

typedef void ( * PFNGLINDEXUBVPROC)(const GLubyte *c);
extern PFNGLINDEXUBVPROC glad_glIndexubv;

typedef void ( * PFNGLPOPCLIENTATTRIBPROC)(void);
extern PFNGLPOPCLIENTATTRIBPROC glad_glPopClientAttrib;

typedef void ( * PFNGLPUSHCLIENTATTRIBPROC)(GLbitfield mask);
extern PFNGLPUSHCLIENTATTRIBPROC glad_glPushClientAttrib;




extern int GLAD_GL_VERSION_1_2;
typedef void ( * PFNGLDRAWRANGEELEMENTSPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices);
extern PFNGLDRAWRANGEELEMENTSPROC glad_glDrawRangeElements;

typedef void ( * PFNGLTEXIMAGE3DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels);
extern PFNGLTEXIMAGE3DPROC glad_glTexImage3D;

typedef void ( * PFNGLTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
extern PFNGLTEXSUBIMAGE3DPROC glad_glTexSubImage3D;

typedef void ( * PFNGLCOPYTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
extern PFNGLCOPYTEXSUBIMAGE3DPROC glad_glCopyTexSubImage3D;




extern int GLAD_GL_VERSION_1_3;
typedef void ( * PFNGLACTIVETEXTUREPROC)(GLenum texture);
extern PFNGLACTIVETEXTUREPROC glad_glActiveTexture;

typedef void ( * PFNGLSAMPLECOVERAGEPROC)(GLfloat value, GLboolean invert);
extern PFNGLSAMPLECOVERAGEPROC glad_glSampleCoverage;

typedef void ( * PFNGLCOMPRESSEDTEXIMAGE3DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data);
extern PFNGLCOMPRESSEDTEXIMAGE3DPROC glad_glCompressedTexImage3D;

typedef void ( * PFNGLCOMPRESSEDTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data);
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC glad_glCompressedTexImage2D;

typedef void ( * PFNGLCOMPRESSEDTEXIMAGE1DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data);
extern PFNGLCOMPRESSEDTEXIMAGE1DPROC glad_glCompressedTexImage1D;

typedef void ( * PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glad_glCompressedTexSubImage3D;

typedef void ( * PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glad_glCompressedTexSubImage2D;

typedef void ( * PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data);
extern PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glad_glCompressedTexSubImage1D;

typedef void ( * PFNGLGETCOMPRESSEDTEXIMAGEPROC)(GLenum target, GLint level, void *img);
extern PFNGLGETCOMPRESSEDTEXIMAGEPROC glad_glGetCompressedTexImage;

typedef void ( * PFNGLCLIENTACTIVETEXTUREPROC)(GLenum texture);
extern PFNGLCLIENTACTIVETEXTUREPROC glad_glClientActiveTexture;

typedef void ( * PFNGLMULTITEXCOORD1DPROC)(GLenum target, GLdouble s);
extern PFNGLMULTITEXCOORD1DPROC glad_glMultiTexCoord1d;

typedef void ( * PFNGLMULTITEXCOORD1DVPROC)(GLenum target, const GLdouble *v);
extern PFNGLMULTITEXCOORD1DVPROC glad_glMultiTexCoord1dv;

typedef void ( * PFNGLMULTITEXCOORD1FPROC)(GLenum target, GLfloat s);
extern PFNGLMULTITEXCOORD1FPROC glad_glMultiTexCoord1f;

typedef void ( * PFNGLMULTITEXCOORD1FVPROC)(GLenum target, const GLfloat *v);
extern PFNGLMULTITEXCOORD1FVPROC glad_glMultiTexCoord1fv;

typedef void ( * PFNGLMULTITEXCOORD1IPROC)(GLenum target, GLint s);
extern PFNGLMULTITEXCOORD1IPROC glad_glMultiTexCoord1i;

typedef void ( * PFNGLMULTITEXCOORD1IVPROC)(GLenum target, const GLint *v);
extern PFNGLMULTITEXCOORD1IVPROC glad_glMultiTexCoord1iv;

typedef void ( * PFNGLMULTITEXCOORD1SPROC)(GLenum target, GLshort s);
extern PFNGLMULTITEXCOORD1SPROC glad_glMultiTexCoord1s;

typedef void ( * PFNGLMULTITEXCOORD1SVPROC)(GLenum target, const GLshort *v);
extern PFNGLMULTITEXCOORD1SVPROC glad_glMultiTexCoord1sv;

typedef void ( * PFNGLMULTITEXCOORD2DPROC)(GLenum target, GLdouble s, GLdouble t);
extern PFNGLMULTITEXCOORD2DPROC glad_glMultiTexCoord2d;

typedef void ( * PFNGLMULTITEXCOORD2DVPROC)(GLenum target, const GLdouble *v);
extern PFNGLMULTITEXCOORD2DVPROC glad_glMultiTexCoord2dv;

typedef void ( * PFNGLMULTITEXCOORD2FPROC)(GLenum target, GLfloat s, GLfloat t);
extern PFNGLMULTITEXCOORD2FPROC glad_glMultiTexCoord2f;

typedef void ( * PFNGLMULTITEXCOORD2FVPROC)(GLenum target, const GLfloat *v);
extern PFNGLMULTITEXCOORD2FVPROC glad_glMultiTexCoord2fv;

typedef void ( * PFNGLMULTITEXCOORD2IPROC)(GLenum target, GLint s, GLint t);
extern PFNGLMULTITEXCOORD2IPROC glad_glMultiTexCoord2i;

typedef void ( * PFNGLMULTITEXCOORD2IVPROC)(GLenum target, const GLint *v);
extern PFNGLMULTITEXCOORD2IVPROC glad_glMultiTexCoord2iv;

typedef void ( * PFNGLMULTITEXCOORD2SPROC)(GLenum target, GLshort s, GLshort t);
extern PFNGLMULTITEXCOORD2SPROC glad_glMultiTexCoord2s;

typedef void ( * PFNGLMULTITEXCOORD2SVPROC)(GLenum target, const GLshort *v);
extern PFNGLMULTITEXCOORD2SVPROC glad_glMultiTexCoord2sv;

typedef void ( * PFNGLMULTITEXCOORD3DPROC)(GLenum target, GLdouble s, GLdouble t, GLdouble r);
extern PFNGLMULTITEXCOORD3DPROC glad_glMultiTexCoord3d;

typedef void ( * PFNGLMULTITEXCOORD3DVPROC)(GLenum target, const GLdouble *v);
extern PFNGLMULTITEXCOORD3DVPROC glad_glMultiTexCoord3dv;

typedef void ( * PFNGLMULTITEXCOORD3FPROC)(GLenum target, GLfloat s, GLfloat t, GLfloat r);
extern PFNGLMULTITEXCOORD3FPROC glad_glMultiTexCoord3f;

typedef void ( * PFNGLMULTITEXCOORD3FVPROC)(GLenum target, const GLfloat *v);
extern PFNGLMULTITEXCOORD3FVPROC glad_glMultiTexCoord3fv;

typedef void ( * PFNGLMULTITEXCOORD3IPROC)(GLenum target, GLint s, GLint t, GLint r);
extern PFNGLMULTITEXCOORD3IPROC glad_glMultiTexCoord3i;

typedef void ( * PFNGLMULTITEXCOORD3IVPROC)(GLenum target, const GLint *v);
extern PFNGLMULTITEXCOORD3IVPROC glad_glMultiTexCoord3iv;

typedef void ( * PFNGLMULTITEXCOORD3SPROC)(GLenum target, GLshort s, GLshort t, GLshort r);
extern PFNGLMULTITEXCOORD3SPROC glad_glMultiTexCoord3s;

typedef void ( * PFNGLMULTITEXCOORD3SVPROC)(GLenum target, const GLshort *v);
extern PFNGLMULTITEXCOORD3SVPROC glad_glMultiTexCoord3sv;

typedef void ( * PFNGLMULTITEXCOORD4DPROC)(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
extern PFNGLMULTITEXCOORD4DPROC glad_glMultiTexCoord4d;

typedef void ( * PFNGLMULTITEXCOORD4DVPROC)(GLenum target, const GLdouble *v);
extern PFNGLMULTITEXCOORD4DVPROC glad_glMultiTexCoord4dv;

typedef void ( * PFNGLMULTITEXCOORD4FPROC)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
extern PFNGLMULTITEXCOORD4FPROC glad_glMultiTexCoord4f;

typedef void ( * PFNGLMULTITEXCOORD4FVPROC)(GLenum target, const GLfloat *v);
extern PFNGLMULTITEXCOORD4FVPROC glad_glMultiTexCoord4fv;

typedef void ( * PFNGLMULTITEXCOORD4IPROC)(GLenum target, GLint s, GLint t, GLint r, GLint q);
extern PFNGLMULTITEXCOORD4IPROC glad_glMultiTexCoord4i;

typedef void ( * PFNGLMULTITEXCOORD4IVPROC)(GLenum target, const GLint *v);
extern PFNGLMULTITEXCOORD4IVPROC glad_glMultiTexCoord4iv;

typedef void ( * PFNGLMULTITEXCOORD4SPROC)(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
extern PFNGLMULTITEXCOORD4SPROC glad_glMultiTexCoord4s;

typedef void ( * PFNGLMULTITEXCOORD4SVPROC)(GLenum target, const GLshort *v);
extern PFNGLMULTITEXCOORD4SVPROC glad_glMultiTexCoord4sv;

typedef void ( * PFNGLLOADTRANSPOSEMATRIXFPROC)(const GLfloat *m);
extern PFNGLLOADTRANSPOSEMATRIXFPROC glad_glLoadTransposeMatrixf;

typedef void ( * PFNGLLOADTRANSPOSEMATRIXDPROC)(const GLdouble *m);
extern PFNGLLOADTRANSPOSEMATRIXDPROC glad_glLoadTransposeMatrixd;

typedef void ( * PFNGLMULTTRANSPOSEMATRIXFPROC)(const GLfloat *m);
extern PFNGLMULTTRANSPOSEMATRIXFPROC glad_glMultTransposeMatrixf;

typedef void ( * PFNGLMULTTRANSPOSEMATRIXDPROC)(const GLdouble *m);
extern PFNGLMULTTRANSPOSEMATRIXDPROC glad_glMultTransposeMatrixd;




extern int GLAD_GL_VERSION_1_4;
typedef void ( * PFNGLBLENDFUNCSEPARATEPROC)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
extern PFNGLBLENDFUNCSEPARATEPROC glad_glBlendFuncSeparate;

typedef void ( * PFNGLMULTIDRAWARRAYSPROC)(GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount);
extern PFNGLMULTIDRAWARRAYSPROC glad_glMultiDrawArrays;

typedef void ( * PFNGLMULTIDRAWELEMENTSPROC)(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount);
extern PFNGLMULTIDRAWELEMENTSPROC glad_glMultiDrawElements;

typedef void ( * PFNGLPOINTPARAMETERFPROC)(GLenum pname, GLfloat param);
extern PFNGLPOINTPARAMETERFPROC glad_glPointParameterf;

typedef void ( * PFNGLPOINTPARAMETERFVPROC)(GLenum pname, const GLfloat *params);
extern PFNGLPOINTPARAMETERFVPROC glad_glPointParameterfv;

typedef void ( * PFNGLPOINTPARAMETERIPROC)(GLenum pname, GLint param);
extern PFNGLPOINTPARAMETERIPROC glad_glPointParameteri;

typedef void ( * PFNGLPOINTPARAMETERIVPROC)(GLenum pname, const GLint *params);
extern PFNGLPOINTPARAMETERIVPROC glad_glPointParameteriv;

typedef void ( * PFNGLFOGCOORDFPROC)(GLfloat coord);
extern PFNGLFOGCOORDFPROC glad_glFogCoordf;

typedef void ( * PFNGLFOGCOORDFVPROC)(const GLfloat *coord);
extern PFNGLFOGCOORDFVPROC glad_glFogCoordfv;

typedef void ( * PFNGLFOGCOORDDPROC)(GLdouble coord);
extern PFNGLFOGCOORDDPROC glad_glFogCoordd;

typedef void ( * PFNGLFOGCOORDDVPROC)(const GLdouble *coord);
extern PFNGLFOGCOORDDVPROC glad_glFogCoorddv;

typedef void ( * PFNGLFOGCOORDPOINTERPROC)(GLenum type, GLsizei stride, const void *pointer);
extern PFNGLFOGCOORDPOINTERPROC glad_glFogCoordPointer;

typedef void ( * PFNGLSECONDARYCOLOR3BPROC)(GLbyte red, GLbyte green, GLbyte blue);
extern PFNGLSECONDARYCOLOR3BPROC glad_glSecondaryColor3b;

typedef void ( * PFNGLSECONDARYCOLOR3BVPROC)(const GLbyte *v);
extern PFNGLSECONDARYCOLOR3BVPROC glad_glSecondaryColor3bv;

typedef void ( * PFNGLSECONDARYCOLOR3DPROC)(GLdouble red, GLdouble green, GLdouble blue);
extern PFNGLSECONDARYCOLOR3DPROC glad_glSecondaryColor3d;

typedef void ( * PFNGLSECONDARYCOLOR3DVPROC)(const GLdouble *v);
extern PFNGLSECONDARYCOLOR3DVPROC glad_glSecondaryColor3dv;

typedef void ( * PFNGLSECONDARYCOLOR3FPROC)(GLfloat red, GLfloat green, GLfloat blue);
extern PFNGLSECONDARYCOLOR3FPROC glad_glSecondaryColor3f;

typedef void ( * PFNGLSECONDARYCOLOR3FVPROC)(const GLfloat *v);
extern PFNGLSECONDARYCOLOR3FVPROC glad_glSecondaryColor3fv;

typedef void ( * PFNGLSECONDARYCOLOR3IPROC)(GLint red, GLint green, GLint blue);
extern PFNGLSECONDARYCOLOR3IPROC glad_glSecondaryColor3i;

typedef void ( * PFNGLSECONDARYCOLOR3IVPROC)(const GLint *v);
extern PFNGLSECONDARYCOLOR3IVPROC glad_glSecondaryColor3iv;

typedef void ( * PFNGLSECONDARYCOLOR3SPROC)(GLshort red, GLshort green, GLshort blue);
extern PFNGLSECONDARYCOLOR3SPROC glad_glSecondaryColor3s;

typedef void ( * PFNGLSECONDARYCOLOR3SVPROC)(const GLshort *v);
extern PFNGLSECONDARYCOLOR3SVPROC glad_glSecondaryColor3sv;

typedef void ( * PFNGLSECONDARYCOLOR3UBPROC)(GLubyte red, GLubyte green, GLubyte blue);
extern PFNGLSECONDARYCOLOR3UBPROC glad_glSecondaryColor3ub;

typedef void ( * PFNGLSECONDARYCOLOR3UBVPROC)(const GLubyte *v);
extern PFNGLSECONDARYCOLOR3UBVPROC glad_glSecondaryColor3ubv;

typedef void ( * PFNGLSECONDARYCOLOR3UIPROC)(GLuint red, GLuint green, GLuint blue);
extern PFNGLSECONDARYCOLOR3UIPROC glad_glSecondaryColor3ui;

typedef void ( * PFNGLSECONDARYCOLOR3UIVPROC)(const GLuint *v);
extern PFNGLSECONDARYCOLOR3UIVPROC glad_glSecondaryColor3uiv;

typedef void ( * PFNGLSECONDARYCOLOR3USPROC)(GLushort red, GLushort green, GLushort blue);
extern PFNGLSECONDARYCOLOR3USPROC glad_glSecondaryColor3us;

typedef void ( * PFNGLSECONDARYCOLOR3USVPROC)(const GLushort *v);
extern PFNGLSECONDARYCOLOR3USVPROC glad_glSecondaryColor3usv;

typedef void ( * PFNGLSECONDARYCOLORPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const void *pointer);
extern PFNGLSECONDARYCOLORPOINTERPROC glad_glSecondaryColorPointer;

typedef void ( * PFNGLWINDOWPOS2DPROC)(GLdouble x, GLdouble y);
extern PFNGLWINDOWPOS2DPROC glad_glWindowPos2d;

typedef void ( * PFNGLWINDOWPOS2DVPROC)(const GLdouble *v);
extern PFNGLWINDOWPOS2DVPROC glad_glWindowPos2dv;

typedef void ( * PFNGLWINDOWPOS2FPROC)(GLfloat x, GLfloat y);
extern PFNGLWINDOWPOS2FPROC glad_glWindowPos2f;

typedef void ( * PFNGLWINDOWPOS2FVPROC)(const GLfloat *v);
extern PFNGLWINDOWPOS2FVPROC glad_glWindowPos2fv;

typedef void ( * PFNGLWINDOWPOS2IPROC)(GLint x, GLint y);
extern PFNGLWINDOWPOS2IPROC glad_glWindowPos2i;

typedef void ( * PFNGLWINDOWPOS2IVPROC)(const GLint *v);
extern PFNGLWINDOWPOS2IVPROC glad_glWindowPos2iv;

typedef void ( * PFNGLWINDOWPOS2SPROC)(GLshort x, GLshort y);
extern PFNGLWINDOWPOS2SPROC glad_glWindowPos2s;

typedef void ( * PFNGLWINDOWPOS2SVPROC)(const GLshort *v);
extern PFNGLWINDOWPOS2SVPROC glad_glWindowPos2sv;

typedef void ( * PFNGLWINDOWPOS3DPROC)(GLdouble x, GLdouble y, GLdouble z);
extern PFNGLWINDOWPOS3DPROC glad_glWindowPos3d;

typedef void ( * PFNGLWINDOWPOS3DVPROC)(const GLdouble *v);
extern PFNGLWINDOWPOS3DVPROC glad_glWindowPos3dv;

typedef void ( * PFNGLWINDOWPOS3FPROC)(GLfloat x, GLfloat y, GLfloat z);
extern PFNGLWINDOWPOS3FPROC glad_glWindowPos3f;

typedef void ( * PFNGLWINDOWPOS3FVPROC)(const GLfloat *v);
extern PFNGLWINDOWPOS3FVPROC glad_glWindowPos3fv;

typedef void ( * PFNGLWINDOWPOS3IPROC)(GLint x, GLint y, GLint z);
extern PFNGLWINDOWPOS3IPROC glad_glWindowPos3i;

typedef void ( * PFNGLWINDOWPOS3IVPROC)(const GLint *v);
extern PFNGLWINDOWPOS3IVPROC glad_glWindowPos3iv;

typedef void ( * PFNGLWINDOWPOS3SPROC)(GLshort x, GLshort y, GLshort z);
extern PFNGLWINDOWPOS3SPROC glad_glWindowPos3s;

typedef void ( * PFNGLWINDOWPOS3SVPROC)(const GLshort *v);
extern PFNGLWINDOWPOS3SVPROC glad_glWindowPos3sv;

typedef void ( * PFNGLBLENDCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern PFNGLBLENDCOLORPROC glad_glBlendColor;

typedef void ( * PFNGLBLENDEQUATIONPROC)(GLenum mode);
extern PFNGLBLENDEQUATIONPROC glad_glBlendEquation;




extern int GLAD_GL_VERSION_1_5;
typedef void ( * PFNGLGENQUERIESPROC)(GLsizei n, GLuint *ids);
extern PFNGLGENQUERIESPROC glad_glGenQueries;

typedef void ( * PFNGLDELETEQUERIESPROC)(GLsizei n, const GLuint *ids);
extern PFNGLDELETEQUERIESPROC glad_glDeleteQueries;

typedef GLboolean ( * PFNGLISQUERYPROC)(GLuint id);
extern PFNGLISQUERYPROC glad_glIsQuery;

typedef void ( * PFNGLBEGINQUERYPROC)(GLenum target, GLuint id);
extern PFNGLBEGINQUERYPROC glad_glBeginQuery;

typedef void ( * PFNGLENDQUERYPROC)(GLenum target);
extern PFNGLENDQUERYPROC glad_glEndQuery;

typedef void ( * PFNGLGETQUERYIVPROC)(GLenum target, GLenum pname, GLint *params);
extern PFNGLGETQUERYIVPROC glad_glGetQueryiv;

typedef void ( * PFNGLGETQUERYOBJECTIVPROC)(GLuint id, GLenum pname, GLint *params);
extern PFNGLGETQUERYOBJECTIVPROC glad_glGetQueryObjectiv;

typedef void ( * PFNGLGETQUERYOBJECTUIVPROC)(GLuint id, GLenum pname, GLuint *params);
extern PFNGLGETQUERYOBJECTUIVPROC glad_glGetQueryObjectuiv;

typedef void ( * PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
extern PFNGLBINDBUFFERPROC glad_glBindBuffer;

typedef void ( * PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint *buffers);
extern PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers;

typedef void ( * PFNGLGENBUFFERSPROC)(GLsizei n, GLuint *buffers);
extern PFNGLGENBUFFERSPROC glad_glGenBuffers;

typedef GLboolean ( * PFNGLISBUFFERPROC)(GLuint buffer);
extern PFNGLISBUFFERPROC glad_glIsBuffer;

typedef void ( * PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
extern PFNGLBUFFERDATAPROC glad_glBufferData;

typedef void ( * PFNGLBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
extern PFNGLBUFFERSUBDATAPROC glad_glBufferSubData;

typedef void ( * PFNGLGETBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, void *data);
extern PFNGLGETBUFFERSUBDATAPROC glad_glGetBufferSubData;

typedef void * ( * PFNGLMAPBUFFERPROC)(GLenum target, GLenum access);
extern PFNGLMAPBUFFERPROC glad_glMapBuffer;

typedef GLboolean ( * PFNGLUNMAPBUFFERPROC)(GLenum target);
extern PFNGLUNMAPBUFFERPROC glad_glUnmapBuffer;

typedef void ( * PFNGLGETBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
extern PFNGLGETBUFFERPARAMETERIVPROC glad_glGetBufferParameteriv;

typedef void ( * PFNGLGETBUFFERPOINTERVPROC)(GLenum target, GLenum pname, void **params);
extern PFNGLGETBUFFERPOINTERVPROC glad_glGetBufferPointerv;




extern int GLAD_GL_VERSION_2_0;
typedef void ( * PFNGLBLENDEQUATIONSEPARATEPROC)(GLenum modeRGB, GLenum modeAlpha);
extern PFNGLBLENDEQUATIONSEPARATEPROC glad_glBlendEquationSeparate;

typedef void ( * PFNGLDRAWBUFFERSPROC)(GLsizei n, const GLenum *bufs);
extern PFNGLDRAWBUFFERSPROC glad_glDrawBuffers;

typedef void ( * PFNGLSTENCILOPSEPARATEPROC)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
extern PFNGLSTENCILOPSEPARATEPROC glad_glStencilOpSeparate;

typedef void ( * PFNGLSTENCILFUNCSEPARATEPROC)(GLenum face, GLenum func, GLint ref, GLuint mask);
extern PFNGLSTENCILFUNCSEPARATEPROC glad_glStencilFuncSeparate;

typedef void ( * PFNGLSTENCILMASKSEPARATEPROC)(GLenum face, GLuint mask);
extern PFNGLSTENCILMASKSEPARATEPROC glad_glStencilMaskSeparate;

typedef void ( * PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
extern PFNGLATTACHSHADERPROC glad_glAttachShader;

typedef void ( * PFNGLBINDATTRIBLOCATIONPROC)(GLuint program, GLuint index, const GLchar *name);
extern PFNGLBINDATTRIBLOCATIONPROC glad_glBindAttribLocation;

typedef void ( * PFNGLCOMPILESHADERPROC)(GLuint shader);
extern PFNGLCOMPILESHADERPROC glad_glCompileShader;

typedef GLuint ( * PFNGLCREATEPROGRAMPROC)(void);
extern PFNGLCREATEPROGRAMPROC glad_glCreateProgram;

typedef GLuint ( * PFNGLCREATESHADERPROC)(GLenum type);
extern PFNGLCREATESHADERPROC glad_glCreateShader;

typedef void ( * PFNGLDELETEPROGRAMPROC)(GLuint program);
extern PFNGLDELETEPROGRAMPROC glad_glDeleteProgram;

typedef void ( * PFNGLDELETESHADERPROC)(GLuint shader);
extern PFNGLDELETESHADERPROC glad_glDeleteShader;

typedef void ( * PFNGLDETACHSHADERPROC)(GLuint program, GLuint shader);
extern PFNGLDETACHSHADERPROC glad_glDetachShader;

typedef void ( * PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint index);
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_glDisableVertexAttribArray;

typedef void ( * PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray;

typedef void ( * PFNGLGETACTIVEATTRIBPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
extern PFNGLGETACTIVEATTRIBPROC glad_glGetActiveAttrib;

typedef void ( * PFNGLGETACTIVEUNIFORMPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
extern PFNGLGETACTIVEUNIFORMPROC glad_glGetActiveUniform;

typedef void ( * PFNGLGETATTACHEDSHADERSPROC)(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders);
extern PFNGLGETATTACHEDSHADERSPROC glad_glGetAttachedShaders;

typedef GLint ( * PFNGLGETATTRIBLOCATIONPROC)(GLuint program, const GLchar *name);
extern PFNGLGETATTRIBLOCATIONPROC glad_glGetAttribLocation;

typedef void ( * PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint *params);
extern PFNGLGETPROGRAMIVPROC glad_glGetProgramiv;

typedef void ( * PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
extern PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog;

typedef void ( * PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint *params);
extern PFNGLGETSHADERIVPROC glad_glGetShaderiv;

typedef void ( * PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
extern PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog;

typedef void ( * PFNGLGETSHADERSOURCEPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
extern PFNGLGETSHADERSOURCEPROC glad_glGetShaderSource;

typedef GLint ( * PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar *name);
extern PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation;

typedef void ( * PFNGLGETUNIFORMFVPROC)(GLuint program, GLint location, GLfloat *params);
extern PFNGLGETUNIFORMFVPROC glad_glGetUniformfv;

typedef void ( * PFNGLGETUNIFORMIVPROC)(GLuint program, GLint location, GLint *params);
extern PFNGLGETUNIFORMIVPROC glad_glGetUniformiv;

typedef void ( * PFNGLGETVERTEXATTRIBDVPROC)(GLuint index, GLenum pname, GLdouble *params);
extern PFNGLGETVERTEXATTRIBDVPROC glad_glGetVertexAttribdv;

typedef void ( * PFNGLGETVERTEXATTRIBFVPROC)(GLuint index, GLenum pname, GLfloat *params);
extern PFNGLGETVERTEXATTRIBFVPROC glad_glGetVertexAttribfv;

typedef void ( * PFNGLGETVERTEXATTRIBIVPROC)(GLuint index, GLenum pname, GLint *params);
extern PFNGLGETVERTEXATTRIBIVPROC glad_glGetVertexAttribiv;

typedef void ( * PFNGLGETVERTEXATTRIBPOINTERVPROC)(GLuint index, GLenum pname, void **pointer);
extern PFNGLGETVERTEXATTRIBPOINTERVPROC glad_glGetVertexAttribPointerv;

typedef GLboolean ( * PFNGLISPROGRAMPROC)(GLuint program);
extern PFNGLISPROGRAMPROC glad_glIsProgram;

typedef GLboolean ( * PFNGLISSHADERPROC)(GLuint shader);
extern PFNGLISSHADERPROC glad_glIsShader;

typedef void ( * PFNGLLINKPROGRAMPROC)(GLuint program);
extern PFNGLLINKPROGRAMPROC glad_glLinkProgram;

typedef void ( * PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
extern PFNGLSHADERSOURCEPROC glad_glShaderSource;

typedef void ( * PFNGLUSEPROGRAMPROC)(GLuint program);
extern PFNGLUSEPROGRAMPROC glad_glUseProgram;

typedef void ( * PFNGLUNIFORM1FPROC)(GLint location, GLfloat v0);
extern PFNGLUNIFORM1FPROC glad_glUniform1f;

typedef void ( * PFNGLUNIFORM2FPROC)(GLint location, GLfloat v0, GLfloat v1);
extern PFNGLUNIFORM2FPROC glad_glUniform2f;

typedef void ( * PFNGLUNIFORM3FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
extern PFNGLUNIFORM3FPROC glad_glUniform3f;

typedef void ( * PFNGLUNIFORM4FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
extern PFNGLUNIFORM4FPROC glad_glUniform4f;

typedef void ( * PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
extern PFNGLUNIFORM1IPROC glad_glUniform1i;

typedef void ( * PFNGLUNIFORM2IPROC)(GLint location, GLint v0, GLint v1);
extern PFNGLUNIFORM2IPROC glad_glUniform2i;

typedef void ( * PFNGLUNIFORM3IPROC)(GLint location, GLint v0, GLint v1, GLint v2);
extern PFNGLUNIFORM3IPROC glad_glUniform3i;

typedef void ( * PFNGLUNIFORM4IPROC)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
extern PFNGLUNIFORM4IPROC glad_glUniform4i;

typedef void ( * PFNGLUNIFORM1FVPROC)(GLint location, GLsizei count, const GLfloat *value);
extern PFNGLUNIFORM1FVPROC glad_glUniform1fv;

typedef void ( * PFNGLUNIFORM2FVPROC)(GLint location, GLsizei count, const GLfloat *value);
extern PFNGLUNIFORM2FVPROC glad_glUniform2fv;

typedef void ( * PFNGLUNIFORM3FVPROC)(GLint location, GLsizei count, const GLfloat *value);
extern PFNGLUNIFORM3FVPROC glad_glUniform3fv;

typedef void ( * PFNGLUNIFORM4FVPROC)(GLint location, GLsizei count, const GLfloat *value);
extern PFNGLUNIFORM4FVPROC glad_glUniform4fv;

typedef void ( * PFNGLUNIFORM1IVPROC)(GLint location, GLsizei count, const GLint *value);
extern PFNGLUNIFORM1IVPROC glad_glUniform1iv;

typedef void ( * PFNGLUNIFORM2IVPROC)(GLint location, GLsizei count, const GLint *value);
extern PFNGLUNIFORM2IVPROC glad_glUniform2iv;

typedef void ( * PFNGLUNIFORM3IVPROC)(GLint location, GLsizei count, const GLint *value);
extern PFNGLUNIFORM3IVPROC glad_glUniform3iv;

typedef void ( * PFNGLUNIFORM4IVPROC)(GLint location, GLsizei count, const GLint *value);
extern PFNGLUNIFORM4IVPROC glad_glUniform4iv;

typedef void ( * PFNGLUNIFORMMATRIX2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern PFNGLUNIFORMMATRIX2FVPROC glad_glUniformMatrix2fv;

typedef void ( * PFNGLUNIFORMMATRIX3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern PFNGLUNIFORMMATRIX3FVPROC glad_glUniformMatrix3fv;

typedef void ( * PFNGLUNIFORMMATRIX4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv;

typedef void ( * PFNGLVALIDATEPROGRAMPROC)(GLuint program);
extern PFNGLVALIDATEPROGRAMPROC glad_glValidateProgram;

typedef void ( * PFNGLVERTEXATTRIB1DPROC)(GLuint index, GLdouble x);
extern PFNGLVERTEXATTRIB1DPROC glad_glVertexAttrib1d;

typedef void ( * PFNGLVERTEXATTRIB1DVPROC)(GLuint index, const GLdouble *v);
extern PFNGLVERTEXATTRIB1DVPROC glad_glVertexAttrib1dv;

typedef void ( * PFNGLVERTEXATTRIB1FPROC)(GLuint index, GLfloat x);
extern PFNGLVERTEXATTRIB1FPROC glad_glVertexAttrib1f;

typedef void ( * PFNGLVERTEXATTRIB1FVPROC)(GLuint index, const GLfloat *v);
extern PFNGLVERTEXATTRIB1FVPROC glad_glVertexAttrib1fv;

typedef void ( * PFNGLVERTEXATTRIB1SPROC)(GLuint index, GLshort x);
extern PFNGLVERTEXATTRIB1SPROC glad_glVertexAttrib1s;

typedef void ( * PFNGLVERTEXATTRIB1SVPROC)(GLuint index, const GLshort *v);
extern PFNGLVERTEXATTRIB1SVPROC glad_glVertexAttrib1sv;

typedef void ( * PFNGLVERTEXATTRIB2DPROC)(GLuint index, GLdouble x, GLdouble y);
extern PFNGLVERTEXATTRIB2DPROC glad_glVertexAttrib2d;

typedef void ( * PFNGLVERTEXATTRIB2DVPROC)(GLuint index, const GLdouble *v);
extern PFNGLVERTEXATTRIB2DVPROC glad_glVertexAttrib2dv;

typedef void ( * PFNGLVERTEXATTRIB2FPROC)(GLuint index, GLfloat x, GLfloat y);
extern PFNGLVERTEXATTRIB2FPROC glad_glVertexAttrib2f;

typedef void ( * PFNGLVERTEXATTRIB2FVPROC)(GLuint index, const GLfloat *v);
extern PFNGLVERTEXATTRIB2FVPROC glad_glVertexAttrib2fv;

typedef void ( * PFNGLVERTEXATTRIB2SPROC)(GLuint index, GLshort x, GLshort y);
extern PFNGLVERTEXATTRIB2SPROC glad_glVertexAttrib2s;

typedef void ( * PFNGLVERTEXATTRIB2SVPROC)(GLuint index, const GLshort *v);
extern PFNGLVERTEXATTRIB2SVPROC glad_glVertexAttrib2sv;

typedef void ( * PFNGLVERTEXATTRIB3DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
extern PFNGLVERTEXATTRIB3DPROC glad_glVertexAttrib3d;

typedef void ( * PFNGLVERTEXATTRIB3DVPROC)(GLuint index, const GLdouble *v);
extern PFNGLVERTEXATTRIB3DVPROC glad_glVertexAttrib3dv;

typedef void ( * PFNGLVERTEXATTRIB3FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
extern PFNGLVERTEXATTRIB3FPROC glad_glVertexAttrib3f;

typedef void ( * PFNGLVERTEXATTRIB3FVPROC)(GLuint index, const GLfloat *v);
extern PFNGLVERTEXATTRIB3FVPROC glad_glVertexAttrib3fv;

typedef void ( * PFNGLVERTEXATTRIB3SPROC)(GLuint index, GLshort x, GLshort y, GLshort z);
extern PFNGLVERTEXATTRIB3SPROC glad_glVertexAttrib3s;

typedef void ( * PFNGLVERTEXATTRIB3SVPROC)(GLuint index, const GLshort *v);
extern PFNGLVERTEXATTRIB3SVPROC glad_glVertexAttrib3sv;

typedef void ( * PFNGLVERTEXATTRIB4NBVPROC)(GLuint index, const GLbyte *v);
extern PFNGLVERTEXATTRIB4NBVPROC glad_glVertexAttrib4Nbv;

typedef void ( * PFNGLVERTEXATTRIB4NIVPROC)(GLuint index, const GLint *v);
extern PFNGLVERTEXATTRIB4NIVPROC glad_glVertexAttrib4Niv;

typedef void ( * PFNGLVERTEXATTRIB4NSVPROC)(GLuint index, const GLshort *v);
extern PFNGLVERTEXATTRIB4NSVPROC glad_glVertexAttrib4Nsv;

typedef void ( * PFNGLVERTEXATTRIB4NUBPROC)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
extern PFNGLVERTEXATTRIB4NUBPROC glad_glVertexAttrib4Nub;

typedef void ( * PFNGLVERTEXATTRIB4NUBVPROC)(GLuint index, const GLubyte *v);
extern PFNGLVERTEXATTRIB4NUBVPROC glad_glVertexAttrib4Nubv;

typedef void ( * PFNGLVERTEXATTRIB4NUIVPROC)(GLuint index, const GLuint *v);
extern PFNGLVERTEXATTRIB4NUIVPROC glad_glVertexAttrib4Nuiv;

typedef void ( * PFNGLVERTEXATTRIB4NUSVPROC)(GLuint index, const GLushort *v);
extern PFNGLVERTEXATTRIB4NUSVPROC glad_glVertexAttrib4Nusv;

typedef void ( * PFNGLVERTEXATTRIB4BVPROC)(GLuint index, const GLbyte *v);
extern PFNGLVERTEXATTRIB4BVPROC glad_glVertexAttrib4bv;

typedef void ( * PFNGLVERTEXATTRIB4DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
extern PFNGLVERTEXATTRIB4DPROC glad_glVertexAttrib4d;

typedef void ( * PFNGLVERTEXATTRIB4DVPROC)(GLuint index, const GLdouble *v);
extern PFNGLVERTEXATTRIB4DVPROC glad_glVertexAttrib4dv;

typedef void ( * PFNGLVERTEXATTRIB4FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
extern PFNGLVERTEXATTRIB4FPROC glad_glVertexAttrib4f;

typedef void ( * PFNGLVERTEXATTRIB4FVPROC)(GLuint index, const GLfloat *v);
extern PFNGLVERTEXATTRIB4FVPROC glad_glVertexAttrib4fv;

typedef void ( * PFNGLVERTEXATTRIB4IVPROC)(GLuint index, const GLint *v);
extern PFNGLVERTEXATTRIB4IVPROC glad_glVertexAttrib4iv;

typedef void ( * PFNGLVERTEXATTRIB4SPROC)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
extern PFNGLVERTEXATTRIB4SPROC glad_glVertexAttrib4s;

typedef void ( * PFNGLVERTEXATTRIB4SVPROC)(GLuint index, const GLshort *v);
extern PFNGLVERTEXATTRIB4SVPROC glad_glVertexAttrib4sv;

typedef void ( * PFNGLVERTEXATTRIB4UBVPROC)(GLuint index, const GLubyte *v);
extern PFNGLVERTEXATTRIB4UBVPROC glad_glVertexAttrib4ubv;

typedef void ( * PFNGLVERTEXATTRIB4UIVPROC)(GLuint index, const GLuint *v);
extern PFNGLVERTEXATTRIB4UIVPROC glad_glVertexAttrib4uiv;

typedef void ( * PFNGLVERTEXATTRIB4USVPROC)(GLuint index, const GLushort *v);
extern PFNGLVERTEXATTRIB4USVPROC glad_glVertexAttrib4usv;

typedef void ( * PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
extern PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer;




extern int GLAD_GL_VERSION_2_1;
typedef void ( * PFNGLUNIFORMMATRIX2X3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern PFNGLUNIFORMMATRIX2X3FVPROC glad_glUniformMatrix2x3fv;

typedef void ( * PFNGLUNIFORMMATRIX3X2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern PFNGLUNIFORMMATRIX3X2FVPROC glad_glUniformMatrix3x2fv;

typedef void ( * PFNGLUNIFORMMATRIX2X4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern PFNGLUNIFORMMATRIX2X4FVPROC glad_glUniformMatrix2x4fv;

typedef void ( * PFNGLUNIFORMMATRIX4X2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern PFNGLUNIFORMMATRIX4X2FVPROC glad_glUniformMatrix4x2fv;

typedef void ( * PFNGLUNIFORMMATRIX3X4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern PFNGLUNIFORMMATRIX3X4FVPROC glad_glUniformMatrix3x4fv;

typedef void ( * PFNGLUNIFORMMATRIX4X3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern PFNGLUNIFORMMATRIX4X3FVPROC glad_glUniformMatrix4x3fv;




extern int GLAD_GL_VERSION_3_0;
typedef void ( * PFNGLCOLORMASKIPROC)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
extern PFNGLCOLORMASKIPROC glad_glColorMaski;

typedef void ( * PFNGLGETBOOLEANI_VPROC)(GLenum target, GLuint index, GLboolean *data);
extern PFNGLGETBOOLEANI_VPROC glad_glGetBooleani_v;

typedef void ( * PFNGLGETINTEGERI_VPROC)(GLenum target, GLuint index, GLint *data);
extern PFNGLGETINTEGERI_VPROC glad_glGetIntegeri_v;

typedef void ( * PFNGLENABLEIPROC)(GLenum target, GLuint index);
extern PFNGLENABLEIPROC glad_glEnablei;

typedef void ( * PFNGLDISABLEIPROC)(GLenum target, GLuint index);
extern PFNGLDISABLEIPROC glad_glDisablei;

typedef GLboolean ( * PFNGLISENABLEDIPROC)(GLenum target, GLuint index);
extern PFNGLISENABLEDIPROC glad_glIsEnabledi;

typedef void ( * PFNGLBEGINTRANSFORMFEEDBACKPROC)(GLenum primitiveMode);
extern PFNGLBEGINTRANSFORMFEEDBACKPROC glad_glBeginTransformFeedback;

typedef void ( * PFNGLENDTRANSFORMFEEDBACKPROC)(void);
extern PFNGLENDTRANSFORMFEEDBACKPROC glad_glEndTransformFeedback;

typedef void ( * PFNGLBINDBUFFERRANGEPROC)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
extern PFNGLBINDBUFFERRANGEPROC glad_glBindBufferRange;

typedef void ( * PFNGLBINDBUFFERBASEPROC)(GLenum target, GLuint index, GLuint buffer);
extern PFNGLBINDBUFFERBASEPROC glad_glBindBufferBase;

typedef void ( * PFNGLTRANSFORMFEEDBACKVARYINGSPROC)(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode);
extern PFNGLTRANSFORMFEEDBACKVARYINGSPROC glad_glTransformFeedbackVaryings;

typedef void ( * PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
extern PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glad_glGetTransformFeedbackVarying;

typedef void ( * PFNGLCLAMPCOLORPROC)(GLenum target, GLenum clamp);
extern PFNGLCLAMPCOLORPROC glad_glClampColor;

typedef void ( * PFNGLBEGINCONDITIONALRENDERPROC)(GLuint id, GLenum mode);
extern PFNGLBEGINCONDITIONALRENDERPROC glad_glBeginConditionalRender;

typedef void ( * PFNGLENDCONDITIONALRENDERPROC)(void);
extern PFNGLENDCONDITIONALRENDERPROC glad_glEndConditionalRender;

typedef void ( * PFNGLVERTEXATTRIBIPOINTERPROC)(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
extern PFNGLVERTEXATTRIBIPOINTERPROC glad_glVertexAttribIPointer;

typedef void ( * PFNGLGETVERTEXATTRIBIIVPROC)(GLuint index, GLenum pname, GLint *params);
extern PFNGLGETVERTEXATTRIBIIVPROC glad_glGetVertexAttribIiv;

typedef void ( * PFNGLGETVERTEXATTRIBIUIVPROC)(GLuint index, GLenum pname, GLuint *params);
extern PFNGLGETVERTEXATTRIBIUIVPROC glad_glGetVertexAttribIuiv;

typedef void ( * PFNGLVERTEXATTRIBI1IPROC)(GLuint index, GLint x);
extern PFNGLVERTEXATTRIBI1IPROC glad_glVertexAttribI1i;

typedef void ( * PFNGLVERTEXATTRIBI2IPROC)(GLuint index, GLint x, GLint y);
extern PFNGLVERTEXATTRIBI2IPROC glad_glVertexAttribI2i;

typedef void ( * PFNGLVERTEXATTRIBI3IPROC)(GLuint index, GLint x, GLint y, GLint z);
extern PFNGLVERTEXATTRIBI3IPROC glad_glVertexAttribI3i;

typedef void ( * PFNGLVERTEXATTRIBI4IPROC)(GLuint index, GLint x, GLint y, GLint z, GLint w);
extern PFNGLVERTEXATTRIBI4IPROC glad_glVertexAttribI4i;

typedef void ( * PFNGLVERTEXATTRIBI1UIPROC)(GLuint index, GLuint x);
extern PFNGLVERTEXATTRIBI1UIPROC glad_glVertexAttribI1ui;

typedef void ( * PFNGLVERTEXATTRIBI2UIPROC)(GLuint index, GLuint x, GLuint y);
extern PFNGLVERTEXATTRIBI2UIPROC glad_glVertexAttribI2ui;

typedef void ( * PFNGLVERTEXATTRIBI3UIPROC)(GLuint index, GLuint x, GLuint y, GLuint z);
extern PFNGLVERTEXATTRIBI3UIPROC glad_glVertexAttribI3ui;

typedef void ( * PFNGLVERTEXATTRIBI4UIPROC)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
extern PFNGLVERTEXATTRIBI4UIPROC glad_glVertexAttribI4ui;

typedef void ( * PFNGLVERTEXATTRIBI1IVPROC)(GLuint index, const GLint *v);
extern PFNGLVERTEXATTRIBI1IVPROC glad_glVertexAttribI1iv;

typedef void ( * PFNGLVERTEXATTRIBI2IVPROC)(GLuint index, const GLint *v);
extern PFNGLVERTEXATTRIBI2IVPROC glad_glVertexAttribI2iv;

typedef void ( * PFNGLVERTEXATTRIBI3IVPROC)(GLuint index, const GLint *v);
extern PFNGLVERTEXATTRIBI3IVPROC glad_glVertexAttribI3iv;

typedef void ( * PFNGLVERTEXATTRIBI4IVPROC)(GLuint index, const GLint *v);
extern PFNGLVERTEXATTRIBI4IVPROC glad_glVertexAttribI4iv;

typedef void ( * PFNGLVERTEXATTRIBI1UIVPROC)(GLuint index, const GLuint *v);
extern PFNGLVERTEXATTRIBI1UIVPROC glad_glVertexAttribI1uiv;

typedef void ( * PFNGLVERTEXATTRIBI2UIVPROC)(GLuint index, const GLuint *v);
extern PFNGLVERTEXATTRIBI2UIVPROC glad_glVertexAttribI2uiv;

typedef void ( * PFNGLVERTEXATTRIBI3UIVPROC)(GLuint index, const GLuint *v);
extern PFNGLVERTEXATTRIBI3UIVPROC glad_glVertexAttribI3uiv;

typedef void ( * PFNGLVERTEXATTRIBI4UIVPROC)(GLuint index, const GLuint *v);
extern PFNGLVERTEXATTRIBI4UIVPROC glad_glVertexAttribI4uiv;

typedef void ( * PFNGLVERTEXATTRIBI4BVPROC)(GLuint index, const GLbyte *v);
extern PFNGLVERTEXATTRIBI4BVPROC glad_glVertexAttribI4bv;

typedef void ( * PFNGLVERTEXATTRIBI4SVPROC)(GLuint index, const GLshort *v);
extern PFNGLVERTEXATTRIBI4SVPROC glad_glVertexAttribI4sv;

typedef void ( * PFNGLVERTEXATTRIBI4UBVPROC)(GLuint index, const GLubyte *v);
extern PFNGLVERTEXATTRIBI4UBVPROC glad_glVertexAttribI4ubv;

typedef void ( * PFNGLVERTEXATTRIBI4USVPROC)(GLuint index, const GLushort *v);
extern PFNGLVERTEXATTRIBI4USVPROC glad_glVertexAttribI4usv;

typedef void ( * PFNGLGETUNIFORMUIVPROC)(GLuint program, GLint location, GLuint *params);
extern PFNGLGETUNIFORMUIVPROC glad_glGetUniformuiv;

typedef void ( * PFNGLBINDFRAGDATALOCATIONPROC)(GLuint program, GLuint color, const GLchar *name);
extern PFNGLBINDFRAGDATALOCATIONPROC glad_glBindFragDataLocation;

typedef GLint ( * PFNGLGETFRAGDATALOCATIONPROC)(GLuint program, const GLchar *name);
extern PFNGLGETFRAGDATALOCATIONPROC glad_glGetFragDataLocation;

typedef void ( * PFNGLUNIFORM1UIPROC)(GLint location, GLuint v0);
extern PFNGLUNIFORM1UIPROC glad_glUniform1ui;

typedef void ( * PFNGLUNIFORM2UIPROC)(GLint location, GLuint v0, GLuint v1);
extern PFNGLUNIFORM2UIPROC glad_glUniform2ui;

typedef void ( * PFNGLUNIFORM3UIPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2);
extern PFNGLUNIFORM3UIPROC glad_glUniform3ui;

typedef void ( * PFNGLUNIFORM4UIPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
extern PFNGLUNIFORM4UIPROC glad_glUniform4ui;

typedef void ( * PFNGLUNIFORM1UIVPROC)(GLint location, GLsizei count, const GLuint *value);
extern PFNGLUNIFORM1UIVPROC glad_glUniform1uiv;

typedef void ( * PFNGLUNIFORM2UIVPROC)(GLint location, GLsizei count, const GLuint *value);
extern PFNGLUNIFORM2UIVPROC glad_glUniform2uiv;

typedef void ( * PFNGLUNIFORM3UIVPROC)(GLint location, GLsizei count, const GLuint *value);
extern PFNGLUNIFORM3UIVPROC glad_glUniform3uiv;

typedef void ( * PFNGLUNIFORM4UIVPROC)(GLint location, GLsizei count, const GLuint *value);
extern PFNGLUNIFORM4UIVPROC glad_glUniform4uiv;

typedef void ( * PFNGLTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, const GLint *params);
extern PFNGLTEXPARAMETERIIVPROC glad_glTexParameterIiv;

typedef void ( * PFNGLTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, const GLuint *params);
extern PFNGLTEXPARAMETERIUIVPROC glad_glTexParameterIuiv;

typedef void ( * PFNGLGETTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, GLint *params);
extern PFNGLGETTEXPARAMETERIIVPROC glad_glGetTexParameterIiv;

typedef void ( * PFNGLGETTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, GLuint *params);
extern PFNGLGETTEXPARAMETERIUIVPROC glad_glGetTexParameterIuiv;

typedef void ( * PFNGLCLEARBUFFERIVPROC)(GLenum buffer, GLint drawbuffer, const GLint *value);
extern PFNGLCLEARBUFFERIVPROC glad_glClearBufferiv;

typedef void ( * PFNGLCLEARBUFFERUIVPROC)(GLenum buffer, GLint drawbuffer, const GLuint *value);
extern PFNGLCLEARBUFFERUIVPROC glad_glClearBufferuiv;

typedef void ( * PFNGLCLEARBUFFERFVPROC)(GLenum buffer, GLint drawbuffer, const GLfloat *value);
extern PFNGLCLEARBUFFERFVPROC glad_glClearBufferfv;

typedef void ( * PFNGLCLEARBUFFERFIPROC)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
extern PFNGLCLEARBUFFERFIPROC glad_glClearBufferfi;

typedef const GLubyte * ( * PFNGLGETSTRINGIPROC)(GLenum name, GLuint index);
extern PFNGLGETSTRINGIPROC glad_glGetStringi;

typedef GLboolean ( * PFNGLISRENDERBUFFERPROC)(GLuint renderbuffer);
extern PFNGLISRENDERBUFFERPROC glad_glIsRenderbuffer;

typedef void ( * PFNGLBINDRENDERBUFFERPROC)(GLenum target, GLuint renderbuffer);
extern PFNGLBINDRENDERBUFFERPROC glad_glBindRenderbuffer;

typedef void ( * PFNGLDELETERENDERBUFFERSPROC)(GLsizei n, const GLuint *renderbuffers);
extern PFNGLDELETERENDERBUFFERSPROC glad_glDeleteRenderbuffers;

typedef void ( * PFNGLGENRENDERBUFFERSPROC)(GLsizei n, GLuint *renderbuffers);
extern PFNGLGENRENDERBUFFERSPROC glad_glGenRenderbuffers;

typedef void ( * PFNGLRENDERBUFFERSTORAGEPROC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
extern PFNGLRENDERBUFFERSTORAGEPROC glad_glRenderbufferStorage;

typedef void ( * PFNGLGETRENDERBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
extern PFNGLGETRENDERBUFFERPARAMETERIVPROC glad_glGetRenderbufferParameteriv;

typedef GLboolean ( * PFNGLISFRAMEBUFFERPROC)(GLuint framebuffer);
extern PFNGLISFRAMEBUFFERPROC glad_glIsFramebuffer;

typedef void ( * PFNGLBINDFRAMEBUFFERPROC)(GLenum target, GLuint framebuffer);
extern PFNGLBINDFRAMEBUFFERPROC glad_glBindFramebuffer;

typedef void ( * PFNGLDELETEFRAMEBUFFERSPROC)(GLsizei n, const GLuint *framebuffers);
extern PFNGLDELETEFRAMEBUFFERSPROC glad_glDeleteFramebuffers;

typedef void ( * PFNGLGENFRAMEBUFFERSPROC)(GLsizei n, GLuint *framebuffers);
extern PFNGLGENFRAMEBUFFERSPROC glad_glGenFramebuffers;

typedef GLenum ( * PFNGLCHECKFRAMEBUFFERSTATUSPROC)(GLenum target);
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC glad_glCheckFramebufferStatus;

typedef void ( * PFNGLFRAMEBUFFERTEXTURE1DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
extern PFNGLFRAMEBUFFERTEXTURE1DPROC glad_glFramebufferTexture1D;

typedef void ( * PFNGLFRAMEBUFFERTEXTURE2DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
extern PFNGLFRAMEBUFFERTEXTURE2DPROC glad_glFramebufferTexture2D;

typedef void ( * PFNGLFRAMEBUFFERTEXTURE3DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
extern PFNGLFRAMEBUFFERTEXTURE3DPROC glad_glFramebufferTexture3D;

typedef void ( * PFNGLFRAMEBUFFERRENDERBUFFERPROC)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC glad_glFramebufferRenderbuffer;

typedef void ( * PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLenum target, GLenum attachment, GLenum pname, GLint *params);
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glad_glGetFramebufferAttachmentParameteriv;

typedef void ( * PFNGLGENERATEMIPMAPPROC)(GLenum target);
extern PFNGLGENERATEMIPMAPPROC glad_glGenerateMipmap;

typedef void ( * PFNGLBLITFRAMEBUFFERPROC)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
extern PFNGLBLITFRAMEBUFFERPROC glad_glBlitFramebuffer;

typedef void ( * PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glad_glRenderbufferStorageMultisample;

typedef void ( * PFNGLFRAMEBUFFERTEXTURELAYERPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
extern PFNGLFRAMEBUFFERTEXTURELAYERPROC glad_glFramebufferTextureLayer;

typedef void * ( * PFNGLMAPBUFFERRANGEPROC)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
extern PFNGLMAPBUFFERRANGEPROC glad_glMapBufferRange;

typedef void ( * PFNGLFLUSHMAPPEDBUFFERRANGEPROC)(GLenum target, GLintptr offset, GLsizeiptr length);
extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC glad_glFlushMappedBufferRange;

typedef void ( * PFNGLBINDVERTEXARRAYPROC)(GLuint array);
extern PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray;

typedef void ( * PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint *arrays);
extern PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays;

typedef void ( * PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint *arrays);
extern PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays;

typedef GLboolean ( * PFNGLISVERTEXARRAYPROC)(GLuint array);
extern PFNGLISVERTEXARRAYPROC glad_glIsVertexArray;




extern int GLAD_GL_VERSION_3_1;
typedef void ( * PFNGLDRAWARRAYSINSTANCEDPROC)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
extern PFNGLDRAWARRAYSINSTANCEDPROC glad_glDrawArraysInstanced;

typedef void ( * PFNGLDRAWELEMENTSINSTANCEDPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount);
extern PFNGLDRAWELEMENTSINSTANCEDPROC glad_glDrawElementsInstanced;

typedef void ( * PFNGLTEXBUFFERPROC)(GLenum target, GLenum internalformat, GLuint buffer);
extern PFNGLTEXBUFFERPROC glad_glTexBuffer;

typedef void ( * PFNGLPRIMITIVERESTARTINDEXPROC)(GLuint index);
extern PFNGLPRIMITIVERESTARTINDEXPROC glad_glPrimitiveRestartIndex;

typedef void ( * PFNGLCOPYBUFFERSUBDATAPROC)(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
extern PFNGLCOPYBUFFERSUBDATAPROC glad_glCopyBufferSubData;

typedef void ( * PFNGLGETUNIFORMINDICESPROC)(GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices);
extern PFNGLGETUNIFORMINDICESPROC glad_glGetUniformIndices;

typedef void ( * PFNGLGETACTIVEUNIFORMSIVPROC)(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params);
extern PFNGLGETACTIVEUNIFORMSIVPROC glad_glGetActiveUniformsiv;

typedef void ( * PFNGLGETACTIVEUNIFORMNAMEPROC)(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName);
extern PFNGLGETACTIVEUNIFORMNAMEPROC glad_glGetActiveUniformName;

typedef GLuint ( * PFNGLGETUNIFORMBLOCKINDEXPROC)(GLuint program, const GLchar *uniformBlockName);
extern PFNGLGETUNIFORMBLOCKINDEXPROC glad_glGetUniformBlockIndex;

typedef void ( * PFNGLGETACTIVEUNIFORMBLOCKIVPROC)(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC glad_glGetActiveUniformBlockiv;

typedef void ( * PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName);
extern PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glad_glGetActiveUniformBlockName;

typedef void ( * PFNGLUNIFORMBLOCKBINDINGPROC)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
extern PFNGLUNIFORMBLOCKBINDINGPROC glad_glUniformBlockBinding;




extern int GLAD_GL_VERSION_3_2;
typedef void ( * PFNGLDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex);
extern PFNGLDRAWELEMENTSBASEVERTEXPROC glad_glDrawElementsBaseVertex;

typedef void ( * PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex);
extern PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glad_glDrawRangeElementsBaseVertex;

typedef void ( * PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex);
extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glad_glDrawElementsInstancedBaseVertex;

typedef void ( * PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const GLint *basevertex);
extern PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glad_glMultiDrawElementsBaseVertex;

typedef void ( * PFNGLPROVOKINGVERTEXPROC)(GLenum mode);
extern PFNGLPROVOKINGVERTEXPROC glad_glProvokingVertex;

typedef GLsync ( * PFNGLFENCESYNCPROC)(GLenum condition, GLbitfield flags);
extern PFNGLFENCESYNCPROC glad_glFenceSync;

typedef GLboolean ( * PFNGLISSYNCPROC)(GLsync sync);
extern PFNGLISSYNCPROC glad_glIsSync;

typedef void ( * PFNGLDELETESYNCPROC)(GLsync sync);
extern PFNGLDELETESYNCPROC glad_glDeleteSync;

typedef GLenum ( * PFNGLCLIENTWAITSYNCPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
extern PFNGLCLIENTWAITSYNCPROC glad_glClientWaitSync;

typedef void ( * PFNGLWAITSYNCPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
extern PFNGLWAITSYNCPROC glad_glWaitSync;

typedef void ( * PFNGLGETINTEGER64VPROC)(GLenum pname, GLint64 *data);
extern PFNGLGETINTEGER64VPROC glad_glGetInteger64v;

typedef void ( * PFNGLGETSYNCIVPROC)(GLsync sync, GLenum pname, GLsizei count, GLsizei *length, GLint *values);
extern PFNGLGETSYNCIVPROC glad_glGetSynciv;

typedef void ( * PFNGLGETINTEGER64I_VPROC)(GLenum target, GLuint index, GLint64 *data);
extern PFNGLGETINTEGER64I_VPROC glad_glGetInteger64i_v;

typedef void ( * PFNGLGETBUFFERPARAMETERI64VPROC)(GLenum target, GLenum pname, GLint64 *params);
extern PFNGLGETBUFFERPARAMETERI64VPROC glad_glGetBufferParameteri64v;

typedef void ( * PFNGLFRAMEBUFFERTEXTUREPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level);
extern PFNGLFRAMEBUFFERTEXTUREPROC glad_glFramebufferTexture;

typedef void ( * PFNGLTEXIMAGE2DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
extern PFNGLTEXIMAGE2DMULTISAMPLEPROC glad_glTexImage2DMultisample;

typedef void ( * PFNGLTEXIMAGE3DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
extern PFNGLTEXIMAGE3DMULTISAMPLEPROC glad_glTexImage3DMultisample;

typedef void ( * PFNGLGETMULTISAMPLEFVPROC)(GLenum pname, GLuint index, GLfloat *val);
extern PFNGLGETMULTISAMPLEFVPROC glad_glGetMultisamplefv;

typedef void ( * PFNGLSAMPLEMASKIPROC)(GLuint maskNumber, GLbitfield mask);
extern PFNGLSAMPLEMASKIPROC glad_glSampleMaski;




extern int GLAD_GL_VERSION_3_3;
typedef void ( * PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)(GLuint program, GLuint colorNumber, GLuint index, const GLchar *name);
extern PFNGLBINDFRAGDATALOCATIONINDEXEDPROC glad_glBindFragDataLocationIndexed;

typedef GLint ( * PFNGLGETFRAGDATAINDEXPROC)(GLuint program, const GLchar *name);
extern PFNGLGETFRAGDATAINDEXPROC glad_glGetFragDataIndex;

typedef void ( * PFNGLGENSAMPLERSPROC)(GLsizei count, GLuint *samplers);
extern PFNGLGENSAMPLERSPROC glad_glGenSamplers;

typedef void ( * PFNGLDELETESAMPLERSPROC)(GLsizei count, const GLuint *samplers);
extern PFNGLDELETESAMPLERSPROC glad_glDeleteSamplers;

typedef GLboolean ( * PFNGLISSAMPLERPROC)(GLuint sampler);
extern PFNGLISSAMPLERPROC glad_glIsSampler;

typedef void ( * PFNGLBINDSAMPLERPROC)(GLuint unit, GLuint sampler);
extern PFNGLBINDSAMPLERPROC glad_glBindSampler;

typedef void ( * PFNGLSAMPLERPARAMETERIPROC)(GLuint sampler, GLenum pname, GLint param);
extern PFNGLSAMPLERPARAMETERIPROC glad_glSamplerParameteri;

typedef void ( * PFNGLSAMPLERPARAMETERIVPROC)(GLuint sampler, GLenum pname, const GLint *param);
extern PFNGLSAMPLERPARAMETERIVPROC glad_glSamplerParameteriv;

typedef void ( * PFNGLSAMPLERPARAMETERFPROC)(GLuint sampler, GLenum pname, GLfloat param);
extern PFNGLSAMPLERPARAMETERFPROC glad_glSamplerParameterf;

typedef void ( * PFNGLSAMPLERPARAMETERFVPROC)(GLuint sampler, GLenum pname, const GLfloat *param);
extern PFNGLSAMPLERPARAMETERFVPROC glad_glSamplerParameterfv;

typedef void ( * PFNGLSAMPLERPARAMETERIIVPROC)(GLuint sampler, GLenum pname, const GLint *param);
extern PFNGLSAMPLERPARAMETERIIVPROC glad_glSamplerParameterIiv;

typedef void ( * PFNGLSAMPLERPARAMETERIUIVPROC)(GLuint sampler, GLenum pname, const GLuint *param);
extern PFNGLSAMPLERPARAMETERIUIVPROC glad_glSamplerParameterIuiv;

typedef void ( * PFNGLGETSAMPLERPARAMETERIVPROC)(GLuint sampler, GLenum pname, GLint *params);
extern PFNGLGETSAMPLERPARAMETERIVPROC glad_glGetSamplerParameteriv;

typedef void ( * PFNGLGETSAMPLERPARAMETERIIVPROC)(GLuint sampler, GLenum pname, GLint *params);
extern PFNGLGETSAMPLERPARAMETERIIVPROC glad_glGetSamplerParameterIiv;

typedef void ( * PFNGLGETSAMPLERPARAMETERFVPROC)(GLuint sampler, GLenum pname, GLfloat *params);
extern PFNGLGETSAMPLERPARAMETERFVPROC glad_glGetSamplerParameterfv;

typedef void ( * PFNGLGETSAMPLERPARAMETERIUIVPROC)(GLuint sampler, GLenum pname, GLuint *params);
extern PFNGLGETSAMPLERPARAMETERIUIVPROC glad_glGetSamplerParameterIuiv;

typedef void ( * PFNGLQUERYCOUNTERPROC)(GLuint id, GLenum target);
extern PFNGLQUERYCOUNTERPROC glad_glQueryCounter;

typedef void ( * PFNGLGETQUERYOBJECTI64VPROC)(GLuint id, GLenum pname, GLint64 *params);
extern PFNGLGETQUERYOBJECTI64VPROC glad_glGetQueryObjecti64v;

typedef void ( * PFNGLGETQUERYOBJECTUI64VPROC)(GLuint id, GLenum pname, GLuint64 *params);
extern PFNGLGETQUERYOBJECTUI64VPROC glad_glGetQueryObjectui64v;

typedef void ( * PFNGLVERTEXATTRIBDIVISORPROC)(GLuint index, GLuint divisor);
extern PFNGLVERTEXATTRIBDIVISORPROC glad_glVertexAttribDivisor;

typedef void ( * PFNGLVERTEXATTRIBP1UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
extern PFNGLVERTEXATTRIBP1UIPROC glad_glVertexAttribP1ui;

typedef void ( * PFNGLVERTEXATTRIBP1UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
extern PFNGLVERTEXATTRIBP1UIVPROC glad_glVertexAttribP1uiv;

typedef void ( * PFNGLVERTEXATTRIBP2UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
extern PFNGLVERTEXATTRIBP2UIPROC glad_glVertexAttribP2ui;

typedef void ( * PFNGLVERTEXATTRIBP2UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
extern PFNGLVERTEXATTRIBP2UIVPROC glad_glVertexAttribP2uiv;

typedef void ( * PFNGLVERTEXATTRIBP3UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
extern PFNGLVERTEXATTRIBP3UIPROC glad_glVertexAttribP3ui;

typedef void ( * PFNGLVERTEXATTRIBP3UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
extern PFNGLVERTEXATTRIBP3UIVPROC glad_glVertexAttribP3uiv;

typedef void ( * PFNGLVERTEXATTRIBP4UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
extern PFNGLVERTEXATTRIBP4UIPROC glad_glVertexAttribP4ui;

typedef void ( * PFNGLVERTEXATTRIBP4UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
extern PFNGLVERTEXATTRIBP4UIVPROC glad_glVertexAttribP4uiv;

typedef void ( * PFNGLVERTEXP2UIPROC)(GLenum type, GLuint value);
extern PFNGLVERTEXP2UIPROC glad_glVertexP2ui;

typedef void ( * PFNGLVERTEXP2UIVPROC)(GLenum type, const GLuint *value);
extern PFNGLVERTEXP2UIVPROC glad_glVertexP2uiv;

typedef void ( * PFNGLVERTEXP3UIPROC)(GLenum type, GLuint value);
extern PFNGLVERTEXP3UIPROC glad_glVertexP3ui;

typedef void ( * PFNGLVERTEXP3UIVPROC)(GLenum type, const GLuint *value);
extern PFNGLVERTEXP3UIVPROC glad_glVertexP3uiv;

typedef void ( * PFNGLVERTEXP4UIPROC)(GLenum type, GLuint value);
extern PFNGLVERTEXP4UIPROC glad_glVertexP4ui;

typedef void ( * PFNGLVERTEXP4UIVPROC)(GLenum type, const GLuint *value);
extern PFNGLVERTEXP4UIVPROC glad_glVertexP4uiv;

typedef void ( * PFNGLTEXCOORDP1UIPROC)(GLenum type, GLuint coords);
extern PFNGLTEXCOORDP1UIPROC glad_glTexCoordP1ui;

typedef void ( * PFNGLTEXCOORDP1UIVPROC)(GLenum type, const GLuint *coords);
extern PFNGLTEXCOORDP1UIVPROC glad_glTexCoordP1uiv;

typedef void ( * PFNGLTEXCOORDP2UIPROC)(GLenum type, GLuint coords);
extern PFNGLTEXCOORDP2UIPROC glad_glTexCoordP2ui;

typedef void ( * PFNGLTEXCOORDP2UIVPROC)(GLenum type, const GLuint *coords);
extern PFNGLTEXCOORDP2UIVPROC glad_glTexCoordP2uiv;

typedef void ( * PFNGLTEXCOORDP3UIPROC)(GLenum type, GLuint coords);
extern PFNGLTEXCOORDP3UIPROC glad_glTexCoordP3ui;

typedef void ( * PFNGLTEXCOORDP3UIVPROC)(GLenum type, const GLuint *coords);
extern PFNGLTEXCOORDP3UIVPROC glad_glTexCoordP3uiv;

typedef void ( * PFNGLTEXCOORDP4UIPROC)(GLenum type, GLuint coords);
extern PFNGLTEXCOORDP4UIPROC glad_glTexCoordP4ui;

typedef void ( * PFNGLTEXCOORDP4UIVPROC)(GLenum type, const GLuint *coords);
extern PFNGLTEXCOORDP4UIVPROC glad_glTexCoordP4uiv;

typedef void ( * PFNGLMULTITEXCOORDP1UIPROC)(GLenum texture, GLenum type, GLuint coords);
extern PFNGLMULTITEXCOORDP1UIPROC glad_glMultiTexCoordP1ui;

typedef void ( * PFNGLMULTITEXCOORDP1UIVPROC)(GLenum texture, GLenum type, const GLuint *coords);
extern PFNGLMULTITEXCOORDP1UIVPROC glad_glMultiTexCoordP1uiv;

typedef void ( * PFNGLMULTITEXCOORDP2UIPROC)(GLenum texture, GLenum type, GLuint coords);
extern PFNGLMULTITEXCOORDP2UIPROC glad_glMultiTexCoordP2ui;

typedef void ( * PFNGLMULTITEXCOORDP2UIVPROC)(GLenum texture, GLenum type, const GLuint *coords);
extern PFNGLMULTITEXCOORDP2UIVPROC glad_glMultiTexCoordP2uiv;

typedef void ( * PFNGLMULTITEXCOORDP3UIPROC)(GLenum texture, GLenum type, GLuint coords);
extern PFNGLMULTITEXCOORDP3UIPROC glad_glMultiTexCoordP3ui;

typedef void ( * PFNGLMULTITEXCOORDP3UIVPROC)(GLenum texture, GLenum type, const GLuint *coords);
extern PFNGLMULTITEXCOORDP3UIVPROC glad_glMultiTexCoordP3uiv;

typedef void ( * PFNGLMULTITEXCOORDP4UIPROC)(GLenum texture, GLenum type, GLuint coords);
extern PFNGLMULTITEXCOORDP4UIPROC glad_glMultiTexCoordP4ui;

typedef void ( * PFNGLMULTITEXCOORDP4UIVPROC)(GLenum texture, GLenum type, const GLuint *coords);
extern PFNGLMULTITEXCOORDP4UIVPROC glad_glMultiTexCoordP4uiv;

typedef void ( * PFNGLNORMALP3UIPROC)(GLenum type, GLuint coords);
extern PFNGLNORMALP3UIPROC glad_glNormalP3ui;

typedef void ( * PFNGLNORMALP3UIVPROC)(GLenum type, const GLuint *coords);
extern PFNGLNORMALP3UIVPROC glad_glNormalP3uiv;

typedef void ( * PFNGLCOLORP3UIPROC)(GLenum type, GLuint color);
extern PFNGLCOLORP3UIPROC glad_glColorP3ui;

typedef void ( * PFNGLCOLORP3UIVPROC)(GLenum type, const GLuint *color);
extern PFNGLCOLORP3UIVPROC glad_glColorP3uiv;

typedef void ( * PFNGLCOLORP4UIPROC)(GLenum type, GLuint color);
extern PFNGLCOLORP4UIPROC glad_glColorP4ui;

typedef void ( * PFNGLCOLORP4UIVPROC)(GLenum type, const GLuint *color);
extern PFNGLCOLORP4UIVPROC glad_glColorP4uiv;

typedef void ( * PFNGLSECONDARYCOLORP3UIPROC)(GLenum type, GLuint color);
extern PFNGLSECONDARYCOLORP3UIPROC glad_glSecondaryColorP3ui;

typedef void ( * PFNGLSECONDARYCOLORP3UIVPROC)(GLenum type, const GLuint *color);
extern PFNGLSECONDARYCOLORP3UIVPROC glad_glSecondaryColorP3uiv;




extern int GLAD_GL_VERSION_4_0;
typedef void ( * PFNGLMINSAMPLESHADINGPROC)(GLfloat value);
extern PFNGLMINSAMPLESHADINGPROC glad_glMinSampleShading;

typedef void ( * PFNGLBLENDEQUATIONIPROC)(GLuint buf, GLenum mode);
extern PFNGLBLENDEQUATIONIPROC glad_glBlendEquationi;

typedef void ( * PFNGLBLENDEQUATIONSEPARATEIPROC)(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
extern PFNGLBLENDEQUATIONSEPARATEIPROC glad_glBlendEquationSeparatei;

typedef void ( * PFNGLBLENDFUNCIPROC)(GLuint buf, GLenum src, GLenum dst);
extern PFNGLBLENDFUNCIPROC glad_glBlendFunci;

typedef void ( * PFNGLBLENDFUNCSEPARATEIPROC)(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
extern PFNGLBLENDFUNCSEPARATEIPROC glad_glBlendFuncSeparatei;

typedef void ( * PFNGLDRAWARRAYSINDIRECTPROC)(GLenum mode, const void *indirect);
extern PFNGLDRAWARRAYSINDIRECTPROC glad_glDrawArraysIndirect;

typedef void ( * PFNGLDRAWELEMENTSINDIRECTPROC)(GLenum mode, GLenum type, const void *indirect);
extern PFNGLDRAWELEMENTSINDIRECTPROC glad_glDrawElementsIndirect;

typedef void ( * PFNGLUNIFORM1DPROC)(GLint location, GLdouble x);
extern PFNGLUNIFORM1DPROC glad_glUniform1d;

typedef void ( * PFNGLUNIFORM2DPROC)(GLint location, GLdouble x, GLdouble y);
extern PFNGLUNIFORM2DPROC glad_glUniform2d;

typedef void ( * PFNGLUNIFORM3DPROC)(GLint location, GLdouble x, GLdouble y, GLdouble z);
extern PFNGLUNIFORM3DPROC glad_glUniform3d;

typedef void ( * PFNGLUNIFORM4DPROC)(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
extern PFNGLUNIFORM4DPROC glad_glUniform4d;

typedef void ( * PFNGLUNIFORM1DVPROC)(GLint location, GLsizei count, const GLdouble *value);
extern PFNGLUNIFORM1DVPROC glad_glUniform1dv;

typedef void ( * PFNGLUNIFORM2DVPROC)(GLint location, GLsizei count, const GLdouble *value);
extern PFNGLUNIFORM2DVPROC glad_glUniform2dv;

typedef void ( * PFNGLUNIFORM3DVPROC)(GLint location, GLsizei count, const GLdouble *value);
extern PFNGLUNIFORM3DVPROC glad_glUniform3dv;

typedef void ( * PFNGLUNIFORM4DVPROC)(GLint location, GLsizei count, const GLdouble *value);
extern PFNGLUNIFORM4DVPROC glad_glUniform4dv;

typedef void ( * PFNGLUNIFORMMATRIX2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
extern PFNGLUNIFORMMATRIX2DVPROC glad_glUniformMatrix2dv;

typedef void ( * PFNGLUNIFORMMATRIX3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
extern PFNGLUNIFORMMATRIX3DVPROC glad_glUniformMatrix3dv;

typedef void ( * PFNGLUNIFORMMATRIX4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
extern PFNGLUNIFORMMATRIX4DVPROC glad_glUniformMatrix4dv;

typedef void ( * PFNGLUNIFORMMATRIX2X3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
extern PFNGLUNIFORMMATRIX2X3DVPROC glad_glUniformMatrix2x3dv;

typedef void ( * PFNGLUNIFORMMATRIX2X4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
extern PFNGLUNIFORMMATRIX2X4DVPROC glad_glUniformMatrix2x4dv;

typedef void ( * PFNGLUNIFORMMATRIX3X2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
extern PFNGLUNIFORMMATRIX3X2DVPROC glad_glUniformMatrix3x2dv;

typedef void ( * PFNGLUNIFORMMATRIX3X4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
extern PFNGLUNIFORMMATRIX3X4DVPROC glad_glUniformMatrix3x4dv;

typedef void ( * PFNGLUNIFORMMATRIX4X2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
extern PFNGLUNIFORMMATRIX4X2DVPROC glad_glUniformMatrix4x2dv;

typedef void ( * PFNGLUNIFORMMATRIX4X3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
extern PFNGLUNIFORMMATRIX4X3DVPROC glad_glUniformMatrix4x3dv;

typedef void ( * PFNGLGETUNIFORMDVPROC)(GLuint program, GLint location, GLdouble *params);
extern PFNGLGETUNIFORMDVPROC glad_glGetUniformdv;

typedef GLint ( * PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)(GLuint program, GLenum shadertype, const GLchar *name);
extern PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC glad_glGetSubroutineUniformLocation;

typedef GLuint ( * PFNGLGETSUBROUTINEINDEXPROC)(GLuint program, GLenum shadertype, const GLchar *name);
extern PFNGLGETSUBROUTINEINDEXPROC glad_glGetSubroutineIndex;

typedef void ( * PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values);
extern PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC glad_glGetActiveSubroutineUniformiv;

typedef void ( * PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
extern PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC glad_glGetActiveSubroutineUniformName;

typedef void ( * PFNGLGETACTIVESUBROUTINENAMEPROC)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
extern PFNGLGETACTIVESUBROUTINENAMEPROC glad_glGetActiveSubroutineName;

typedef void ( * PFNGLUNIFORMSUBROUTINESUIVPROC)(GLenum shadertype, GLsizei count, const GLuint *indices);
extern PFNGLUNIFORMSUBROUTINESUIVPROC glad_glUniformSubroutinesuiv;

typedef void ( * PFNGLGETUNIFORMSUBROUTINEUIVPROC)(GLenum shadertype, GLint location, GLuint *params);
extern PFNGLGETUNIFORMSUBROUTINEUIVPROC glad_glGetUniformSubroutineuiv;

typedef void ( * PFNGLGETPROGRAMSTAGEIVPROC)(GLuint program, GLenum shadertype, GLenum pname, GLint *values);
extern PFNGLGETPROGRAMSTAGEIVPROC glad_glGetProgramStageiv;

typedef void ( * PFNGLPATCHPARAMETERIPROC)(GLenum pname, GLint value);
extern PFNGLPATCHPARAMETERIPROC glad_glPatchParameteri;

typedef void ( * PFNGLPATCHPARAMETERFVPROC)(GLenum pname, const GLfloat *values);
extern PFNGLPATCHPARAMETERFVPROC glad_glPatchParameterfv;

typedef void ( * PFNGLBINDTRANSFORMFEEDBACKPROC)(GLenum target, GLuint id);
extern PFNGLBINDTRANSFORMFEEDBACKPROC glad_glBindTransformFeedback;

typedef void ( * PFNGLDELETETRANSFORMFEEDBACKSPROC)(GLsizei n, const GLuint *ids);
extern PFNGLDELETETRANSFORMFEEDBACKSPROC glad_glDeleteTransformFeedbacks;

typedef void ( * PFNGLGENTRANSFORMFEEDBACKSPROC)(GLsizei n, GLuint *ids);
extern PFNGLGENTRANSFORMFEEDBACKSPROC glad_glGenTransformFeedbacks;

typedef GLboolean ( * PFNGLISTRANSFORMFEEDBACKPROC)(GLuint id);
extern PFNGLISTRANSFORMFEEDBACKPROC glad_glIsTransformFeedback;

typedef void ( * PFNGLPAUSETRANSFORMFEEDBACKPROC)(void);
extern PFNGLPAUSETRANSFORMFEEDBACKPROC glad_glPauseTransformFeedback;

typedef void ( * PFNGLRESUMETRANSFORMFEEDBACKPROC)(void);
extern PFNGLRESUMETRANSFORMFEEDBACKPROC glad_glResumeTransformFeedback;

typedef void ( * PFNGLDRAWTRANSFORMFEEDBACKPROC)(GLenum mode, GLuint id);
extern PFNGLDRAWTRANSFORMFEEDBACKPROC glad_glDrawTransformFeedback;

typedef void ( * PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)(GLenum mode, GLuint id, GLuint stream);
extern PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC glad_glDrawTransformFeedbackStream;

typedef void ( * PFNGLBEGINQUERYINDEXEDPROC)(GLenum target, GLuint index, GLuint id);
extern PFNGLBEGINQUERYINDEXEDPROC glad_glBeginQueryIndexed;

typedef void ( * PFNGLENDQUERYINDEXEDPROC)(GLenum target, GLuint index);
extern PFNGLENDQUERYINDEXEDPROC glad_glEndQueryIndexed;

typedef void ( * PFNGLGETQUERYINDEXEDIVPROC)(GLenum target, GLuint index, GLenum pname, GLint *params);
extern PFNGLGETQUERYINDEXEDIVPROC glad_glGetQueryIndexediv;




extern int GLAD_GL_VERSION_4_1;
typedef void ( * PFNGLRELEASESHADERCOMPILERPROC)(void);
extern PFNGLRELEASESHADERCOMPILERPROC glad_glReleaseShaderCompiler;

typedef void ( * PFNGLSHADERBINARYPROC)(GLsizei count, const GLuint *shaders, GLenum binaryFormat, const void *binary, GLsizei length);
extern PFNGLSHADERBINARYPROC glad_glShaderBinary;

typedef void ( * PFNGLGETSHADERPRECISIONFORMATPROC)(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
extern PFNGLGETSHADERPRECISIONFORMATPROC glad_glGetShaderPrecisionFormat;

typedef void ( * PFNGLDEPTHRANGEFPROC)(GLfloat n, GLfloat f);
extern PFNGLDEPTHRANGEFPROC glad_glDepthRangef;

typedef void ( * PFNGLCLEARDEPTHFPROC)(GLfloat d);
extern PFNGLCLEARDEPTHFPROC glad_glClearDepthf;

typedef void ( * PFNGLGETPROGRAMBINARYPROC)(GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary);
extern PFNGLGETPROGRAMBINARYPROC glad_glGetProgramBinary;

typedef void ( * PFNGLPROGRAMBINARYPROC)(GLuint program, GLenum binaryFormat, const void *binary, GLsizei length);
extern PFNGLPROGRAMBINARYPROC glad_glProgramBinary;

typedef void ( * PFNGLPROGRAMPARAMETERIPROC)(GLuint program, GLenum pname, GLint value);
extern PFNGLPROGRAMPARAMETERIPROC glad_glProgramParameteri;

typedef void ( * PFNGLUSEPROGRAMSTAGESPROC)(GLuint pipeline, GLbitfield stages, GLuint program);
extern PFNGLUSEPROGRAMSTAGESPROC glad_glUseProgramStages;

typedef void ( * PFNGLACTIVESHADERPROGRAMPROC)(GLuint pipeline, GLuint program);
extern PFNGLACTIVESHADERPROGRAMPROC glad_glActiveShaderProgram;

typedef GLuint ( * PFNGLCREATESHADERPROGRAMVPROC)(GLenum type, GLsizei count, const GLchar *const*strings);
extern PFNGLCREATESHADERPROGRAMVPROC glad_glCreateShaderProgramv;

typedef void ( * PFNGLBINDPROGRAMPIPELINEPROC)(GLuint pipeline);
extern PFNGLBINDPROGRAMPIPELINEPROC glad_glBindProgramPipeline;

typedef void ( * PFNGLDELETEPROGRAMPIPELINESPROC)(GLsizei n, const GLuint *pipelines);
extern PFNGLDELETEPROGRAMPIPELINESPROC glad_glDeleteProgramPipelines;

typedef void ( * PFNGLGENPROGRAMPIPELINESPROC)(GLsizei n, GLuint *pipelines);
extern PFNGLGENPROGRAMPIPELINESPROC glad_glGenProgramPipelines;

typedef GLboolean ( * PFNGLISPROGRAMPIPELINEPROC)(GLuint pipeline);
extern PFNGLISPROGRAMPIPELINEPROC glad_glIsProgramPipeline;

typedef void ( * PFNGLGETPROGRAMPIPELINEIVPROC)(GLuint pipeline, GLenum pname, GLint *params);
extern PFNGLGETPROGRAMPIPELINEIVPROC glad_glGetProgramPipelineiv;

typedef void ( * PFNGLPROGRAMUNIFORM1IPROC)(GLuint program, GLint location, GLint v0);
extern PFNGLPROGRAMUNIFORM1IPROC glad_glProgramUniform1i;

typedef void ( * PFNGLPROGRAMUNIFORM1IVPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
extern PFNGLPROGRAMUNIFORM1IVPROC glad_glProgramUniform1iv;

typedef void ( * PFNGLPROGRAMUNIFORM1FPROC)(GLuint program, GLint location, GLfloat v0);
extern PFNGLPROGRAMUNIFORM1FPROC glad_glProgramUniform1f;

typedef void ( * PFNGLPROGRAMUNIFORM1FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
extern PFNGLPROGRAMUNIFORM1FVPROC glad_glProgramUniform1fv;

typedef void ( * PFNGLPROGRAMUNIFORM1DPROC)(GLuint program, GLint location, GLdouble v0);
extern PFNGLPROGRAMUNIFORM1DPROC glad_glProgramUniform1d;

typedef void ( * PFNGLPROGRAMUNIFORM1DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
extern PFNGLPROGRAMUNIFORM1DVPROC glad_glProgramUniform1dv;

typedef void ( * PFNGLPROGRAMUNIFORM1UIPROC)(GLuint program, GLint location, GLuint v0);
extern PFNGLPROGRAMUNIFORM1UIPROC glad_glProgramUniform1ui;

typedef void ( * PFNGLPROGRAMUNIFORM1UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
extern PFNGLPROGRAMUNIFORM1UIVPROC glad_glProgramUniform1uiv;

typedef void ( * PFNGLPROGRAMUNIFORM2IPROC)(GLuint program, GLint location, GLint v0, GLint v1);
extern PFNGLPROGRAMUNIFORM2IPROC glad_glProgramUniform2i;

typedef void ( * PFNGLPROGRAMUNIFORM2IVPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
extern PFNGLPROGRAMUNIFORM2IVPROC glad_glProgramUniform2iv;

typedef void ( * PFNGLPROGRAMUNIFORM2FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1);
extern PFNGLPROGRAMUNIFORM2FPROC glad_glProgramUniform2f;

typedef void ( * PFNGLPROGRAMUNIFORM2FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
extern PFNGLPROGRAMUNIFORM2FVPROC glad_glProgramUniform2fv;

typedef void ( * PFNGLPROGRAMUNIFORM2DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1);
extern PFNGLPROGRAMUNIFORM2DPROC glad_glProgramUniform2d;

typedef void ( * PFNGLPROGRAMUNIFORM2DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
extern PFNGLPROGRAMUNIFORM2DVPROC glad_glProgramUniform2dv;

typedef void ( * PFNGLPROGRAMUNIFORM2UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1);
extern PFNGLPROGRAMUNIFORM2UIPROC glad_glProgramUniform2ui;

typedef void ( * PFNGLPROGRAMUNIFORM2UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
extern PFNGLPROGRAMUNIFORM2UIVPROC glad_glProgramUniform2uiv;

typedef void ( * PFNGLPROGRAMUNIFORM3IPROC)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
extern PFNGLPROGRAMUNIFORM3IPROC glad_glProgramUniform3i;

typedef void ( * PFNGLPROGRAMUNIFORM3IVPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
extern PFNGLPROGRAMUNIFORM3IVPROC glad_glProgramUniform3iv;

typedef void ( * PFNGLPROGRAMUNIFORM3FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
extern PFNGLPROGRAMUNIFORM3FPROC glad_glProgramUniform3f;

typedef void ( * PFNGLPROGRAMUNIFORM3FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
extern PFNGLPROGRAMUNIFORM3FVPROC glad_glProgramUniform3fv;

typedef void ( * PFNGLPROGRAMUNIFORM3DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
extern PFNGLPROGRAMUNIFORM3DPROC glad_glProgramUniform3d;

typedef void ( * PFNGLPROGRAMUNIFORM3DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
extern PFNGLPROGRAMUNIFORM3DVPROC glad_glProgramUniform3dv;

typedef void ( * PFNGLPROGRAMUNIFORM3UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
extern PFNGLPROGRAMUNIFORM3UIPROC glad_glProgramUniform3ui;

typedef void ( * PFNGLPROGRAMUNIFORM3UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
extern PFNGLPROGRAMUNIFORM3UIVPROC glad_glProgramUniform3uiv;

typedef void ( * PFNGLPROGRAMUNIFORM4IPROC)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
extern PFNGLPROGRAMUNIFORM4IPROC glad_glProgramUniform4i;

typedef void ( * PFNGLPROGRAMUNIFORM4IVPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
extern PFNGLPROGRAMUNIFORM4IVPROC glad_glProgramUniform4iv;

typedef void ( * PFNGLPROGRAMUNIFORM4FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
extern PFNGLPROGRAMUNIFORM4FPROC glad_glProgramUniform4f;

typedef void ( * PFNGLPROGRAMUNIFORM4FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
extern PFNGLPROGRAMUNIFORM4FVPROC glad_glProgramUniform4fv;

typedef void ( * PFNGLPROGRAMUNIFORM4DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
extern PFNGLPROGRAMUNIFORM4DPROC glad_glProgramUniform4d;

typedef void ( * PFNGLPROGRAMUNIFORM4DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
extern PFNGLPROGRAMUNIFORM4DVPROC glad_glProgramUniform4dv;

typedef void ( * PFNGLPROGRAMUNIFORM4UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
extern PFNGLPROGRAMUNIFORM4UIPROC glad_glProgramUniform4ui;

typedef void ( * PFNGLPROGRAMUNIFORM4UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
extern PFNGLPROGRAMUNIFORM4UIVPROC glad_glProgramUniform4uiv;

typedef void ( * PFNGLPROGRAMUNIFORMMATRIX2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern PFNGLPROGRAMUNIFORMMATRIX2FVPROC glad_glProgramUniformMatrix2fv;

typedef void ( * PFNGLPROGRAMUNIFORMMATRIX3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern PFNGLPROGRAMUNIFORMMATRIX3FVPROC glad_glProgramUniformMatrix3fv;

typedef void ( * PFNGLPROGRAMUNIFORMMATRIX4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern PFNGLPROGRAMUNIFORMMATRIX4FVPROC glad_glProgramUniformMatrix4fv;

typedef void ( * PFNGLPROGRAMUNIFORMMATRIX2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
extern PFNGLPROGRAMUNIFORMMATRIX2DVPROC glad_glProgramUniformMatrix2dv;

typedef void ( * PFNGLPROGRAMUNIFORMMATRIX3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
extern PFNGLPROGRAMUNIFORMMATRIX3DVPROC glad_glProgramUniformMatrix3dv;

typedef void ( * PFNGLPROGRAMUNIFORMMATRIX4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
extern PFNGLPROGRAMUNIFORMMATRIX4DVPROC glad_glProgramUniformMatrix4dv;

typedef void ( * PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC glad_glProgramUniformMatrix2x3fv;

typedef void ( * PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC glad_glProgramUniformMatrix3x2fv;

typedef void ( * PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC glad_glProgramUniformMatrix2x4fv;

typedef void ( * PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC glad_glProgramUniformMatrix4x2fv;

typedef void ( * PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC glad_glProgramUniformMatrix3x4fv;

typedef void ( * PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC glad_glProgramUniformMatrix4x3fv;

typedef void ( * PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
extern PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC glad_glProgramUniformMatrix2x3dv;

typedef void ( * PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
extern PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC glad_glProgramUniformMatrix3x2dv;

typedef void ( * PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
extern PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC glad_glProgramUniformMatrix2x4dv;

typedef void ( * PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
extern PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC glad_glProgramUniformMatrix4x2dv;

typedef void ( * PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
extern PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC glad_glProgramUniformMatrix3x4dv;

typedef void ( * PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
extern PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC glad_glProgramUniformMatrix4x3dv;

typedef void ( * PFNGLVALIDATEPROGRAMPIPELINEPROC)(GLuint pipeline);
extern PFNGLVALIDATEPROGRAMPIPELINEPROC glad_glValidateProgramPipeline;

typedef void ( * PFNGLGETPROGRAMPIPELINEINFOLOGPROC)(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
extern PFNGLGETPROGRAMPIPELINEINFOLOGPROC glad_glGetProgramPipelineInfoLog;

typedef void ( * PFNGLVERTEXATTRIBL1DPROC)(GLuint index, GLdouble x);
extern PFNGLVERTEXATTRIBL1DPROC glad_glVertexAttribL1d;

typedef void ( * PFNGLVERTEXATTRIBL2DPROC)(GLuint index, GLdouble x, GLdouble y);
extern PFNGLVERTEXATTRIBL2DPROC glad_glVertexAttribL2d;

typedef void ( * PFNGLVERTEXATTRIBL3DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
extern PFNGLVERTEXATTRIBL3DPROC glad_glVertexAttribL3d;

typedef void ( * PFNGLVERTEXATTRIBL4DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
extern PFNGLVERTEXATTRIBL4DPROC glad_glVertexAttribL4d;

typedef void ( * PFNGLVERTEXATTRIBL1DVPROC)(GLuint index, const GLdouble *v);
extern PFNGLVERTEXATTRIBL1DVPROC glad_glVertexAttribL1dv;

typedef void ( * PFNGLVERTEXATTRIBL2DVPROC)(GLuint index, const GLdouble *v);
extern PFNGLVERTEXATTRIBL2DVPROC glad_glVertexAttribL2dv;

typedef void ( * PFNGLVERTEXATTRIBL3DVPROC)(GLuint index, const GLdouble *v);
extern PFNGLVERTEXATTRIBL3DVPROC glad_glVertexAttribL3dv;

typedef void ( * PFNGLVERTEXATTRIBL4DVPROC)(GLuint index, const GLdouble *v);
extern PFNGLVERTEXATTRIBL4DVPROC glad_glVertexAttribL4dv;

typedef void ( * PFNGLVERTEXATTRIBLPOINTERPROC)(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
extern PFNGLVERTEXATTRIBLPOINTERPROC glad_glVertexAttribLPointer;

typedef void ( * PFNGLGETVERTEXATTRIBLDVPROC)(GLuint index, GLenum pname, GLdouble *params);
extern PFNGLGETVERTEXATTRIBLDVPROC glad_glGetVertexAttribLdv;

typedef void ( * PFNGLVIEWPORTARRAYVPROC)(GLuint first, GLsizei count, const GLfloat *v);
extern PFNGLVIEWPORTARRAYVPROC glad_glViewportArrayv;

typedef void ( * PFNGLVIEWPORTINDEXEDFPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
extern PFNGLVIEWPORTINDEXEDFPROC glad_glViewportIndexedf;

typedef void ( * PFNGLVIEWPORTINDEXEDFVPROC)(GLuint index, const GLfloat *v);
extern PFNGLVIEWPORTINDEXEDFVPROC glad_glViewportIndexedfv;

typedef void ( * PFNGLSCISSORARRAYVPROC)(GLuint first, GLsizei count, const GLint *v);
extern PFNGLSCISSORARRAYVPROC glad_glScissorArrayv;

typedef void ( * PFNGLSCISSORINDEXEDPROC)(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
extern PFNGLSCISSORINDEXEDPROC glad_glScissorIndexed;

typedef void ( * PFNGLSCISSORINDEXEDVPROC)(GLuint index, const GLint *v);
extern PFNGLSCISSORINDEXEDVPROC glad_glScissorIndexedv;

typedef void ( * PFNGLDEPTHRANGEARRAYVPROC)(GLuint first, GLsizei count, const GLdouble *v);
extern PFNGLDEPTHRANGEARRAYVPROC glad_glDepthRangeArrayv;

typedef void ( * PFNGLDEPTHRANGEINDEXEDPROC)(GLuint index, GLdouble n, GLdouble f);
extern PFNGLDEPTHRANGEINDEXEDPROC glad_glDepthRangeIndexed;

typedef void ( * PFNGLGETFLOATI_VPROC)(GLenum target, GLuint index, GLfloat *data);
extern PFNGLGETFLOATI_VPROC glad_glGetFloati_v;

typedef void ( * PFNGLGETDOUBLEI_VPROC)(GLenum target, GLuint index, GLdouble *data);
extern PFNGLGETDOUBLEI_VPROC glad_glGetDoublei_v;




extern int GLAD_GL_VERSION_4_2;
typedef void ( * PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance);
extern PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC glad_glDrawArraysInstancedBaseInstance;

typedef void ( * PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLuint baseinstance);
extern PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC glad_glDrawElementsInstancedBaseInstance;

typedef void ( * PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC glad_glDrawElementsInstancedBaseVertexBaseInstance;

typedef void ( * PFNGLGETINTERNALFORMATIVPROC)(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint *params);
extern PFNGLGETINTERNALFORMATIVPROC glad_glGetInternalformativ;

typedef void ( * PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC)(GLuint program, GLuint bufferIndex, GLenum pname, GLint *params);
extern PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC glad_glGetActiveAtomicCounterBufferiv;

typedef void ( * PFNGLBINDIMAGETEXTUREPROC)(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
extern PFNGLBINDIMAGETEXTUREPROC glad_glBindImageTexture;

typedef void ( * PFNGLMEMORYBARRIERPROC)(GLbitfield barriers);
extern PFNGLMEMORYBARRIERPROC glad_glMemoryBarrier;

typedef void ( * PFNGLTEXSTORAGE1DPROC)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
extern PFNGLTEXSTORAGE1DPROC glad_glTexStorage1D;

typedef void ( * PFNGLTEXSTORAGE2DPROC)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
extern PFNGLTEXSTORAGE2DPROC glad_glTexStorage2D;

typedef void ( * PFNGLTEXSTORAGE3DPROC)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
extern PFNGLTEXSTORAGE3DPROC glad_glTexStorage3D;

typedef void ( * PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)(GLenum mode, GLuint id, GLsizei instancecount);
extern PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC glad_glDrawTransformFeedbackInstanced;

typedef void ( * PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount);
extern PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC glad_glDrawTransformFeedbackStreamInstanced;




extern int GLAD_GL_VERSION_4_3;
typedef void ( * PFNGLCLEARBUFFERDATAPROC)(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void *data);
extern PFNGLCLEARBUFFERDATAPROC glad_glClearBufferData;

typedef void ( * PFNGLCLEARBUFFERSUBDATAPROC)(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
extern PFNGLCLEARBUFFERSUBDATAPROC glad_glClearBufferSubData;

typedef void ( * PFNGLDISPATCHCOMPUTEPROC)(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
extern PFNGLDISPATCHCOMPUTEPROC glad_glDispatchCompute;

typedef void ( * PFNGLDISPATCHCOMPUTEINDIRECTPROC)(GLintptr indirect);
extern PFNGLDISPATCHCOMPUTEINDIRECTPROC glad_glDispatchComputeIndirect;

typedef void ( * PFNGLCOPYIMAGESUBDATAPROC)(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
extern PFNGLCOPYIMAGESUBDATAPROC glad_glCopyImageSubData;

typedef void ( * PFNGLFRAMEBUFFERPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
extern PFNGLFRAMEBUFFERPARAMETERIPROC glad_glFramebufferParameteri;

typedef void ( * PFNGLGETFRAMEBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
extern PFNGLGETFRAMEBUFFERPARAMETERIVPROC glad_glGetFramebufferParameteriv;

typedef void ( * PFNGLGETINTERNALFORMATI64VPROC)(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint64 *params);
extern PFNGLGETINTERNALFORMATI64VPROC glad_glGetInternalformati64v;

typedef void ( * PFNGLINVALIDATETEXSUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
extern PFNGLINVALIDATETEXSUBIMAGEPROC glad_glInvalidateTexSubImage;

typedef void ( * PFNGLINVALIDATETEXIMAGEPROC)(GLuint texture, GLint level);
extern PFNGLINVALIDATETEXIMAGEPROC glad_glInvalidateTexImage;

typedef void ( * PFNGLINVALIDATEBUFFERSUBDATAPROC)(GLuint buffer, GLintptr offset, GLsizeiptr length);
extern PFNGLINVALIDATEBUFFERSUBDATAPROC glad_glInvalidateBufferSubData;

typedef void ( * PFNGLINVALIDATEBUFFERDATAPROC)(GLuint buffer);
extern PFNGLINVALIDATEBUFFERDATAPROC glad_glInvalidateBufferData;

typedef void ( * PFNGLINVALIDATEFRAMEBUFFERPROC)(GLenum target, GLsizei numAttachments, const GLenum *attachments);
extern PFNGLINVALIDATEFRAMEBUFFERPROC glad_glInvalidateFramebuffer;

typedef void ( * PFNGLINVALIDATESUBFRAMEBUFFERPROC)(GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
extern PFNGLINVALIDATESUBFRAMEBUFFERPROC glad_glInvalidateSubFramebuffer;

typedef void ( * PFNGLMULTIDRAWARRAYSINDIRECTPROC)(GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride);
extern PFNGLMULTIDRAWARRAYSINDIRECTPROC glad_glMultiDrawArraysIndirect;

typedef void ( * PFNGLMULTIDRAWELEMENTSINDIRECTPROC)(GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride);
extern PFNGLMULTIDRAWELEMENTSINDIRECTPROC glad_glMultiDrawElementsIndirect;

typedef void ( * PFNGLGETPROGRAMINTERFACEIVPROC)(GLuint program, GLenum programInterface, GLenum pname, GLint *params);
extern PFNGLGETPROGRAMINTERFACEIVPROC glad_glGetProgramInterfaceiv;

typedef GLuint ( * PFNGLGETPROGRAMRESOURCEINDEXPROC)(GLuint program, GLenum programInterface, const GLchar *name);
extern PFNGLGETPROGRAMRESOURCEINDEXPROC glad_glGetProgramResourceIndex;

typedef void ( * PFNGLGETPROGRAMRESOURCENAMEPROC)(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
extern PFNGLGETPROGRAMRESOURCENAMEPROC glad_glGetProgramResourceName;

typedef void ( * PFNGLGETPROGRAMRESOURCEIVPROC)(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei count, GLsizei *length, GLint *params);
extern PFNGLGETPROGRAMRESOURCEIVPROC glad_glGetProgramResourceiv;

typedef GLint ( * PFNGLGETPROGRAMRESOURCELOCATIONPROC)(GLuint program, GLenum programInterface, const GLchar *name);
extern PFNGLGETPROGRAMRESOURCELOCATIONPROC glad_glGetProgramResourceLocation;

typedef GLint ( * PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC)(GLuint program, GLenum programInterface, const GLchar *name);
extern PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC glad_glGetProgramResourceLocationIndex;

typedef void ( * PFNGLSHADERSTORAGEBLOCKBINDINGPROC)(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);
extern PFNGLSHADERSTORAGEBLOCKBINDINGPROC glad_glShaderStorageBlockBinding;

typedef void ( * PFNGLTEXBUFFERRANGEPROC)(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
extern PFNGLTEXBUFFERRANGEPROC glad_glTexBufferRange;

typedef void ( * PFNGLTEXSTORAGE2DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
extern PFNGLTEXSTORAGE2DMULTISAMPLEPROC glad_glTexStorage2DMultisample;

typedef void ( * PFNGLTEXSTORAGE3DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
extern PFNGLTEXSTORAGE3DMULTISAMPLEPROC glad_glTexStorage3DMultisample;

typedef void ( * PFNGLTEXTUREVIEWPROC)(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
extern PFNGLTEXTUREVIEWPROC glad_glTextureView;

typedef void ( * PFNGLBINDVERTEXBUFFERPROC)(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
extern PFNGLBINDVERTEXBUFFERPROC glad_glBindVertexBuffer;

typedef void ( * PFNGLVERTEXATTRIBFORMATPROC)(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
extern PFNGLVERTEXATTRIBFORMATPROC glad_glVertexAttribFormat;

typedef void ( * PFNGLVERTEXATTRIBIFORMATPROC)(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
extern PFNGLVERTEXATTRIBIFORMATPROC glad_glVertexAttribIFormat;

typedef void ( * PFNGLVERTEXATTRIBLFORMATPROC)(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
extern PFNGLVERTEXATTRIBLFORMATPROC glad_glVertexAttribLFormat;

typedef void ( * PFNGLVERTEXATTRIBBINDINGPROC)(GLuint attribindex, GLuint bindingindex);
extern PFNGLVERTEXATTRIBBINDINGPROC glad_glVertexAttribBinding;

typedef void ( * PFNGLVERTEXBINDINGDIVISORPROC)(GLuint bindingindex, GLuint divisor);
extern PFNGLVERTEXBINDINGDIVISORPROC glad_glVertexBindingDivisor;

typedef void ( * PFNGLDEBUGMESSAGECONTROLPROC)(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
extern PFNGLDEBUGMESSAGECONTROLPROC glad_glDebugMessageControl;

typedef void ( * PFNGLDEBUGMESSAGEINSERTPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
extern PFNGLDEBUGMESSAGEINSERTPROC glad_glDebugMessageInsert;

typedef void ( * PFNGLDEBUGMESSAGECALLBACKPROC)(GLDEBUGPROC callback, const void *userParam);
extern PFNGLDEBUGMESSAGECALLBACKPROC glad_glDebugMessageCallback;

typedef GLuint ( * PFNGLGETDEBUGMESSAGELOGPROC)(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
extern PFNGLGETDEBUGMESSAGELOGPROC glad_glGetDebugMessageLog;

typedef void ( * PFNGLPUSHDEBUGGROUPPROC)(GLenum source, GLuint id, GLsizei length, const GLchar *message);
extern PFNGLPUSHDEBUGGROUPPROC glad_glPushDebugGroup;

typedef void ( * PFNGLPOPDEBUGGROUPPROC)(void);
extern PFNGLPOPDEBUGGROUPPROC glad_glPopDebugGroup;

typedef void ( * PFNGLOBJECTLABELPROC)(GLenum identifier, GLuint name, GLsizei length, const GLchar *label);
extern PFNGLOBJECTLABELPROC glad_glObjectLabel;

typedef void ( * PFNGLGETOBJECTLABELPROC)(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
extern PFNGLGETOBJECTLABELPROC glad_glGetObjectLabel;

typedef void ( * PFNGLOBJECTPTRLABELPROC)(const void *ptr, GLsizei length, const GLchar *label);
extern PFNGLOBJECTPTRLABELPROC glad_glObjectPtrLabel;

typedef void ( * PFNGLGETOBJECTPTRLABELPROC)(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);
extern PFNGLGETOBJECTPTRLABELPROC glad_glGetObjectPtrLabel;




extern int GLAD_GL_VERSION_4_4;
typedef void ( * PFNGLBUFFERSTORAGEPROC)(GLenum target, GLsizeiptr size, const void *data, GLbitfield flags);
extern PFNGLBUFFERSTORAGEPROC glad_glBufferStorage;

typedef void ( * PFNGLCLEARTEXIMAGEPROC)(GLuint texture, GLint level, GLenum format, GLenum type, const void *data);
extern PFNGLCLEARTEXIMAGEPROC glad_glClearTexImage;

typedef void ( * PFNGLCLEARTEXSUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data);
extern PFNGLCLEARTEXSUBIMAGEPROC glad_glClearTexSubImage;

typedef void ( * PFNGLBINDBUFFERSBASEPROC)(GLenum target, GLuint first, GLsizei count, const GLuint *buffers);
extern PFNGLBINDBUFFERSBASEPROC glad_glBindBuffersBase;

typedef void ( * PFNGLBINDBUFFERSRANGEPROC)(GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizeiptr *sizes);
extern PFNGLBINDBUFFERSRANGEPROC glad_glBindBuffersRange;

typedef void ( * PFNGLBINDTEXTURESPROC)(GLuint first, GLsizei count, const GLuint *textures);
extern PFNGLBINDTEXTURESPROC glad_glBindTextures;

typedef void ( * PFNGLBINDSAMPLERSPROC)(GLuint first, GLsizei count, const GLuint *samplers);
extern PFNGLBINDSAMPLERSPROC glad_glBindSamplers;

typedef void ( * PFNGLBINDIMAGETEXTURESPROC)(GLuint first, GLsizei count, const GLuint *textures);
extern PFNGLBINDIMAGETEXTURESPROC glad_glBindImageTextures;

typedef void ( * PFNGLBINDVERTEXBUFFERSPROC)(GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides);
extern PFNGLBINDVERTEXBUFFERSPROC glad_glBindVertexBuffers;




extern int GLAD_GL_VERSION_4_5;
typedef void ( * PFNGLCLIPCONTROLPROC)(GLenum origin, GLenum depth);
extern PFNGLCLIPCONTROLPROC glad_glClipControl;

typedef void ( * PFNGLCREATETRANSFORMFEEDBACKSPROC)(GLsizei n, GLuint *ids);
extern PFNGLCREATETRANSFORMFEEDBACKSPROC glad_glCreateTransformFeedbacks;

typedef void ( * PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC)(GLuint xfb, GLuint index, GLuint buffer);
extern PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC glad_glTransformFeedbackBufferBase;

typedef void ( * PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC)(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
extern PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC glad_glTransformFeedbackBufferRange;

typedef void ( * PFNGLGETTRANSFORMFEEDBACKIVPROC)(GLuint xfb, GLenum pname, GLint *param);
extern PFNGLGETTRANSFORMFEEDBACKIVPROC glad_glGetTransformFeedbackiv;

typedef void ( * PFNGLGETTRANSFORMFEEDBACKI_VPROC)(GLuint xfb, GLenum pname, GLuint index, GLint *param);
extern PFNGLGETTRANSFORMFEEDBACKI_VPROC glad_glGetTransformFeedbacki_v;

typedef void ( * PFNGLGETTRANSFORMFEEDBACKI64_VPROC)(GLuint xfb, GLenum pname, GLuint index, GLint64 *param);
extern PFNGLGETTRANSFORMFEEDBACKI64_VPROC glad_glGetTransformFeedbacki64_v;

typedef void ( * PFNGLCREATEBUFFERSPROC)(GLsizei n, GLuint *buffers);
extern PFNGLCREATEBUFFERSPROC glad_glCreateBuffers;

typedef void ( * PFNGLNAMEDBUFFERSTORAGEPROC)(GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags);
extern PFNGLNAMEDBUFFERSTORAGEPROC glad_glNamedBufferStorage;

typedef void ( * PFNGLNAMEDBUFFERDATAPROC)(GLuint buffer, GLsizeiptr size, const void *data, GLenum usage);
extern PFNGLNAMEDBUFFERDATAPROC glad_glNamedBufferData;

typedef void ( * PFNGLNAMEDBUFFERSUBDATAPROC)(GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data);
extern PFNGLNAMEDBUFFERSUBDATAPROC glad_glNamedBufferSubData;

typedef void ( * PFNGLCOPYNAMEDBUFFERSUBDATAPROC)(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
extern PFNGLCOPYNAMEDBUFFERSUBDATAPROC glad_glCopyNamedBufferSubData;

typedef void ( * PFNGLCLEARNAMEDBUFFERDATAPROC)(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void *data);
extern PFNGLCLEARNAMEDBUFFERDATAPROC glad_glClearNamedBufferData;

typedef void ( * PFNGLCLEARNAMEDBUFFERSUBDATAPROC)(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
extern PFNGLCLEARNAMEDBUFFERSUBDATAPROC glad_glClearNamedBufferSubData;

typedef void * ( * PFNGLMAPNAMEDBUFFERPROC)(GLuint buffer, GLenum access);
extern PFNGLMAPNAMEDBUFFERPROC glad_glMapNamedBuffer;

typedef void * ( * PFNGLMAPNAMEDBUFFERRANGEPROC)(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
extern PFNGLMAPNAMEDBUFFERRANGEPROC glad_glMapNamedBufferRange;

typedef GLboolean ( * PFNGLUNMAPNAMEDBUFFERPROC)(GLuint buffer);
extern PFNGLUNMAPNAMEDBUFFERPROC glad_glUnmapNamedBuffer;

typedef void ( * PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC)(GLuint buffer, GLintptr offset, GLsizeiptr length);
extern PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC glad_glFlushMappedNamedBufferRange;

typedef void ( * PFNGLGETNAMEDBUFFERPARAMETERIVPROC)(GLuint buffer, GLenum pname, GLint *params);
extern PFNGLGETNAMEDBUFFERPARAMETERIVPROC glad_glGetNamedBufferParameteriv;

typedef void ( * PFNGLGETNAMEDBUFFERPARAMETERI64VPROC)(GLuint buffer, GLenum pname, GLint64 *params);
extern PFNGLGETNAMEDBUFFERPARAMETERI64VPROC glad_glGetNamedBufferParameteri64v;

typedef void ( * PFNGLGETNAMEDBUFFERPOINTERVPROC)(GLuint buffer, GLenum pname, void **params);
extern PFNGLGETNAMEDBUFFERPOINTERVPROC glad_glGetNamedBufferPointerv;

typedef void ( * PFNGLGETNAMEDBUFFERSUBDATAPROC)(GLuint buffer, GLintptr offset, GLsizeiptr size, void *data);
extern PFNGLGETNAMEDBUFFERSUBDATAPROC glad_glGetNamedBufferSubData;

typedef void ( * PFNGLCREATEFRAMEBUFFERSPROC)(GLsizei n, GLuint *framebuffers);
extern PFNGLCREATEFRAMEBUFFERSPROC glad_glCreateFramebuffers;

typedef void ( * PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC)(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
extern PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC glad_glNamedFramebufferRenderbuffer;

typedef void ( * PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC)(GLuint framebuffer, GLenum pname, GLint param);
extern PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC glad_glNamedFramebufferParameteri;

typedef void ( * PFNGLNAMEDFRAMEBUFFERTEXTUREPROC)(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
extern PFNGLNAMEDFRAMEBUFFERTEXTUREPROC glad_glNamedFramebufferTexture;

typedef void ( * PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC)(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
extern PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC glad_glNamedFramebufferTextureLayer;

typedef void ( * PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC)(GLuint framebuffer, GLenum buf);
extern PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC glad_glNamedFramebufferDrawBuffer;

typedef void ( * PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC)(GLuint framebuffer, GLsizei n, const GLenum *bufs);
extern PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC glad_glNamedFramebufferDrawBuffers;

typedef void ( * PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC)(GLuint framebuffer, GLenum src);
extern PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC glad_glNamedFramebufferReadBuffer;

typedef void ( * PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC)(GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments);
extern PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC glad_glInvalidateNamedFramebufferData;

typedef void ( * PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC)(GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
extern PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC glad_glInvalidateNamedFramebufferSubData;

typedef void ( * PFNGLCLEARNAMEDFRAMEBUFFERIVPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint *value);
extern PFNGLCLEARNAMEDFRAMEBUFFERIVPROC glad_glClearNamedFramebufferiv;

typedef void ( * PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint *value);
extern PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC glad_glClearNamedFramebufferuiv;

typedef void ( * PFNGLCLEARNAMEDFRAMEBUFFERFVPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat *value);
extern PFNGLCLEARNAMEDFRAMEBUFFERFVPROC glad_glClearNamedFramebufferfv;

typedef void ( * PFNGLCLEARNAMEDFRAMEBUFFERFIPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
extern PFNGLCLEARNAMEDFRAMEBUFFERFIPROC glad_glClearNamedFramebufferfi;

typedef void ( * PFNGLBLITNAMEDFRAMEBUFFERPROC)(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
extern PFNGLBLITNAMEDFRAMEBUFFERPROC glad_glBlitNamedFramebuffer;

typedef GLenum ( * PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC)(GLuint framebuffer, GLenum target);
extern PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC glad_glCheckNamedFramebufferStatus;

typedef void ( * PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC)(GLuint framebuffer, GLenum pname, GLint *param);
extern PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC glad_glGetNamedFramebufferParameteriv;

typedef void ( * PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLuint framebuffer, GLenum attachment, GLenum pname, GLint *params);
extern PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC glad_glGetNamedFramebufferAttachmentParameteriv;

typedef void ( * PFNGLCREATERENDERBUFFERSPROC)(GLsizei n, GLuint *renderbuffers);
extern PFNGLCREATERENDERBUFFERSPROC glad_glCreateRenderbuffers;

typedef void ( * PFNGLNAMEDRENDERBUFFERSTORAGEPROC)(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
extern PFNGLNAMEDRENDERBUFFERSTORAGEPROC glad_glNamedRenderbufferStorage;

typedef void ( * PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
extern PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC glad_glNamedRenderbufferStorageMultisample;

typedef void ( * PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC)(GLuint renderbuffer, GLenum pname, GLint *params);
extern PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC glad_glGetNamedRenderbufferParameteriv;

typedef void ( * PFNGLCREATETEXTURESPROC)(GLenum target, GLsizei n, GLuint *textures);
extern PFNGLCREATETEXTURESPROC glad_glCreateTextures;

typedef void ( * PFNGLTEXTUREBUFFERPROC)(GLuint texture, GLenum internalformat, GLuint buffer);
extern PFNGLTEXTUREBUFFERPROC glad_glTextureBuffer;

typedef void ( * PFNGLTEXTUREBUFFERRANGEPROC)(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
extern PFNGLTEXTUREBUFFERRANGEPROC glad_glTextureBufferRange;

typedef void ( * PFNGLTEXTURESTORAGE1DPROC)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width);
extern PFNGLTEXTURESTORAGE1DPROC glad_glTextureStorage1D;

typedef void ( * PFNGLTEXTURESTORAGE2DPROC)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
extern PFNGLTEXTURESTORAGE2DPROC glad_glTextureStorage2D;

typedef void ( * PFNGLTEXTURESTORAGE3DPROC)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
extern PFNGLTEXTURESTORAGE3DPROC glad_glTextureStorage3D;

typedef void ( * PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC)(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
extern PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC glad_glTextureStorage2DMultisample;

typedef void ( * PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC)(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
extern PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC glad_glTextureStorage3DMultisample;

typedef void ( * PFNGLTEXTURESUBIMAGE1DPROC)(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
extern PFNGLTEXTURESUBIMAGE1DPROC glad_glTextureSubImage1D;

typedef void ( * PFNGLTEXTURESUBIMAGE2DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
extern PFNGLTEXTURESUBIMAGE2DPROC glad_glTextureSubImage2D;

typedef void ( * PFNGLTEXTURESUBIMAGE3DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
extern PFNGLTEXTURESUBIMAGE3DPROC glad_glTextureSubImage3D;

typedef void ( * PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC)(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data);
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC glad_glCompressedTextureSubImage1D;

typedef void ( * PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC glad_glCompressedTextureSubImage2D;

typedef void ( * PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC glad_glCompressedTextureSubImage3D;

typedef void ( * PFNGLCOPYTEXTURESUBIMAGE1DPROC)(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
extern PFNGLCOPYTEXTURESUBIMAGE1DPROC glad_glCopyTextureSubImage1D;

typedef void ( * PFNGLCOPYTEXTURESUBIMAGE2DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
extern PFNGLCOPYTEXTURESUBIMAGE2DPROC glad_glCopyTextureSubImage2D;

typedef void ( * PFNGLCOPYTEXTURESUBIMAGE3DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
extern PFNGLCOPYTEXTURESUBIMAGE3DPROC glad_glCopyTextureSubImage3D;

typedef void ( * PFNGLTEXTUREPARAMETERFPROC)(GLuint texture, GLenum pname, GLfloat param);
extern PFNGLTEXTUREPARAMETERFPROC glad_glTextureParameterf;

typedef void ( * PFNGLTEXTUREPARAMETERFVPROC)(GLuint texture, GLenum pname, const GLfloat *param);
extern PFNGLTEXTUREPARAMETERFVPROC glad_glTextureParameterfv;

typedef void ( * PFNGLTEXTUREPARAMETERIPROC)(GLuint texture, GLenum pname, GLint param);
extern PFNGLTEXTUREPARAMETERIPROC glad_glTextureParameteri;

typedef void ( * PFNGLTEXTUREPARAMETERIIVPROC)(GLuint texture, GLenum pname, const GLint *params);
extern PFNGLTEXTUREPARAMETERIIVPROC glad_glTextureParameterIiv;

typedef void ( * PFNGLTEXTUREPARAMETERIUIVPROC)(GLuint texture, GLenum pname, const GLuint *params);
extern PFNGLTEXTUREPARAMETERIUIVPROC glad_glTextureParameterIuiv;

typedef void ( * PFNGLTEXTUREPARAMETERIVPROC)(GLuint texture, GLenum pname, const GLint *param);
extern PFNGLTEXTUREPARAMETERIVPROC glad_glTextureParameteriv;

typedef void ( * PFNGLGENERATETEXTUREMIPMAPPROC)(GLuint texture);
extern PFNGLGENERATETEXTUREMIPMAPPROC glad_glGenerateTextureMipmap;

typedef void ( * PFNGLBINDTEXTUREUNITPROC)(GLuint unit, GLuint texture);
extern PFNGLBINDTEXTUREUNITPROC glad_glBindTextureUnit;

typedef void ( * PFNGLGETTEXTUREIMAGEPROC)(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
extern PFNGLGETTEXTUREIMAGEPROC glad_glGetTextureImage;

typedef void ( * PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC)(GLuint texture, GLint level, GLsizei bufSize, void *pixels);
extern PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC glad_glGetCompressedTextureImage;

typedef void ( * PFNGLGETTEXTURELEVELPARAMETERFVPROC)(GLuint texture, GLint level, GLenum pname, GLfloat *params);
extern PFNGLGETTEXTURELEVELPARAMETERFVPROC glad_glGetTextureLevelParameterfv;

typedef void ( * PFNGLGETTEXTURELEVELPARAMETERIVPROC)(GLuint texture, GLint level, GLenum pname, GLint *params);
extern PFNGLGETTEXTURELEVELPARAMETERIVPROC glad_glGetTextureLevelParameteriv;

typedef void ( * PFNGLGETTEXTUREPARAMETERFVPROC)(GLuint texture, GLenum pname, GLfloat *params);
extern PFNGLGETTEXTUREPARAMETERFVPROC glad_glGetTextureParameterfv;

typedef void ( * PFNGLGETTEXTUREPARAMETERIIVPROC)(GLuint texture, GLenum pname, GLint *params);
extern PFNGLGETTEXTUREPARAMETERIIVPROC glad_glGetTextureParameterIiv;

typedef void ( * PFNGLGETTEXTUREPARAMETERIUIVPROC)(GLuint texture, GLenum pname, GLuint *params);
extern PFNGLGETTEXTUREPARAMETERIUIVPROC glad_glGetTextureParameterIuiv;

typedef void ( * PFNGLGETTEXTUREPARAMETERIVPROC)(GLuint texture, GLenum pname, GLint *params);
extern PFNGLGETTEXTUREPARAMETERIVPROC glad_glGetTextureParameteriv;

typedef void ( * PFNGLCREATEVERTEXARRAYSPROC)(GLsizei n, GLuint *arrays);
extern PFNGLCREATEVERTEXARRAYSPROC glad_glCreateVertexArrays;

typedef void ( * PFNGLDISABLEVERTEXARRAYATTRIBPROC)(GLuint vaobj, GLuint index);
extern PFNGLDISABLEVERTEXARRAYATTRIBPROC glad_glDisableVertexArrayAttrib;

typedef void ( * PFNGLENABLEVERTEXARRAYATTRIBPROC)(GLuint vaobj, GLuint index);
extern PFNGLENABLEVERTEXARRAYATTRIBPROC glad_glEnableVertexArrayAttrib;

typedef void ( * PFNGLVERTEXARRAYELEMENTBUFFERPROC)(GLuint vaobj, GLuint buffer);
extern PFNGLVERTEXARRAYELEMENTBUFFERPROC glad_glVertexArrayElementBuffer;

typedef void ( * PFNGLVERTEXARRAYVERTEXBUFFERPROC)(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
extern PFNGLVERTEXARRAYVERTEXBUFFERPROC glad_glVertexArrayVertexBuffer;

typedef void ( * PFNGLVERTEXARRAYVERTEXBUFFERSPROC)(GLuint vaobj, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides);
extern PFNGLVERTEXARRAYVERTEXBUFFERSPROC glad_glVertexArrayVertexBuffers;

typedef void ( * PFNGLVERTEXARRAYATTRIBBINDINGPROC)(GLuint vaobj, GLuint attribindex, GLuint bindingindex);
extern PFNGLVERTEXARRAYATTRIBBINDINGPROC glad_glVertexArrayAttribBinding;

typedef void ( * PFNGLVERTEXARRAYATTRIBFORMATPROC)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
extern PFNGLVERTEXARRAYATTRIBFORMATPROC glad_glVertexArrayAttribFormat;

typedef void ( * PFNGLVERTEXARRAYATTRIBIFORMATPROC)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
extern PFNGLVERTEXARRAYATTRIBIFORMATPROC glad_glVertexArrayAttribIFormat;

typedef void ( * PFNGLVERTEXARRAYATTRIBLFORMATPROC)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
extern PFNGLVERTEXARRAYATTRIBLFORMATPROC glad_glVertexArrayAttribLFormat;

typedef void ( * PFNGLVERTEXARRAYBINDINGDIVISORPROC)(GLuint vaobj, GLuint bindingindex, GLuint divisor);
extern PFNGLVERTEXARRAYBINDINGDIVISORPROC glad_glVertexArrayBindingDivisor;

typedef void ( * PFNGLGETVERTEXARRAYIVPROC)(GLuint vaobj, GLenum pname, GLint *param);
extern PFNGLGETVERTEXARRAYIVPROC glad_glGetVertexArrayiv;

typedef void ( * PFNGLGETVERTEXARRAYINDEXEDIVPROC)(GLuint vaobj, GLuint index, GLenum pname, GLint *param);
extern PFNGLGETVERTEXARRAYINDEXEDIVPROC glad_glGetVertexArrayIndexediv;

typedef void ( * PFNGLGETVERTEXARRAYINDEXED64IVPROC)(GLuint vaobj, GLuint index, GLenum pname, GLint64 *param);
extern PFNGLGETVERTEXARRAYINDEXED64IVPROC glad_glGetVertexArrayIndexed64iv;

typedef void ( * PFNGLCREATESAMPLERSPROC)(GLsizei n, GLuint *samplers);
extern PFNGLCREATESAMPLERSPROC glad_glCreateSamplers;

typedef void ( * PFNGLCREATEPROGRAMPIPELINESPROC)(GLsizei n, GLuint *pipelines);
extern PFNGLCREATEPROGRAMPIPELINESPROC glad_glCreateProgramPipelines;

typedef void ( * PFNGLCREATEQUERIESPROC)(GLenum target, GLsizei n, GLuint *ids);
extern PFNGLCREATEQUERIESPROC glad_glCreateQueries;

typedef void ( * PFNGLGETQUERYBUFFEROBJECTI64VPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
extern PFNGLGETQUERYBUFFEROBJECTI64VPROC glad_glGetQueryBufferObjecti64v;

typedef void ( * PFNGLGETQUERYBUFFEROBJECTIVPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
extern PFNGLGETQUERYBUFFEROBJECTIVPROC glad_glGetQueryBufferObjectiv;

typedef void ( * PFNGLGETQUERYBUFFEROBJECTUI64VPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
extern PFNGLGETQUERYBUFFEROBJECTUI64VPROC glad_glGetQueryBufferObjectui64v;

typedef void ( * PFNGLGETQUERYBUFFEROBJECTUIVPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
extern PFNGLGETQUERYBUFFEROBJECTUIVPROC glad_glGetQueryBufferObjectuiv;

typedef void ( * PFNGLMEMORYBARRIERBYREGIONPROC)(GLbitfield barriers);
extern PFNGLMEMORYBARRIERBYREGIONPROC glad_glMemoryBarrierByRegion;

typedef void ( * PFNGLGETTEXTURESUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
extern PFNGLGETTEXTURESUBIMAGEPROC glad_glGetTextureSubImage;

typedef void ( * PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void *pixels);
extern PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC glad_glGetCompressedTextureSubImage;

typedef GLenum ( * PFNGLGETGRAPHICSRESETSTATUSPROC)(void);
extern PFNGLGETGRAPHICSRESETSTATUSPROC glad_glGetGraphicsResetStatus;

typedef void ( * PFNGLGETNCOMPRESSEDTEXIMAGEPROC)(GLenum target, GLint lod, GLsizei bufSize, void *pixels);
extern PFNGLGETNCOMPRESSEDTEXIMAGEPROC glad_glGetnCompressedTexImage;

typedef void ( * PFNGLGETNTEXIMAGEPROC)(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
extern PFNGLGETNTEXIMAGEPROC glad_glGetnTexImage;

typedef void ( * PFNGLGETNUNIFORMDVPROC)(GLuint program, GLint location, GLsizei bufSize, GLdouble *params);
extern PFNGLGETNUNIFORMDVPROC glad_glGetnUniformdv;

typedef void ( * PFNGLGETNUNIFORMFVPROC)(GLuint program, GLint location, GLsizei bufSize, GLfloat *params);
extern PFNGLGETNUNIFORMFVPROC glad_glGetnUniformfv;

typedef void ( * PFNGLGETNUNIFORMIVPROC)(GLuint program, GLint location, GLsizei bufSize, GLint *params);
extern PFNGLGETNUNIFORMIVPROC glad_glGetnUniformiv;

typedef void ( * PFNGLGETNUNIFORMUIVPROC)(GLuint program, GLint location, GLsizei bufSize, GLuint *params);
extern PFNGLGETNUNIFORMUIVPROC glad_glGetnUniformuiv;

typedef void ( * PFNGLREADNPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data);
extern PFNGLREADNPIXELSPROC glad_glReadnPixels;

typedef void ( * PFNGLGETNMAPDVPROC)(GLenum target, GLenum query, GLsizei bufSize, GLdouble *v);
extern PFNGLGETNMAPDVPROC glad_glGetnMapdv;

typedef void ( * PFNGLGETNMAPFVPROC)(GLenum target, GLenum query, GLsizei bufSize, GLfloat *v);
extern PFNGLGETNMAPFVPROC glad_glGetnMapfv;

typedef void ( * PFNGLGETNMAPIVPROC)(GLenum target, GLenum query, GLsizei bufSize, GLint *v);
extern PFNGLGETNMAPIVPROC glad_glGetnMapiv;

typedef void ( * PFNGLGETNPIXELMAPFVPROC)(GLenum map, GLsizei bufSize, GLfloat *values);
extern PFNGLGETNPIXELMAPFVPROC glad_glGetnPixelMapfv;

typedef void ( * PFNGLGETNPIXELMAPUIVPROC)(GLenum map, GLsizei bufSize, GLuint *values);
extern PFNGLGETNPIXELMAPUIVPROC glad_glGetnPixelMapuiv;

typedef void ( * PFNGLGETNPIXELMAPUSVPROC)(GLenum map, GLsizei bufSize, GLushort *values);
extern PFNGLGETNPIXELMAPUSVPROC glad_glGetnPixelMapusv;

typedef void ( * PFNGLGETNPOLYGONSTIPPLEPROC)(GLsizei bufSize, GLubyte *pattern);
extern PFNGLGETNPOLYGONSTIPPLEPROC glad_glGetnPolygonStipple;

typedef void ( * PFNGLGETNCOLORTABLEPROC)(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void *table);
extern PFNGLGETNCOLORTABLEPROC glad_glGetnColorTable;

typedef void ( * PFNGLGETNCONVOLUTIONFILTERPROC)(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void *image);
extern PFNGLGETNCONVOLUTIONFILTERPROC glad_glGetnConvolutionFilter;

typedef void ( * PFNGLGETNSEPARABLEFILTERPROC)(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void *row, GLsizei columnBufSize, void *column, void *span);
extern PFNGLGETNSEPARABLEFILTERPROC glad_glGetnSeparableFilter;

typedef void ( * PFNGLGETNHISTOGRAMPROC)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void *values);
extern PFNGLGETNHISTOGRAMPROC glad_glGetnHistogram;

typedef void ( * PFNGLGETNMINMAXPROC)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void *values);
extern PFNGLGETNMINMAXPROC glad_glGetnMinmax;

typedef void ( * PFNGLTEXTUREBARRIERPROC)(void);
extern PFNGLTEXTUREBARRIERPROC glad_glTextureBarrier;




extern int GLAD_GL_VERSION_4_6;
typedef void ( * PFNGLSPECIALIZESHADERPROC)(GLuint shader, const GLchar *pEntryPoint, GLuint numSpecializationConstants, const GLuint *pConstantIndex, const GLuint *pConstantValue);
extern PFNGLSPECIALIZESHADERPROC glad_glSpecializeShader;

typedef void ( * PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC)(GLenum mode, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
extern PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC glad_glMultiDrawArraysIndirectCount;

typedef void ( * PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC)(GLenum mode, GLenum type, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
extern PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC glad_glMultiDrawElementsIndirectCount;

typedef void ( * PFNGLPOLYGONOFFSETCLAMPPROC)(GLfloat factor, GLfloat units, GLfloat clamp);
extern PFNGLPOLYGONOFFSETCLAMPPROC glad_glPolygonOffsetClamp;




}
# 3 "/home/ai/AUR30LA/src/aur/view/VAO.h" 2
# 1 "/home/ai/AUR30LA/src/aur/view/VBO.h" 1
       


class VBO {
    public:
     GLuint ID;
     VBO(GLfloat* vertices, GLsizeiptr size);
     void Bind();
     void Unbind();
     void Delete();
};
# 4 "/home/ai/AUR30LA/src/aur/view/VAO.h" 2

class VAO {
 public:
  GLuint ID;
  VAO();
  void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
  void Bind();
  void Unbind();
  void Delete();
};
# 2 "/home/ai/AUR30LA/src/aur/view/VAO.cpp" 2

VAO::VAO() {
 glad_glGenVertexArrays(1, &ID);
}
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
 VBO.Bind();
 glad_glVertexAttribPointer(layout, numComponents, type, 0, stride, offset);
 glad_glEnableVertexAttribArray(layout);
 VBO.Unbind();
}
void VAO::Bind() {glad_glBindVertexArray(ID);}
void VAO::Unbind() {glad_glBindVertexArray(0);}
void VAO::Delete() {glad_glDeleteVertexArrays(1, &ID);}
