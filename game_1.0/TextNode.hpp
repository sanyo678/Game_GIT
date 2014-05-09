#pragma once
class TextNode : public SceneNode
{
public:
							TextNode(b2World*, const FontHolder& fonts, const std::string& text);
	void					setString(const std::string& text);
	virtual void	        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
							~TextNode(void);

	sf::Text				mText;
	double					lifetime;
};

