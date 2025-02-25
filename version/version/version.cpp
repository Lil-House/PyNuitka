#include "version.h"
#include "util.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "include/detours.h"

VOID WTF(LPCSTR lpWtf)
{
    for (;;)
        MessageBoxA(NULL, lpWtf, "PyNuitka", MB_OK);
}

const auto snippet_code_interact = R"(try:
    import sys

    old_sys_stdin = sys.stdin
    old_sys_stdout = sys.stdout
    old_sys_stderr = sys.stderr

    sys.stdin = open("conin$", "r")
    sys.stdout = open("conout$", "w")
    sys.stderr = open("conout$", "w")

    try:
        import code

        code.interact()
    except BaseException as e:
        print(e)
finally:
    sys.stdin = old_sys_stdin
    sys.stdout = old_sys_stdout
    sys.stderr = old_sys_stderr
)";

HMODULE hModDll;
HMODULE hModExe;

enum PyGILState_STATE
{
    PyGILState_LOCKED = 0x0,
    PyGILState_UNLOCKED = 0x1,
};

typedef PyGILState_STATE(__fastcall *PyGILState_Ensure_t)();
PyGILState_Ensure_t p_PyGILState_Ensure;
typedef int(__fastcall *PyRun_SimpleString_t)(const char *s);
PyRun_SimpleString_t p_PyRun_SimpleString;
typedef void(__fastcall *PyGILState_Release_t)(PyGILState_STATE oldstate);
PyGILState_Release_t p_PyGILState_Release;

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
    for (;;)
    {
        if (MessageBoxA(NULL, "interact?", "PyNuitka", MB_YESNO) == IDYES)
        {
            PyGILState_STATE state = p_PyGILState_Ensure();

            int retcode = p_PyRun_SimpleString(snippet_code_interact);
            // Returns 0 on success or -1 if an exception was raised.
            if (retcode != 0)
                printf("p_PyRun_SimpleString() = %d\n", retcode);

            p_PyGILState_Release(state);
        }
    }
    return 0;
}

VOID HandlePython310Module(HMODULE hMod_python310)
{
    p_PyGILState_Ensure = (PyGILState_Ensure_t)GetProcAddress(hMod_python310, "PyGILState_Ensure");
    if (!p_PyGILState_Ensure)
        return;
    p_PyRun_SimpleString = (PyRun_SimpleString_t)GetProcAddress(hMod_python310, "PyRun_SimpleString");
    if (!p_PyRun_SimpleString)
        return;
    p_PyGILState_Release = (PyGILState_Release_t)GetProcAddress(hMod_python310, "PyGILState_Release");
    if (!p_PyGILState_Release)
        return;

    CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        hModDll = hModule;
        ZeroMemoryDllNameFromLdrDataTableEntry(hModDll);

        hModExe = GetModuleHandleA(NULL);

        if (AllocConsole())
        {
            FILE *fp;
            freopen_s(&fp, "conin$", "r", stdin);
            freopen_s(&fp, "conout$", "w", stdout);
            freopen_s(&fp, "conout$", "w", stderr);
        }

        HMODULE hMod_python310 = GetModuleHandleA("python310.dll");
        if (hMod_python310)
            HandlePython310Module(hMod_python310);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        if (lpReserved)
            return TRUE;

        WTF("dwReason == DLL_PROCESS_DETACH && !lpReserved");
    }
    return TRUE;
}
