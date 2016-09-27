Dragonfly 2c
Kelly Zhang (kezhang)

Engine Code & Game Code written and tested in Visual Studio 2015. 
NOT TESTED ON LINUX. make WITH CAUTION.

Engine contains the basic functionality (and some more) expected in this iteration.

TestGame contains the Dragonfly Naiad version of Saucer Shoot.

AudioTest contains a soundboard that tests Audio and ViewObject functionalities.

CollisionTest contains visual tests for object collision and movement.

DragonflyTests contains (sparse) unit testing for individual classes in the library.
    - Run DragonflyTests.exe in Debug/
    - Test output should appear in dragonfly.log

EXTRA ADDITIONAL FEATURES:
- df-config.txt parsing support
- Event registration. Objects now can registerEvent() and have the respective managers keep track of objects with those events
- Joystick support. Very barebones. Dragonfly just wraps around the existing SFML functionality & support. (TODO: Thouroughly test this)

--------------------------------------------------------------------

To build:

0) Setup development environment for Windows, Linux or MacOS.
See http://dragonfly.wpi.edu/engine/index.html#setup for details.

1) Build, as appropriate for the platform (e.g., "make" on Linux or
Mac, F7 on Windows from Visual Studio).

2) Run game, as appropriate for the platform (e.g., "./game" on
Linux or Mac, F5 on Windows from Visual Studio)

--------------------------------------------------------------------

Using this version of Dragonfly:

1) Download .zip or clone project
2) Extract the header files and the lib/ folder from Dragonfly/ and place them in a separate folder
3) Create an empty C++ project
4) Point additional library settings to the lib/ folder
5) Point additional include settings to where the header files are
6) Repeat steps 4 & 5 for SFML library

--------------------------------------------------------------------


Directories:

Engine/ - contains Visual Studio solution files (Microsoft Windows)
Engine/Debug - contains build files for the solution
Engine/Dragonfly/ - contains engine source code & project settings
Engine/Dragonfly/lib/ - contains Dragonfly .lib file
Engine/Dragonfly/include/ - contains Dragonfly header files

##Projects that use Dragonfly library##
TestGame/
saucer-shoot/
Engine/CollisionTest/
Engine/DragonflyTests/
Engine/AudioTest/

DragonflyTemplate.zip - Visual Studio Template with preloaded project settings to use Dragonfly. (TODO: Outdated project settings. Fix)

--------------------------------------------------------------------
