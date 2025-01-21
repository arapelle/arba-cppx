#include <arba/cppx/macro/exception.hpp>

#include <gtest/gtest.h>

#include <format>
#include <stdexcept>

TEST(enabled_exceptions_tests, try_throw_catch__abort_with_message__ok)
{
#ifdef ARBA_CPPX_NO_EXCEPTIONS
    FAIL();
#endif
    CPPX_TRY
    {
        CPPX_THROW(std::runtime_error("exception"), "error_msg");
    }
    CPPX_CATCH(const std::invalid_argument& err)
    {
        FAIL();
    }
    CPPX_CATCH(const std::runtime_error& err)
    {
        const std::string err_what = err.what();
        ASSERT_EQ(err_what, "exception");
    }
    CPPX_CATCH(const std::exception& err)
    {
        FAIL();
    }
}

TEST(enabled_exceptions_tests, try_throw_catch__abort_without_message__ok)
{
#ifdef ARBA_CPPX_NO_EXCEPTIONS
    FAIL();
#endif
    ARBA_CPPX_TRY
    {
        ARBA_CPPX_THROW(std::runtime_error("exception"));
    }
    ARBA_CPPX_CATCH(const std::invalid_argument& err)
    {
        FAIL();
    }
    ARBA_CPPX_CATCH(const std::runtime_error& err)
    {
        const std::string err_what = err.what();
        ASSERT_EQ(err_what, "exception");
    }
    ARBA_CPPX_CATCH(const std::exception& err)
    {
        FAIL();
    }
}
