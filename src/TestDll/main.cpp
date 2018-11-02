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


void char_mix(const char *in1, const char *in2, char *out)
{
	size_t j = 0;
		for ( size_t i = 0; (in1[i] && in2[i]); ++i)
		{
			out[j++] = in1[i];
			out[j++] = in2[i];
		}
	out[j] = '\0';
}


// out should be double size
PREFIX void __stdcall char_mix_stdcall(const char *in1, const char *in2, char *out)
{
#pragma EXPORT
	char_mix(in1, in2, out);
}


// out should be double size
PREFIX void __cdecl char_mix_cdecl(const char *in1, const char *in2, char *out)
{
	char_mix(in1, in2, out);
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
