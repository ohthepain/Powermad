// GateViewLcd.h

#include "View.h"
#include "MidiEvent.h"
#include <myassert.h>

namespace Atomic
{
	class GateViewLcd : public ViewLcd
	{
	public:
		static void Init();
		static void Shutdown();
		static GateViewLcd* GetInstance() { myassert(mInstance); return mInstance; }

	protected:
		virtual ViewId GetViewId() const { return ViewId::Gate; }

	private:
		static GateViewLcd* mInstance;
		GateViewLcd();
		virtual ~GateViewLcd() {}

		virtual void HandleActiveEvent(const Event& event);
		void HandleMidiClock();
	};
}
