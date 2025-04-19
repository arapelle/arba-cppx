#define ARBA_CPPX_NO_EXCEPTIONS

#include <arba/cppx/preprocessor/exception.hpp>

#include <gtest/gtest.h>

#include <format>
#include <stdexcept>

struct Foo
{
    Foo(const Foo&) {}
    std::string_view what() const { return "Foo::what()"; }
};

// clang-format off
TEST(disabled_exceptions_tests, try_throw_catch__throw_with_message__abort_with_message)
{
    ASSERT_DEATH({
        ARBA_CPPX_TRY
        {
            ARBA_CPPX_THROW(std::runtime_error("exception"), "error_msg");
        }
        ARBA_CPPX_CATCH(const std::exception& err)
        {
            FAIL() << err.what();
        }
        ARBA_CPPX_CATCH(int err_code)
        {
            FAIL() << err_code;
        }
        ARBA_CPPX_CATCH(Foo err)
        {
            FAIL() << err.what();
        }
        }, "error_msg"
        );
}

TEST(disabled_exceptions_tests, try_throw_catch__throw_without_message__abort_without_message)
{
    ASSERT_DEATH({
        CPPX_TRY
        {
            CPPX_THROW(std::runtime_error("exception"));
        }
        CPPX_CATCH(std::exception& err)
        {
            FAIL() << err.what();
        }
        }, ""
        );
}

TEST(disabled_exceptions_tests, try_throw_catch__catch_any__abort_with_message)
{
    ASSERT_DEATH({
        ARBA_CPPX_TRY
        {
            ARBA_CPPX_THROW(std::runtime_error("exception"), "error_msg");
        }
        ARBA_CPPX_CATCH(const std::invalid_argument& err)
        {
            FAIL() << err.what();
        }
        ARBA_CPPX_CATCH_ANY()
        {
            FAIL();
        }
        }, "error_msg"
        );
}

TEST(disabled_exceptions_tests, try_throw_catch__rethrow__abort_with_message)
{
    ASSERT_DEATH({
        ARBA_CPPX_TRY
        {
            ARBA_CPPX_THROW(std::runtime_error("exception"), "error_msg");
        }
        ARBA_CPPX_CATCH_ANY()
        {
            ARBA_CPPX_RETHROW();
        }
        }, "error_msg"
        );
}

// clang-format on
