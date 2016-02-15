// Pre-processors for Expat library.
// Modified all .c files in Expat to include this file.

#ifndef EXPAT_DEFS_H
#define EXPAT_DEFS_H

// Static library
#define XML_STATIC

// Win32 platform
#ifdef _WIN32
#define COMPILED_FROM_DSP
// Unicode support
#endif
#define XML_UNICODE_WCHAR_T


#endif
