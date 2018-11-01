
#pragma once

#include <windows.h>
#include <string>


// Forward declaration
template<typename ReturnType, typename ... Args> class Function;

// RAII for .dll handle
class Library
{
	private:
		HMODULE m_handle = NULL;
		template<typename, typename ...> friend class Function;
	public:
		Library(const std::string &name)
		{
				if ( !(m_handle = LoadLibraryA(name.c_str())) )
					throw std::runtime_error( std::string("Can't load library") + name );
		}
		~Library()
		{
				if ( m_handle )
					FreeLibrary(m_handle);
		}
};


// Variadic template representing a function imported from .dll
template<typename ReturnType, typename ... Args> class Function
{
	private:
		const Library &m_lib;
		using Fn = ReturnType (__stdcall *)(Args ...);
		Fn m_func = NULL;
	public:
		Function(const Library &lib, const std::string &name) : m_lib(lib)
		{
				if ( !(m_func = (Fn)GetProcAddress(m_lib.m_handle, name.c_str())) )
					throw std::runtime_error( std::string("Can't get proc address for ") + name );
		}
		~Function() {}

		ReturnType operator()(Args ... args) const { return m_func(args ...); }
};
