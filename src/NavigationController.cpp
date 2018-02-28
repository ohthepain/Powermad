// NavigationController.cpp

#include "NavigationController.h"

namespace Atomic
{
	NavigationController* NavigationController::mInstance = nullptr;

	NavigationController::NavigationController()
	{
		mSong = new Song();
	}

	NavigationController::~NavigationController()
	{
		delete mSong;
		mSong = nullptr;
	}

	void NavigationController::Init()
	{
		mInstance = new NavigationController();
	}

	void NavigationController::Shutdown()
	{
		delete mInstance;
		mInstance = nullptr;
	}
}
