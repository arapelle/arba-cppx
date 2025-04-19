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
TEST(disabled_exceptions_tests, try_throw_catch__abort_with_message__ok)
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

TEST(disabled_exceptions_tests, try_throw_catch__abort_without_message__ok)
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
// clang-format on
