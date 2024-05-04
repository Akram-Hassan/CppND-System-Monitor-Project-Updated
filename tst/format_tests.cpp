#include  <string>

#include <gtest/gtest.h>
#include <format.h>

TEST(FormatTests, FormatTest) {
    EXPECT_STREQ(Format::ElapsedTime(6).c_str(),    "00:00:06");
    EXPECT_STREQ(Format::ElapsedTime(13).c_str(),   "00:00:13");
    EXPECT_STREQ(Format::ElapsedTime(60).c_str(),   "00:01:00");
    EXPECT_STREQ(Format::ElapsedTime(127).c_str(),  "00:02:07");
    EXPECT_STREQ(Format::ElapsedTime(3598).c_str(), "00:59:58");
    EXPECT_STREQ(Format::ElapsedTime(3600).c_str(), "01:00:00");
}