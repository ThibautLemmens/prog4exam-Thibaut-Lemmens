#pragma once
#include "TransformComponent.h"


namespace dae
{
	class GridManager;

	class GridComponent : public BaseComponent
	{
	public:
		GridComponent();
		~GridComponent();

		virtual void Update() override;
		virtual void Initialize() override {};

		void TriggerCollide() {};
		void MoveTo(int pos);

		int GetPos() const;
		int GetDest() const;

		bool IsTrigger() const;
		void SetTrigger(bool trig) { trigger = trig; };
		bool IsMoving() const;
		void SetMoving(bool move) { Move = move; };

		void Tag(std::string tag) { m_Tag = tag; };
		std::string Tag() const { return m_Tag; };

		void SetSpeed(float speed);
		float GetSpeed();

		void AddManager(GridManager* grid) { Grid = grid; };
		void AddTransform(TransformComponent* transform) { Transform = transform; };

	protected:
		bool Move = false;
		bool trigger = true;
		int GridPos;
		glm::vec2 startVector;
		int Destination;
		glm::vec2 DestinationVector;
		std::string m_Tag;
		float MoveSpeed = 0.24f;
		float Time = 0;
		TransformComponent* Transform = nullptr;
		GridManager* Grid = nullptr;

		glm::vec2 Lerp(glm::vec2 start, glm::vec2 end, float percent)
		{
			return (start + percent * (end - start));
		}

	private:
		
	};
}