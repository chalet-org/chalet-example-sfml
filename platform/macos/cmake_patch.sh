#!/usr/bin/env bash

perl -i -pe 's/.*/\tif(NOT SFML_OS_ANDROID AND NOT SFML_OS_MACOSX)/ if $.==115' chalet_external/sfml/cmake/Macros.cmake
