#include "headers.hpp"


TextNode::TextNode(b2World* _pw, const FontHolder& fonts, const std::string& text)
	:SceneNode(_pw)
{
	mText.setFont(fonts.get(Fonts::main));
	mText.setCharacterSize(30);
	mText.setColor(sf::Color::Black);
	setString(text);
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
   target.draw(mText, states);
}

void TextNode::setString(const std::string& text)
{
	mText.setString(text);
	//centerOrigin(mText);
}

TextNode::~TextNode(void)
{
}
