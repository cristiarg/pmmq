#define CATCH_CONFIG_MAIN

#include "catch2/catch.hpp"
#include "Broker.hpp"

TEST_CASE("Broker 1")
{
    const auto xb1 = std::make_shared<Broker>();

    REQUIRE(xb1 != nullptr);
}