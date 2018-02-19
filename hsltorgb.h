#include <SDL_stdinc.h>

struct RGB
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
};

struct HSL
{
	float H;
	float S;
	float L;
};

struct RGB HSLToRGB(struct HSL hsl);
Uint32 RGBToInt(struct RGB);
struct RGB IntToRGB(Uint32);
