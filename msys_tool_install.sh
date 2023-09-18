#!/bin/bash

pacman -S mingw-w64-i686-toolchain
pacman -S mingw-w64-x86_64-toolchain

yes | pacman -S base-devel
yes | pacman -S autoconf-wrapper
yes | pacman -S msys/autoconf
yes | pacman -S msys/automake-wrapper
yes | pacman -S unzip
yes | pacman -S cmake
yes | pacman -S libiconv
yes | pacman -S git
yes | pacman -S pax