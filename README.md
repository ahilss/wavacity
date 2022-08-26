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
