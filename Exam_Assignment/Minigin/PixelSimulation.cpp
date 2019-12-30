#include "MiniginPCH.h"
#include "PixelSimulation.h"

pixSim::type pixSim::GetType(unsigned int pixelInfo)
{
	return type(pixelInfo / 100);
}
