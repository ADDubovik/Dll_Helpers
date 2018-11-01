#include <gtest/gtest.h>

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



#include "../main.h"
