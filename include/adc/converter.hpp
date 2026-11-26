#ifndef MHAA_ADC_CONVERTER_HPP
#define MHAA_ADC_CONVERTER_HPP

#include <stdint.h>
#include <adc/types.hpp>

namespace mhaa
{
    namespace adc
    {
        /** @brief Acquires unsigned, single-ended, straight-binary samples. */
        class Converter
        {
        public:
            virtual ~Converter() = default;

            /** @brief Starts or arms one conversion. Busy includes an unread conversion. */
            virtual Status start(ChannelId channel) = 0;

            /** @brief Polls and consumes one completed sample. Changes output on Success only. */
            virtual Status try_read(Sample &sample) = 0;
            virtual uint8_t resolution_bits() const = 0;
        };
    }
}

#endif
