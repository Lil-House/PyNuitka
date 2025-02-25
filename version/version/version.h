#pragma once

#pragma region EXPORT
#define EXPORT_PREFIX R"(C:\Windows\System32\version.)"

#pragma comment(linker, "/EXPORT:GetFileVersionInfoA=" EXPORT_PREFIX "GetFileVersionInfoA,@1")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoByHandle=" EXPORT_PREFIX "GetFileVersionInfoByHandle,@2")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExA=" EXPORT_PREFIX "GetFileVersionInfoExA,@3")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExW=" EXPORT_PREFIX "GetFileVersionInfoExW,@4")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeA=" EXPORT_PREFIX "GetFileVersionInfoSizeA,@5")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExA=" EXPORT_PREFIX "GetFileVersionInfoSizeExA,@6")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExW=" EXPORT_PREFIX "GetFileVersionInfoSizeExW,@7")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeW=" EXPORT_PREFIX "GetFileVersionInfoSizeW,@8")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoW=" EXPORT_PREFIX "GetFileVersionInfoW,@9")
#pragma comment(linker, "/EXPORT:VerFindFileA=" EXPORT_PREFIX "VerFindFileA,@10")
#pragma comment(linker, "/EXPORT:VerFindFileW=" EXPORT_PREFIX "VerFindFileW,@11")
#pragma comment(linker, "/EXPORT:VerInstallFileA=" EXPORT_PREFIX "VerInstallFileA,@12")
#pragma comment(linker, "/EXPORT:VerInstallFileW=" EXPORT_PREFIX "VerInstallFileW,@13")
#pragma comment(linker, "/EXPORT:VerLanguageNameA=" EXPORT_PREFIX "VerLanguageNameA,@14")
#pragma comment(linker, "/EXPORT:VerLanguageNameW=" EXPORT_PREFIX "VerLanguageNameW,@15")
#pragma comment(linker, "/EXPORT:VerQueryValueA=" EXPORT_PREFIX "VerQueryValueA,@16")
#pragma comment(linker, "/EXPORT:VerQueryValueW=" EXPORT_PREFIX "VerQueryValueW,@17")
#pragma endregion

#include <windows.h>

typedef struct _CALLBACK_CONTEXT
{
    DWORD64 R15;
    DWORD64 R14;
    DWORD64 R13;
    DWORD64 R12;
    DWORD64 R11;
    DWORD64 R10;
    DWORD64 R9;
    DWORD64 R8;
    DWORD64 Rdi;
    DWORD64 Rsi;
    DWORD64 Rbp;
    DWORD64 Rsp;
    DWORD64 Rbx;
    DWORD64 Rdx;
    DWORD64 Rcx;
    DWORD64 Rax;
    DWORD64 RFlags;
    DWORD64 JumpAddress;
} CALLBACK_CONTEXT, *PCALLBACK_CONTEXT;

