# Testing FFT library from DSP CMSIS

CMSIS DSP [Library](https://www.keil.com/pack/doc/CMSIS/DSP/html/group__ComplexFFT.html) is used for FFT evaluation. This project is divided into two parts
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
  
[STM32F446RET6](https://www.st.com/en/microcontrollers-microprocessors/stm32f446re.html) is used with 180 MHz CLK frequency.

Check details in [Jupyter Notebook](ASD_V2_STM32_FFT_simulation.ipynb) and Source code for STM32 especially [ASD_FFT_testbench.h](STM32F4_Project/Core/Inc/ASD_FFT_testbench.h) file containing benchmarking function. More examples of using CMSIS DSP are in SDK folder **todo PATH**.

# Test signal

The samples count with sampling frequency directly influence sampling time. When choosing how many samples are needed following factors must be taken into account:
* what precision is needed - more samples means higher prcision but longer FFT evaluation time,
* what sampling rate is needed - based on Nyquist-Shannon theorem it should be twice as high as the highest harmonic in the signal. In case of sound analysys 44 kHz is enought.
* wheter samples can be gather in background or in blocking function,
* if sampling time is too high, is it possible to use "windowing".

By windowing I mean feedeing longer cyclic array with samples and evaluating FFT on selected subarray. Using this method higher reshreshrate can be achieved but some samples will be reused more than one time.

<p align="center">
  <img width="500" alt="Refresh rate of 44 kHz FFT varing with number of samples" src="Results/fft_note_1.png">
</p>

If 1024 points FFT would be chosen, then even with blocking sampling function entire buffer will be fed with frequency greather than 30 Hz. The 30 Hz frequency is required to achieve realtime respone time, but the higher frequency the better.

# Signal generation

Using numpy the signal can be generated. It consists of 1024 samples with values set by sum of 2 harmonics (low and higher) with white noise:

```python
np.random.seed(1)

# Twice as many samples are needed
samples_count = 1024

# Testing frequencies
frequency_1 = 30
frequency_2 = 19999

noise = np.random.normal(loc=0, scale=0.1, size=samples_count)

sampling_time = samples_count * 1 / sampling_frequency

t = np.arange(samples_count) / sampling_frequency
val = np.sin(2 * pi * frequency_1 * t) + 0.1 * np.sin(2 * pi * frequency_2 * t) + noise
```

1024 samples of signal:

<p align="center">
  <img width="500" alt="1024 samples of the signal" src="Results/fft_note_2.png">
</p>

# sdfgScipy FFT

Usining scipy FFt can be obtained. As argument it gets list of time-based samples, and returnes frequency doimain complex list. Half of dlaczego polowa???????

```python
import scipy.fftpack

yf = scipy.fftpack.fft(val)
mags = 2.0/samples_count * np.abs(yf[:samples_count//2])

```


```python
sig_fft_real = yf.real
sig_fft_imag = yf.imag
```


```python
xf = sampling_frequency*np.arange(samples_count)/samples_count
```











* CLOCK: 36MHz
* Optimization: None -O0

The same signal samples are processed, but there is no difference when changing samples applied. Achieved 1116 Hz refresh rate. Results are staedy, differ only by 1 ieration.

## Test_2_36MHz_256_Ofast

* CLOCK: 36MHz
* Optimization: None -Ofast

A bit slower, 1097 Hz.