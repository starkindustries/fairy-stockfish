# Developers Guide

This guide is specifically designed for users who are working on a Windows operating system. Please adapt the instructions accordingly if you are using a different OS.

## Install Windows-Subsystem-for-Linux (WSL)

We recommend using WSL for compiling Fairy Stockfish. Install WSL from PowerShell:

```
wsl --install -d ubuntu
```

## Cross-compiling Fairy Stockfish

Launch WSL and install the necessary tools:
```
sudo apt update
sudo apt install -y g++ mingw-w64
```

Cross-compile Fairy Stockfish to a `.exe` file with the following commands:
```
make clean
make build ARCH=x86-64 COMP=mingw
```

Once the build completes, verify your `.exe`:
```
$ file stockfish.exe
stockfish.exe: PE32+ executable (console) x86-64, for MS Windows
```

Verify the .exe works back in PowerShell:
```
PS C:\fairy-stockfish\src> .\stockfish.exe
Fairy-Stockfish 080623 by Fabian Fichter
```

Enter the `uci` command and verify that Stockfish returns the `uciok` response:
```
uci
id name Fairy-Stockfish 080623
id author Fabian Fichter

option name Debug Log File type string default
option name Threads type spin default 1 min 1 max 512
[...]
uciok
```

## Install Python Binding

```
python setup.py install
```

OR 
```
pip install wheel
python setup.py bdist_wheel
```

Then:
```
pip install .\dist\pyffish-0.0.78-cp311-cp311-win_amd64.whl --force-reinstall
```

## Building Doxygen Documentation

Make sure you have `Doxygen` and `Graphviz` installed. Then run the `doxygen` command in the root directory:
```
doxygen
```