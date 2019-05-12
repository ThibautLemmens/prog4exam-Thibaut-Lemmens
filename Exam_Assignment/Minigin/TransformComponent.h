#pragma once
#include "BaseComponent.h"
#include "glm\common.hpp"

namespace dae
{ 
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent() { m_Position = { 0,0 }; m_Scale = { 1,1 }; };
		TransformComponent(glm::vec2 Pos, glm::vec2 scale) { m_Position = Pos; m_Scale = scale; };
		virtual ~TransformComponent() {};

		//get and set Pos
		glm::vec2 Position()const
		{return m_Position;};

		void Position(glm::vec2 Pos)
		{m_Position = Pos;};

		//get and set Pos
		glm::vec2 Scale()const
		{return m_Scale;};

		void Scale(glm::vec2 scale)
		{m_Scale = scale;};

	private:
		glm::vec2 m_Position;
		glm::vec2 m_Scale;
	};
}