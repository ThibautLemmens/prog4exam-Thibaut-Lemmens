#pragma once
#include "Logger.h"
#include "Time.h"
#include <functional>

namespace dae
{
	class GameObject;
	class TransformComponent;
	class BaseComponent
	{
		//friend class GameObject;

	public:
		BaseComponent() :m_pGameObject{nullptr} {};
		virtual ~BaseComponent() {};
		
		GameObject* GetGameObject() { return m_pGameObject; };

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

		TransformComponent* GetTransform() const;

	protected:
		virtual void Initialize() =0;
		virtual void Update() =0;

		GameObject* m_pGameObject;
	};
}
