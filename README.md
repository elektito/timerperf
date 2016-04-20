timerperf
=========

This is a very simple program to test the performance of different
clocks on your computer. Simply build it with `make` and then run
`./timerperf` to see how much each timer call takes.

`timerperf` calculates the performance of `gettimeofday` and the
different flavors of `clock_gettime`.
