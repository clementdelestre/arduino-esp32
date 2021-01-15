#include "rgbColor.hpp"

uint8_t RgbColor::CalculateBrightness() const
{
	return (uint8_t)(((uint16_t)R + (uint16_t)G + (uint16_t)B) / 3);
}

RgbColor RgbColor::Dim(uint8_t ratio) const
{
    // specifically avoids float math
    return RgbColor(_elementDim(R, ratio), _elementDim(G, ratio), _elementDim(B, ratio));
}

RgbColor RgbColor::Brighten(uint8_t ratio) const
{
    // specifically avoids float math
    return RgbColor(_elementBrighten(R, ratio), _elementBrighten(G, ratio), _elementBrighten(B, ratio));
}

void RgbColor::Darken(uint8_t delta)
{
	if (R > delta)
	{
		R -= delta;
	}
	else
	{
		R = 0;
	}

	if (G > delta)
	{
		G -= delta;
	}
	else
	{
		G = 0;
	}

	if (B > delta)
	{
		B -= delta;
	}
	else
	{
		B = 0;
	}
}

void RgbColor::Lighten(uint8_t delta)
{
	if (R < 255 - delta)
	{
		R += delta;
	}
	else
	{
		R = 255;
	}

	if (G < 255 - delta)
	{
		G += delta;
	}
	else
	{
		G = 255;
	}

	if (B < 255 - delta)
	{
		B += delta;
	}
	else
	{
		B = 255;
	}
}

RgbColor RgbColor::LinearBlend(const RgbColor& left, const RgbColor& right, float progress)
{
	return RgbColor( left.R + ((right.R - left.R) * progress),
		left.G + ((right.G - left.G) * progress),
		left.B + ((right.B - left.B) * progress));
}

RgbColor RgbColor::BilinearBlend(const RgbColor& c00, 
    const RgbColor& c01, 
    const RgbColor& c10, 
    const RgbColor& c11, 
    float x, 
    float y)
{
    float v00 = (1.0f - x) * (1.0f - y);
    float v10 = x * (1.0f - y);
    float v01 = (1.0f - x) * y;
    float v11 = x * y;

    return RgbColor(
        c00.R * v00 + c10.R * v10 + c01.R * v01 + c11.R * v11,
        c00.G * v00 + c10.G * v10 + c01.G * v01 + c11.G * v11,
        c00.B * v00 + c10.B * v10 + c01.B * v01 + c11.B * v11);
}