## C-step-counter

This port of the algorithm was developed within the thesis *Open-source algorithm for wearables in healthcare-applications* made by Anna Brondin & Marcus Nordstrom at Malmö University.

## Guide

You may need to optimise constants used in the algoritm which may depend on the actual accelerometer used.

 - Walk 150 steps (count them manually) while collecting raw accelerometry data into a CSV file formated as *time(ms), X, Y, Z*
 - These raw data should be collected multiple times and in different conditions (e.g. different walking speeds, styles, different terrains etc.)
 - Find the best constants with [C-optimize-variables](https://github.com/MarcusNordstrom/C-optimize-variables)
 - Modify the constants in this algorithm, for that, use the functions:
   - changeWindowSize(scoringWindowSize);
   - changeDetectionThreshold(detectionThreshold_whole, detectionThreshold_frac);
   - changeTimeThreshold(postTimeThreshold);
 - Build the library with cmake or add the library into your project
