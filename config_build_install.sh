#!/bin/bash

# builds with all hw drivers disabled
# run ./autogen.sh && ./configure --help for more options

./autogen.sh
./configure --disable-all-drivers --enable-demo --without-zlib --without-libserialport --without-libftdi --without-libhidapi --without-libbluez --without-libnettle --without-libusb --without-librevisa --without-libgpib --without-libieee1284 --without-libgio --disable-ruby --disable-java --disable-python
./build_and_install.sh
