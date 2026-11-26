#ifndef MHAA_ADC_REFERENCE_CONTROL_HPP
#define MHAA_ADC_REFERENCE_CONTROL_HPP

#include <stdint.h>
#include <adc/types.hpp>

namespace mhaa
{
    namespace adc
    {
        /** @brief Selects a voltage reference when the target offers a choice. */
        class ReferenceControl
        {
        public:
            virtual ~ReferenceControl() = default;

            virtual Status set_reference(ReferenceSelection reference) = 0;

            /** @brief Reports the selected nominal reference in microvolts when known.
             *  @return False leaves voltage_uv unchanged.
             */
            virtual bool nominal_reference_uv(uint32_t &voltage_uv) const = 0;
        };
    }
}

#endif
