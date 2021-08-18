#include "SDL.h"
#include <stdlib.h>
#include "hsltorgb.h"
#include <math.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define FIRE_A 32
#define FIRE_B 129
SDL_Renderer *renderer=NULL;
SDL_Texture *texture=NULL;
struct RGB pallete[256];
Uint32 screen[WINDOW_HEIGHT][WINDOW_WIDTH];
Uint32 buffer[WINDOW_HEIGHT][WINDOW_WIDTH];
void game_loop_iter(){
for(int x=0;x < WINDOW_WIDTH;x++){
screen[WINDOW_HEIGHT-1][x]=abs(32768+rand())%256;
}
for(int y=0;y < WINDOW_HEIGHT-1;y++){
for(int x=0;x < WINDOW_WIDTH;x++){
screen[y][x]=((screen[(y+1)%WINDOW_HEIGHT][(x-1+WINDOW_WIDTH)%WINDOW_WIDTH]+screen[(y+1)%WINDOW_HEIGHT][(x)%WINDOW_WIDTH]+screen[(y+1)%WINDOW_HEIGHT][(x+1)%WINDOW_WIDTH]+screen[(y+2)%WINDOW_HEIGHT][(x)%WINDOW_WIDTH])*FIRE_A)/FIRE_B;
buffer[y][x]=RGBToInt(pallete[screen[y][x]]);
}
}
SDL_UpdateTexture(texture,NULL,buffer,WINDOW_WIDTH*4);
SDL_RenderCopy(renderer,texture,NULL,NULL);
SDL_RenderPresent(renderer);
}
int main(int argc,char **argv){
SDL_Window *window;
SDL_Init(SDL_INIT_EVERYTHING);
window=SDL_CreateWindow("fire_wasm_sdl",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_OPENGL);
renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
for(int x=0;x < 256;x++){
int h=x/3;
int l=x*2;
if(l > 255){l=255;}
struct HSL hsl={h/255.0,1,l/255.0};
pallete[x]=HSLToRGB(hsl);
}
texture=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STATIC,WINDOW_WIDTH,WINDOW_HEIGHT);
for(int y=0;y < WINDOW_HEIGHT;y++){
for(int x=0;x < WINDOW_WIDTH;x++){
screen[y][x]=0;
}
}
#ifdef __EMSCRIPTEN__
emscripten_set_main_loop(game_loop_iter, 0, 1);
#else
while(!SDL_QuitRequested()){
game_loop_iter();
}
#endif
SDL_DestroyTexture(texture);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();
return 0;
}
