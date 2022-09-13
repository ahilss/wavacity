/**********************************************************************

  Audacity: A Digital Audio Editor

  Spectrum.h

  Dominic Mazzoni

**********************************************************************/

#ifndef __WAVACITY_SPECTRUM__
#define __WAVACITY_SPECTRUM__

#include "FFT.h"

/*
  This function computes the power (mean square amplitude) as
  a function of frequency, for some block of audio data.

  width: the number of samples
  calculates windowSize/2 frequency samples
*/

bool ComputeSpectrum(const float * data, size_t width, size_t windowSize,
                     double rate, float *out, bool autocorrelation,
                     int windowFunc = eWinFuncHann);

#endif
