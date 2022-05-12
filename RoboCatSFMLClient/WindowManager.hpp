class WindowManager
{

public:
	static bool StaticInit();
	static std::unique_ptr< sf::RenderTexture >	mRenderTexture;
	static std::unique_ptr< sf::RenderWindow >	mRenderWindow;
	static void SetDefaultView();
	static void SetCameraView();
	static void SetViewCenter(Vector3 center);
	static sf::View GetCameraView();
	static void ApplyRenderTextureToWindow();

private:
	static sf::View mCamera;
};

