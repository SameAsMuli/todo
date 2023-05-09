# TODO

[![sameasmuli-todo](https://snapcraft.io/sameasmuli-todo/badge.svg)](https://snapcraft.io/sameasmuli-todo)
[![Build](https://github.com/SameAsMuli/todo/actions/workflows/cmake.yml/badge.svg)](https://github.com/SameAsMuli/todo/actions)
[![Codacy](https://github.com/SameAsMuli/todo/actions/workflows/codacy.yml/badge.svg)](https://github.com/SameAsMuli/todo/actions)

A command line TODO management utility written in C++.

Written mostly as an exercise to learn C++ but also because I was unable to find an existing program that did what I wanted out of the box e.g. file searching and directory-level tasks.

Inspired by similar projects such as [Taskwarrior](https://taskwarrior.org/).

## Features

**Current:**

- Multiple priority levels for TODOs (low, normal, high and urgent).
- Add, remove, complete, uncomplete and archive TODOs.
- Automatic archiving of complete TODOs after 24 hours.
- Location-based TODOs (allows different TODO lists for different directories/projects).
- Compatible with any POSIX system.
- File searching for a defined TODO string

## Installation

Available for installation via the snap store:

[![Get it from the Snap Store](https://snapcraft.io/static/images/badges/en/snap-store-black.svg)](https://snapcraft.io/sameasmuli-todo)

## Build From Source

Requires a C++17 compatible compiler, CMake, git, and an internet connection to compile; all other dependencies are downloaded via CMake. Create a build directory in the root of the project and compile using CMake:

```
mkdir build
cd build
cmake ..
make install
```
