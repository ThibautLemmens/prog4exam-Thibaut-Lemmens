#pragma once
#include "Logger.h"
#include "Time.h"
#include <functional>
class GameObject;
namespace dae
{
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

	protected:
		virtual void Initialize() {};
		virtual void Update(float) {};

		GameObject* m_pGameObject;
	};
}
