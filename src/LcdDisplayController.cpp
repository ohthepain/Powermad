// LcdDisplayController.cpp

#include "Event.h"
#include "LcdDisplayController.h"
#include <Arduino.h>
#include <LiquidCrystal.h>

#define LCD_RS_PIN 31
#define CONTRAST_PIN 30
#define LCD_RW_PIN 29
#define LCD_ENABLE_PIN 28
#define LCD_D0_PIN 27
#define LCD_D1_PIN 26
#define LCD_D2_PIN 25
#define LCD_D3_PIN 24
#define LCD_D4_PIN 35
#define LCD_D5_PIN 36
#define LCD_D6_PIN 37
#define LCD_D7_PIN 38
 
byte smiley[8] = { 0b00000, 0b00000, 0b01010, 0b00000, 0b00000, 0b10001, 0b01110, 0b00000 };
byte armsUp[8] = { 0b00100, 0b01010, 0b00100, 0b10101, 0b01110, 0b00100, 0b00100, 0b01010 };
byte frownie[8] = { 0b00000, 0b00000, 0b01010, 0b00000, 0b00000, 0b00000, 0b01110, 0b10001 }; 

namespace Atomic
{
	LcdDisplayController* LcdDisplayController::mInstance = nullptr;

	LcdDisplayController::LcdDisplayController()
	{
		mLiquidCrystal = new LiquidCrystal(LCD_RS_PIN, LCD_RW_PIN, LCD_ENABLE_PIN,
			LCD_D0_PIN, LCD_D1_PIN, LCD_D2_PIN, LCD_D3_PIN,
			LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

		EventController::EventHandler handler = [&](const Event& event) { this->HandleEvent(event); return 0; };
		EventController::GetInstance()->AddEventHandler(Event::SecondClock, handler);

		// Switch on the backlight and LCD contrast levels
		pinMode(CONTRAST_PIN, OUTPUT);
		analogWrite(CONTRAST_PIN, CONTRAST_PIN);

		mLiquidCrystal->begin(20,4);               // initialize the lcd 

		mLiquidCrystal->createChar (0, smiley);    // load character to the LCD
		mLiquidCrystal->createChar (1, armsUp);    // load character to the LCD
		mLiquidCrystal->createChar (2, frownie);   // load character to the LCD

		mLiquidCrystal->home ();                   // go home
		mLiquidCrystal->print("Hello, ARDUINO ");  
		mLiquidCrystal->setCursor ( 0, 1 );        // go to the next line
		mLiquidCrystal->print (" FORUM - fm   ");      
	}

	LcdDisplayController::~LcdDisplayController()
	{
		delete mLiquidCrystal;
		mLiquidCrystal = nullptr;
	}

	void LcdDisplayController::Init()
	{
		mInstance = new LcdDisplayController();
	}

	void LcdDisplayController::Shutdown()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	void LcdDisplayController::HandleEvent(const Event& event)
	{
		static bool dwit = false;
		if (dwit)
		{
			Serial.println("dwit true");
			mLiquidCrystal->setCursor ( 14, 1 );
			mLiquidCrystal->print (char(2));
		}
		else
		{
			Serial.println("dwit false");
			mLiquidCrystal->setCursor ( 14, 1 );
			mLiquidCrystal->print ( char(0));
		}
		dwit = !dwit;
	}
}
