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
 * Registry access
 */
#ifndef __7I_REGISTRY_HPP__
#define __7I_REGISTRY_HPP__

#include <string>

#include <Windows.h>

/**
 * Helper class to access a registry key.
 */
class RegistryKey
{
  HKEY key;
public:
  struct CreateTag {};
  static CreateTag Create;

  /**
   * Open an existing registry key.
   * \param parent Parent key.
   * \param key Key path.
   * \param access Registry access flags.
   * \throws HRESULTException in case of an error.
   */
  RegistryKey (HKEY parent, const wchar_t* key, REGSAM access);
  /**
   * Create a new or open an existing registry key.
   * \param parent Parent key.
   * \param key Key path.
   * \param access Registry access flags.
   * \param tag Unused parameter; used for open vs create behaviour selection.
   * \throws HRESULTException in case of an error.
   */
  RegistryKey (HKEY parent, const wchar_t* key, REGSAM access, CreateTag& tag);
  ~RegistryKey ();

  /**
   * Write a DWORD value to the registry.
   * \param name Name of the value.
   * \param value Actual value.
   * \throws HRESULTException in case of an error.
   */
  void WriteDWORD (const wchar_t* name, DWORD value);
  /**
   * Write a string value to the registry.
   * \param name Name of the value.
   * \param value Actual value.
   * \throws HRESULTException in case of an error.
   */
  void WriteString (const wchar_t* name, const wchar_t* value);

  /**
   * Read a string value from the registry.
   * \param name Name of the value.
   * \returns Actual value.
   * \throws HRESULTException in case of an error.
   */
  std::wstring ReadString (const wchar_t* name);

  /**
   * Query number of subkeys under the key.
   * \returns Number of subkeys.
   * \throws HRESULTException in case of an error.
   */
  size_t NumSubkeys ();
};

/**
 * Helper to access a registry key rooted under HKEY_LOCAL_MACHINE
 * or HKEY_CURRENT_USER, depending on the current user's permissions.
 */
class AutoRootRegistryKey
{
  std::aligned_storage<sizeof(RegistryKey), std::alignment_of<RegistryKey>::value>::type wrappedKey;

  RegistryKey& GetRegKey()
  {
    return reinterpret_cast<RegistryKey&> (wrappedKey);
  }
  const RegistryKey& GetRegKey() const
  {
    return reinterpret_cast<const RegistryKey&> (wrappedKey);
  }
public:
  typedef RegistryKey::CreateTag CreateTag;

  /**
   * Open an existing registry key under HKEY_LOCAL_MACHINE
   * or HKEY_CURRENT_USER, depending on the current user's permissions.
   * Tries HKEY_LOCAL_MACHINE first. If this fails due to insufficient
   * permissions, or because the key doesn't existm, HKEY_CURRENT_USER
   * is tried. If that fails, or in case of any other error,
   * HRESULTException is thrown.
   * \param key Key path.
   * \param access Registry access flags.
   * \throws HRESULTException in case of an error.
   */
  AutoRootRegistryKey (const wchar_t* key, REGSAM access);
  /**
   * Create a new or open an existing registry key under HKEY_LOCAL_MACHINE
   * or HKEY_CURRENT_USER, depending on the current user's permissions.
   * Tries HKEY_LOCAL_MACHINE first. If this fails due to insufficient
   * permissions HKEY_CURRENT_USER is tried. If that fails, or in case
   * of any other error, HRESULTException is thrown.
   * \param parent Parent key.
   * \param key Key path.
   * \param access registry access flags.
   * \param tag Unused parameter; used for open vs create behaviour selection.
   * \throws HRESULTException in case of an error.
   */
  AutoRootRegistryKey (const wchar_t* key, REGSAM access, CreateTag& tag);
  ~AutoRootRegistryKey()
  {
    reinterpret_cast<RegistryKey&> (wrappedKey).~RegistryKey();
  }

  /**\name Access to wrapped RegistryKey instance
   * @{ */
  operator RegistryKey& () { return GetRegKey(); }
  operator const RegistryKey& () const { return GetRegKey(); }
  /** @} */

  /**\name Forwarders of RegistryKey methods
   * @{ */
  void WriteDWORD (const wchar_t* name, DWORD value)
  { GetRegKey().WriteDWORD (name, value); }
  void WriteString (const wchar_t* name, const wchar_t* value)
  { GetRegKey().WriteString (name, value); }

  std::wstring ReadString (const wchar_t* name)
  { return GetRegKey().ReadString (name); }

  size_t NumSubkeys ()
  { return GetRegKey().NumSubkeys(); }
  /** @} */
};

#endif // __7I_REGISTRY_HPP__
