#include "util.h"

#include <windows.h>
#include <winternl.h>

BOOL ZeroMemoryDllNameFromLdrDataTableEntry(HMODULE hMod)
{
    LIST_ENTRY *ListEntryHead = &NtCurrentTeb()->ProcessEnvironmentBlock->Ldr->InMemoryOrderModuleList - 1;
    for (LIST_ENTRY *ListEntry = ListEntryHead->Flink; ListEntry != ListEntryHead; ListEntry = ListEntry->Flink)
    {
        LDR_DATA_TABLE_ENTRY *LdrDataTableEntry = CONTAINING_RECORD(ListEntry, LDR_DATA_TABLE_ENTRY, Reserved1);
        if (LdrDataTableEntry->DllBase == hMod)
        {
            UNICODE_STRING *DllName = &LdrDataTableEntry->FullDllName;
            DllName[0].Length = 0;
            ZeroMemory(DllName[0].Buffer, DllName[0].MaximumLength);
            DllName[1].Length = 0;
            ZeroMemory(DllName[1].Buffer, DllName[1].MaximumLength);
            return TRUE;
        }
    }
    return FALSE;
}

PWSTR GetFullDllNameFromLdrDataTableEntry(HMODULE hMod)
{
    LIST_ENTRY *ListEntryHead = &NtCurrentTeb()->ProcessEnvironmentBlock->Ldr->InMemoryOrderModuleList - 1;
    for (LIST_ENTRY *ListEntry = ListEntryHead->Flink; ListEntry != ListEntryHead; ListEntry = ListEntry->Flink)
    {
        LDR_DATA_TABLE_ENTRY *LdrDataTableEntry = CONTAINING_RECORD(ListEntry, LDR_DATA_TABLE_ENTRY, Reserved1);
        if (LdrDataTableEntry->DllBase == hMod)
        {
            UNICODE_STRING *DllName = &LdrDataTableEntry->FullDllName;
            return DllName[0].Buffer;
        }
    }
    return NULL;
}

PWSTR GetBaseDllNameFromLdrDataTableEntry(HMODULE hMod)
{
    LIST_ENTRY *ListEntryHead = &NtCurrentTeb()->ProcessEnvironmentBlock->Ldr->InMemoryOrderModuleList - 1;
    for (LIST_ENTRY *ListEntry = ListEntryHead->Flink; ListEntry != ListEntryHead; ListEntry = ListEntry->Flink)
    {
        LDR_DATA_TABLE_ENTRY *LdrDataTableEntry = CONTAINING_RECORD(ListEntry, LDR_DATA_TABLE_ENTRY, Reserved1);
        if (LdrDataTableEntry->DllBase == hMod)
        {
            UNICODE_STRING *DllName = &LdrDataTableEntry->FullDllName;
            return DllName[1].Buffer;
        }
    }
    return NULL;
}
