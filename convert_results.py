#!/usr/bin/env python3

import sys

timeseries = {}
with open(sys.argv[1], "r") as infile:
    for line in infile:
        time, pid, tickets, ticks = line.split(',')
        if time not in timeseries:
            timeseries[time] = {}
        timeseries[time][pid] = ticks.strip()

with open(sys.argv[2], "w") as outfile:
    for time, ticks in timeseries.items():
        print(
            f"{time} {ticks['1']} {ticks['2']} {ticks['3']} {ticks['4']} {ticks['5']} {ticks['6']}",
            file=outfile
        )
