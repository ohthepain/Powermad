// SongViewLcd.h

#include "View.h"
#include "MidiEvent.h"
#include <myassert.h>

namespace Atomic
{
	class SongViewLcd : public ViewLcd
	{
	public:
		static void Init();
		static void Shutdown();
		static SongViewLcd* GetInstance() { myassert(mInstance); return mInstance; }

	protected:
		virtual ViewId GetViewId() const { return ViewId::Song; }

	private:
		static SongViewLcd* mInstance;
		SongViewLcd();
		virtual ~SongViewLcd() {}

		virtual void HandleActiveEvent(const Event& event);
		void HandleMidiClock();
	};
}
