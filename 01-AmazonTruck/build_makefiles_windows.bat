setlocal cd /d %~dp0
RD /S /Q "build"
MKDIR build
CD build
cmake -G "MinGW Makefiles" ..
make
