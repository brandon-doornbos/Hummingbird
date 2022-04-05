#!/bin/sh

if command -v mangohud &> /dev/null; then
    mangohud ./hummingbird
else
    ./hummingbird
fi
