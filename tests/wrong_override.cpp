#include <adc/converter.hpp>

using namespace mhaa::adc;

class WrongOverride final : public Converter
{
public:
    Status start(ChannelId channel) const override;
};
