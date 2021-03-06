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

#include "ArgsHelper.hpp"

static const wchar_t arg_burn_filehandle[] = L"burn.filehandle.self";
static const wchar_t arg_burn_embedded[] = L"burn.embedded";

const wchar_t* ArgsHelper::burnEmbeddedPipeName = L"burn.embedded.name";
const wchar_t* ArgsHelper::burnEmbeddedPipeSecret = L"burn.embedded.secret";
const wchar_t* ArgsHelper::burnEmbeddedPipePPID = L"burn.embedded.ppid";

ArgsHelper::ArgsHelper (int argc, const wchar_t* const argv[])
{
    for (int a = 1; a < argc; a++)
    {
        const wchar_t* arg (argv[a]);
        if (arg[0] == '-')
        {
            if (_wcsnicmp (arg+1, arg_burn_filehandle, wcslen (arg_burn_filehandle)) == 0)
            {
                // Special case; treat as long options, separated by '='
                auto sep = wcschr (arg + 1, '=');
                options[arg_burn_filehandle] = sep ? sep+1 : nullptr;
            }
            else if (_wcsnicmp (arg+1, arg_burn_embedded, wcslen (arg_burn_embedded)) == 0)
            {
                // Special case; actually three arguments follow: connection name, secret, parent PID
                if (++a < argc) { options[burnEmbeddedPipeName] = argv[a]; }
                if (++a < argc) { options[burnEmbeddedPipeSecret] = argv[a]; }
                if (++a < argc) { options[burnEmbeddedPipePPID] = argv[a]; }
            }
            else if (arg[1] == '-')
            {
                // --long option - no value
                options[arg] = nullptr;
            }
            else
            {
                // -s ...hort option - value after 1st letter
                MyUString opt_str (arg, 2);
                options[opt_str] = arg+2;
            }
        }
        else
        {
            freeArgs.push_back (arg);
        }
    }
}

bool ArgsHelper::GetOption (const wchar_t* prefix, const wchar_t*& value) const
{
    OptionsMapType::const_iterator opt (options.find (prefix));
    if (opt == options.end()) return false;
    value = opt->second;
    return true;
}

bool ArgsHelper::GetOption (const wchar_t* option) const
{
    OptionsMapType::const_iterator opt (options.find (option));
    return opt != options.end();
}

void ArgsHelper::GetFreeArgs (std::vector<const wchar_t*>& args) const
{
    args = freeArgs;
}

