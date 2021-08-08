[![MacOS / clang](https://github.com/wrazik/TankBotFight/actions/workflows/macos_clang.yaml/badge.svg)](https://github.com/wrazik/TankBotFight/actions/workflows/macos_clang.yaml)
[![Ubuntu / gcc11](https://github.com/wrazik/TankBotFight/actions/workflows/ubuntu_gcc.yaml/badge.svg)](https://github.com/wrazik/TankBotFight/actions/workflows/ubuntu_gcc.yaml)
# TankBotFight - platform for code competition

This project is C++ Platform for competition between AI bots written in any supported language.

Client will communicate with platform with platform via sockets.

![scheme](https://user-images.githubusercontent.com/6102580/122928199-eca20500-d369-11eb-9020-ba32641b6cbf.png)



# Current state
Currently we have moving & shooting tank, background with customly generated roads. No network yet, no collisions yet.
![ezgif com-gif-maker](https://user-images.githubusercontent.com/6102580/124426797-d5501800-dd6a-11eb-8df5-14d487e59c32.gif)


# How to run
To compile the project you should have compiler that supports C++20 & cmake.
You have to remember about two things: 
- Graphical files are stored in git-lfs
- range-v3 library is added as submodule

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

Now, you can proceed with standard cmake-like project:
```
mkdir build
cd build
cmake ..
make
```

# Contributing
TODO
# Supported languages
TODO
# API definition
TODO
# Compilation
TODO
