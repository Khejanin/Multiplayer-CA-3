namespace sf
{
	class Event;
	class RenderWindow;
}

class StateStack
{
public:
	enum class Action
	{
		Push,
		Pop,
		Clear
	};

public:
	static void StaticInit();
	static unique_ptr< StateStack >	sInstance;
	template <typename T>
	void RegisterState(EState state_id);
	template <typename T, typename Param1>
	void RegisterState(EState state_id, Param1 arg1);
	void Update(float dt);
	void Draw();
	void HandleEvent(const sf::Event& event);

	static void PushState(EState state_id);
	static void PopState();
	static void ClearStates();

	bool IsEmpty() const;

private:
	StateStack();
	State::Ptr CreateState(EState EState);
	void ApplyPendingChanges();

private:
	struct PendingChange
	{
		explicit PendingChange(Action action, EState EState = EState::kNone);
		Action action;
		EState state_id;
	};

private:
	std::vector<State::Ptr> m_stack;
	std::vector<PendingChange> m_pending_list;
	std::map<EState, std::function<State::Ptr()>> m_state_factory;
};

template <typename T>
void StateStack::RegisterState(EState state_id)
{
	m_state_factory[state_id] = [this]()
	{
		return State::Ptr(new T());
	};
}

template <typename T, typename Param1>
void StateStack::RegisterState(EState state_id, Param1 arg1)
{
	m_state_factory[state_id] = [this, arg1]()
	{
		return State::Ptr(new T(arg1));
	};
}
