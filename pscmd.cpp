/*
	Pscmd
	--------
	License     	Apache 2.0 License
	--------
	Copyright 2018 SMALLSO Studios.

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
	------
	E-mail      	xiaoyy@altca.cn
	WorkQQ   	20177621
	Website   	https://www.xiaoyy.org/
	------
	SMALLSO Studios.
	2018/5/17 22:08
*/

#include "stdafx.h"
#include "pscmd.h"

/* NTAPI ZwQueryInformationProcess */
typedef NTSTATUS(NTAPI * Typedef_ZwQueryInformationProcess)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);
Typedef_ZwQueryInformationProcess pNTAPI_ZwQueryInformationProcess =
(Typedef_ZwQueryInformationProcess)GetProcAddress(GetModuleHandle(L"ntdll.dll"), "ZwQueryInformationProcess");

/*
	获取指定进程命令行字符串，失败返回 FALSE（Unicode Version）
	--------
	HANDLE hProcess							需获取其命令行字符串的进程句柄，该句柄应具有 PROCESS_QUERY_INFORMATION 和 PROCESS_VM_READ 访问权限
	LPCWSTR lpcBuffer							指向接收命令行字符串的宽字符缓冲区指针，缓冲区应使用 memset 初始化为 zero，该参数可以为 NULL
	SIZE_T nSize										参数 lpcBuffer 指向的宽字符缓冲区有效大小（Bytes），该参数可以为 NULL
	SIZE_T* lpNumberOfBytesCopied	实际复制到 lpcBuffer 指向的宽字符缓冲区中的字节数（Bytes），如 lpcBuffer 为 NULL 或 nSize 太小，该参数将返回所需缓冲区的建议大小（Bytes），该参数可以为 NULL
*/
BOOL WINAPI GetProcessCommandLineW(HANDLE hProcess, LPCWSTR lpcBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesCopied)
{
	BOOL result = FALSE;
	if (pNTAPI_ZwQueryInformationProcess)
	{
		PROCESS_BASIC_INFORMATION BasicInfo; memset(&BasicInfo, NULL, sizeof(BasicInfo));
		PEB PebBaseInfo; memset(&PebBaseInfo, NULL, sizeof(PebBaseInfo));
		RTL_USER_PROCESS_PARAMETERS ProcessParameters; memset(&ProcessParameters, NULL, sizeof(ProcessParameters));
		if (pNTAPI_ZwQueryInformationProcess(hProcess, PROCESSINFOCLASS::ProcessBasicInformation, &BasicInfo, sizeof(BasicInfo), NULL) == STATUS_SUCCESS)
		{
			if (ReadProcessMemory(hProcess, BasicInfo.PebBaseAddress, &PebBaseInfo, sizeof(PebBaseInfo), NULL)
				&& ReadProcessMemory(hProcess, PebBaseInfo.ProcessParameters, &ProcessParameters, sizeof(ProcessParameters), NULL))
			{
				if (lpcBuffer && nSize >= ProcessParameters.CommandLine.Length + 2)
					result = ReadProcessMemory(hProcess, ProcessParameters.CommandLine.Buffer, (LPVOID)lpcBuffer,
						ProcessParameters.CommandLine.Length, lpNumberOfBytesCopied);
				else if (lpNumberOfBytesCopied) { *lpNumberOfBytesCopied = ProcessParameters.CommandLine.Length + 2; result = TRUE; }
			}
		}
	}
	return result;
}

/*
	获取指定进程命令行字符串，失败返回 FALSE（Ansi Version）
	--------
	GetProcessCommandLineA 是基于 GetProcessCommandLineW 的 Ansi 版本，应用程序应尽可能使用 GetProcessCommandLineW，而不是此 GetProcessCommandLineA
	--------
	HANDLE hProcess							需获取其命令行字符串的进程句柄，该句柄应具有 PROCESS_QUERY_INFORMATION 和 PROCESS_VM_READ 访问权限
	LPCWSTR lpcBuffer							指向接收命令行字符串的多字节缓冲区指针，缓冲区应使用 memset 初始化为 zero，该参数可以为 NULL
	SIZE_T nSize										参数 lpcBuffer 指向的多字节缓冲区有效大小（Bytes），该参数可以为 NULL
	SIZE_T* lpNumberOfBytesCopied	实际复制到 lpcBuffer 指向的多字节缓冲区中的字节数（Bytes），如 lpcBuffer 为 NULL 或 nSize 太小，该参数将返回所需缓冲区的建议大小（Bytes），该参数可以为 NULL
*/
BOOL WINAPI GetProcessCommandLineA(HANDLE hProcess, LPCSTR lpcBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesCopied)
{
	BOOL result = FALSE;
	SIZE_T nCommandLineSize = NULL;
	if (GetProcessCommandLineW(hProcess, NULL, NULL, &nCommandLineSize))
	{
		WCHAR* lpLocalBuffer = (WCHAR*)malloc(nCommandLineSize);
		if (lpLocalBuffer)
		{
			memset(lpLocalBuffer, NULL, nCommandLineSize);
			if (GetProcessCommandLineW(hProcess, lpLocalBuffer, nCommandLineSize, &nCommandLineSize))
			{
				INT iNumberOfBytes = WideCharToMultiByte(CP_ACP, NULL, lpLocalBuffer, nCommandLineSize, (LPSTR)lpcBuffer, nSize, NULL, NULL);
				if (lpNumberOfBytesCopied) *lpNumberOfBytesCopied = (!lpcBuffer || (nSize < (iNumberOfBytes + 1))) ?  iNumberOfBytes + 1 : iNumberOfBytes;
				result = iNumberOfBytes > 0;
			}
			free(lpLocalBuffer);
		}
	}
	return result;
}
