#define ARBA_CPPX_NO_EXCEPTIONS

#include <arba/cppx/macro/exception.hpp>

#include <gtest/gtest.h>

#include <format>
#include <stdexcept>

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
            FAIL();
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
        CPPX_CATCH(const std::exception& err)
        {
            FAIL();
        }
        }, ""
        );
}
// clang-format on
