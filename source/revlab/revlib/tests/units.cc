#include "gtest/gtest.h"

#include "LIB_units.hh"

using namespace revlab::units;

namespace {

TEST(Units, ConvertKilometerToMeters) {
	EXPECT_FLOAT_EQ(LIB_unit_distance(1.0f, kilometer), 1000.0f);
}

TEST(Units, ConvertMeterToMeters) {
	EXPECT_FLOAT_EQ(LIB_unit_distance(5.0f, meter), 5.0f);
}

TEST(Units, ConvertCentimeterToMeters) {
	EXPECT_FLOAT_EQ(LIB_unit_distance(100.0f, centimeter), 1.0f);
}

TEST(Units, ConvertMillimeterToMeters) {
	EXPECT_FLOAT_EQ(LIB_unit_distance(1000.0f, millimiter), 1.0f);
}

TEST(Units, ConvertInchToMeters) {
	EXPECT_FLOAT_EQ(LIB_unit_distance(1.0f, inch), 0.0254f);
}

TEST(Units, ConvertFootToMeters) {
	EXPECT_FLOAT_EQ(LIB_unit_distance(1.0f, foot), 0.3048f);
}

TEST(Units, ConvertZero) {
	EXPECT_FLOAT_EQ(LIB_unit_distance(0.0f, meter), 0.0f);
}

TEST(Units, ConvertNegativeDistance) {
	EXPECT_FLOAT_EQ(LIB_unit_distance(-5.0f, centimeter), -0.05f);
}

TEST(Units, ConvertFractionalDistance) {
	EXPECT_FLOAT_EQ(LIB_unit_distance(2.5f, kilometer), 2500.0f);
}

TEST(Units, ConvertLargeDistance) {
	EXPECT_FLOAT_EQ(LIB_unit_distance(100.0f, kilometer), 100000.0f);
}

}  // namespace
