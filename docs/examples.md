# ADC Contract example

[The conformance program](../tests/conformance.cpp) pairs a simulated implementation with assertions at the Contract boundary. The fake implements `Converter` with `override` and separates the pending flag from a ready sample. Its configured 10-bit test case produces 700. The test first polls an idle converter, then starts channel zero and verifies that a pending poll preserves the sentinel value. It marks the fake ready and consumes the sample. Separate simulated controls show how a reference or trigger can accept one route and reject another.

## Implementation excerpt

This class is taken from the program. The linked source contains the test cases and any additional fixtures.

```cpp
#include <adc/converter.hpp>
#include <adc/reference_control.hpp>
#include <adc/trigger_control.hpp>


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
```

## Build and run

From this repository root, with assertions enabled, compile the full program. A passing run exits with status 0 and prints no output. Use `conformance.exe` on Windows.

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude tests/conformance.cpp -o conformance
./conformance
```

To verify enforcement of the abstract interface, compile the two negative sources separately. The first should diagnose an abstract type and the second an incompatible override.

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -fsyntax-only tests/missing_override.cpp
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -fsyntax-only tests/wrong_override.cpp
```
