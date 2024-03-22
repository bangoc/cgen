cmake_minimum_required(VERSION 2.8)
project(training)
add_executable(demo demo.c bst-int.c)
add_executable(rand-put rand-put.c bst-int.c)