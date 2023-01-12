#!/bin/bash

make -j$(nproc)
sudo make install -j$(nproc)
