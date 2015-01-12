# diagnostics-standalone

Stand-alone versions of some flow diagnostics tools from OPM.
Any programs and supporting parts have been extracted from the
opm-core module and modified to compile and run without OPM.

This package contains a program: compute_eikonal_from_files,
that solves the anisotropic eikonal equation.

To build the program, create a directory parallel to this one
and call it eikonal-build, run cmake there and run make:

cd ..
mkdir eikonal-build
cmake ../eikonal
make

Then the program should be ready for use. You can use it from MRST
by using the opmEikonal.m function, although it requires a function
(the writeMRSTGrid function) that is not generally available.


# Troubleshooting:

The program requires a fairly new version of Boost (1.49), and
on (for example) Ubuntu 12.04 version 1.46.1 is standard, you may
need to upgrade your libboost-dev package.

You may want to edit the path given in opmEikonal.m to the program
if you chose to build it in a different location.
