#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/rhein/Desktop/svr-sample-function/svr-vivado-hls/svr-vivado-hls/solution1/.autopilot/db/a.g.bc ${1+"$@"}
