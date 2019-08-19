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

		void Init(std::string&& data);

		std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
		bool StoreTexture(const std::string& name, std::shared_ptr<Texture2D> tex);
		std::shared_ptr<Texture2D> GetTexture(const std::string& name);
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size);
	private:
		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_Textures;
		std::unordered_map<std::string, std::shared_ptr<Font>> m_Fonts;
	};

}
