//Alex Nogueira / D00242564
class Animation : public sf::Drawable, public sf::Transformable
{
public:
	Animation();
	explicit Animation(const sf::Texture& texture);

	void SetTexture(const sf::Texture& texture);
	const sf::Texture* GetTexture() const;

	void SetFrameSize(sf::Vector2i mFrameSize);
	sf::Vector2i GetFrameSize() const;

	void SetNumFrames(std::size_t numFrames);
	std::size_t GetNumFrames() const;

	void SetDuration(float duration);
	float GetDuration() const;

	void SetRepeating(bool flag);
	bool IsRepeating() const;

	void Restart();
	bool IsFinished() const;

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;

	sf::IntRect Update(float dt);


private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


private:
	sf::Sprite m_sprite;
	sf::Vector2i m_frame_size;
	std::size_t m_num_frames;
	std::size_t m_current_frame;
	float m_duration;
	float m_elapsed_time;
	bool m_repeat;
};

