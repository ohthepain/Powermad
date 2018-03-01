// SeqViewLcd.h

#include "View.h"
#include "Event.h"
#include <assert.h>

namespace Atomic
{
	class SeqViewLcd : public ViewLcd
	{
	public:
		static void Init();
		static void Shutdown();
		static SeqViewLcd* GetInstance() { assert(mInstance); return mInstance; }

	protected:
		virtual ViewId GetViewId() const { return ViewId::Seq; }

	private:
		static SeqViewLcd* mInstance;
		SeqViewLcd();
		virtual ~SeqViewLcd() {}

		virtual void HandleActiveEvent(const Event& event);
		void HandleMidiClock();
	};
}
