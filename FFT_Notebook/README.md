# FFT library from DSP CMSIS

The DSP CMSIS [Library](https://www.keil.com/pack/doc/CMSIS/DSP/html/group__ComplexFFT.html) is used for efficient FFT evaluation. This directory contains source code and results of testing the library.

This project's files are divided into two groups:
* Jupyter Notebook:
  * generation time-based signal, 
  * generation frequency specrum using scipy FFT,
  * evaluation bins-bounds function and generationg LUT,
  * reconstructing oryginal signal from CMSIS lib's results using IFFT,
  * comparing results.
* STM32CubeIDE project:
  * evaluating FFT based on sample signal from Notebook,
  * comparing with arrays of magnitudes from Notebook,
  * estimating execution time and accuracy.
  
[STM32F446RET6](https://www.st.com/en/microcontrollers-microprocessors/stm32f446re.html) with 180 MHz CLK frequency is used.

Check details in [Jupyter Notebook](ASD_V2_STM32_FFT_simulation.ipynb) and source code for STM32 especially [ASD_FFT_testbench.h](STM32F4_Project/Core/Inc/ASD_FFT_testbench.h) file containing benchmarking function. More examples of using CMSIS DSP are in SDK folder:
```
\STM32Cube\Repository\STM32Cube_FW_F4_X\Drivers\CMSIS\DSP\Examples
```
## Requirements
* minimum FFT refreshrate: 30 Hz (optimal 60 Hz),
* sampling frequency: 44 kHz,
* 1024 points FFT.


# Test signal

The samples count with the sampling frequency directly influence sampling time. When choosing how many samples are needed following factors must be taken into account:
* what precision is needed - more samples means higher prcision but longer FFT evaluation time,
* what sampling rate is needed - based on Nyquist-Shannon theorem it should be twice as high as the highest harmonic in the signal. In case of sound analysys 44 kHz is enough.
* wheter samples can be gather in background or in blocking function,
* if sampling takes too long, is it possible to use "windowing" to extract a batch of samples.

By windowing I mean feeding longer cyclic buffer with samples and evaluating FFT on selected subarray. By using this method higher reshreshrate can be achieved but some samples will be reused more than one time.

<p align="center">
  <img width="500" alt="Refresh rate of 44 kHz FFT varing with number of samples" src="Results/fft_note_1.png">
</p>

If 1024 points FFT would be chosen, then even with blocking sampling function entire buffer will be fed with frequency greather than 30 Hz.

## Input signal generation

Using numpy the signal can be generated. It consists of 1024 samples with values set by sum of 2 harmonics (low and higher) with white noise:

```python
np.random.seed(1)

samples_count = 1024
sampling_time = samples_count * 1 / sampling_frequency

# Testing frequencies
frequency_1 = 30
frequency_2 = 19999

noise = np.random.normal(loc=0, scale=0.1, size=samples_count)

# Time samples
t = np.arange(samples_count) / sampling_frequency

# Amplitude samples
val = np.sin(2 * pi * frequency_1 * t) + 0.1 * np.sin(2 * pi * frequency_2 * t) + noise
```

The 1024 samples of signal are shown in the plot.

<p align="center">
  <img width="500" alt="1024 samples of the signal" src="Results/fft_note_2.png">
</p>

## Reference FFT

By using scipy the FFT results can be obtained. As argument it gets list of time-based samples, and returnes frequency doimain complex list. Only half of the resulting FFT data is being preserved, due to conjugate symmetry, other half of the data is redundant.

```python
import scipy.fftpack

ref_fft_data = scipy.fftpack.fft(val)
mags = 2.0/samples_count * np.abs(ref_fft_data[:samples_count//2])
freqs = sampling_frequency*np.arange(samples_count//2)/samples_count

```

Resulting complex list (or numpy array) can be split to real and imaginary parts.

```python
sig_fft_real = yf.real
sig_fft_imag = yf.imag
```

<p align="center">
  <img width="500" alt="FFT of mixed signal (30 Hz + 19999 Hz + white noise)" src="Results/fft_note_3.png">
</p>

# Using CMSIS FFT Library

The detalis about using FFT DSP CMSIS can be found in the example [arm_fft_bin_example](arm_fft_bin_example.zip). To see how to add DSP CMSIS to the project see this article.

Following functions are needed:
```c
  arm_cfft_f32(&arm_cfft_sR_f32_len1024, testInput_f32_10khz, ifftFlag, doBitReverse);

  /* Process the data through the Complex Magnitude Module for
  calculating the magnitude at each bin */
  arm_cmplx_mag_f32(testInput_f32_10khz, testOutput, fftSize);

  /* Calculates maxValue and returns corresponding BIN value */
  arm_max_f32(testOutput, fftSize, &maxValue, &testIndex);
```

In  the example *testInput_f32_10khz* is float32_t array of twice length (2048) with interleaved data of real samples and imaginary part (0 at the beginning).

*arm_cfft_sR_f32_len1024* is structure constant used to indicate length of FFT points and required tables sizes used in mixed-radix algorithm.

*testOutput* length is 1024 the same as value of *fftSize*.
*maxValue* and *testIndex* can be used to retrive value of max lobe in the spectrum.

## Benchmarking FFT CMSIS

Results of benchmarking function:

```
START TEST, IT WILL TAKE 10000 MS...
STOP TEST! DONE 51196 ITERATIONS AND (WITH 1024 FFT POINTS) GOT 5119 Hz REFRESH RATE (T = 195 US), ERROR: 0.031%.
```

Resulting error is calculated with comparison to FFT data from Jupyter Notebook. The average relative error is 0.031%. The execution time is negligibly small in comparison to the sampling time.

The results from embedded system are transfered to Jupyter Notebook for further visualization.

## FFT results visualization	

The data in frequency domain is identical. FFT from scipy and from CMSIS are compared.

<p align="center">
  <img width="500" alt="FFT data comparison" src="Results/fft_note_9.png">
</p>

Also reconstructed time-based signal are identical. Oryginal signal and the time-based signal reconstructed from embedded system FFT results are compared.

<p align="center">
  <img width="500" alt="Reconstructed FFT" src="Results/fft_note_10.png">
</p>

Zoom in

<p align="center">
  <img width="500" alt="Reconstructed FFT" src="Results/fft_note_11.png">
</p>

# Bins to bounds conversion

The figh resolution amplitude spectrum must be narrowed down to 19 bands of the display. So exponential conversion function must be used.

Exponential function if better for visualization because it highlights small changes in lower frequencies. Resultings bands has narrower frequency range on lower frequencies and higher frequency range on higher frequencies.

|Bin|Min/Max frequency|Frequency range|
|:--|---|---|
|Bin 0 |from 0.0 Hz to 86.11 Hz| 86.11 Hz|
|Bin 1 |from 86.11 Hz to 258.32 Hz|  172.21 Hz|
|Bin 2 |from 258.32 Hz to 559.69 Hz|  301.37 Hz|
|Bin 3 |from 559.69 Hz to 990.22 Hz| 430.53 Hz|
|Bin 4 |from 990.22 Hz to 1549.9 Hz|  559.69 Hz|
|Bin 5 |from 1549.9 Hz to 2238.75 Hz|  688.85 Hz|
|Bin 6 |from 2238.75 Hz to 3013.7 Hz|  774.95 Hz|
|Bin 7 |from 3013.7 Hz to 3917.81 Hz|  904.11 Hz|
|Bin 8 |from 3917.81 Hz to 4951.08 Hz|  1033.27 Hz|
|Bin 9 |from 4951.08 Hz to 6113.5 Hz|  1162.43 Hz|
|Bin 10 |from 6113.5 Hz to 7405.09 Hz|  1291.59 Hz|
|Bin 11 |from 7405.09 Hz to 8825.83 Hz|  1420.74 Hz|
|Bin 12 |from 8825.83 Hz to 10332.68 Hz|  1506.85 Hz|
|Bin 13 |from 10332.68 Hz to 11968.69 Hz|  1636.01 Hz|
|Bin 14 |from 11968.69 Hz to 13776.91 Hz| 1808.22 Hz|
|Bin 15 |from 13776.91 Hz to 15671.23 Hz|  1894.32 Hz|
|Bin 16 |from 15671.23 Hz to 17651.66 Hz|  1980.43 Hz|
|Bin 17 |from 17651.66 Hz to 19804.31 Hz| 2152.64 Hz|
|Bin 18 |from 19804.31 Hz to 22043.05 Hz| 2238.75 Hz|

## Conversion function

The exponent factor must be choosen so that each band has assigned at least one bin.

```python
def gen_bins(bands_count, samples_count, k=1.0):
  return [floor(bands_count*(i/samples_count)**k) for i in range(0, samples_count)]
```

Smaller values of *k* works better - there is less bins assigned to low index bounds.

<p align="center">
  <img width="500" alt="Bins to bounds function - different values of k" src="Results/fft_note_5.png">
</p>

<p align="center">
  <img width="500" alt="Bins to bounds function - bargraph" src="Results/fft_note_6.png">
</p>

*k* = 0.5 is choosen. Resulting numbe of assigned bins to bounds:
```
Number of bins per bound:  {0: 2, 1: 4, 2: 7, 3: 10, 4: 13, 5: 16, 6: 18, 7: 21, 8: 24, 9: 27, 10: 30, 11: 33, 12: 35, 13: 38, 14: 42, 15: 44, 16: 46, 17: 50, 18: 52} , total:  512 
```

<p align="center">
  <img width="500" alt="Bins to bounds function k = 0.5" src="Results/fft_note_7.png">
</p>

## The display visualization

Using the amplitude spectrum and bins to bounds LUT visualization can be done.

<p align="center">
  <img width="500" alt="Audio Spectrum Display visualization" src="Results/fft_note_8.png">
</p>

The input signal can have too high amplitude so that some bands can oveershoot the display limits. Normalising signal is not a good option. It is better to set limit and indicate the overshoot - red color in the visualization.

## Examplar binds to bounds LUT

Size of the LUT is half size of the input signal = 512. The FFT data is at first full size = 1024 but then it get's halved resulting in 512 magintudes values which have to be narrowed down to 19 bands.

```c
#define BINS_COUNT 512
const int bins[BINS_COUNT] = {0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18};
```