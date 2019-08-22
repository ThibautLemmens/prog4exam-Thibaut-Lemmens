#pragma once
#include "TransformComponent.h"

class GridManager;

namespace dae
{
	class GridComponent : public BaseComponent
	{
	public:
		GridComponent();
		~GridComponent();

		void TriggerCollide() {};
		void MoveTo(int pos) {};

		void Tag(std::string tag) { m_Tag = tag; };
		std::string Tag() const { return m_Tag; };

	protected:
		bool Move = false;
		bool trigger = true;
		int GridPos;
		std::string m_Tag;
	private:
		TransformComponent* transform = nullptr;
		GridManager* Grid = nullptr;
	};
}
