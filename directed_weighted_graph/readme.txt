-------------------------------------------------------------------------------------------------------------
All the steps to follow to run the project are below
-------------------------------------------------------------------------------------------------------------

Vscode Installation:
-------------------------------------------------------------------------------------------------------------
1- Download visual studio code and install it.
	https://code.visualstudio.com/docs/?dv=win


Working Environment for GoogleTest Compile on Windows: 
-------------------------------------------------------------------------------------------------------------
1- Download cmake and install it. 
	https://cmake.org/download/cmake-3.25.3-windows-x86_64.msi
2- Download python and install it.
	https://www.python.org/downloads/
3- Download MSYS(Minimal SYStem) and install it.
http://downloads.sourceforge.net/mingw/MSYS-1.0.11.exe


To Compile GoogleTest:
-------------------------------------------------------------------------------------------------------------
1- Download googletest.
	https://github.com/google/googletest
2- Copy to source code(googletest-main) to path below.
	C:\msys\1.0\home\Samsung
3- Run msys.bat file that installed path below. 
	C:\msys\1.0
4- Change and make a build directory.
	cd C:\msys\1.0\home\Samsung\googletest-main
	mkdir build
	cd build
5- Run cmake to generate libraries and run make command.
	cmake -G "MSYS Makefiles" ..
	make
Finally, libgtest.a and libgtest_main.a libraries are created in ..\googletest-main\build\lib file.

After that, libraries path to Vscode project are added and unit tests can be written. 
Related path should be added to c_cpp_properties.json file.
	Example: 
			"includePath": [
                "${workspaceFolder}/**",
                "C:/Users/Samsung/Documents/googletest/googletest/include"
            ],

After the working environment preparation, graph codes and unit tests were written. 
The following command was used to compile the tests via terminal.
	g++ .\test_directedWeightedGraph.cpp -o test_directedWeightedGraph -IC:/Users/Samsung/Documents/googletest/googletest/include -LC:/Users/Samsung/Documents/googletest/build/lib -lgtest -lgtest_main
	./test_directedWeightedGraph.exe