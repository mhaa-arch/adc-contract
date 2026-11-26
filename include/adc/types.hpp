#ifndef MHAA_ADC_TYPES_HPP
#define MHAA_ADC_TYPES_HPP

#include <stdint.h>

namespace mhaa
{
    namespace adc
    {
        enum class ChannelId : uint16_t
        {
        };
        using Sample = uint32_t;
        enum class Reference
        {
            Supply,
            Internal,
            External
        };
        enum class ReferenceId : uint16_t
        {
        };
        struct ReferenceSelection
        {
            Reference kind;
            ReferenceId id;
        };

        enum class TriggerId : uint16_t
        {
        };
        enum class TriggerKind
        {
            Software,
            External,
            Timer
        };
        struct TriggerSource
        {
            TriggerKind kind;
            TriggerId source_id;
        };

        enum class Status
        {
            Success,
            Busy,
            NoSample,
            InvalidChannel,
            Unsupported,
            Error
        };
    }
}

#endif
