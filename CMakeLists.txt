cmake_minimum_required(VERSION 3.10.0)
project(csort VERSION 0.1.0 LANGUAGES C)

add_executable(csort bubble.c common.c heap.c insertion.c main.c merge.c quick.c selection.c stopwatch.c)

