Thinger Linux client is a library that allows connecting your Linux IoT devices to the [thinger.io](http://thinger.io "thinger.io IoT Cloud Platform") cloud platform, or even your private server deployment. This is a library specifically designed for the Linux Operating Systems, so you can easily connect devices like a Raspberry Pi, Intel Edison, Ubuntu, Mac, etc.

## In progress

This library is currently being developed and should not be integrated in any production device until it is more mature and tested. The library interface may change as it evolve to a stable version. Some things that requires attention now are:

 - Document code
 - Provide more examples and use cases
 - Provide a proper guide for installing the client as a service and support more devices like beaglebone
 - Check the reconnection mechanism and its reliability
 - Handle signals for proper daemon shutdown
 - Support OTA updates?
 - Load credentials from external config files?
 - Distribute the code as library?
 
## Quickstart
 
The simplest way to start using thinger.io platform in Linux is by modifying the ```src/main.cpp``` to add your username, device, and device credentials. 
Then you can type in your terminal ```./run.sh```, that will compile, start and run the thinger.io client.
  
## Notes for compiling on Raspberry Pi

- Check the compiler version and install a newer compiler if necessary. At least GCC 4.8.2.
- Install CMake ```sudo apt-get install cmake```
- Install Open SSL Libraries (not required but useful for secured connection) ```sudo apt-get install libssl-dev```

## License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The class is licensed under the [MIT License](http://opensource.org/licenses/MIT):

Copyright &copy; 2017 [THINK BIG LABS S.L.](http://thinger.io)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.