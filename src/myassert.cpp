// myassert.cpp

#include "myassert.h"
#include "LcdDisplayController.h"
#include <Arduino.h>

namespace Atomic
{
	void delay(uint32_t msec)
	{
		uint32_t lastmillis = millis();
		while (millis() < lastmillis + msec) {}
		lastmillis = millis();
	}

	void DisplayAssert(const char* file, int line, const char* exp)
	{
		Serial.println("Assertion failed:");
		Serial.print("File: ");
		Serial.println(file);
		Serial.print("Line: ");
		Serial.println(line);
		Serial.print("Exp: ");
		Serial.println(exp);		
	}

	void __attribute__((noreturn)) __my_assert_func(const char* file, int line, const char* exp)
	{
		while (1)
		{
			delay(1000);
			DisplayAssert(file, line, exp);
		}
		char temp[21];
		strncpy(temp, exp, 20);
		Atomic::LcdDisplayController::GetInstance()->Clear();
		Atomic::LcdDisplayController::GetInstance()->WriteToScreen(0, 0, "Assert line");
		delay(1000);
		Atomic::LcdDisplayController::GetInstance()->WriteToScreen(12, 0, line);
		delay(1000);
		Atomic::LcdDisplayController::GetInstance()->WriteToScreen(0, 1, file);
		delay(1000);
		Atomic::LcdDisplayController::GetInstance()->WriteToScreen(0, 2, temp);
		delay(1000);
		while (true)
		{
			Atomic::LcdDisplayController::GetInstance()->WriteToScreen(19, 0, (char)1);
			Atomic::LcdDisplayController::GetInstance()->WriteToScreen(19, 3, (char)2);
			delay(500);
			Atomic::LcdDisplayController::GetInstance()->WriteToScreen(19, 0, (char)2);
			Atomic::LcdDisplayController::GetInstance()->WriteToScreen(19, 3, (char)1);
			delay(500);
		}
	}
}
