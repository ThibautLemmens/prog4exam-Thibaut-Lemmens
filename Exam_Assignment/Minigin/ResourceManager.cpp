#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

dae::ResourceManager::~ResourceManager()
{
	std::unordered_map<std::string, Texture2D*>::iterator it = m_Textures.begin();

	// Iterate over the map using iterator
	while (it != m_Textures.end())
	{
		delete it->second;
		it++;
	}

	std::unordered_map<std::string, Font*>::iterator it1 = m_Fonts.begin();
	// Iterate over the map using iterator
	while (it1 != m_Fonts.end())
	{
		delete it1->second;
		it1++;
	}
}

void dae::ResourceManager::Init(std::string&& dataPath)
{
	mDataPath = std::move(dataPath);

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

dae::Texture2D* dae::ResourceManager::LoadTexture(const std::string& file)
{
	std::string fullPath = mDataPath + file;
	SDL_Texture *texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return new Texture2D(texture);
}

bool dae::ResourceManager::StoreTexture(const std::string & name, Texture2D* tex)
{
	if (tex == nullptr)
	{
		dae::Logger::LogWarning(L"[ResourceManager] Cant Store! Texture is Nullptr");
		return false;
	}
	std::unordered_map<std::string, Texture2D*>::iterator i = m_Textures.find(name);
	if (i != m_Textures.end())
	{
		Logger::LogError(L"[ResourceManager] Cant Store! Name Already Exists");
	}

	m_Textures.insert(std::pair<std::string, Texture2D*>(name, tex));

	return true;
}

dae::Texture2D* dae::ResourceManager::GetTexture(const std::string & name)
{
	std::unordered_map<std::string, Texture2D*>::iterator i = m_Textures.find(name);
	if (i == m_Textures.end())
	{
		Logger::LogError(L"[ResourceManager] Cant get! Name doesn't Exists");
		return nullptr;
	}
	else
	{
		return i->second;
	}
}

dae::Font* dae::ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	return new Font(mDataPath + file, size);
}
