#pragma once
#include <memory>
#include "TransformComponent.h"
#include "Texture2D.h"
#include "SceneObject.h"

namespace dae
{
	class GameObject final : public SceneObject
	{
	public:
		void Update() override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y, float z);
		TransformComponent* Transform() { return &m_Transform; };

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


		template <class T>
		bool GetComponent()
		{
			return GetComponent<T>() != nullptr;
		}

		template <class T>
		T* GetComponent()
		{
			const type_info& ti = typeid(T);
			for (auto* component : m_Components)
			{
				if (component && typeid(*component) == ti)
					return static_cast<T*>(component);
			}
			return nullptr;
		}

		void AddComponent(BaseComponent* component)
		{
			m_Components.push_back(component);
		};

	private:
		TransformComponent m_Transform;
		std::shared_ptr<Texture2D> mTexture;
		std::vector<BaseComponent*> m_Components;
	};
}
