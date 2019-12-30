#include "MiniginPCH.h"
#include "RenderingStack.h"

#include "Renderer.h"

#define StartSize 64

dae::RenderingStack::RenderingStack()
{
	BufferSwitch = true;
	RawRenderData.reserve(StartSize);
	ProcessedRenderDataBufferA.reserve(StartSize);
	ProcessedRenderDataBufferB.reserve(StartSize);
}

dae::RenderingStack::~RenderingStack()
{
}

void dae::RenderingStack::ClearBuffer()
{
	RawRenderData.clear();

	if (BufferSwitch)
	{
		ProcessedRenderDataBufferB.clear();
	}
	else
	{
		ProcessedRenderDataBufferA.clear();
	}
}

void dae::RenderingStack::CLip(const Camera &view)
{
	SDL_Rect camera = view.GetView();

	for (size_t i = 0; i < RawRenderData.size(); i++)
	{
		if (RawRenderData[i].Destination.x < camera.x + camera.w &&
			RawRenderData[i].Destination.x + RawRenderData[i].Destination.w > camera.x &&
			RawRenderData[i].Destination.y < camera.y + camera.h &&
			RawRenderData[i].Destination.y + RawRenderData[i].Destination.h > camera.y)
		{
			if (BufferSwitch)
			{
				ProcessedRenderDataBufferB.push_back(RawRenderData[i]);
			}
			else
			{
				ProcessedRenderDataBufferA.push_back(RawRenderData[i]);
			}
		}
	}
}

void dae::RenderingStack::DrawBuffer()
{
	if (BufferSwitch)
	{
		for (size_t i = 0; i < ProcessedRenderDataBufferA.size(); i++)
		{
			dae::Renderer::GetInstance().RenderTexture(*ProcessedRenderDataBufferA[i].Texture,
				&ProcessedRenderDataBufferA[i].Destination,
				&ProcessedRenderDataBufferA[i].Source);
		}
	}
	else
	{
		for (size_t i = 0; i < ProcessedRenderDataBufferB.size(); i++)
		{
			dae::Renderer::GetInstance().RenderTexture(*ProcessedRenderDataBufferB[i].Texture,
				&ProcessedRenderDataBufferB[i].Destination,
				&ProcessedRenderDataBufferB[i].Source);
		}
	}
}

void dae::RenderingStack::Swap()
{
	BufferSwitch = !BufferSwitch;
}

void dae::RenderingStack::Add(const RenderData &data)
{
	RawRenderData.push_back(data);

}
