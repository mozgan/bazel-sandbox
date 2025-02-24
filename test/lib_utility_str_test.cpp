#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <string>
#include <string_view>

#include "lib/utility/str.hpp"

TEST(StringToInt, ValidPositive) {
  auto result = string_to<int>("123");
  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result.value(), 123);
}

TEST(StringToInt, ValidNegative) {
  auto result = string_to<int>("-456");
  ASSERT_TRUE(result);
  EXPECT_EQ(result, -456);
}

TEST(StringToInt, ValidZero) {
  auto result = string_to<int>("0");
  ASSERT_TRUE(result);
  EXPECT_EQ(result, 0);
}

TEST(StringToInt, ValidMaxInt) {
  auto result = string_to<int>(std::to_string(std::numeric_limits<int>::max()));
  ASSERT_TRUE(result);
  EXPECT_EQ(result, std::numeric_limits<int>::max());
}

TEST(StringToInt, ValidMinInt) {
  auto result = string_to<int>(std::to_string(std::numeric_limits<int>::min()));
  ASSERT_TRUE(result);
  EXPECT_EQ(result, std::numeric_limits<int>::min());
}

TEST(StringToInt, ValidPartialNumber) {
  auto result = string_to<int>("123abc");
  ASSERT_EQ(result, 123);
}

TEST(StringToInt, InvalidNonNumber) {
  auto result = string_to<int>("abc");
  ASSERT_FALSE(result);
}

TEST(StringToInt, InvalidEmpty) {
  auto result = string_to<int>("");
  ASSERT_FALSE(result);
}

TEST(StringToInt, InvalidOverflow) {
  auto result =
      string_to<int>(std::to_string(std::numeric_limits<int>::max()) + "0");
  ASSERT_FALSE(result);
}

TEST(StringToInt, InvalidUnderflow) {
  auto result =
      string_to<int>(std::to_string(std::numeric_limits<int>::min()) + "0");
  ASSERT_FALSE(result);
}

TEST(StringToUnsigned, ValidPositive) {
  auto result = string_to<unsigned int>("123");
  ASSERT_TRUE(result);
  EXPECT_EQ(result, static_cast<unsigned int>(123));
}

TEST(StringToUnsigned, ValidZero) {
  const auto result = string_to<int>("0");
  ASSERT_TRUE(result);
  EXPECT_EQ(result, 0);
}

TEST(StringToUnsigned, ValidMaxUnsigned) {
  auto result = string_to<unsigned int>(
      std::to_string(std::numeric_limits<unsigned int>::max()));
  ASSERT_TRUE(result);
  EXPECT_EQ(result, std::numeric_limits<unsigned int>::max());
}

TEST(StringToUnsigned, ValidPartialNumber) {
  auto result = string_to<unsigned>("123abc");
  ASSERT_EQ(result, static_cast<unsigned>(123));
}

TEST(StringToUnsigned, RejectsNegative) {
  auto result = string_to<unsigned int>("-123");
  ASSERT_FALSE(result);
}

TEST(StringToUnsigned, InvalidNonNumber) {
  auto result = string_to<unsigned>("abc");
  ASSERT_FALSE(result);
}

TEST(StringToUnsigned, InvalidEmpty) {
  auto result = string_to<unsigned>("");
  ASSERT_FALSE(result);
}

TEST(StringToUnsigned, InvalidNegative) {
  auto result = string_to<unsigned>("-123");
  ASSERT_FALSE(result);
}

TEST(StringToUnsigned, InvalidOverflow) {
  auto result = string_to<unsigned>(
      std::to_string(std::numeric_limits<unsigned int>::max()) + "0");
  ASSERT_FALSE(result);
}

TEST(StringToInt, HexadecimalConversion) {
  std::string input_hex_max = "7FFFFFFF";
  auto result_hex_max = string_to<int>(input_hex_max, 16);
  ASSERT_TRUE(result_hex_max.has_value());
  ASSERT_EQ(result_hex_max.value(), std::numeric_limits<int>::max());
}

TEST(StringToInt, OctalConversion) {
  std::string input_oct_max = "17777777777";
  auto result_oct_max = string_to<int>(input_oct_max, 8);
  ASSERT_TRUE(result_oct_max.has_value());
  ASSERT_EQ(result_oct_max.value(), std::numeric_limits<int>::max());
}

