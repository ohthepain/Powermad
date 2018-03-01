// SongViewLcd.h

#include "Event.h"
#include <assert.h>
#include <LcdDisplayController.h>

namespace Atomic
{
	class View
	{
	public:
		View() : mIsActive(false) {}
		virtual ~View() {}
		void SetActive(bool active) { mIsActive = active; }
		bool IsActive() const { return mIsActive; }
		virtual ViewId GetViewId() const = 0;

		virtual void HandleEvent(const Event& event);
		virtual void HandleActiveEvent(const Event& event) = 0;
	private:
		bool mIsActive;
	};

	class ViewLcd : public View
	{
	public:
		ViewLcd() : mLcdDisplayController(LcdDisplayController::GetInstance()) {}
		virtual ~ViewLcd() {}
	protected:
		LcdDisplayController* mLcdDisplayController;
	};

	class SongViewLcd : public ViewLcd
	{
	public:
		static void Init();
		static void Shutdown();
		static SongViewLcd* GetInstance() { assert(mInstance); return mInstance; }

	protected:
		virtual ViewId GetViewId() const { return ViewId::Song; }

	private:
		static SongViewLcd* mInstance;
		SongViewLcd();
		virtual ~SongViewLcd() {}

		virtual void HandleActiveEvent(const Event& event);
	};
}
