#define CATCH_CONFIG_MAIN

#include <iostream>
#include <strstream>

#include "catch.hpp"

#include "Message.hpp"
#include "Broker.hpp"
#include "IConsumer.hpp"

#include "Producer1.hpp"
#include "Consumer1.hpp"

static const int PROD_COUNT{ 3 };
static const int CONS_COUNT{ 275 };
static const int MESS_COUNT{ 2300 };

TEST_CASE("Broker 1")
{
    auto brok = std::make_shared<pmmq::Broker>();

    std::vector<XProducer1> prod_vec;
    for (int i = 0; i < PROD_COUNT; i++) {
        prod_vec.push_back(std::make_shared<Producer1>(brok, L'a', (i + 1), MESS_COUNT));
    }

    std::vector<XConsumer1> cons_vec;
    for (int i = 0; i < CONS_COUNT; i++) {
        auto cons = std::make_shared<Consumer1>(L'a');

        brok->subscribe(cons);

        cons_vec.push_back(cons);
    }

    for (auto& prod : prod_vec) {
        prod->produce();
    }

    for (const auto& cons : cons_vec) {
        //const Consumer1* const cons1 = dynamic_cast<Consumer1*>(cons.get());
        REQUIRE(MESS_COUNT * PROD_COUNT == cons->get_consumed_count());
    }
}

