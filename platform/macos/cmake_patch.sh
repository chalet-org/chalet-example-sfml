#!/usr/bin/env bash

SFML_PATH="$1"

perl -i -pe 's/.*/\t\t\tset_target_properties(${target} PROPERTIES DEBUG_POSTFIX "")/ if $.==98' "$SFML_PATH/cmake/Macros.cmake"
perl -i -pe 's/.*/\tif(NOT SFML_OS_ANDROID AND NOT SFML_OS_MACOSX)/ if $.==115' "$SFML_PATH/cmake/Macros.cmake"


