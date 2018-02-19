emcc main.c hsltorgb.c -s WASM=1 -s USE_SDL=2 -o fire.html -s ALLOW_MEMORY_GROWTH=1
firefox fire.html
