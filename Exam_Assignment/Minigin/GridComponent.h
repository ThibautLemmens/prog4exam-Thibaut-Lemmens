#pragma once
#include "TransformComponent.h"


namespace dae
{
	class MoveGridManager;

	class GridComponent : public BaseComponent
	{
	public:
		GridComponent();
		~GridComponent();

		virtual void Update() override;
		virtual void Initialize() override {};

		void TriggerCollide() {};
		void MoveTo(int pos);

		glm::vec2 GridLocation(int loc);

		int GetPos() const;
		int GetDest() const;

		//do not use, or use carefully
		void SetPos(glm::vec2 pos) { startVector = pos; };
		void SetDest(glm::vec2 pos) { DestinationVector = pos; startVector = GridLocation(GridPos); };
		void SetDestLocation(int loc) { Destination= loc; };
		bool IsTrigger() const;
		void SetTrigger(bool trig) { trigger = trig; };
		bool IsMoving() const;
		void SetMoving(bool move) { Move = move; };

		void Tag(std::string tag) { m_Tag = tag; };
		std::string Tag() const { return m_Tag; };

		void SetSpeed(float speed);
		float GetSpeed();

		void AddManager(MoveGridManager* grid) { Grid = grid; };
		void AddTransform(TransformComponent* transform) { Transform = transform; };

		MoveGridManager* GetManager() const {return Grid;};

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
		MoveGridManager* Grid = nullptr;

		glm::vec2 Lerp(glm::vec2 start, glm::vec2 end, float percent)
		{
			return (start + percent * (end - start));
		}

	private:
		
	};
}