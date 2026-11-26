# ADC Contract guide

Starting, completing and consuming a conversion are separate events. In particular, a completed but unread sample still occupies the converter. Start with the conversion lifecycle, then read how reference and trigger routes are named.

1. Start with [the contract](contract.md) for implementer obligations and capability boundaries.
2. Read [the conformance example](examples.md) for an implementation you can compile locally.
3. Consult [the portability notes](compatibility.md) before choosing a hardware mapping.