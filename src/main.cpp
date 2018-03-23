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
#include <setjmp.h> 
//#include <notused.h>

#include <vector>
extern "C" {
#include <lua-5.3.4/src/lua.h>
#include <lua-5.3.4/src/lauxlib.h>
#include <lua-5.3.4/src/lualib.h>
}

#include "lua-5.3.4/src/luapluscd.h"

#define ScriptRegisterMemberDirect(state,name,ptr,directfunctor) \
{ \
  assert(ptr != nullptr); \
  lua_pushdirectclosure(state, *ptr, &directfunctor); \
  lua_setglobal(state, name); \
}

#define ScriptRegisterDirect(state,name,directfunctor) \
{ \
  lua_pushdirectclosure(state, directfunctor, 0); \
  lua_setglobal(state, name); \
}

int spankmesilly(int n)
{
  msg("spankmesilly: ", n);
  return n;
}

std::vector<int> myvectorofint;

#define LED 13

extern "C" {
  int _open( const char *filename, int oflag, int pmode)
  {
    //myassert(false);
    return 0;
  }

  #include <sys/time.h>

  int _gettimeofday( struct timeval *tv, void *tzvp )
  {
      tv->tv_usec = micros();  // get remaining microseconds
      tv->tv_sec = tv->tv_usec / 1000000;  // convert to seconds
      return 0;  // return non-zero for error
  }  

  #include <sys/times.h>
  clock_t _times(struct tms* tms) {
    return (clock_t)-1;
  }
}

lua_State* L = nullptr;

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

  L = luaL_newstate(); 
  //lua_close(L); 
  luaopen_base(L);             /* opens the basic library */
  luaopen_table(L);            /* opens the table library */
  //luaopen_io(L);               /* opens the I/O library */
  luaopen_string(L);           /* opens the string lib. */
  luaopen_math(L);             /* opens the math lib. */

  ScriptRegisterDirect(L, "dospank", spankmesilly);
}

void loop()
{
  delay(500);
  msg(5);

  luaL_dostring(L, "a = 10 + 5"); 
  lua_getglobal(L, "a"); 
  int i = lua_tointeger(L, -1); 
  msg("i is ", i);
  luaL_dostring(L, "i = 11 dospank(i)");
}

int main()
{
  setup();

  while (true)
  {
    loop();
  }
}