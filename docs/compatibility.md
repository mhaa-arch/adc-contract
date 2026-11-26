# Porting the ADC Contract

Channel IDs, reference route IDs and trigger route IDs describe the bound converter's map. Hardware Definitions can describe mux selections, reference facilities and trigger sources. The Adapter translates those facts into the logical map and documents any reserved inputs or rate and settling restrictions. Some converters expose only one reference or support software triggering only.

The code width and unsigned representation are portable. Signed and differential samples and calibrated voltage conversion require a separate model. Matching code widths alone do not imply matching voltages, precision or acquisition times.

This repository's host simulations and shared API compile/link checks provide source-level evidence. Target timing and physical behavior require hardware validation.
