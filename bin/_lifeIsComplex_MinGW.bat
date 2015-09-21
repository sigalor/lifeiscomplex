@echo off
echo OpenGL Programm Assistent - MinGW
echo =======================================

set staticDefault=-static-libgcc -static-libstdc++
set staticSFML=-lglew32 -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -ljpeg
:: -lwinmm and -lgdi32 for staticSDL too, but static SFML already contains them
:: Information for static SDL linking from here: http://stackoverflow.com/a/18561999
set staticSDL=-lmingw32 -lSDL2main -lSDL2 -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid
set staticSDLTTF=-lSDL2_ttf -lfreetype

g++ -IC:/MinGW/include/ -LC:/MinGW/lib/ -std=c++11 -fmax-errors=1 -s -Os -o lifeIsComplex.exe /path/to/src/lifeIsComplex.cpp %staticDefault% %staticSDL% %staticSFML% %staticSDLTTF%
echo.
upx lifeIsComplex.exe
echo.
pause