// ArpViewLcd.h

#include "View.h"
#include "MidiEvent.h"
#include <myassert.h>

namespace Atomic
{
	class ArpViewLcd : public ViewLcd
	{
	public:
		static void Init();
		static void Shutdown();
		static ArpViewLcd* GetInstance() { myassert(mInstance); return mInstance; }

	protected:
		virtual ViewId GetViewId() const { return ViewId::Arp; }

	private:
		static ArpViewLcd* mInstance;
		ArpViewLcd();
		virtual ~ArpViewLcd() {}

		virtual void HandleActiveEvent(const Event& event);
		void HandleMidiClock();
	};
}
