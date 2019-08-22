#pragma once
#include "Singleton.h"
#include <unordered_map>


namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
		std::string mDataPath;
	public:
		ResourceManager() = default;
		~ResourceManager();
		void Init(std::string&& data);

		Texture2D* LoadTexture(const std::string& file);
		bool StoreTexture(const std::string& name, Texture2D* tex);
		Texture2D* GetTexture(const std::string& name);
		Font* LoadFont(const std::string& file, unsigned int size);
	private:
		std::unordered_map<std::string, Texture2D*> m_Textures;
		std::unordered_map<std::string, Font*> m_Fonts;
	};

}
