Dragonfly Naiad
Kelly Zhang (kezhang)

Engine Code & Game Code written and tested in Visual Studio 2015. 
NOT YET TESTED ON LINUX. make WITH CAUTION.

Engine contains the basic functionality expected in this iteration, along with basic Joystick support.

TestGame contains the Dragonfly Naiad version of Saucer Shoot.

KNOWN BUGS:
Bullets sometimes do not go the full length and are destroyed early.
Graphical rendering hiccups. (Saucers "teleport")

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
vs-2015/TestGame/ - contains a "game" that makes a bunch of heroes to test engine capabilities
vs-2015/Dragonfly/ - contains engine source code

dragonfly.log is in vs-2015/Debug/

--------------------------------------------------------------------
