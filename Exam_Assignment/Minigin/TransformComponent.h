#pragma once
#include "BaseComponent.h"
#include "glm\common.hpp"
#include <Vector>

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent() { m_Position = { 0,0,0 }; m_Scale = { 1,1 }; };
		TransformComponent(glm::vec3 Pos, glm::vec2 scale) { m_Position = Pos; m_Scale = scale; };
		virtual ~TransformComponent()
		{
			delete m_Parent;
			m_Children.clear();
		};

		//get and set Pos
		const glm::vec3 Position()const
		{
			if (m_Parent)
			{
				return m_Parent->Position() + m_Position;
			}
			else
			{
				return m_Position;
			}
		};

		void Position(glm::vec3 Pos)
		{
			m_Position = Pos;
		};
		void Position(float x, float y, float z)
		{
			m_Position = glm::vec3(x, y, z);
		};
		void Position(float x, float y)
		{
			m_Position = glm::vec3(x, y, m_Position.z);
		};

		//move adds to current Positions
		void Move(float x, float y, float z)
		{
			m_Position += glm::vec3(x, y, z);
		};
		void Move(glm::vec3 Pos)
		{
			m_Position += Pos;
		};

		//get and set Pos
		const glm::vec2 Scale()const
		{
			if (m_Parent)
			{
				if (m_Flipped) return m_Parent->Scale() * m_Scale * glm::vec2(-1, 1);
				return m_Parent->Scale() * m_Scale;
			}
			else
			{
				if (m_Flipped) return m_Scale * glm::vec2(-1, 1);
				return m_Scale;
			}
		};

		void Scale(glm::vec2 scale)
		{
			m_Scale = scale;
		};
		void Scale(float x, float y)
		{
			m_Scale = glm::vec2(x, y);
		};

		//rotates character
		void Flip() { m_Flipped = !m_Flipped; };
		void Flip(bool flip) { m_Flipped = flip; };

		//empty
		virtual void Initialize() override {};
		//empty
		virtual void Update() override {};

		//get and set Parent
		void Parent(TransformComponent* Parent, bool CurrentLocation)
		{
			m_Parent = Parent;
			Parent->InsertChild(this);
			if (CurrentLocation)
			{
				m_Position = m_Parent->Position() - m_Position;
			}
		};
		TransformComponent* const Parent() { return m_Parent; };

		//give a child to this obj
		void AddChild(TransformComponent*Child, bool CurrentLocation)
		{
			if (Child->Parent() == nullptr)
			{
				m_Children.push_back(Child); Child->Parent(this, CurrentLocation);
			}
			else
			{
				Child->Parent()->RemoveChild(Child);
				m_Children.push_back(Child); Child->Parent(this, CurrentLocation);
			}
		};

		//remove a child from this obj
		void RemoveChild(TransformComponent*Child)
		{
			for (size_t i{ 0 }; i < m_Children.size(); i++)
			{
				if (m_Children[i] == Child)
				{
					std::swap(m_Children.back(), m_Children[i]);
					m_Children.pop_back();
					Child->ResetParent();
				}
			}
		}



	private:
		TransformComponent* m_Parent;
		std::vector<TransformComponent*> m_Children;

		glm::vec3 m_Position;
		glm::vec2 m_Scale;

		bool m_Flipped = false;

		void ResetParent() { m_Parent = nullptr; };
		void InsertChild(TransformComponent* child) { m_Children.push_back(child); };
	};
}