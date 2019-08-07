#pragma once


class Producer1 {
public:
    Producer1(pmmq::XBroker& _broker, wchar_t _message_type, int _id, int _message_count)
        : broker{_broker}
        , message_type{_message_type}
        , id{_id}
        , message_count{_message_count}
    {
    }

    void produce()
    {
        for (int i = 0; i < message_count; i++) {
            std::wstringstream ss;
            ss << L"Message " << (i + 1) << L" of type " << message_type << L" from producer " << id;
            auto m = std::make_shared<pmmq::Message>(message_type, ss.str());
            broker->dispatch(m);
        }
    }

private:
    pmmq::XBroker broker;
    const wchar_t message_type;
    const int id;
    const int message_count;
};

using XProducer1 = std::shared_ptr<Producer1>;

