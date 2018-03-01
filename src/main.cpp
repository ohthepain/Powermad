// xfacetest.ino

#include "Event.h"
#include "TimerController.h"
#include "TempoMonitor.h"
#include "PanelButtonsController.h"
#include "NavigationController.h"
#include "Song.h"
#include "InternalMidiClock.h"
#include "EventMonitor.h"
#include "InputPinManager.h"
#include "LcdDisplayController.h"

#define LED 13

void setup()
{
  Atomic::EventController::Init();
  Atomic::EventMonitor::Init();
  Atomic::NavigationController::Init();
  Atomic::PanelButtonsController::Init();
  Atomic::TimerController::Init();
  Atomic::TempoMonitor::Init();
  Atomic::InternalMidiClock::Init();
  Atomic::InputPinManager::Init();
  Atomic::InputPinManager::GetInstance()->AddDigitalInputPin(8, Atomic::Event::RightJoystickButton);
  Atomic::InputPinManager::GetInstance()->AddAnalogInputPin(2, Atomic::Event::RightJoystickX);
  Atomic::InputPinManager::GetInstance()->AddAnalogInputPin(4, Atomic::Event::RightJoystickY);
  Atomic::InputPinManager::GetInstance()->AddAnalogInputPin(21, Atomic::Event::RightJoystickX);
  Atomic::InputPinManager::GetInstance()->AddAnalogInputPin(22, Atomic::Event::RightJoystickY);
  Atomic::InputPinManager::GetInstance()->AddDigitalInputPin(23, Atomic::Event::RightJoystickButton);
  Atomic::LcdDisplayController::Init();
}

void loop()
{
}

int main()
{
  setup();
  while (true)
  {
    loop();
  }
}