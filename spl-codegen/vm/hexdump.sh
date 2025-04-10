#!/bin/sh
# dump the given file in hex, with a big-endian format
od --endian=big -t x4 "$@"
