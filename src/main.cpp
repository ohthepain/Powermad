// xfacetest.ino

#include "Event.h"
#include "TimerController.h"
#include "TempoMonitor.h"
#include "PanelButtonsController.h"
#include "NavigationController.h"
#include "Song.h"
#include "InternalMidiClock.h"
#include "EventMonitor.h"

#define LED 13

void setup()
{
  Atomic::EventController::Init();
  Atomic::NavigationController::Init();
  Atomic::PanelButtonsController::Init();
  Atomic::TimerController::Init();
  Atomic::TempoMonitor::Init();
  Atomic::InternalMidiClock::Init();
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