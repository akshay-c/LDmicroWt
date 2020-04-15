# About LDMicro
LDmicro is a ladder logic editor, simulator and compiler for 8-bit microcontrollers. It can generate native code for Atmel AVR and Microchip PIC16 CPUs from a ladder diagram.

# LDMicro for Web
This is a Linux compatible version of the original LDMicro program for windows created by Jonathan Westhues, and ported to run on a web browser using the Wt library.

GitHub repository of LDMicro for windows can be found [here](https://github.com/akshay-c/LDmicro).

# Instructions
Before modifying contents of this git account, kindly make sure that you do not add unnecessary files that are created during the make process. In order to do so ensure that you always run the cmake and make commands in the build directory. The entire build directory is ignored by the gitignore file present in this file's parent directory.



## External package dependencies
The install commands for all the packages required to compile LDMicro for Linux are given below:

_Note_: Be sure to run `sudo apt-get update` and `sudo apt-get upgrade` before running the following commands

* Cmake: `sudo apt-get install cmake`
* GCC: 
  ```
  sudo apt-get install gcc
  sudo apt-get install g++
  ```
* MinGW: 
  ```
  sudo apt-get install gcc-mingw-w64
  sudo apt-get install g++-mingw-w64
  ```
* Perl: `sudo apt-get install perl`
* Wt:
  ```
  git clone https://github.com/emweb/wt.git
  mkdir build; cd build
  cmake ..
  sudo make install
  sudo ldconfig
  ```

# Building LDMicro for Linux
LDmicro for Linux is built using MinGW C++ compiler.

### Building the Makefile
In order to generate the Makefile that can be used to compile the project, simply run the following commands from a terminal in the project directory:
```
cd /LDmicro/
mkdir build
cd build/
cmake ..
```

### Building LDMicro for Linux
Simply run `make` in the build directory of the project to compile.

_Note_: In order to compile and create an executable, the Makefile must first be generated (see [Building the Makefile](#building-the-makefile)).

Multiple Perl Scripts are executed during the build phase. Perl is required in order to execute these scripts. To install the perl packages from the terminal (see [External package dependencies](#external-package-dependencies)).

## Running and testing LDMicro for Web
### Starting the webserver
If your cmake and make commands run successfully, you should now see an executable named `ldmicro.wt` along with the folders `docroot` and `approot` copied in your build directory.
We can now start the server on localport 9090 using following command:
`./ldmicro.wt --docroot ./docroot --approot ./approot --http-address 0.0.0.0 --http-port 9090`

### Run the webpage
You could now execute the webpage for LDmicro either using localhost or by typing in your ip adress at port 9090 as follows:
* visit `http://localhost:9090/` or
* `http://<your ip address>:9090/`
