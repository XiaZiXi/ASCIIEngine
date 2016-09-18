Dragonfly Egg
Kelly Zhang (kezhang)

Engine Code & Game Code written and tested in Visual Studio 2015. 
NOT YET TESTED ON LINUX. make WITH CAUTION.

TestGame contains a few tests in LibraryTest.cpp. Could have added more but was
short on time. Currently it has a few functions attempting tests on LogManager and
one on testing the Clock class. Running TestGame.exe will make 100 heroes and by using
step events, it will change its position every 1 second until after 5 seconds, when
game over is called.

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
