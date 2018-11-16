#pragma once

#include <windows.h>
#include <string>


namespace DllHelpers
{
	enum CallingConventions {__stdcall__, __cdecl__};


	// Forward declaration
	template<CallingConventions, typename ReturnType, typename ... Args> class Function;
	

	// RAII for .dll handle
	// Noncopyable
	class Library
	{
		private:
			HMODULE m_handle = NULL;
			template<CallingConventions, typename, typename ...> friend class Function;
		public:
			// Constructs the Library from the ANSI-string representing the .dll-file name
			Library(const std::string &name)
			{
					if ( (m_handle = LoadLibraryA(name.c_str())) == nullptr )
						throw std::runtime_error( std::string("Can't load library ") + name );
			}
			// Constructs the Library from the UNICODE-string representing the .dll-file name
			Library(const std::wstring &name)
			{
					if ( (m_handle = LoadLibraryW(name.c_str())) == nullptr )
						throw std::runtime_error( std::string("Can't load library ") + std::string(name.begin(), name.end()) );
			}

			Library(const Library&) = delete;
			Library& operator=(const Library&) = delete;

			~Library()
			{
					if ( m_handle )
						FreeLibrary(m_handle);
			}
	};


	namespace Implementation
	{
		template<CallingConventions convention, typename ReturnType, typename ... Args> struct FnTypeProvider
		{
		};

		template<typename ReturnType, typename ... Args> struct FnTypeProvider<CallingConventions::__cdecl__, ReturnType, Args ...>
		{
			// Function type with calling convention "cdecl"
			using Fn = ReturnType (__cdecl *)(Args ...);
		};

		template<typename ReturnType, typename ... Args> struct FnTypeProvider<CallingConventions::__stdcall__, ReturnType, Args ...>
		{
			// Function type with calling convention "stdcall"
			using Fn = ReturnType (__stdcall *)(Args ...);
		};
	} // namespace Implementation


	// Variadic template representing a function imported from the .dll
	template<CallingConventions convention, typename ReturnType, typename ... Args> class Function
	{
		private:
			const Library &m_lib;
			// Type depending on calling convention
			using Fn = typename Implementation::FnTypeProvider<convention, ReturnType, Args ...>::Fn;
			Fn m_func = NULL;
		public:
			// Constructs the Function from the Library instance and the function name
			Function(const Library &lib, const std::string &name) : m_lib(lib)
			{
					if ( (m_func = (Fn)GetProcAddress(m_lib.m_handle, name.c_str())) == nullptr )
						throw std::runtime_error( std::string("Can't get proc address for ") + name );
			}
			~Function() {}

			ReturnType operator()(Args ... args) const { return m_func(args ...); }
	};
} // namespace DllHelpers
