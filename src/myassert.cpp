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

	#ifndef NDEBUG
	void write()
	{
		Serial.println("");
	}

	void dowrite(const char* s)
	{
		Serial.print(s);
	}

	void dowrite(int i)
	{
		Serial.print(i);
	}
	#endif

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

	void __attribute__((noreturn)) __my_assert_func(const char* file, int line, const char* exp, const char* msg)
	{
		DisplayAssert(file, line, exp);
		char temp[21];
		if (msg != nullptr)
		{
			strncpy(temp, msg, 20);
		}
		else
		{
			strncpy(temp, exp, 20);
		}
		Atomic::LcdDisplayController::GetInstance()->Clear();
		Atomic::LcdDisplayController::GetInstance()->WriteToScreen(0, 0, "Assert line");
		Atomic::LcdDisplayController::GetInstance()->WriteToScreen(12, 0, line);
		Atomic::LcdDisplayController::GetInstance()->WriteToScreen(0, 1, file);
		Atomic::LcdDisplayController::GetInstance()->WriteToScreen(0, 2, temp);
		while (true)
		{
			Atomic::LcdDisplayController::GetInstance()->WriteToScreen(19, 0, (char)1);
			Atomic::LcdDisplayController::GetInstance()->WriteToScreen(19, 3, (char)2);
			delay(700);
			Atomic::LcdDisplayController::GetInstance()->WriteToScreen(19, 0, (char)2);
			Atomic::LcdDisplayController::GetInstance()->WriteToScreen(19, 3, (char)1);
			delay(700);
			DisplayAssert(file, line, exp);
		}
	}
}
