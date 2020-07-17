#pragma once

// I dont remember where this color struct comes from but conflicts with the classic 4 unsigned bytes color that Source engine likes to use
struct Color2
{
	int r;
	int g;
	int b;
	int a;

	Color2()
	{
		this->r = 0;
		this->g = 0;
		this->b = 0;
		this->a = 255;
	}

	Color2(int r, int g, int b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 255;
	}

	Color2(int r, int g, int b, int a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	Color2 operator / (float div)
	{
		Color2 color = *this;
		color.r = color.r / div;
		color.g = color.g / div;
		color.b = color.b / div;
		return color;
	}

	Color2& operator /= (float div)
	{
		Color2& color = *this;
		color.r /= div;
		color.g /= div;
		color.b /= div;
		return color;
	}

	Color2& operator *= (float coeff)
	{
		Color2& color = *this;
		color.r *= coeff;
		color.g *= coeff;
		color.b *= coeff;
		return color;
	}

	static Color2 FromHSB(float hue, float saturation, float brightness)
	{
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - (int)h;
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));

		if (h < 1)
		{
			return Color2(
					(unsigned char)(brightness * 255),
					(unsigned char)(t * 255),
					(unsigned char)(p * 255)
			);
		}
		else if (h < 2)
		{
			return Color2(
					(unsigned char)(q * 255),
					(unsigned char)(brightness * 255),
					(unsigned char)(p * 255)
			);
		}
		else if (h < 3)
		{
			return Color2(
					(unsigned char)(p * 255),
					(unsigned char)(brightness * 255),
					(unsigned char)(t * 255)
			);
		}
		else if (h < 4)
		{
			return Color2(
					(unsigned char)(p * 255),
					(unsigned char)(q * 255),
					(unsigned char)(brightness * 255)
			);
		}
		else if (h < 5)
		{
			return Color2(
					(unsigned char)(t * 255),
					(unsigned char)(p * 255),
					(unsigned char)(brightness * 255)
			);
		}
		else
		{
			return Color2(
					(unsigned char)(brightness * 255),
					(unsigned char)(p * 255),
					(unsigned char)(q * 255)
			);
		}
	}
};

struct Color
{
    Color(unsigned char Red, unsigned char Green, unsigned char Blue, unsigned char Alpha = 255)
    {
        RGBA[0] = Red;
        RGBA[1] = Green;
        RGBA[2] = Blue;
        RGBA[3] = Alpha;
    }

    unsigned char RGBA[4];
};

struct ColorRGBA
{
	ColorRGBA(unsigned char Red, unsigned char Green, unsigned char Blue, unsigned char Alpha = 255)
	{
		RGBA[0] = Red;
		RGBA[1] = Green;
		RGBA[2] = Blue;
		RGBA[3] = Alpha;
	}

	unsigned char RGBA[4];
};