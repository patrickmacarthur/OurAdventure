OurAdventure
============

OurAdventure is a text-based adventure program.


Installation Instructions
-------------------------

The OurAdventure build system is based on cmake and requires cmake 2.6 or 
higher.

The build system has only been tested on Linux.  Building on Mac OS X and
Windows is probably possible but may be difficult.

To build:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

The executable will be in located at `build/src/OurAdventure`.  The default
cave file is in the `cave.dat` file.  You may install this into `/usr/local`
with:

    $ sudo make install

If you installed it, you may run the program with:

    $ OurAdventure

Otherwise, you may run the program from the main OurAdventure directory with:

    $ build/src/OurAdventure -c cave.dat

