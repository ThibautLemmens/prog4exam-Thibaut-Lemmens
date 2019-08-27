#include "MiniginPCH.h"
#include "SceneRenderer.h"


dae::SceneRenderer::SceneRenderer()
{
}


dae::SceneRenderer::~SceneRenderer()
{
	for (size_t i = 0; i < m_RenderComponentes.size(); i++)
	{
		delete m_RenderComponentes[i];
	}
}

void dae::SceneRenderer::RenderUpdate()
{
}

void dae::SceneRenderer::Render()
{
	for (RenderComponent* rc: m_RenderComponentes)
	{
		rc->Render();
	}
}

dae::RenderComponent* dae::SceneRenderer::GetComponent(TransformComponent * transform)
{
	m_RenderComponentes.push_back(new RenderComponent(transform));
	m_RenderComponentes.back()->Connect(m_RenderComponentes.back()->Transform()->GetGameObject());
	return m_RenderComponentes.back();
}

bool dae::SceneRenderer::RemoveComponent(RenderComponent* rendercomponent)
{
	for (size_t i = 0; i < m_RenderComponentes.size(); i++)
	{
		if (m_RenderComponentes[i] == rendercomponent)
		{
			std::swap(m_RenderComponentes.back(), m_RenderComponentes[i]);
			m_RenderComponentes.pop_back();
			return true;
		}
	}
	
	return false;
}
