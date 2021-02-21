# TODO
A command line TODO management utility written in C++.

Written mostly as an exercise to learn C++ but also because I was unable to find an existing program that did what I wanted out of the box e.g. live display, file searching and directory-level tasks.

Inspired by similar projects such as [Taskwarrior](https://taskwarrior.org/).

## Features
**Current:**
* Multiple priority levels for TODOs (low, normal and urgent).
* Add, remove, complete, uncomplete and archive TODOs.
* Automatic archiving of complete TODOs after 24 hours.

**Planned:**
* Location-based TODOs (allows different TODO lists for different directories/projects).
* File searching for a defined TODO string
* "Live Display" to update TODO list as items are added or files are updated.

## Platforms
Currently tested on both Linux and MacOS. Should work on any POSIX compatible system.

## Dependencies
Requires CMake and an internet connection to compile; all other dependencies are downloaded via CMake.

## Installation
Create a build directory in the root of the project and compile using CMake:
```
mkdir build
cd build
cmake ..
make install
```
