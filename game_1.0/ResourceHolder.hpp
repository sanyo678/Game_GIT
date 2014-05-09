//шаблон класса для автоматизированного хранения ресурсов
#pragma once

template <typename Resource, typename Identifier> //<тип ресурса(sf::Texture, sf::Sound, sf::Font), идентификатор ресурса(предположительно enum)>
class ResourceHolder
{
	public:
		void			load(Identifier id, const std::string& filename);//загрузить ресурс из файла
		Resource&		get(Identifier id) const;//извлечь ресурс
	
	private:
		std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;//контейнер для ресурсов
};



