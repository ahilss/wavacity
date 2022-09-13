# Wavvy Audio Editor

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
    -Dwavvy_use_wxwidgets=system \
    -Dwavvy_use_expat=system \
    -Dwavvy_use_lame=system \
    -Dwavvy_use_sndfile=system \
    -Dwavvy_use_soxr=system \
    -Dwavvy_use_portaudio=system \
    -Dwavvy_use_sqlite=local \
    -Dwavvy_use_ffmpeg=linked \
    -Dwavvy_use_id3tag=system \
    -Dwavvy_use_mad=system \
    -Dwavvy_use_nyquist=local \
    -Dwavvy_use_vamp=off \
    -Dwavvy_use_ogg=system \
    -Dwavvy_use_vorbis=system \
    -Dwavvy_use_flac=system \
    -Dwavvy_use_lv2=off \
    -Dwavvy_use_midi=off \
    -Dwavvy_use_portmixer=off \
    -Dwavvy_use_portsmf=off \
    -Dwavvy_use_sbsms=off \
    -Dwavvy_use_soundtouch=system \
    -Dwavvy_use_twolame=off \
    -Dwavvy_use_vst=off"

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
