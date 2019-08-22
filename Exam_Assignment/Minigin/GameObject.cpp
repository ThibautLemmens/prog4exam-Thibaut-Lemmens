#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"

dae::GameObject::~GameObject()
{
	for (auto c :m_Components)
	{
		delete c;
	}
}

void dae::GameObject::Update()
{
	for (size_t i = 0; i < m_Components.size(); i++)
	{
		m_Components[i]->Update();
	}
}


//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	mTexture = ResourceManager::GetInstance().LoadTexture(filename);
//}

void dae::GameObject::SetPosition(float x, float y, float z)
{
	m_Transform.Position(x, y, z);
}
