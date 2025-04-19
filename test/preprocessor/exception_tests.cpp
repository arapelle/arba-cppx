#include <arba/cppx/preprocessor/exception.hpp>

#include <gtest/gtest.h>

#include <format>
#include <stdexcept>

TEST(enabled_exceptions_tests, try_throw_catch__throw_with_abort_message__catch_runtime_error)
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

TEST(enabled_exceptions_tests, try_throw_catch__throw_without_abort_message__catch_runtime_error)
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

TEST(enabled_exceptions_tests, try_throw_catch__catch_any__catch_any)
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
    ARBA_CPPX_CATCH_ANY()
    {
        SUCCEED();
    }
}

TEST(enabled_exceptions_tests, try_throw_catch__rethrow__ok)
{
#ifdef ARBA_CPPX_NO_EXCEPTIONS
    FAIL();
#endif
    try
    {
        ARBA_CPPX_TRY
        {
            ARBA_CPPX_THROW(std::runtime_error("exception"));
        }
        ARBA_CPPX_CATCH_ANY()
        {
            ARBA_CPPX_RETHROW();
        }
    }
    catch (const std::runtime_error& err)
    {
        SUCCEED();
    }
}
