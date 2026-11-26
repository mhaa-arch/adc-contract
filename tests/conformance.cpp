#include <adc/converter.hpp>
#include <adc/reference_control.hpp>
#include <adc/trigger_control.hpp>

#include <cassert>

using namespace mhaa::adc;

class Fake final : public Converter
{
public:
    Fake(uint8_t bits, Sample value) : bits_(bits), value_(value) {}

    Status start(ChannelId channel) override
    {
        if (channel != ChannelId{})
        {
            return Status::InvalidChannel;
        }
        if (started_)
        {
            return Status::Busy;
        }
        started_ = true;
        return Status::Success;
    }

    Status try_read(Sample &sample) override
    {
        if (!started_)
        {
            return Status::NoSample;
        }
        if (!ready)
        {
            return Status::Busy;
        }
        sample = value_;
        started_ = false;
        return Status::Success;
    }

    uint8_t resolution_bits() const override { return bits_; }

    bool ready = false;

private:
    uint8_t bits_;
    Sample value_;
    bool started_ = false;
};

class ConfigurableInputs final : public ReferenceControl, public TriggerControl
{
public:
    Status set_reference(ReferenceSelection reference) override
    {
        return reference.kind == Reference::Supply && reference.id == ReferenceId{} ? Status::Success : Status::Unsupported;
    }
    bool nominal_reference_uv(uint32_t &voltage_uv) const override
    {
        voltage_uv = 3300000;
        return true;
    }

    Status set_trigger(TriggerSource trigger) override
    {
        return trigger.kind == TriggerKind::Software && trigger.source_id == TriggerId{}
                   ? Status::Success
                   : Status::Unsupported;
    }
};

int main()
{
    Fake fake(10, 700);
    Converter &converter = fake;
    Sample sample = 7;
    assert(converter.try_read(sample) == Status::NoSample && sample == 7);
    assert(converter.start(ChannelId{}) == Status::Success);
    assert(converter.try_read(sample) == Status::Busy && sample == 7);
    fake.ready = true;
    assert(converter.try_read(sample) == Status::Success && sample == 700);
    assert(converter.resolution_bits() == 10);
    ConfigurableInputs inputs;
    ReferenceControl &reference = inputs;
    TriggerControl &trigger = inputs;
    assert(reference.set_reference({Reference::External, ReferenceId{}}) == Status::Unsupported);
    assert(reference.set_reference({Reference::Supply, ReferenceId{}}) == Status::Success);
    assert(trigger.set_trigger({TriggerKind::Timer, static_cast<TriggerId>(2)}) == Status::Unsupported);
    assert(trigger.set_trigger({TriggerKind::Software, TriggerId{}}) == Status::Success);
}
