#include "WindowGenerator.h"

//Includes generales
#include <exception>
#include <iostream>

//Includes de Ogre
#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <OgreRenderSystem.h>
#include <OgreFileSystemLayer.h>

// SDL
#include "SDL.h"
#include <SDL_video.h>
#include <SDL_syswm.h>

WindowGenerator* WindowGenerator::instance_ = 0;

using namespace Ogre;

void WindowGenerator::initWindow(std::string name)
{
	Ogre::ConfigOptionMap ropts = mRoot_->getRenderSystem()->getConfigOptions();

	std::istringstream mode(ropts["Video Mode"].currentValue);
	Ogre::String token;
	
	mode >> winWidth_;     // width
	mode >> token; // 'x' as separator between width and height
	mode >> winHeight_;     // height

	std::cout << '\n' << winWidth_ << " " << winHeight_ << '\n';

	if (!SDL_WasInit(SDL_INIT_VIDEO | SDL_INIT_TIMER))
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
			SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
			/*EXCEPCION*/
		}

#ifdef _DEBUG
	int flags = 0;
#else
	int flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
#endif

	sdlWindow_ = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth_, winHeight_, flags);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	if (SDL_GetWindowWMInfo(sdlWindow_, &wmInfo) == SDL_FALSE) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
			"Couldn't get WM Info! (SDL2)",
			"BaseApplication::setup");
	}

	Ogre::NameValuePairList params;

	params["FSAA"] = ropts["FSAA"].currentValue;
	params["vsync"] = ropts["VSync"].currentValue;
	params["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;
	params["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	renderWindow_ = mRoot_->createRenderWindow(name, winWidth_, winHeight_, false, &params);

	//////////por si queremos que la ventana oculte el cursor
	SDL_SetWindowGrab(sdlWindow_, SDL_bool(false));
	SDL_ShowCursor(true);
	
	mRoot_->addFrameListener(this);
}

WindowGenerator::WindowGenerator(Root* root, const std::string& name) : mRoot_(root)
{
	initWindow(name);
}

WindowGenerator* WindowGenerator::getInstance()
{
	if (instance_ == nullptr)
	{
		return nullptr;
	}

	return instance_;
}

bool WindowGenerator::setupInstance(Root* root, const std::string& name)
{
	if (instance_ == 0)
	{
		instance_ = new WindowGenerator(root, name);
		return true;
	}

	return false;
}

void WindowGenerator::clean()
{
	delete instance_;
}

WindowGenerator::~WindowGenerator()
{
	if (renderWindow_ != nullptr) {
		mRoot_->destroyRenderTarget(renderWindow_);
		renderWindow_ = nullptr;
	}
}

RenderWindow* WindowGenerator::getRenderWindow()
{
	return renderWindow_;
}


RenderWindow* WindowGenerator::getRenderWindow() const
{
	return renderWindow_;
}

inline RenderSystem* WindowGenerator::getRenderSystem()
{
	return nullptr;//renderSystem_;
}

inline RenderSystem* WindowGenerator::getRenderSystem() const
{
	return nullptr;//renderSystem_;
}

SDL_Window* WindowGenerator::getSDLWindow()
{
	return sdlWindow_;
}

SDL_Window* WindowGenerator::getSDLWindow() const
{
	return sdlWindow_;
}

uint32_t WindowGenerator::getWindowWidth() const
{
	return winWidth_;
}

uint32_t WindowGenerator::getWindowHeight() const
{
	return winHeight_;
}
