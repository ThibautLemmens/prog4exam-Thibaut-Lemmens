#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

dae::BaseComponent::~BaseComponent()
{
}

dae::TransformComponent* dae::BaseComponent::GetTransform() const
{
#if _DEBUG
	if (m_pGameObject == nullptr)
	{
		Logger::LogWarning(L"GameObject is Null");
		return nullptr;
	}
#endif

	return m_pGameObject->Transform();
}
