=======================
MAC

clang -c -I./include ./src/glad.c -DGL_SILENCE_DEPRECATION

clang++ -o easyMelts -std=c++17 -I/opt/homebrew/include -I./include -I./include/imgui -I./include/melts ./src/*.cpp glad.o -L./lib -L/opt/homebrew/lib -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lxlsxwriter -lmeltslibwin -lxml2 -lz -liconv -DGL_SILENCE_DEPRECATION -DEASYMELTS_UPDATE_SYSTEM



/opt/homebrew/bin/g++-14 -o easyMelts -std=c++17 -I/opt/homebrew/Cellar/gcc/14.2.0_1/include/c++/14 -I/opt/homebrew/include -I./include -I./include/imgui -I./include/melts ./src/*.cpp ./src/glad.c -L./lib -L/opt/homebrew/lib -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lxlswriter -lmeltslibwin -L/opt/homebrew/Cellar/gcc/14.2.0_1/lib/gcc/14 -static-libstdc++ -static-libgcc -lstdc++fs -DGL_SILENCE_DEPRECATION -DEASYMELTS_UPDATE_SYSTEM

clang -I/opt/homebrew/include -I./include ./src/glad.c -L./lib -L/opt/homebrew/lib -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -static-libgcc -lstdc++fs -DGL_SILENCE_DEPRECATION -DEASYMELTS_UPDATE_SYSTEM

clang++ -o easyMelts -std=c++17 -I/opt/homebrew/include -I./include -I./include/imgui -I./include/melts ./src/*.cpp glad.o -L./lib -L/opt/homebrew/lib -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lxlsxwriter -lmeltslibwin -L/opt/homebrew/Cellar/gcc/14.2.0_1/lib/gcc/14 -static-libstdc++ -static-libgcc -lstdc++fs -DGL_SILENCE_DEPRECATION -DEASYMELTS_UPDATE_SYSTEM

/opt/homebrew/bin/g++-14 -o easyMelts -std=c++17 -I/opt/homebrew/Cellar/gcc/14.2.0_1/include/c++/14 -I./include -I./include/imgui -I./include/melts *.cpp glad.c -L./macos -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lOpenXLSX -lmeltslibwin -L/opt/homebrew/Cellar/gcc/14.2.0_1/lib/gcc/14 -static-libstdc++ -static-libgcc -lstdc++fs -DGL_SILENCE_DEPRECATION

=======================
MINGW

Still need libwinpthread-1.dll - doesn't seem to be a way to get round this.

(actually use mingw directory)

x86_64-w64-mingw32-g++ -o easyMelts.exe -std=c++17 -I./include -I./include/imgui -I./include/melts *.cpp glad.c -L./mingw /usr/x86_64-w64-mingw32/lib/libglfw3.a -lOpenXLSX -lmeltslibwin  /usr/x86_64-w64-mingw32/lib/libgdi32.a /usr/x86_64-w64-mingw32/lib/libssp.a /usr/x86_64-w64-mingw32/lib/libglu32.a -lopengl32 -static-libstdc++ -lstdc++fs -static-libgcc -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,-no-whole-archive -Wl,-Bdynamic -lws2_32 -luuid

=======================
UBUNTU

OpenXLSX newer cmake than Ubuntu 18.04 - can install via anaconda.

g++ -o easyMelts -std=c++17 -fPIC -I./include -I./include/imgui -I./include/melts *.cpp glad.c -L./lib -lglfw3 -lOpenXLSX -lmeltslibwin -static-libstdc++ -lstdc++fs  -static-libgcc -lGL -lpthread -ldl -lm

May need to reocmpile OpenXLSX with something like CXXFLAGS='-D_GLIBCXX_USE_CXX11_ABI=0' (actually doesn't seem to make any difference) and/or force OpenXLSX to use g++ as linker and/or compile glad.c separately first.

Need to tidy up <string> include.

On WSL Ubuntu 18.04 install mesa-utils
