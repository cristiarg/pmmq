#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Message.hpp"
#include "Broker.hpp"

//unsigned int Factorial( unsigned int number ) {
//    return number <= 1 ? number : Factorial(number-1)*number;
//}

//TEST_CASE( "Factorials are computed", "[factorial]" )
//{
//    //REQUIRE( Factorial(1) == 1 );
//    //REQUIRE( Factorial(2) == 2 );
//    //REQUIRE( Factorial(3) == 6 );
//    //REQUIRE( Factorial(10) == 3628800 );
//}

TEST_CASE("Broker 1")
{
    const auto xb1 = std::make_shared<Broker>();
    REQUIRE(xb1 != nullptr);
}
