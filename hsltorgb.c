#include "hsltorgb.h"

float HueToRGB(float v1, float v2, float vH)
{
	if (vH < 0)
		vH += 1;

	if (vH > 1)
		vH -= 1;

	if ((6 * vH) < 1)
		return (v1 + (v2 - v1) * 6 * vH);

	if ((2 * vH) < 1)
		return v2;

	if ((3 * vH) < 2)
		return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);

	return v1;
}

  struct RGB HSLToRGB(struct HSL hsl)

      {

            double v;

            double r,g,b;
            float h = hsl.H;
            float sl = hsl.S;
            float l = hsl.L;

 

            r = l;   // default to gray

            g = l;

            b = l;

            v = (l <= 0.5) ? (l * (1.0 + sl)) : (l + sl - l * sl);

            if (v > 0)

            {

                  double m;

                  double sv;

                  int sextant;

                  double fract, vsf, mid1, mid2;

 

                  m = l + l - v;

                  sv = (v - m ) / v;

                  h *= 6.0;

                  sextant = (int)h;

                  fract = h - sextant;

                  vsf = v * sv * fract;

                  mid1 = m + vsf;

                  mid2 = v - vsf;

                  switch (sextant)

                  {

                        case 0:

                              r = v;

                              g = mid1;

                              b = m;

                              break;

                        case 1:

                              r = mid2;

                              g = v;

                              b = m;

                              break;

                        case 2:

                              r = m;

                              g = v;

                              b = mid1;

                              break;

                        case 3:

                              r = m;

                              g = mid2;

                              b = v;

                              break;

                        case 4:

                              r = mid1;

                              g = m;

                              b = v;

                              break;

                        case 5:

                              r = v;

                              g = m;

                              b = mid2;

                              break;

                  }

            }

            struct RGB rgb;

            rgb.R = r * 255;

            rgb.G = g * 255;

            rgb.B = b * 255;

            return rgb;

      }

Uint32 RGBToInt(struct RGB rgb) {
    return (rgb.R << 16) | (rgb.G << 8) | rgb.B;
}

struct RGB IntToRGB(Uint32 intvalue) {
    struct RGB ret;
    ret.R = intvalue >> 16;
    ret.G = (intvalue >> 8) & 255;
    ret.B = intvalue & 255;
    return ret;
}
