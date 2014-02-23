//������ ������ ��� ������������������� �������� ��������
#pragma once
#include <memory>
#include <assert.h>

template <typename Resource, typename Identifier> //<��� �������(sf::Texture, sf::Sound, sf::Font), ������������� �������(���������������� enum)>
class ResourceHolder
{
	public:
		void			load(Identifier id, const std::string& filename);//��������� ������ �� �����
		Resource&		get(Identifier id) const;//������� ������
	
	private:
		std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;//��������� ��� ��������
};

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource>  resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - failed to load "+filename);//����������, ���� �� ������� ���������
	auto inserted = mResourceMap.insert(std::make_pair(id,std::move(resource))); //������� � map
	assert(inserted.second);//�������� �������
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = mResourceMap.find(id);//����� (���������� std::pair<K, T>)
	assert(found != mResourceMap.end());//�������� ������
	
	return *found->second;//������� Resource
}

