class Client : public Engine
{
public:
	static std::unique_ptr<Client> s_instance;
	static bool StaticInit();

protected:

	Client();

	virtual void	DoFrame() override;
	virtual void	HandleEvent(sf::Event& p_event) override;
	virtual bool	PollEvent(sf::Event& p_event) override;
	virtual void	EstablishConnection();
	virtual void	CloseConnection();
	static  void	RegisterStates();

private:
	bool is_connected = false;
};
