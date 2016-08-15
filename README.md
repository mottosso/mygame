### mygame

![image](https://cloud.githubusercontent.com/assets/2152766/17715767/93d2abb8-63fd-11e6-8430-c797cf2b4cbc.png)

An OpenGL game.

NOT USABLE. This is a learning exercise only.

<br>

### Build

Repository contains and statically compiles all dependencies on any platform via CMake.

**Dependencies**

All dependent libraries are included with the project, here are the tools needed to compile.

- cmake 3+
- C++11 compliant compiler

```cmd
$ git clone --recursive https://github.com/mottosso/mygame.git
$ cd mygame
$ mkdir build && cd build

:: Replace with your flavour
$ cmake -G "Visual Studio 14 2015" ..
$ cmake --build .

:: Run game
$ mygame/Debug/mygame
```

<br>

### Workflow

Once project files has been generated, and once the project has been built, then what?

1. The CMakeLists.txt includes a wildcard to capture all files in `/src` and `/include`. Re-running `cmake ..` would then cause any new files to be automatically added to compiler toolchain you happen to be using, such as Visual Studio.
