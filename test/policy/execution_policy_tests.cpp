#include <arba/cppx/policy/execution_policy.hpp>

#include <gtest/gtest.h>
#include <algorithm>
#include <random>

int func(cppx::ExecutionPolicy auto)
{
    return 0;
}

int func(std::execution::parallel_policy)
{
    return 642;
}

TEST(execution_policy_tests, test_execution_policy)
{
    ASSERT_EQ(func(std::execution::par), 642);
    ASSERT_EQ(func(std::execution::seq), 0);
    ASSERT_EQ(func(std::execution::unseq), 0);
    ASSERT_EQ(func(std::execution::par_unseq), 0);
}

static_assert(cppx::execution::are_all_std_policies_available() ==
#ifdef ARBA_CPPX_EXECUTION_ALL_STD_POLICIES
    true
#else
    false
#endif
);

#ifdef ARBA_CPPX_EXECUTION_ALL_STD_POLICIES
TEST(execution_policy_tests, execution_backend__use_or_not__ok)
{
    using duration_type = std::chrono::duration<float, ::std::chrono::milliseconds::period>;
    using clock_type = std::chrono::steady_clock;

    std::array<unsigned, 1024*1024> uints;

    std::ranges::generate(uints, std::mt19937_64(47));
    clock_type::time_point start_time_point = clock_type::now();
    std::sort(std::execution::seq, uints.begin(), uints.end());
    duration_type seq_duration = std::chrono::duration_cast<duration_type>(clock_type::now() - start_time_point);
    std::cout << "Chrono 'seq_duration' = " << seq_duration.count() << "ms" << std::endl;

    std::ranges::generate(uints, std::mt19937_64(47));
    start_time_point = clock_type::now();
    std::sort(std::execution::par, uints.begin(), uints.end());
    duration_type par_duration = std::chrono::duration_cast<duration_type>(clock_type::now() - start_time_point);
    std::cout << "Chrono 'par_duration' = " << par_duration.count() << "ms" << std::endl;

    if constexpr (cppx::execution::are_all_std_policies_available())
    {
        ASSERT_LT(par_duration.count(), seq_duration.count() * 0.6);
    }
    else
    {
        FAIL();
    }
}
#endif
