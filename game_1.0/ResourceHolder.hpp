//шаблон класса для автоматизированного хранения ресурсов
#pragma once
#include <memory>
#include <assert.h>

template <typename Resource, typename Identifier> //<тип ресурса(sf::Texture, sf::Sound, sf::Font), идентификатор ресурса(предположительно enum)>
class ResourceHolder
{
	public:
		void			load(Identifier id, const std::string& filename);//загрузить ресурс из файла
		Resource&		get(Identifier id) const;//извлечь ресурс
	
	private:
		std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;//контейнер для ресурсов
};

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource>  resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - failed to load "+filename);//исключение, если не удается загрузить
	auto inserted = mResourceMap.insert(std::make_pair(id,std::move(resource))); //вставка в map
	assert(inserted.second);//проверка вставки
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = mResourceMap.find(id);//поиск (возвращает std::pair<K, T>)
	assert(found != mResourceMap.end());//проверка поиска
	
	return *found->second;//возврат Resource
}

