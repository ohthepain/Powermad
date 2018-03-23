// UserMessage.cpp

#include "UserMessage.h"
#include "LcdDisplayController.h"
#include "myassert.h"

namespace Atomic
{
	void WarnUser(const char* title, const char* message)
	{
		Atomic::LcdDisplayController::GetInstance()->Clear();
		Atomic::LcdDisplayController::GetInstance()->WriteToScreen(0, 0, title);
		Atomic::LcdDisplayController::GetInstance()->WriteToScreen(0, 1, message);
		msg("WarnUser: title: ", title);
		msg("WarnUser: message: ", message);
	}
}
