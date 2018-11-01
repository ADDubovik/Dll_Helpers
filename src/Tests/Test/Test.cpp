#include <gtest/gtest.h>

#include "DllHelpers.h"


TEST(DllTest, Test01)
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



#include "../main.h"
