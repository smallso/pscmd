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

#pragma once

/* Contains the necessary Windows SDK header files */
#include "windows.h"
#include "winternl.h"

/* Defining the request result status code in NTSTATUS */
#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)

/* Automatically selects the corresponding API based on the character set type of the current project */
#ifdef _UNICODE
	typedef WCHAR* PCMDBUFFER_T;
	#define GetProcessCommandLine GetProcessCommandLineW
#else
	typedef CHAR* PCMDBUFFER_T;
	#define GetProcessCommandLine GetProcessCommandLineA
#endif

/* Multiple version declarations for GetProcessCommandLine */
BOOL
WINAPI
GetProcessCommandLineW(
	_In_			HANDLE		hProcess,
	_In_opt_	LPCWSTR		lpcBuffer,
	_In_opt_	SIZE_T			nSize,
	_In_opt_	SIZE_T*			lpNumberOfBytesCopied
);

BOOL
WINAPI
GetProcessCommandLineA(
	_In_			HANDLE		hProcess,
	_In_opt_	LPCSTR		lpcBuffer,
	_In_opt_	SIZE_T			nSize,
	_In_opt_	SIZE_T*			lpNumberOfBytesCopied
);
