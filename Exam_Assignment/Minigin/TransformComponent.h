#pragma once
#include "BaseComponent.h"
#include "glm\common.hpp"

namespace dae
{ 
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent() { m_Position = { 0,0,0 }; m_Scale = { 1,1 }; };
		TransformComponent(glm::vec3 Pos, glm::vec2 scale) { m_Position = Pos; m_Scale = scale; };
		virtual ~TransformComponent() {};

		//get and set Pos
		const glm::vec3 Position()const
		{return m_Position;};

		void Position(glm::vec3 Pos)
		{m_Position = Pos;};
		void Position(float x, float y, float z)
		{m_Position = glm::vec3(x,y,z);};

		//move adds to current Positions
		void Move(float x, float y, float z)
		{m_Position += glm::vec3(x, y, z);};
		void Move(glm::vec3 Pos)
		{m_Position += Pos;};

		//get and set Pos
		const glm::vec2 Scale()const
		{return m_Scale;};

		void Scale(glm::vec2 scale)
		{m_Scale = scale;};
		void Scale(float x, float y)
		{m_Scale = glm::vec2(x, y);};

		virtual void Initialize() override {};
		virtual void Update() override {};

	private:

		glm::vec3 m_Position;
		glm::vec2 m_Scale;
	};
}