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

		//load texture, but doesnt store
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
		//store a texture
		bool StoreTexture(const std::string& name, Texture2D* tex);
		bool StoreTexture(const std::string& name, const std::string& file);
		//get stored texture
		std::weak_ptr <Texture2D> GetTexture(const std::string& name);

		//TODO: Font support

		//loads font, doesnt store
		Font* LoadFont(const std::string& file, unsigned int size);
	private:
		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_Textures;
		std::unordered_map<std::string, std::shared_ptr<Font>> m_Fonts;
	};

}
