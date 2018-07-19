# ipass2
Library for MPU6050 Accelerometer and Gyroscope

Build environment provided my Chris Smeele and Robert Bezem

Dependencies
Essential:

arm-none-eabi-gcc 5.4.0
gcc 5.4.0
CMake version 3.5.1
Non-essential:

Valgrind-3.11.0 Used for detecting memory leaks, Linux only.
Python 2.7.12 Used by Lizard.
Lizard version 1.14.10 Used for calculating code complexity metrics.
Linux package install commands:

sudo apt install g++
sudo apt install cmake
sudo apt install valgrind
sudo apt install python2.7
sudo pip2 install lizard
Non-essential dependencies are normally only run during testing. Tests are run by the continuous integration, but it could be helpful to be able to run them offline.

Actual dependency version numbers may vary as long as the CLI interface and behavior match


