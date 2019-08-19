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

void dae::GameObject::Update(){}


void dae::GameObject::SetTexture(const std::string& filename)
{
	mTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y, float z)
{
	m_Transform.Position(x, y, z);
}
