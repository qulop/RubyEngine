#include <gtest/gtest.h>

#include <common/types/Result.hpp>
#include <common/types/String.hpp>


namespace {
    constexpr Kiwi::u32 TEST_INTEGER = 9516;
    const Kiwi::String TEST_STRING = "AmyClaraVika";


    struct TestData {
        Kiwi::u32 value = 0;
        Kiwi::String text;

        TestData() = default;
        TestData(Kiwi::u32 v, const Kiwi::String& t) :
            value(v),
            text(t)
        {}

        bool operator==(const TestData& other) const {
            return value == other.value && text == other.text;
        }
    };

    struct MoveOnlyData {
        Kiwi::u32 data = 0;

        MoveOnlyData() = default;
        explicit MoveOnlyData(Kiwi::u32 d) :
            data(d)
        {}

        MoveOnlyData(const MoveOnlyData&) = delete;
        MoveOnlyData& operator=(const MoveOnlyData&) = delete;

        MoveOnlyData(MoveOnlyData&&) = default;
        MoveOnlyData& operator=(MoveOnlyData&&) = default;
    };
}


TEST(Result_Test, InitializationWithSuccessValue) {
    using namespace Kiwi;

    Result<u32> successResult = Success(TEST_INTEGER);

    EXPECT_TRUE(successResult);
    EXPECT_TRUE(successResult.HasValue());
    EXPECT_FALSE(successResult.HasError());
    EXPECT_EQ(successResult.GetValue(), TEST_INTEGER);
}

TEST(Result_Test, InitializationWithError) {
    using namespace Kiwi;

    constexpr auto testError = Error{ .kind = EGeneralError::INVALID_ARGUMENT };
    constexpr Result<u32> errorResult = testError;

    EXPECT_FALSE(errorResult);
    EXPECT_FALSE(errorResult.HasValue());
    EXPECT_TRUE(errorResult.HasError());
    EXPECT_EQ(errorResult.GetError().kind, testError.kind);
}

TEST(Result_Test, ValueOrDefault) {
    using namespace Kiwi;

    constexpr Result<u32> result = Error{ .kind = EGeneralError::INVALID_ARGUMENT };

    EXPECT_EQ(result.ValueOr(TEST_INTEGER), TEST_INTEGER);
}

TEST(Result_Test, LValueAccessAndMutation) {
    using namespace Kiwi;

    const u32 mutatedValue = 6159;
    const String mutatedString = "VictoriaClaraAmy";
    TestData mutatedData(mutatedValue, mutatedString);

    Result<TestData> result = Success<TestData>(std::in_place, TEST_INTEGER, TEST_STRING);

    TestData& data = result.GetValue();
    data = mutatedData;

    EXPECT_EQ(result.GetValue(), mutatedData);
}

TEST(Result_Test, PointerOperators) {
    using namespace Kiwi;

    Result<TestData> result = Success(TestData(TEST_INTEGER, TEST_STRING));

    EXPECT_EQ(result->value, TEST_INTEGER);
    EXPECT_EQ(result->text, TEST_STRING);

    EXPECT_EQ((*result).value, TEST_INTEGER);
    EXPECT_EQ((*result).text, TEST_STRING);

    TestData& data1 = result.GetValue();
    TestData& data2 = *result;
    EXPECT_EQ(&data1, &data2);

    constexpr u32 mutatedValue = 10;
    result->value = 10;
    EXPECT_EQ(result->value, mutatedValue);
}

TEST(Result_Test, GetValueDeathExpected) {
    using namespace Kiwi;

    Result<u32> result = Error{ .kind = EGeneralError::INVALID_ARGUMENT };
    EXPECT_DEATH(KIWI_IGNORE_RETURN(result.GetValue()), "");
}

TEST(Result_Test, GetErrorDeathExpected) {
    using namespace Kiwi;

    Result<u32> result = Success(10u);
    EXPECT_DEATH(KIWI_IGNORE_RETURN(result.GetError()), "");
}

/* TODO:
    Replace `std::expected` with `std::variant` in the Result implementation
    Right now after `Result::StealValue()` or `Result::StealError()` call `std::expected` doesn't
    resetting itself
*/
TEST(Result_Test, ValueSteal) {
    using namespace Kiwi;

    Result<MoveOnlyData> result = Success(MoveOnlyData(TEST_INTEGER));
    EXPECT_TRUE(result.HasValue());

    auto&& stolenData = result.StealValue();


    // EXPECT_FALSE(result.HasValue());
    EXPECT_EQ(stolenData.data, TEST_INTEGER);
}

TEST(Result_Test, ErrorSteal) {
    using namespace Kiwi;

    auto testError = Error{ .kind = EGeneralError::INVALID_ARGUMENT };

    Result<MoveOnlyData> result = testError;
    EXPECT_TRUE(result.HasError());

    auto&& stolenError = result.StealError();

    // EXPECT_FALSE(result.HasError());
    EXPECT_EQ(stolenError, testError);
}

TEST(Result_Test, VoidPartialSpecializationWithValue) {
    using namespace Kiwi;

    Result<void> result = Success<void>();

    EXPECT_TRUE(result.HasValue());
}

TEST(Result_Test, VoidPartialSpecializationWithError) {
    using namespace Kiwi;

    Result<void> result = Error{ .kind = EGeneralError::INVALID_ARGUMENT };

    EXPECT_TRUE(result.HasError());
}
