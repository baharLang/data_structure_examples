Working Environment for GoogleTest Compile on Windows 
1- Download cmake and install it. 
	https://cmake.org/download/cmake-3.25.3-windows-x86_64.msi
2- Download python and install it.
	https://www.python.org/downloads/
3- Download MSYS(Minimal SYStem) and install it.
http://downloads.sourceforge.net/mingw/MSYS-1.0.11.exe

To Compile GoogleTest:
1- Download googletest.
	https://github.com/google/googletest
2- Copy to source code(googletest-main) to path below.
	C:\msys\1.0\home\Samsung
3- Run msys.bat file that installed path below. 
	C:\msys\1.0
4- Change and make directory.
	cd C:\msys\1.0\home\Samsung\googletest-main
	mkdir build
	cd build
5- Run cmake to generate libraries and run make command.
	cmake -G "MSYS Makefiles" ..
	make
Finally, libgtest.a and libgtest_main.a libraries are created in ..\googletest-main\build\lib file.

After that, libraries path to Vscode project are added and unit tests can be written. 

NOTE: 	I wrote the methods for question 1,2,3. 
		I prepare the working environment for googleTest but unfortunately i could not write tests yet.
		directed_weighted_graph_test.cpp is shown as template file. 