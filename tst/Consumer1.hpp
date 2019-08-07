#pragma once


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

    void Consumer1::consume(pmmq::XMessage& /*_message*/) const override
    {
        //std::wcout << _message->contents << std::endl;
        //REQUIRE(_message->contents.size() > 0);
        ++consumed_count;
    }

    int get_consumed_count() const
    {
        return consumed_count;
    }

private:
    mutable int consumed_count;
};

using XConsumer1 = std::shared_ptr<Consumer1>;

