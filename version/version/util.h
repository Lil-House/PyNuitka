#pragma once
#include <windows.h>

BOOL ZeroMemoryDllNameFromLdrDataTableEntry(HMODULE hMod);
PWSTR GetFullDllNameFromLdrDataTableEntry(HMODULE hMod);
PWSTR GetBaseDllNameFromLdrDataTableEntry(HMODULE hMod);
