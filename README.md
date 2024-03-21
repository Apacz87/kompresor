# kompresor

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)  

A C++ CLI tool for file compression and decompression

## Description

Features:

- Simple command-line interface for easy use,
- Supports basic compression using the deflate algorithm
- Offers functionalities for compressing, decompressing, and listing archive contents

## Command-line interface

```console
SYNOPSIS
        ./build/exec -c <files>... [-o <output file>] [-v] [--version]
        ./build/exec -d <file> [-o <output dir>] [-v] [--version]
        ./build/exec -l <files>... [-v] [--version]
        ./build/exec -h [-v] [--version]

OPTIONS
        -c          Compresses one or more files
        -d          Decompresses a zip archive
        -l          Lists the contents of a zip archive
        -h, --help  Display help message
        -v, --verbose
                    Enables verbose output with additional details

        --version   Print version information
```

## Compilation

```sh
$ cmake -S . -B build
# With an indication of the compiler (g++/clang++)
$ cmake -S . -B build -D CMAKE_CXX_COMPILER=clang++

$ cmake --build build --config Release

# Checking the correctness of code formatting.
$ cmake --build build --target clang-format-check
# Formatting the code according to the accepted rules.
$ cmake --build build --target clang-format
```