TEST(StringToFloat, Positive) {
  float expected = 1.23F;
  auto result = string_to<float>("1.23");
  ASSERT_TRUE(result);
  EXPECT_FLOAT_EQ(expected, result.value());
}

TEST(StringToFloat, Negative) {
  auto result = string_to<float>("-1.23");
  ASSERT_TRUE(result);
  EXPECT_FLOAT_EQ(-1.23F, result.value());
}

TEST(StringToFloat, Invalid) {
  auto result = string_to<float>("invalid");
  ASSERT_FALSE(result);
}

TEST(StringToFloat, Empty) {
  auto result = string_to<float>("");
  ASSERT_FALSE(result);
}

TEST(StringToFloat, Locale) {
  // Could extend to support locales
  auto result = string_to<float>("1,23");
  ASSERT_EQ(result, 1);
}

TEST(StringToFloat, Pointer) {
  const char* str = "1.23";
  auto result = string_to<float>(str);
  ASSERT_EQ(result, 1.23F);
}

TEST(StringToDouble, ValidConversion) {
  auto result = string_to<double>(std::string("123.45"));
  ASSERT_TRUE(result.has_value());
  EXPECT_DOUBLE_EQ(result.value(), 123.45);
}

TEST(StringToDouble, InvalidConversion) {
  auto result = string_to<double>(std::string("abc"));
  ASSERT_FALSE(result.has_value());
}

TEST(StringToDouble, NegativeValue) {
  auto result = string_to<double>(std::string("-67.89"));
  ASSERT_TRUE(result.has_value());
  EXPECT_DOUBLE_EQ(result.value(), -67.89);
}

TEST(StringToDouble, ScientificNotation) {
  auto result = string_to<double>(std::string("1.23e4"));
  ASSERT_TRUE(result.has_value());
  EXPECT_DOUBLE_EQ(result.value(), 12300.0);
}

TEST(StringToDouble, UnsuccessfulConversionWithTrailingWhitespaces) {
  auto result = string_to<double>(std::string("   789.012  "));
  ASSERT_FALSE(result.has_value());
}

TEST(StringToDouble, UnsuccessfulConversionWithLeadingAndTrailingWhitespaces) {
  auto result = string_to<double>(std::string("  \t  -456.789 \n"));
  ASSERT_FALSE(result.has_value());
}

TEST(StringToDouble, SuccessfulConversionOfZero) {
  auto result = string_to<double>(std::string("0"));
  ASSERT_TRUE(result.has_value());
  EXPECT_DOUBLE_EQ(result.value(), 0.0);
}

TEST(StringToDouble, SuccessfulConversionOfPositiveInfinity) {
  auto result = string_to<double>(std::string("inf"));
  ASSERT_TRUE(result.has_value());
  EXPECT_DOUBLE_EQ(result.value(), std::numeric_limits<double>::infinity());
}

TEST(StringToDouble, SuccessfulConversionOfNegativeInfinity) {
  auto result = string_to<double>(std::string("-inf"));
  ASSERT_TRUE(result.has_value());
  EXPECT_DOUBLE_EQ(result.value(), -std::numeric_limits<double>::infinity());
}

TEST(StringToDouble, SuccessfulConversionOfNaN) {
  auto result = string_to<double>(std::string("nan"));
  ASSERT_TRUE(result.has_value());
  EXPECT_TRUE(std::isnan(result.value()));
}

TEST(StringToDouble, LargePositiveValue) {
  auto result =
      string_to<double>(std::to_string(std::numeric_limits<double>::max()));
  ASSERT_TRUE(result.has_value());
  EXPECT_DOUBLE_EQ(result.value(), std::numeric_limits<double>::max());
}

TEST(StringToDouble, LargeNegativeValue) {
  auto result =
      string_to<double>(std::to_string(std::numeric_limits<double>::lowest()));
  ASSERT_TRUE(result.has_value());
  EXPECT_DOUBLE_EQ(result.value(), std::numeric_limits<double>::lowest());
}

TEST(StringToDouble, PrecisionLoss) {
  auto result = string_to<double>(std::to_string(1.234567890123456789));
  ASSERT_TRUE(result.has_value());
  EXPECT_DOUBLE_EQ(result.value(), 1.234568);
}

TEST(StringToDouble, SuccessfulConversionOverflow) {
  auto result = string_to<double>(
      std::to_string(std::numeric_limits<double>::max()) + "1");
  EXPECT_EQ(result, std::numeric_limits<double>::max());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
