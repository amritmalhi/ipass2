#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

TEST_CASE("Test case", "[tags][otherTags]") {
    REQUIRE(10 == 10);
}
