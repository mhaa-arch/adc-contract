#ifndef MHAA_ADC_TRIGGER_CONTROL_HPP
#define MHAA_ADC_TRIGGER_CONTROL_HPP

#include <adc/types.hpp>

namespace mhaa
{
    namespace adc
    {
        /** @brief Selects the event that starts an armed conversion. */
        class TriggerControl
        {
        public:
            virtual ~TriggerControl() = default;
            virtual Status set_trigger(TriggerSource source) = 0;
        };
    }
}

#endif
