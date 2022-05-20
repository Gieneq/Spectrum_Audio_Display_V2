# Test 256 FFT

Several Tests CMSIS DSP library from ST and Samples generated from Notebook

## Test_1_36MHz_256_O0

* CLOCK: 36MHz
* Optimization: None -O0

The same signal samples are processed, but there is no difference when changing samples applied. Achieved 1116 Hz refresh rate. Results are staedy, differ only by 1 ieration.

## Test_2_36MHz_256_Ofast

* CLOCK: 36MHz
* Optimization: None -Ofast

A bit slower, 1097 Hz.