### mygame

An OpenGL game.

NOT USABLE. This is a learning exercise only.

<br>

### Build

Repository contains and statically compiles all dependencies on any platform via CMake.

```cmd
$ git clone https://github.com/mottosso/mygame.git
$ cd mygame
$ mkdir build && cd build

:: Replace with your flavour
$ cmake -G "Visual Studio 14 2015" ..
$ cmake --build .

:: Run game
$ mygame/Debug/mygame
```
