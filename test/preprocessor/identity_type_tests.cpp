#include <arba/cppx/preprocessor/identity_type.hpp>

#include <gtest/gtest.h>

#include <format>

#define ARBA_DEFINE_TYPE(using_type, type) using using_type = ARBA_CPPX_PP_IDENTITY_TYPE(type)
#define DEFINE_TYPE(using_type, type) using using_type = CPPX_PP_IDENTITY_TYPE(type)

TEST(identity_type_tests, identity_type__ok)
{
    ARBA_DEFINE_TYPE(container_t, std::vector<int>);
    static_assert(std::is_same_v<container_t, std::vector<int>>);
    DEFINE_TYPE(pair_t, (std::pair<int, int>));
    static_assert(std::is_same_v<pair_t, std::pair<int, int>>);
}
