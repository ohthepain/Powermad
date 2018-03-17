// xfacetest.ino

#include "MidiEvent.h"
#include "TimerController.h"
#include "TempoMonitor.h"
#include "PanelButtonsController.h"
#include "NavigationController.h"
#include "Song.h"
#include "InternalMidiClock.h"
#include "EventMonitor.h"
#include "InputPinManager.h"
#include "JoystickManager.h"
#include "LcdDisplayController.h"
#include "SongViewLcd.h"
#include "SeqViewLcd.h"
#include "ArpViewLcd.h"
#include "GateViewLcd.h"
#include "MidiManager.h"
#include "UsbMidiController.h"
#include "DinMidiController.h"
#include "SongPlayer.h"
#include "Event.h"
#include "SongPositionManager.h"
#include <usb_midi.h>
#include <Arduino.h>
#include "myassert.h"

#define LED 13

void setup()
{
  Atomic::EventController::Init();
  Atomic::EventMonitor::Init();
  Atomic::PanelButtonsController::Init();
  Atomic::TimerController::Init();
  Atomic::TempoMonitor::Init();
  Atomic::InputPinManager::Init();
  Atomic::InputPinManager::GetInstance()->AddAnalogInputPin(16, Atomic::AnalogInputId::LeftJoystickX);
  Atomic::InputPinManager::GetInstance()->AddAnalogInputPin(17, Atomic::AnalogInputId::LeftJoystickY);
  Atomic::InputPinManager::GetInstance()->AddDigitalInputPin(18, Atomic::KeyId::LeftJoystickButton);
  Atomic::InputPinManager::GetInstance()->AddAnalogInputPin(21, Atomic::AnalogInputId::RightJoystickX);
  Atomic::InputPinManager::GetInstance()->AddAnalogInputPin(22, Atomic::AnalogInputId::RightJoystickY);
  Atomic::InputPinManager::GetInstance()->AddDigitalInputPin(23, Atomic::KeyId::RightJoystickButton);
  Atomic::JoystickManager::Init();
  Atomic::JoystickManager::GetInstance()->AddJoytickAxis(Atomic::JoystickAxisId::LeftX,  Atomic::AnalogInputId::LeftJoystickX);
  Atomic::JoystickManager::GetInstance()->AddJoytickAxis(Atomic::JoystickAxisId::LeftY,  Atomic::AnalogInputId::LeftJoystickY);
  Atomic::JoystickManager::GetInstance()->AddJoytickAxis(Atomic::JoystickAxisId::RightX, Atomic::AnalogInputId::RightJoystickX);
  Atomic::JoystickManager::GetInstance()->AddJoytickAxis(Atomic::JoystickAxisId::RightY, Atomic::AnalogInputId::RightJoystickY);
  Atomic::LcdDisplayController::Init();

  Atomic::SongPlayer::Init();
  Atomic::NavigationController::Init();
  Atomic::InternalMidiClock::Init();
  Atomic::MidiManager::Init();
 	#ifdef USB_MIDI
  Atomic::UsbMidiController::Init();
  #endif
  Atomic::DinMidiController::Init();
  Atomic::SongViewLcd::Init();
  Atomic::SeqViewLcd::Init();
  Atomic::ArpViewLcd::Init();
  Atomic::GateViewLcd::Init();

  Atomic::NavigationController::GetInstance()->CreateSong();

  Atomic::SongPositionManager::Init();
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