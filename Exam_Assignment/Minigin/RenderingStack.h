#pragma once
#include <SDL_rect.h>
#include "Texture2D.h"
#include "Camera.h"

namespace dae
{
	struct RenderData {
		dae::Texture2D* Texture;
		SDL_Rect Destination;
		SDL_Rect Source;
	public:
		RenderData(dae::Texture2D* tex, SDL_Rect dest, SDL_Rect src)
			:Texture{ tex }
			, Destination{ dest }
			, Source{ src }
		{}

		//rule of 5
		RenderData(const RenderData& data) :
			Texture(data.Texture),
			Destination(data.Destination),
			Source(data.Source)
		{}
		//move constructor with noexcept to force vectors to use move instead of copy
		RenderData(RenderData&& data) noexcept :
			Texture(std::move(data.Texture)),
			Destination(std::move(data.Destination)),
			Source(std::move(data.Source))
		{}
		RenderData& operator=(const RenderData& data) {
			return *this = RenderData(data);
		}
		RenderData& operator=(RenderData&& data) noexcept {
			Texture = std::move(data.Texture);
			Destination = std::move(data.Destination);
			Source = std::move(data.Source);
		}

	};

	class RenderingStack final : public Singleton<RenderingStack>
	{
	public:
		RenderingStack();
		~RenderingStack();

		//add data to the stack
		void Add(const RenderData &data);
		//clear to be used buffer
		void ClearBuffer();
		//fill buffer with relevant RenderData
		void CLip(const Camera &view);
		//draws a buffer
		void DrawBuffer();
		//swaps what buffer to use and to draw
		void Swap();

	private:
		bool BufferSwitch;

		std::vector<RenderData> RawRenderData;
		std::vector<RenderData> ProcessedRenderDataBufferA;
		std::vector<RenderData> ProcessedRenderDataBufferB;
	};

}