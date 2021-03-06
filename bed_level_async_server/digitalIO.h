#pragma once
#include "config.h"

// Assign output variables to GPIO pins
#define relay01 16
#define relay02 17
#define relay03 18
#define relay04 19

#define relay05 26
#define relay06 27
#define relay07 32
#define relay08 33

String side, part, action;
void timeEvent(String side, String part, int time);
void stop(String side, String part);
void head_up(String side);
void head_down(String side);
void feet_up(String side);
void feet_down(String side);
void head_reset(String side, String part);
void feet_reset(String side, String part);

void disable_all() {
	digitalWrite(relay01, HIGH);
	digitalWrite(relay02, HIGH);
	digitalWrite(relay03, HIGH);
	digitalWrite(relay04, HIGH);
	digitalWrite(relay05, HIGH);
	digitalWrite(relay06, HIGH);
	digitalWrite(relay07, HIGH);
	digitalWrite(relay08, HIGH);
}

void enable_all() {
	digitalWrite(relay01, LOW);
	digitalWrite(relay02, LOW);
	digitalWrite(relay03, LOW);
	digitalWrite(relay04, LOW);
	digitalWrite(relay05, LOW);
	digitalWrite(relay06, LOW);
	digitalWrite(relay07, LOW);
	digitalWrite(relay08, LOW);
}

void relay_init() {
	// Initialize the output variables as outputs
	pinMode(relay01, OUTPUT);
	pinMode(relay02, OUTPUT);
	pinMode(relay03, OUTPUT);
	pinMode(relay04, OUTPUT);
	pinMode(relay05, OUTPUT);
	pinMode(relay06, OUTPUT);
	pinMode(relay07, OUTPUT);
	pinMode(relay08, OUTPUT);
	// Prime outputs to desired value
	disable_all();
}

void gpio_act(String side, String part, String action) {

#ifdef DEBUG
	Serial.println("[GPIO] Settings:");
	Serial.print("[GPIO] -->side:");
	Serial.println(side);
	Serial.print("[GPIO] -->part:");
	Serial.println(part);
	Serial.print("[GPIO] -->action:");
	Serial.println(action);
#endif // DEBUG

	if (action == "stop")
	{
		stop(side, part);
	}
	if (part == "head")
	{
		if (action == "up")
		{
			head_up(side);
		}
		else if (action == "down")
		{
			head_down(side);
		}
		else if (action == "reset")
		{
			head_reset(side, part);
		}
		else
		{
			//TODO
		}
	}
	if (part == "feet")
	{
		if (action == "up")
		{
			feet_up(side);
		}
		else if (action == "down")
		{
			feet_down(side);
		}
		else if (action == "reset")
		{
			feet_reset(side, part);
		}
		else
		{
			//TODO
		}

	}
}
void head_up(String side) {
	if (side == "booth")
	{
		digitalWrite(relay02, HIGH);
		digitalWrite(relay06, HIGH);
		digitalWrite(relay01, LOW);
		digitalWrite(relay05, LOW);
	}
	else if (side == "right")
	{
		digitalWrite(relay02, HIGH);
		digitalWrite(relay01, LOW);
	}
	else
	{
		digitalWrite(relay06, HIGH);
		digitalWrite(relay05, LOW);
	}
}
void head_down(String side) {
	if (side == "booth")
	{
		digitalWrite(relay01, HIGH);
		digitalWrite(relay05, HIGH);
		digitalWrite(relay02, LOW);
		digitalWrite(relay06, LOW);
	}
	else if (side == "right")
	{
		digitalWrite(relay01, HIGH);
		digitalWrite(relay02, LOW);
	}
	else
	{
		digitalWrite(relay05, HIGH);
		digitalWrite(relay06, LOW);
	}
}
void head_reset(String side, String part) {
	head_down(side);
	delay(5000);
	stop(side, part);
}
void feet_up(String side) {
	if (side == "booth")
	{
		digitalWrite(relay04, HIGH);
		digitalWrite(relay08, HIGH);
		digitalWrite(relay03, LOW);
		digitalWrite(relay07, LOW);
	}
	else if (side == "right")
	{
		digitalWrite(relay04, HIGH);
		digitalWrite(relay03, LOW);
	}
	else
	{
		digitalWrite(relay08, HIGH);
		digitalWrite(relay07, LOW);
	}
}
void feet_down(String side) {
	if (side == "booth")
	{
		digitalWrite(relay03, HIGH);
		digitalWrite(relay07, HIGH);
		digitalWrite(relay04, LOW);
		digitalWrite(relay08, LOW);
	}
	else if (side == "right")
	{
		digitalWrite(relay03, HIGH);
		digitalWrite(relay04, LOW);
	}
	else
	{
		digitalWrite(relay07, HIGH);
		digitalWrite(relay08, LOW);
	}
}
void feet_reset(String side, String part) {
	feet_down(side);
	delay(5000);
	stop(side, part);
}

void stop(String side, String part) {
	if (side == "booth")
	{
		if (part == "head")
		{
			digitalWrite(relay01, HIGH);
			digitalWrite(relay02, HIGH);
			digitalWrite(relay05, HIGH);
			digitalWrite(relay06, HIGH);
		}
		else
		{
			digitalWrite(relay03, HIGH);
			digitalWrite(relay04, HIGH);
			digitalWrite(relay07, HIGH);
			digitalWrite(relay08, HIGH);
		}
	}
	else if (side == "right")
	{
		if (part == "head")
		{
			digitalWrite(relay01, HIGH);
			digitalWrite(relay02, HIGH);
		}
		else
		{
			digitalWrite(relay03, HIGH);
			digitalWrite(relay04, HIGH);
		}
	}
	else if (side == "left")
	{
		if (part == "head")
		{
			digitalWrite(relay05, HIGH);
			digitalWrite(relay06, HIGH);
		}
		else
		{
			digitalWrite(relay07, HIGH);
			digitalWrite(relay08, HIGH);
		}
	}
	else
	{
		disable_all();
	}
}


void calibrate() {
	head_reset("booth", "head");
	feet_reset("booth", "feet");
}

void timeEvent(String side, String part, int time) {
	calibrate();
	Serial.println("[PRESET] TimerEvent");
	Serial.print("[PRESET] Time: ");
	Serial.println(time);
	gpio_act(side, part, "up");
	delay(time);
	stop(side, part);
}