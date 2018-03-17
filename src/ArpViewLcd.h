// ArpViewLcd.h

#include "View.h"
#include "MidiEvent.h"
//#include "Song.h"
#include <myassert.h>

namespace Atomic
{
	class Arp;

	class ArpViewLcd : public ViewLcd
	{
	public:
		static void Init();
		static void Shutdown();
		static ArpViewLcd* GetInstance() { myassert(mInstance); return mInstance; }

		void SetCurrentArp(Arp* arp) { mArp = arp; }

	protected:
		virtual ViewId GetViewId() const { return ViewId::Arp; }

	private:
		static ArpViewLcd* mInstance;
		ArpViewLcd();
		virtual ~ArpViewLcd() {}

		void Refresh();
		void DrawBar(int n, uint8_t value);

		virtual void HandleActiveEvent(const Event& event);
		void HandleMidiClock();

		void SetCursor(int row, int column);

		Arp* mArp;
		int mCurrentRow;
		int mCurrentColumn;
		int mCurrentPage;
	};
}
