# McDota 

[![Gitter](https://badges.gitter.im/McDota/community.svg)](https://gitter.im/McDota/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)

![Bugboy](https://i.imgur.com/qC9hz14.png)

McDota is a Cheat and tinker tool for Dota 2 on Linux.

It has been built from the ground-up to be faster and better than previous cheats.

## Features
* Fully Dynamic Panorama UI that is created on runtime and modifies no files.
* Integrity System that tries to detect when and where updates break the cheat.
* All features are native C++
* No ConVars are changed ever
* Lua Execution ( implemented but not used, see `vscriptSystem->RunScript` )
* Camera Zoom, pitch/yaw
* ESP, spotted ESP ( when seen by enemy team ), info.
* No Fog / No Fog of War ( not a maphack )
* Full Protobuf packet interception/inspection/editing.
* More...
## System Requirements
* CMake
* a C++17 compiler ( like `clang` or `gcc` )
* Build essentials( make, `gdb`, etc.. )
* [google protobufs](https://github.com/protocolbuffers/protobuf/archive/v3.7.0.tar.gz) development library - Version 3.7.0 is recommended! The Newest versions are not compatible and will segfault even in proto2 mode!
## Build Instructions
####**Update:** Dota Anime-Patch has Introduced Pre-2011 String ABI into the game. This means you Need to build protobufs from Source!
#### (Pre-Requisite)Building Protobufs
```
First, uninstall any protobuf-devel package your distro may have. (Just the headers/libs don't remove Gnome)

git clone https://github.com/protocolbuffers/protobuf
git checkout v3.15.3
make -j8 CFLAGS=-D_GLIBCXX_USE_CXX11_ABI=0 CXXFLAGS=-D_GLIBCXX_USE_CXX11_ABI=0
cd src
sudo make install
sudo ldconfig #refresh .so cache

Check in the terminal the Version is correct.
[gamer@localhost McDota-Master]$ protoc --version
libprotoc 3.15.3
```


First Build Protobufs
`./rebuildprotos.sh`

Now you can build the project 
`cmake . && make -j`


*For a Debug Build*
`cmake . -DCMAKE_BUILD_TYPE="Debug" . && make -j`

## Usage Instructions
There are 3 different load scripts.
 **#2 is the Recommended way to load for online play**


 1. `load` will load "libMcDota.so" normally into the game. I normally use this just for development and don't recommend that you use it online because it is easy to detect.
 2. `load_carto` has Cartographer Integration(R) and will first check for [Cartographer](https://github.com/LWSS/Cartographer) to be loaded, then it will set the Cartographer settings for you, and finally inject McDota into the game. 
 3. `load-stealth` Will rename and move"libMcdota.so" into a file that looks legit and then load it into the Game. ( Originally made by [Marc](https://github.com/Marc3842h) for Spookware ). This is a good compromise if you don't want to install or use Cartographer.


Each script also has a corresponding unload script.  
#1 uses no spaces, #2 uses underscores, and #3 uses dashes. I use this format to tab autocomplete

Press `Insert` to Open/Close the in-game Menu ( works in-game and in-menu )
## Screenshots
![Main](https://i.imgur.com/k3HGweu.png)
![Visuals](https://i.imgur.com/MrkXw9Q.png)
## Known Issues
* There is a very rare tcmalloc bug I have encountered that will just crash your game. I can't seem to reproduce it when it happens.
* Sometimes the UI will not open on the first time, I think I have fixed this, but if this happens to you, check the console and just try again.
* Debug builds do not unload
* SELinux might cause a problem with hardhooks

## Credits
LWSS(me) - Founder

[praydog](https://github.com/praydog) - His [research](http://praydog.com/index.php/2015/06/24/an-analysis-of-the-source-2-engine-part-1-the-schema-system/) into the SchemaSystem helped me especially when I was starting the project.

[subhook](https://github.com/Zeex/subhook) - I Use a modified version of this library to do the Hard Hooks used for GC msgs ( changing .code section )

## License
GPL3 - 
see LICENSE.txt
