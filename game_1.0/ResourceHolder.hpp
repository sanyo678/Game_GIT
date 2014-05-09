//������ ������ ��� ������������������� �������� ��������
#pragma once

template <typename Resource, typename Identifier> //<��� �������(sf::Texture, sf::Sound, sf::Font), ������������� �������(���������������� enum)>
class ResourceHolder
{
	public:
		void			load(Identifier id, const std::string& filename);//��������� ������ �� �����
		Resource&		get(Identifier id) const;//������� ������
	
	private:
		std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;//��������� ��� ��������
};



