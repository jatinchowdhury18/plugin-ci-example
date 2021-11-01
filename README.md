# SimplePlugin

[![CI](https://github.com/jatinchowdhury18/plugin-ci-example/actions/workflows/cmake.yml/badge.svg)](https://github.com/jatinchowdhury18/plugin-ci-example/actions/workflows/cmake.yml)
[![CI-Projucer](https://github.com/jatinchowdhury18/plugin-ci-example/actions/workflows/projucer.yml/badge.svg)](https://github.com/jatinchowdhury18/plugin-ci-example/actions/workflows/projucer.yml)
![gitlab-actions](https://gitlab.com/Chowdhury-DSP/plugin-ci-example/badges/main/pipeline.svg)
[![Build Status](https://dev.azure.com/jatinchowdhury180362/plugin-ci-example/_apis/build/status/jatinchowdhury18.plugin-ci-example?branchName=main)](https://dev.azure.com/jatinchowdhury180362/plugin-ci-example/_build/latest?definitionId=1&branchName=main)
[![License](https://img.shields.io/badge/License-BSD-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

This repository contains a simple audio plugin with examples
for how to use various Continuous Integration services.

Currently the following CI services are supported:
- GitHub Actions
- Azure Pipelines
- GitLab CI

## Building

To build from scratch, you must have CMake installed.

```bash
# Clone the repository
$ git clone https://github.com/jatinchowdhury18/plugin-ci-example.git
$ cd plugin-ci-example

# initialize and set up submodules
$ git submodule update --init --recursive

# build with CMake
$ cmake -Bbuild
$ cmake --build build --config Release
```

## License

The code in this repository is open source, and is licensed
under the BSD 3-clause license. Enjoy!
