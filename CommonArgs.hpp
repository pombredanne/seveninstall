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
 * Common command argument handling
 */
#ifndef __7I_COMMONARGS_HPP__
#define __7I_COMMONARGS_HPP__

#include "InstallScope.hpp"

#include <optional>

class ArgsHelper;

/**
 * Class for common command argument handling
 */
class CommonArgs
{
  const ArgsHelper& args;
public:
  CommonArgs (const ArgsHelper& args) : args (args) {}

  /**
   * Get GUID (\c -g) argument.
   * \param guid Returns a pointer to the GUID argument, if one is present.
   * \param required If \c true, prints a message if the argument is missing.
   * \returns Whether a GUID (\c -g) argument was given.
   */
  bool GetGUID (const wchar_t*& guid, bool reportMissing = true);
  /**
   * Get InstallScope (\c -U or \c -M) argument.
   */
  std::optional<InstallScope> GetInstallScope ();
};

#endif // __7I_COMMONARGS_HPP__
