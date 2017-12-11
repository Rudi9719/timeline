echo Updating APT
sudo apt update
echo Installing dependencies
sudo apt install libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-net-dev libsdl2-image-dev
echo Compiling Sources
g++ -Wall Classes/*.cpp Wrappers/*.cpp main.cpp -I/usr/include/SDL2 -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_mixer -lSDL2_net -lSDL2_ttf -lSDL2_image   -o timeline
echo Starting Binary
./timeline
