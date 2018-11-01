#include <windows.h>


#define PREFIX  extern "C" __declspec(dllexport)
// Some magic (MSVC-specific?) to get function name undecorated without adding a .def-file
#define EXPORT comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__)


PREFIX double __stdcall sum_stdcall(const double a, const double b)
{
#pragma EXPORT
	return a + b;
}


PREFIX double __cdecl sum_cdecl(const double a, const double b)
{
	return a + b;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
		switch (ul_reason_for_call)
		{
			case DLL_PROCESS_ATTACH:
			break;
			case DLL_THREAD_ATTACH:
			break;
			case DLL_THREAD_DETACH:
			break;
			case DLL_PROCESS_DETACH:
			break;
		}
	return TRUE;
}