// clang-format off
#define DEFINE_ASM(name)                                                                                               \
__pragma(code_seg(push, ".text"))                                                                                      \
__declspec(allocate(".text")) BYTE asm_##name[0x00DB] = {                                                              \
    /* 0000 */ 0xE8, 0x00, 0x00, 0x00, 0x00,                               /* call $+5                       */        \
    /* 0005 */ 0x9C,                                                       /* pushfq                         */        \
    /* 0006 */ 0x48, 0x83, 0x6C, 0x24, 0x08, 0x05,                         /* sub qword ptr ss:[rsp+8],5     */        \
    /* 000C */ 0x48, 0x89, 0x44, 0x24, 0xF8,                               /* mov qword ptr ss:[rsp-8],rax   */        \
    /* 0011 */ 0x48, 0x89, 0x4C, 0x24, 0xF0,                               /* mov qword ptr ss:[rsp-10],rcx  */        \
    /* 0016 */ 0x48, 0x89, 0x54, 0x24, 0xE8,                               /* mov qword ptr ss:[rsp-18],rdx  */        \
    /* 001B */ 0x48, 0x89, 0x5C, 0x24, 0xE0,                               /* mov qword ptr ss:[rsp-20],rbx  */        \
    /* 0020 */ 0x48, 0x89, 0x64, 0x24, 0xD8,                               /* mov qword ptr ss:[rsp-28],rsp  */        \
    /* 0025 */ 0x48, 0x89, 0x6C, 0x24, 0xD0,                               /* mov qword ptr ss:[rsp-30],rbp  */        \
    /* 002A */ 0x48, 0x89, 0x74, 0x24, 0xC8,                               /* mov qword ptr ss:[rsp-38],rsi  */        \
    /* 002F */ 0x48, 0x89, 0x7C, 0x24, 0xC0,                               /* mov qword ptr ss:[rsp-40],rdi  */        \
    /* 0034 */ 0x48, 0x83, 0xEC, 0x40,                                     /* sub rsp,40                     */        \
    /* 0038 */ 0x4C, 0x89, 0x44, 0x24, 0xF8,                               /* mov qword ptr ss:[rsp-8],r8    */        \
    /* 003D */ 0x4C, 0x89, 0x4C, 0x24, 0xF0,                               /* mov qword ptr ss:[rsp-10],r9   */        \
    /* 0042 */ 0x4C, 0x89, 0x54, 0x24, 0xE8,                               /* mov qword ptr ss:[rsp-18],r10  */        \
    /* 0047 */ 0x4C, 0x89, 0x5C, 0x24, 0xE0,                               /* mov qword ptr ss:[rsp-20],r11  */        \
    /* 004C */ 0x4C, 0x89, 0x64, 0x24, 0xD8,                               /* mov qword ptr ss:[rsp-28],r12  */        \
    /* 0051 */ 0x4C, 0x89, 0x6C, 0x24, 0xD0,                               /* mov qword ptr ss:[rsp-30],r13  */        \
    /* 0056 */ 0x4C, 0x89, 0x74, 0x24, 0xC8,                               /* mov qword ptr ss:[rsp-38],r14  */        \
    /* 005B */ 0x4C, 0x89, 0x7C, 0x24, 0xC0,                               /* mov qword ptr ss:[rsp-40],r15  */        \
    /* 0060 */ 0x48, 0x83, 0xEC, 0x40,                                     /* sub rsp,40                     */        \
    /* 0064 */ 0x48, 0x8B, 0xCC,                                           /* mov rcx,rsp                    */        \
    /* 0067 */ 0x48, 0x8B, 0xDC,                                           /* mov rbx,rsp                    */        \
    /* 006A */ 0x48, 0x83, 0xEC, 0x20,                                     /* sub rsp,20                     */        \
    /* 006E */ 0x48, 0x83, 0xE4, 0xF0,                                     /* and rsp,FFFFFFFFFFFFFFF0       */        \
    /* 0072 */ 0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* mov rax,0                      */        \
    /* 007C */ 0xFF, 0xD0,                                                 /* call rax                       */        \
    /* 007E */ 0x48, 0x8B, 0xE3,                                           /* mov rsp,rbx                    */        \
    /* 0081 */ 0x48, 0x83, 0xC4, 0x40,                                     /* add rsp,40                     */        \
    /* 0085 */ 0x4C, 0x8B, 0x7C, 0x24, 0xC0,                               /* mov r15,qword ptr ss:[rsp-40]  */        \
    /* 008A */ 0x4C, 0x8B, 0x74, 0x24, 0xC8,                               /* mov r14,qword ptr ss:[rsp-38]  */        \
    /* 008F */ 0x4C, 0x8B, 0x6C, 0x24, 0xD0,                               /* mov r13,qword ptr ss:[rsp-30]  */        \
    /* 0094 */ 0x4C, 0x8B, 0x64, 0x24, 0xD8,                               /* mov r12,qword ptr ss:[rsp-28]  */        \
    /* 0099 */ 0x4C, 0x8B, 0x5C, 0x24, 0xE0,                               /* mov r11,qword ptr ss:[rsp-20]  */        \
    /* 009E */ 0x4C, 0x8B, 0x54, 0x24, 0xE8,                               /* mov r10,qword ptr ss:[rsp-18]  */        \
    /* 00A3 */ 0x4C, 0x8B, 0x4C, 0x24, 0xF0,                               /* mov r9,qword ptr ss:[rsp-10]   */        \
    /* 00A8 */ 0x4C, 0x8B, 0x44, 0x24, 0xF8,                               /* mov r8,qword ptr ss:[rsp-8]    */        \
    /* 00AD */ 0x48, 0x83, 0xC4, 0x40,                                     /* add rsp,40                     */        \
    /* 00B1 */ 0x48, 0x8B, 0x7C, 0x24, 0xC0,                               /* mov rdi,qword ptr ss:[rsp-40]  */        \
    /* 00B6 */ 0x48, 0x8B, 0x74, 0x24, 0xC8,                               /* mov rsi,qword ptr ss:[rsp-38]  */        \
    /* 00BB */ 0x48, 0x8B, 0x6C, 0x24, 0xD0,                               /* mov rbp,qword ptr ss:[rsp-30]  */        \
    /* 00C0 */ 0x0F, 0x1F, 0x44, 0x00, 0x00,                               /* nop dword ptr ds:[rax+rax],eax */        \
    /* 00C5 */ 0x48, 0x8B, 0x5C, 0x24, 0xE0,                               /* mov rbx,qword ptr ss:[rsp-20]  */        \
    /* 00CA */ 0x48, 0x8B, 0x54, 0x24, 0xE8,                               /* mov rdx,qword ptr ss:[rsp-18]  */        \
    /* 00CF */ 0x48, 0x8B, 0x4C, 0x24, 0xF0,                               /* mov rcx,qword ptr ss:[rsp-10]  */        \
    /* 00D4 */ 0x48, 0x8B, 0x44, 0x24, 0xF8,                               /* mov rax,qword ptr ss:[rsp-8]   */        \
    /* 00D9 */ 0x9D,                                                       /* popfq                          */        \
    /* 00DA */ 0xC3,                                                       /* ret                            */        \
};                                                                                                                     \
__pragma(code_seg(pop))                                                                                                \
__declspec(noinline) void __stdcall name(PCALLBACK_CONTEXT Context)
// clang-format on

#define FILLIN_ASM(name)                                                                                               \
    do                                                                                                                 \
    {                                                                                                                  \
        PVOID buf_##name = &name;                                                                                      \
        WriteProcessMemory(GetCurrentProcess(), &asm_##name[0x74], &buf_##name, sizeof(buf_##name), NULL);             \
    } while (0)
