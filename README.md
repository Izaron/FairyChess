# Fairy Chess Engine
Article on Habr (Russian): https://habr.com/ru/post/654745/

### How to build
You need to install SFML libraries before build
```
git clone https://github.com/Izaron/FairyChess.git
cd FairyChess/src/ && mkdir build && cd build

export CXX=/usr/bin/g++-11  # use any compiler with proper C++20 support
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --target fairy_chess

# make symlinks to the images folder
ln -s ../../images images 
# make symlink to the font file
sudo ln /usr/share/fonts/truetype/open-sans/OpenSans-Regular.ttf font.ttf

./fairy_chess
```

### How to run tests
We use Google GMock tests framework
```
cmake --build .
ctest
```
