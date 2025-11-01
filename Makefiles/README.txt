=======================
MAC

brew install libxlsxwriter
brew install glfw

clang -c -I./include ./src/glad.c -DGL_SILENCE_DEPRECATION

clang++ -o easyMelts -std=c++17 -I/opt/homebrew/include -I./include -I./include/imgui -I./include/melts ./src/*.cpp glad.o libMELTSbatch.a /opt/homebrew/lib/libglfw3.a /opt/homebrew/lib/libxlsxwriter.a -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
-lxml2 -lz -liconv -DGL_SILENCE_DEPRECATION -DEASYMELTS_UPDATE_SYSTEM

clang++ -o easyMelts -std=c++17 -I/usr/local/include -I./include -I./include/imgui -I./include/melts ./src/*.cpp glad.o -L./lib -lmeltslibwin /usr/local/lib/libglfw3.a /usr/local/lib/libxlsxwriter.a -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lxml2 -lz -liconv -DGL_SILENCE_DEPRECATION -DEASYMELTS_UPDATE_SYSTEM

=======================
WINDOWS (Rtools)

pacman -Sy libxml2 zlib

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
