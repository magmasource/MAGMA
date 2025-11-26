=======================
MAC

clang -c -I./include ./src/glad.c -DGL_SILENCE_DEPRECATION

clang++ -o easyMelts -std=c++17 -I/opt/homebrew/include -I./include -I./include/imgui -I./include/melts ./src/*.cpp glad.o -L./lib -L/opt/homebrew/lib -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lxlsxwriter -lmeltslibwin -lxml2 -lz -liconv -DGL_SILENCE_DEPRECATION -DEASYMELTS_UPDATE_SYSTEM



/opt/homebrew/bin/g++-14 -o easyMelts -std=c++17 -I/opt/homebrew/Cellar/gcc/14.2.0_1/include/c++/14 -I/opt/homebrew/include -I./include -I./include/imgui -I./include/melts ./src/*.cpp ./src/glad.c -L./lib -L/opt/homebrew/lib -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lxlswriter -lmeltslibwin -L/opt/homebrew/Cellar/gcc/14.2.0_1/lib/gcc/14 -static-libstdc++ -static-libgcc -lstdc++fs -DGL_SILENCE_DEPRECATION -DEASYMELTS_UPDATE_SYSTEM

clang -I/opt/homebrew/include -I./include ./src/glad.c -L./lib -L/opt/homebrew/lib -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -static-libgcc -lstdc++fs -DGL_SILENCE_DEPRECATION -DEASYMELTS_UPDATE_SYSTEM

clang++ -o easyMelts -std=c++17 -I/opt/homebrew/include -I./include -I./include/imgui -I./include/melts ./src/*.cpp glad.o -L./lib -L/opt/homebrew/lib -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lxlsxwriter -lmeltslibwin -L/opt/homebrew/Cellar/gcc/14.2.0_1/lib/gcc/14 -static-libstdc++ -static-libgcc -lstdc++fs -DGL_SILENCE_DEPRECATION -DEASYMELTS_UPDATE_SYSTEM

/opt/homebrew/bin/g++-14 -o easyMelts -std=c++17 -I/opt/homebrew/Cellar/gcc/14.2.0_1/include/c++/14 -I./include -I./include/imgui -I./include/melts *.cpp glad.c -L./macos -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lOpenXLSX -lmeltslibwin -L/opt/homebrew/Cellar/gcc/14.2.0_1/lib/gcc/14 -static-libstdc++ -static-libgcc -lstdc++fs -DGL_SILENCE_DEPRECATION

=======================
WINDOWS (Rtools)

pacman -Sy libxml2

Would be better to build these (especially libxlsxwriter, as the prebuilt package is dynamic only).

pacman -Sy mingw-w64-x86_64-libxlsxwriter
pacman -Sy mingw-w64-x86_64-glfw

g++ -o easyMelts.exe -std=c++17 -I./include -I./include/imgui -I./include/melts -I/mingw64/include src/*.cpp src/glad.c -L/mingw64/lib -lxlsxwriter -Wl,-Bstatic -L./lib -lmeltslibwin -lglfw3 -lopengl32 -lgdi32 -lxml2 -lz -llzma -liconv -static-libstdc++ -lstdc++ -static-libgcc -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,-no-whole-archive -Wl,-Bdynamic -lws2_32 -luuid -DEASYMELTS_UPDATE_SYSTEM

=======================
UBUNTU

sudo apt-get install -y zlib1g-dev
git clone https://github.com/jmcnamara/libxlsxwriter.git
cd libxlsxwriter
make
sudo make install

sudo apt install libglfw3 libglfw3-dev
sudo apt install libxml2 libxml2-dev

g++ -o easyMelts -std=c++17 -fPIC -I./include -I./include/imgui -I./include/melts -I/usr/local/include src/*.cpp src/glad.c -L./lib -lmeltslibwin -L/usr/local/lib -lxlsxwriter -L/usr/lib/x86_64-linux-gnu -lglfw -lxml2 -lz -static-libstdc++ -lstdc++  -static-libgcc -lGL -lpthread -ldl -lm -DEASYMELTS_UPDATE_SYSTEM
