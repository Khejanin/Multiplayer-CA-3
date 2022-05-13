typedef shared_ptr<sf::Texture> TexturePtr;
typedef shared_ptr<sf::SoundBuffer> SoundPtr;
typedef shared_ptr<sf::Font> FontPtr;
typedef shared_ptr<sf::Shader> ShaderPtr;

class SpriteComponent
{
public:

	SpriteComponent(GameObject* inGameObject);
	~SpriteComponent();

	void SetTexture(TexturePtr inTexture);
	void SetTextureRect(sf::IntRect rect);
	virtual sf::Sprite& GetSprite();

protected:

	sf::Sprite m_sprite;

	//don't want circular reference...
	GameObject* mGameObject;
};

typedef shared_ptr< SpriteComponent >	SpriteComponentPtr;

