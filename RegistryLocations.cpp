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

#include "RegistryLocations.hpp"

#include "Paths.hpp"
#include "Registry.hpp"

const char regPathUninstallInfo[] = "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\";
const char regPathDependencyInfo[] = "Software\\Classes\\Installer\\Dependencies\\";
const char regPathDependentsSubkey[] = "\\Dependents";
const wchar_t regValLogFileName[] = L"LogFileName";
const wchar_t regValInstallDir[] = L"InstallDir";

MyUString ReadRegistryListFilePath (InstallScope installScope, const wchar_t* guid)
{
  const REGSAM key_access (KEY_READ | KEY_WOW64_64KEY);
  {
    MyUString keyPathUninstall (regPathUninstallInfo);
    keyPathUninstall += guid;
    RegistryKey key (RegistryParent (installScope), keyPathUninstall.Ptr(), key_access);
    return key.ReadString (regValLogFileName);
  }
}

MyUString ReadRegistryOutputDir (InstallScope installScope, const wchar_t* guid)
{
  const REGSAM key_access (KEY_READ | KEY_WOW64_64KEY);
  {
    MyUString keyPathUninstall (regPathUninstallInfo);
    keyPathUninstall += guid;
    RegistryKey key (RegistryParent (installScope), keyPathUninstall.Ptr(), key_access);
    return key.ReadString (regValInstallDir);
  }
}

void WriteToRegistry (InstallScope installScope, const wchar_t* guid, const wchar_t* listFileName,const wchar_t* directory)
{
  HKEY reg_parent = RegistryParent (installScope);
  const REGSAM key_access (KEY_ALL_ACCESS | KEY_WOW64_64KEY);
  {
    MyUString keyPathUninstall (regPathUninstallInfo);
    keyPathUninstall += guid;
    RegistryKey key (reg_parent, keyPathUninstall.Ptr(), key_access, RegistryKey::Create);
    key.WriteString (regValLogFileName, listFileName);
    key.WriteString (regValInstallDir, directory);
    key.WriteDWORD (L"SystemComponent", 1);
  }
  {
    MyUString keyPathDependencies (regPathDependencyInfo);
    keyPathDependencies += guid;
    RegistryKey key (reg_parent, keyPathDependencies.Ptr(), key_access, RegistryKey::Create);
  // DisplayName?
  // Version?
  }
}
