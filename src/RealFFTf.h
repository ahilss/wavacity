#ifndef __realfftf_h
#define __realfftf_h

#include "Wavacity.h"

#include "Experimental.h"

#include "MemoryX.h"

using fft_type = float;
struct FFTParam {
   ArrayOf<int> BitReversed;
   ArrayOf<fft_type> SinTable;
   size_t Points;
#ifdef EXPERIMENTAL_EQ_SSE_THREADED
   int pow2Bits;
#endif
};

struct FFTDeleter{
   void operator () (FFTParam *p) const;
};

using HFFT = std::unique_ptr<
   FFTParam, FFTDeleter
>;

HFFT GetFFT(size_t);
void RealFFTf(fft_type *, const FFTParam *);
void InverseRealFFTf(fft_type *, const FFTParam *);
void ReorderToTime(const FFTParam *hFFT, const fft_type *buffer, fft_type *TimeOut);
void ReorderToFreq(const FFTParam *hFFT, const fft_type *buffer,
		   fft_type *RealOut, fft_type *ImagOut);

#endif

