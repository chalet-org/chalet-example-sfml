#!/usr/bin/env bash

SFML_PATH="$1"

perl -i -pe 's/.*/\tif(NOT SFML_OS_ANDROID AND NOT SFML_OS_MACOSX)/ if $.==115' "$SFML_PATH/cmake/Macros.cmake"
