# Wavacity Audio Editor

## Prerequisites

expat  
libid3tag  
flac  
lame  
libmad  
libogg  
libsndfile  
libvorbis  
ffmpeg  
soundtouch  
soxr  
portaudio-wasm  
wxwidgets-wasm  

## Building

export CFLAGS=-I/Users/ahilss/emsdk/3.1.12-wasm32/emscripten/system/local/include  
export CXXFLAGS=-I/Users/ahilss/emsdk/3.1.12-wasm32/emscripten/system/local/include  
export LDFLAGS=-L/Users/ahilss/emsdk/3.1.12-wasm32/emscripten/system/local/lib  

export CMAKE_ARGS=" \
    -DCMAKE_SYSTEM_NAME=Linux \
    -DCMAKE_PREFIX_PATH=/Users/ahilss/emsdk/3.1.12-wasm32/emscripten/system/local \
    -DWASM=1 \
    -DwxWidgets_CONFIG_EXECUTABLE=~/emsdk/3.1.12-wasm32/emscripten/system/local/bin/wx-config \
    -Dwavacity_use_wxwidgets=system \
    -Dwavacity_use_expat=system \
    -Dwavacity_use_lame=system \
    -Dwavacity_use_sndfile=system \
    -Dwavacity_use_soxr=system \
    -Dwavacity_use_portaudio=system \
    -Dwavacity_use_sqlite=local \
    -Dwavacity_use_ffmpeg=linked \
    -Dwavacity_use_id3tag=system \
    -Dwavacity_use_mad=system \
    -Dwavacity_use_nyquist=local \
    -Dwavacity_use_vamp=off \
    -Dwavacity_use_ogg=system \
    -Dwavacity_use_vorbis=system \
    -Dwavacity_use_flac=system \
    -Dwavacity_use_lv2=off \
    -Dwavacity_use_midi=off \
    -Dwavacity_use_portmixer=off \
    -Dwavacity_use_portsmf=off \
    -Dwavacity_use_sbsms=off \
    -Dwavacity_use_soundtouch=system \
    -Dwavacity_use_twolame=off \
    -Dwavacity_use_vst=off"

$EMSCRIPTEN/emcmake cmake $CMAKE_ARGS $SOURCE_DIR

$EMSCRIPTEN/emmake make
=======
[![Audacity](https://forum.audacityteam.org/styles/prosilver/theme/images/Audacity-logo_75px_trans_forum.png)](https://www.audacityteam.org) 
=========================

[**Audacity**](https://www.audacityteam.org) is an easy-to-use, multi-track audio editor and recorder for Windows, Mac OS X, GNU/Linux and other operating systems. Developed by a group of volunteers as open source.

- **Recording** from any real, or virtual audio device that is available to the host system.
- **Export / Import** a wide range of audio formats, extendible with FFmpeg.
- **High quality** using 32-bit float audio processing.
- **Plug-ins** Support for multiple audio plug-in formats, including VST, LV2, AU.
- **Macros** for chaining commands and batch processing.
- **Scripting** in Python, Perl, or any language that supports named pipes.
- **Nyquist** Very powerful built-in scripting language that may also be used to create plug-ins.
- **Editing** multi-track editing with sample accuracy and arbitrary sample rates.
- **Accessibility** for VI users.
- **Analysis and visualization** tools to analyze audio, or other signal data.

## Getting Started

For end users, the latest Windows and macOS release version of Audacity is available from the [Audacity website](https://www.audacityteam.org/download/).
Help with using Audacity is available from the [Audacity Forum](https://forum.audacityteam.org/).
Information for developers is available from the [Audacity Wiki](https://wiki.audacityteam.org/wiki/For_Developers).
