class WindowManager
{

public:
	static bool StaticInit();
	static std::unique_ptr< sf::RenderWindow >	sInstance;
	static void SetDefaultView();
	static void SetCameraView();
	static void SetViewCenter(Vector3 center);

private:
	static sf::View mCamera;
};

