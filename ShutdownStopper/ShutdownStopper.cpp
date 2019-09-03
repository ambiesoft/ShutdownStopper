// ShutdownStopper.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../../lsMisc/CreateSimpleWindow.h"

using namespace Ambiesoft;

// https://www.codesd.com/item/use-shutdownblockrequestcreate-in-the-win32-console-application.html
typedef BOOL(WINAPI *SBRCREATEFUNC)(HWND, LPCWSTR);

void RegisterShutdownBlockReason(HWND hWnd) {
	SBRCREATEFUNC ShutdownBlockReasonCreate;
	// HWND hWnd = GetForegroundWindow();
	// HWND hWnd = GetConsoleWindow();
	HINSTANCE hinstLib = LoadLibrary(TEXT("user32.dll"));
	if (hinstLib != NULL) {
		ShutdownBlockReasonCreate = (SBRCREATEFUNC)GetProcAddress(hinstLib, "ShutdownBlockReasonCreate");
		if (ShutdownBlockReasonCreate != NULL) {
			if (!(ShutdownBlockReasonCreate)(hWnd, L"Preventing shutdown")) {
				printf("\nfailed To Register Reason, failure code: %d\n", GetLastError());
			}
			else {
				printf("\nRegistered ShutdownBlockReasonCreate\n");
			}
		}
		else {
			printf("\nCouldn't load ShutdownBlockReasonCreate procedure\n");
		}
	}
	else {
		printf("\nFailed to LoadLibrary(\"user32.dll\")\n");
	}
}

int _tmain(int argc, _TCHAR* argv[]) {
	HWND h = CreateSimpleWindow();
	RegisterShutdownBlockReason(h);
	printf("Type to terminate program.\n");
	_getch();
	return 0;
}