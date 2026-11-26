# Building

Builds run on GitHub (no compiler needed on your Windows 7/8 PC).
1. Push to GitHub. 2. Open the repo's Actions tab, open the latest "Build Windows" run.
3. Download the `AbsoluteCinema-windows` artifact, unzip, run `AbsoluteCinema.exe`.
Stack: C++17, Qt 5.15.2 (MinGW 8.1, 64-bit). Qt 5.15 is the last Qt that supports Windows 7; it is past official support.
The 64-bit build needs 64-bit Windows. A 32-bit build is a later addition.
Local build: install Qt 5.15.2 with MinGW, then `qmake AbsoluteCinema.pro && mingw32-make`.
