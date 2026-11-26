#include <adc/converter.hpp>

using namespace mhaa::adc;

class Incomplete final : public Converter
{
public:
    Status try_read(Sample &sample) override;
    uint8_t resolution_bits() const override;
};

int main()
{
    Incomplete implementation;
    (void)implementation;
}
