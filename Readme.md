[![MacOS / clang](https://github.com/wrazik/TankBotFight/actions/workflows/macos_clang.yaml/badge.svg)](https://github.com/wrazik/TankBotFight/actions/workflows/macos_clang.yaml)
[![Ubuntu / gcc11](https://github.com/wrazik/TankBotFight/actions/workflows/ubuntu_gcc.yaml/badge.svg)](https://github.com/wrazik/TankBotFight/actions/workflows/ubuntu_gcc.yaml)
[![Windows / msvc](https://github.com/wrazik/TankBotFight/actions/workflows/windows_msvc.yaml/badge.svg)](https://github.com/wrazik/TankBotFight/actions/workflows/windows_msvc.yaml)
# TankBotFight - platform for code competition

This project is C++ Platform for competition between AI bots written in any supported language.

Client will communicate with platform with platform via sockets.

![scheme](https://user-images.githubusercontent.com/6102580/122928199-eca20500-d369-11eb-9020-ba32641b6cbf.png)






# Current state
Currently we have moving & shooting tank, background with customly generated roads. No network yet, no collisions yet.


https://user-images.githubusercontent.com/6102580/141752043-4d35d34a-1e36-4264-9967-169acfb3823b.mp4


# How to run
To compile the project you should have compiler that supports C++20 & cmake.
You have to remember about two things: 
- Graphical files are stored in git-lfs
- Package manager is stored as github submodule
- Dependencies are installed via vcpkg




## Downloading the repo

So, before you start, you must first download checkout git-lfs (https://git-lfs.github.com/)
```bash
> git lfs install
> git lfs pull
```
In case you already run `git lfs install` before cloning the repo, `pull` is not needed

To download submodules, run:
```bash
> git submodule init
> git submodule update
```

Next step is to install all dependencies with vcpkg

## Install dependencies with package manager

### Linux & MacOS
```bash
  ./vcpkg/bootstrap-vcpkg.sh
  ./vcpkg/vcpkg install
```
### Windows

```bash
.\vcpkg\bootstrap-vcpkg.bat
.\vcpkg\vcpkg install
```

## CMake generation
```
mkdir build
cd build
cmake ..
make
```

# Contributing
We need help! If you have time & want to help - take a look at "Issues". 

All PRs should contain tests. 

To format the code, please use clang-format (configuration file is attached to the repo)


