/*
    SevenInstall
    Copyright (c) 2013-2017 Frank Richter

    This is free and unencumbered software released into the public domain.

    Anyone is free to copy, modify, publish, use, compile, sell, or
    distribute this software, either in source code form or as a compiled
    binary, for any purpose, commercial or non-commercial, and by any
    means.

    In jurisdictions that recognize copyright laws, the author or authors
    of this software dedicate any and all copyright interest in the
    software to the public domain. We make this dedication for the benefit
    of the public at large and to the detriment of our heirs and
    successors. We intend this dedication to be an overt act of
    relinquishment in perpetuity of all present and future rights to this
    software under copyright law.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
    OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

    For more information, please refer to <http://unlicense.org>
*/

/**\file
 * Additional printf functions
 */
#ifndef __SUPPORT_PRINTF_HPP__
#define __SUPPORT_PRINTF_HPP__

#define NOMINMAX
#include <windows.h>

//@{
/// Print to a Windows file handle
int Hwprintf (HANDLE handle, const wchar_t* format, ...);
int vHprintf (HANDLE handle, const wchar_t* format, va_list args);
int vHwprintf (HANDLE handle, const wchar_t* format, va_list args);
//@}

#endif // __SUPPORT_PRINTF_HPP__
