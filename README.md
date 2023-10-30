# Table of Contents

* **[R-Type 👾](#r-type-)**
* **[Supported Platforms](#supported-platforms)**
* **[Required dependencies](#required-dependencies)**
* **[Compilation](#compilation)**
* **[Server](#server)**

# R-Type 👾
This project reproduces the [Horizontal Shoot'em Up](https://en.wikipedia.org/wiki/Shoot_%27em_up#Scrolling_shooters) game with the [same name](http://www.hardcoregaming101.net/r-type/) as the project.
> <picture>
>   <source media="(prefers-color-scheme: dark)" srcset="https://github.com/Mqxx/GitHub-Markdown/blob/main/blockquotes/badge/dark-theme/note.svg">
>   <img alt="Note" src="https://github.com/Mqxx/GitHub-Markdown/blob/main/blockquotes/badge/dark-theme/note.svg">
> </picture><br>
>
> The game may differ from the original one, as it is not supposed to be an exact replica

The project is composed of two different parts: The client and the server, both in C++.

The project is based on the SFML library to handle the server as well as to display all the things.

# Supported Platforms
The game can run on Linux and Windows 10.

# Required dependencies
For Linux, you'll need cmake and GCC

For Windows, you'll need cmake and MinGW-w64

# Compilation

To compile the project:

On Linux use
```
cmake -B"build" -H"."
cd build
make
cd ..
```
On Windows, you can use the `build.bat` batch file, or do it manually, like so:
```
make -B"build" -H"."
cmake --build "build" -j 8
```

# Server
To launch the server, you just have to do it like this:
```
./server <server-port>
```

# Client
To launch the client, just do:
```
./client
```

After this you're able to select between single and multiplayer. The single player launches the level 1, while the multiplayer asks you for a server port
