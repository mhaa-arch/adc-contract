# ADC contract

## Conversion lifecycle

[Converter](../include/adc/converter.hpp) owns one outstanding conversion at a time. A valid `ChannelId` names an input on that converter. `start` accepts the channel, then starts software conversion or arms the selected trigger. Treat `InvalidChannel` as a configuration error and `Busy` as an outstanding conversion or unread sample.

`try_read` polls without blocking. It reports `Busy` while pending and `NoSample` when idle. `Success` stores and consumes the result. A terminal `Error` returns the converter to idle. Every non-success result preserves the caller's sample. A converter reports a resolution from 1 through 32 bits and returns straight-binary values from zero through `2^n - 1` for an `n`-bit result.

## Reference and trigger controls

[ReferenceControl](../include/adc/reference_control.hpp) selects a supply, internal or external reference and the converter-local route within that category. ID zero denotes the default route of the category. `nominal_reference_uv` may report a nominal voltage in microvolts. A false return preserves the output. The nominal value excludes measurement and calibration.

[TriggerControl](../include/adc/trigger_control.hpp) selects software or a mapped external or timer route. Use trigger ID zero for software. Both controls report `Busy` during an outstanding or unread conversion. Document supported selections and any settling time before sampling.

## Implementation boundary

The Adapter owns resource state. The caller must keep the implementation alive during each call and arrange access from other execution contexts. Document the contexts and concurrency guarantees of the actual implementation. Shared public types are in [`adc/types.hpp`](../include/adc/types.hpp).
