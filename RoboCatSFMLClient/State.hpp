class State
{
public:
	typedef unique_ptr<State> Ptr;
	
public:
	State();
	virtual ~State();
	virtual void Draw() = 0;
	virtual bool Update(float dt) = 0;
	virtual bool HandleEvent(const sf::Event& event) = 0;
	virtual void OnActivate();
	virtual void OnDestroy();

protected:
	void RequestStackPush(EState state_id);
	void RequestStackPop();
	void RequestStackClear();
};