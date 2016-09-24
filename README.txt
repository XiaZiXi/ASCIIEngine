Dragonfly Spawn
Kelly Zhang (kezhang)

Engine Code & Game Code written and tested in Visual Studio 2015. 
NOT TESTED ON LINUX. make WITH CAUTION.

Engine contains the basic functionality expected in this iteration, along with basic Joystick support.

TestGame contains the Dragonfly Naiad version of Saucer Shoot.

CollisionTest contains visual tests for object collision and movement.

DragonflyTests contains (sparse) unit testing for individual classes in the library.
    - Run DragonflyTests.exe in Debug/
    - Test output should appear in dragonfly.log

ERRORS:


KNOWN BUGS:
- Event registration doesn't work & causes access violations. Reverted back to having onEvent call all objects in the game world.

NOT YET TESTED:
- Sprite drawing
- Audio & Music

--------------------------------------------------------------------

To build:

0) Setup development environment for Windows, Linux or MacOS.
See http://dragonfly.wpi.edu/engine/index.html#setup for details.

1) Build, as appropriate for the platform (e.g., "make" on Linux or
Mac, F7 on Windows from Visual Studio).

2) Run game, as appropriate for the platform (e.g., "./game" on
Linux or Mac, F5 on Windows from Visual Studio)

--------------------------------------------------------------------

Directories:

vs-2015/ - contains Visual Studio solution files (Microsoft Windows)
vs-2015/Debug - should contain the Dragonfly library and the TestGame.exe
vs-2015/Dragonfly/ - contains engine source code

##Projects that use Dragonfly library##
vs-2015/TestGame/
vs-2015/CollisionTest/
vs-2015/DragonflyTests

DragonflyTemplate.zip - Visual Studio Template with preloaded project settings to use Dragonfly.

--------------------------------------------------------------------
