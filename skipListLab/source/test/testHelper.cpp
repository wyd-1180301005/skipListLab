# ifndef testhelper_cpp
# define testhelper_cpp

# include "gtest/gtest.h"
using namespace testing;

template<typename T>
AssertionResult  assert_equal(T a ,T b)
{
    if (a==b)
    {
        return AssertionSuccess() ;
    }
    return AssertionFailure() << __FILE__ <<" : "<<__LINE__;
}

# endif