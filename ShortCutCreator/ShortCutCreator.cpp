#include <windows.h>
#include <direct.h>
#include <fstream>
#include <string>
#include <iostream>

void load();
void create();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	load();
	return 0;
}

using namespace std;

void load()
{
	wfstream fname,parmeter,rundir;
	fname.open(".\\shrtset\\shortcutn", ios::in);
	parmeter.open(".\\shrtset\\shortcutp", ios::in);
	rundir.open(".\\shrtset\\shortcutd", ios::in);
	if ((fname.is_open() && parmeter.is_open() && rundir.is_open()) == false)
	{
		fname.close();
		parmeter.close();
		rundir.close();
		create();
	}
	wstring filename, parmeters,rdir;
	getline(fname, filename);
	getline(parmeter, parmeters);
	getline(rundir, rdir);
	HINSTANCE hInstance = ShellExecute(nullptr, nullptr, filename.c_str(), parmeters.c_str(), rdir.c_str(), SW_SHOWDEFAULT);
	if (hInstance <= (HINSTANCE)32)
	{
		MessageBox(nullptr, (wstring(L"Fatal Error!\nError Code(ShellExecute):") + to_wstring((int)hInstance)).c_str(), L"Open File error", MB_ICONERROR | MB_OK);
	}
	fname.close();
	parmeter.close();
	rundir.close();
}

void create()
{
	AllocConsole();
	FILE* stream;
	freopen_s(&stream, "CON", "r", stdin);
	freopen_s(&stream, "CON", "w", stdout);
	SetConsoleTitle(L"ShortCut Creator");
	HWND _consoleHwnd;
	wchar_t* cd = new wchar_t[MAX_PATH];
	_wgetcwd(cd, MAX_PATH);
	for (int i = 0; i < 100; i++)
	{
		_consoleHwnd = FindWindow(NULL, L"ShortCut Creator");
		if (_consoleHwnd)
			break;
		Sleep(100);
	}
	HANDLE _handleOutput;
	_handleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	printf("ShortCut Creator\n\nThe shortcut setting file was save in:%ls\n\nPlease type the execute name:", cd);
	std::wstring fn, pr, rd;
	getline(wcin, fn);
	printf("\nPlease type the Parmeter(empty is no):");
	getline(wcin, pr);
	printf("\nPlease type the Run Directory(empty is the execute directory):");
	getline(wcin, rd);
	_mkdir(".\\shrtset");
	wfstream fname(".\\shrtset\\shortcutn", ios::out | ios::trunc), parme(".\\shrtset\\shortcutp", ios::out | ios::trunc), rund(".\\shrtset\\shortcutd", ios::out | ios::trunc);
	fname << fn;
	parme << pr;
	rund << rd;
	fname.close();
	parme.close();
	rund.close();
	printf("\n\n\n\n\n\n\n\n\n\n\nCompleted");
	system("pause");
	FreeConsole();
}