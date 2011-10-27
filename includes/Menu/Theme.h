#ifndef __MENUTHEMEH__
#define __MENUTHEMEH__

class Theme
{
	public:
		static void ChangeRGB(int RGB, int Value)
		{
			if(Value >= 255)
				Value = 255;
			else if(Value <= 0)
				Value = 0;

			RGBValue[RGB] = Value;
		}

		static int ReturnRGB(int RGB)
		{
			return RGBValue[RGB];
		}

	private:
		static int RGBValue[3];
};

#endif

