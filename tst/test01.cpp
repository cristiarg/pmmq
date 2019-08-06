#define CATCH_CONFIG_MAIN

#include <iostream>

#include "catch.hpp"

#include "Message.hpp"
#include "Broker.hpp"
#include "IProducer.hpp"
#include "IConsumer.hpp"

class Producer1 : public pmmq::IProducer {
public:
    Producer1(pmmq::XBroker& _broker)
        : pmmq::IProducer(_broker)
    {
    }

    ~Producer1() override
    {
    }
};

class Consumer1 : public pmmq::IConsumer {
public:
    Consumer1(const wchar_t _message_type)
        : pmmq::IConsumer(_message_type)
        , consumed_count{0}
    {
    }

    Consumer1::~Consumer1() override
    {
    }

    void Consumer1::consume(pmmq::XMessage& _message) const override
    {
        REQUIRE(_message->contents.size() > 0);
        ++consumed_count;
    }

    int get_consumed_count() const
    {
        return consumed_count;
    }

private:
    mutable int consumed_count;
};

TEST_CASE("Broker 1: ctor/dtor")
{
    {
        auto xb1 = std::make_shared<pmmq::Broker>();
        REQUIRE(xb1 != nullptr);
    }
    REQUIRE(true);
}

TEST_CASE("Broker 1: subscribe/unsubscribe")
{
    int res{0};

    auto xb1 = std::make_shared<pmmq::Broker>();
    REQUIRE(xb1 != nullptr);

    auto cons1 = std::make_shared<Consumer1>(L'a');
    REQUIRE(cons1 != nullptr);
    res = xb1->subscribe(cons1);
    REQUIRE(res == 0);

    auto cons2 = std::make_shared<Consumer1>(L'a');
    REQUIRE(cons2 != nullptr);
    res = xb1->subscribe(cons2);
    REQUIRE(res == 0);

    res = xb1->unsubscribe(cons1);
    REQUIRE(res == 0);
    res = xb1->unsubscribe(cons1);
    REQUIRE(res == 0);
}

//TEST_CASE("Broker 2: simple use")
//{
//    int res{0};
//
//    auto xb1 = std::make_shared<pmmq::Broker>();
//    REQUIRE(xb1 != nullptr);
//
//    auto prod1 = std::make_shared<Producer1>(xb1);
//    REQUIRE(prod1 != nullptr);
//
//    auto cons1 = std::make_shared<Consumer1>(L'a');
//    REQUIRE(cons1 != nullptr);
//    res = xb1->subscribe(cons1);
//    REQUIRE(res == 0);
//
//    auto cons2 = std::make_shared<Consumer1>(L'a');
//    REQUIRE(cons2 != nullptr);
//    res = xb1->subscribe(cons2);
//    REQUIRE(res == 0);
//
//    const int message_count = 7;
//
//    for (int i = 0; i < message_count; i++) {
//        pmmq::XMessage mess1 = std::make_shared<pmmq::Message>(L'a', L"a message of type 'a'");
//        REQUIRE(mess1 != nullptr);
//
//        res = prod1->dispatch(mess1);
//        REQUIRE(res == 0);
//    }
//
//    res = xb1->unsubscribe(cons1);
//    REQUIRE(res == 0);
//    res = xb1->unsubscribe(cons1);
//    REQUIRE(res == 0);
//
//    REQUIRE(message_count== cons1->get_consumed_count());
//}

