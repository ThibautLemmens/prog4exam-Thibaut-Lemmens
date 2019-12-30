#pragma once

namespace pixSim
{
	enum class Pixel : unsigned int
	{
		//Dynamic 0-99
		Sand = 0,
		//Fluid 100-199
		Water = 100,
		Lava = 101,
		//Gas 200-299
		Steam = 200,
		ToxicGas = 201,
		//Static 300-399
		Rock = 300,
		Wood = 301,
		//Special 400-499
		Fire = 400
	};

	enum class type : unsigned int
	{
		Dynamic = 0,
		Fluid = 1,
		Gas = 2,
		Static = 3,
		Special = 4
	};

	type GetType(unsigned int pixelInfo);

	struct UpdateReturn
	{
		unsigned int Posistion;
		Pixel currType;
		uint32_t Color;
	};

}