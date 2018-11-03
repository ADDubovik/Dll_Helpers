#include <gtest/gtest.h>
#include <windows.h>

#include "DllHelpers.h"


TEST(DllTest, LibrarySuccessLoadTest)
{
		try
		{
			DllHelpers::Library lib("TestDll.dll");
		}
		catch (std::exception)
		{
			// Should not execute this
			EXPECT_TRUE(false);
		}
}


TEST(DllTest, LibraryUnsuccessLoadTest)
{
		try
		{
			DllHelpers::Library lib("sjhggkjytrjqweoirtenslakjfkgrehjksfakldjhfgkrkdhgkdfsfaewfsvklrhskdjf.dll");
			// Should not execute this because of exception
			EXPECT_TRUE(false);
		}
		catch (std::exception &e)
		{
			// Should execute this
			EXPECT_TRUE(true);
			EXPECT_EQ(std::string(e.what()), "Can't load library sjhggkjytrjqweoirtenslakjfkgrehjksfakldjhfgkrkdhgkdfsfaewfsvklrhskdjf.dll");
		}
}


TEST(DllTest, LibraryUnicodeSuccessLoadTest)
{
		try
		{
			DllHelpers::Library lib(L"TestDll.dll");
		}
		catch (std::exception)
		{
			// Should not execute this
			EXPECT_TRUE(false);
		}
}


TEST(DllTest, LibraryUnicodeUnsuccessLoadTest)
{
		try
		{
			DllHelpers::Library lib(L"sjhggkjytrjqweoirtenslakjfkgrehjksfakldjhfgkrkdhgkdfsfaewfsvklrhskdjf.dll");
			// Should not execute this because of exception
			EXPECT_TRUE(false);
		}
		catch (std::exception &e)
		{
			// Should execute this
			EXPECT_TRUE(true);
			EXPECT_EQ(std::string(e.what()), "Can't load library sjhggkjytrjqweoirtenslakjfkgrehjksfakldjhfgkrkdhgkdfsfaewfsvklrhskdjf.dll");
		}
}


TEST(DllTest, FunctionSuccessTest01)
{
		try
		{
			DllHelpers::Library lib("TestDll.dll");
			DllHelpers::Function<DllHelpers::__cdecl__, double, double, double>   sum_cdecl  (lib, "sum_cdecl");
			DllHelpers::Function<DllHelpers::__stdcall__, double, double, double> sum_stdcall(lib, "sum_stdcall");

			EXPECT_EQ(  sum_cdecl(3.0, 5.0), 3.0+5.0);
			EXPECT_EQ(sum_stdcall(3.0, 5.0), 3.0+5.0);
		}
		catch (std::exception)
		{
			// Should not execute this
			EXPECT_TRUE(false);
		}
}


TEST(DllTest, FunctionSuccessTest02)
{
		try
		{
			DllHelpers::Library lib("TestDll.dll");
			DllHelpers::Function<DllHelpers::__cdecl__, void, char*, char*, char*>   char_mix_cdecl   (lib, "char_mix_cdecl");
			DllHelpers::Function<DllHelpers::__stdcall__, void, char*, char*, char*> char_mix_stdcall (lib, "char_mix_stdcall");

			char in1[11] = "0123456789";
			char in2[11] = "abcdefghjk";

				{
					char out[21];
					char_mix_cdecl(in1, in2, out);
					EXPECT_EQ(std::string("0a1b2c3d4e5f6g7h8j9k"), out);
				}

				{
					char out[21];
					char_mix_stdcall(in1, in2, out);
					EXPECT_EQ(std::string("0a1b2c3d4e5f6g7h8j9k"), out);
				}
		}
		catch (std::exception)
		{
			// Should not execute this
			EXPECT_TRUE(false);
		}
}


TEST(DllTest, FunctionUnsuccessTest01)
{
		try
		{
			DllHelpers::Library lib("TestDll.dll");
			DllHelpers::Function<DllHelpers::__cdecl__, double, double, double>   sum_cdecl  (lib, "sum_lkdjgklfjslgjfd");
			// Should not execute this because of exception
			EXPECT_TRUE(false);
		}
		catch (std::exception &e)
		{
			// Should execute this
			EXPECT_TRUE(true);
			EXPECT_EQ(std::string(e.what()), "Can't get proc address for sum_lkdjgklfjslgjfd");
		}
}


TEST(DllTest, FunctionUnsuccessTest02)
{
		try
		{
			DllHelpers::Library lib("TestDll.dll");
			DllHelpers::Function<DllHelpers::__stdcall__, double, double, double> sum_stdcall(lib, "sum_jsdgtiwesufd");
			// Should not execute this because of exception
			EXPECT_TRUE(false);
		}
		catch (std::exception &e)
		{
			// Should execute this
			EXPECT_TRUE(true);
			EXPECT_EQ(std::string(e.what()), "Can't get proc address for sum_jsdgtiwesufd");
		}
}


TEST(DllHelpersTest, WinAPITest01)
{
		// "GetComputerNameA" from kernel32.dll invocation
		try
		{
			DllHelpers::Library kernel32("kernel32.dll");
			DllHelpers::Function<DllHelpers::__stdcall__, BOOL, LPSTR, LPDWORD> computerName(kernel32, "GetComputerNameA");

			DWORD length = MAX_COMPUTERNAME_LENGTH + 1;
			char name[MAX_COMPUTERNAME_LENGTH + 1];
			BOOL result = computerName((LPSTR)&name[0], (LPDWORD)&length);

			std::cout << std::endl << "Your computer's name is: " << name << std::endl << std::endl;
		}
		catch(...)
		{
			EXPECT_TRUE(false);
		}
}



#include "../main.h"
