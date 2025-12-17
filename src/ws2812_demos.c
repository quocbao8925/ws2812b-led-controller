/**
 ******************************************************************************
 * @file           : ws2812_demos.h
 * @brief          : Ws2812b demos source
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 Lars Boegild Thomsen <lbthomsen@gmail.com>.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "main.h"
#include "ws2812.h"
#include "ws2812_demos.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>


uint8_t active_demo = 0;
const uint8_t led_line_colors[][3] = {
        { 10, 0, 0 },
        { 0, 10, 0 },
        { 0, 0, 10 },
        { 10, 10, 0 },
        { 0, 10, 10 },
        { 10, 0, 10 },
        { 10, 10, 10 }
};
const uint8_t rainbow_colors[32][3] = {
    {100,   0,   0}, {100,  43,   0}, {100,  86,   0}, { 83, 100,   0},
    { 56, 100,   0}, { 13, 100,   0}, {  0, 100,  33}, {  0, 100,  76},
    {  0, 100, 100}, {  0,  76, 100}, {  0,  33, 100}, { 13,   0, 100},
    { 56,   0, 100}, { 83,   0, 100}, {100,   0,  86}, {100,   0,  43},
    {100,   0,   0}, {100,  43,   0}, {100,  86,   0}, { 83, 100,   0},
    { 56, 100,   0}, { 13, 100,   0}, {  0, 100,  33}, {  0, 100,  76},
    {  0, 100, 100}, {  0,  76, 100}, {  0,  33, 100}, { 13,   0, 100},
    { 56,   0, 100}, { 83,   0, 100}, {100,   0,  86}, {100,   0,  43}
};
const uint8_t blue_to_red[16][3] = {
    {  0,   0, 100},
	{  0,   0, 95},
	{  0,   0, 95},
	{  0,   0, 90},
	{ 15,   0, 90},
	{ 20,   0, 85},
	{ 20,   0, 85},
    { 25,   0, 85},
    { 50,   0, 80},
    { 75,   0, 80},
    { 80,   0, 75},
    { 80,   0,  75},
    { 90,   0,  50},
    { 90,   0,  25},
	{100,   0,   0},
	{100,   0,   0},
};

void ws2812_demos_set(ws2812_handleTypeDef *ws2812, uint8_t demo) {
    active_demo = demo;
}

void ws2812_demos_tick(ws2812_handleTypeDef *ws2812, uint16_t p1, uint8_t speed) {

    static const uint32_t led_interval = 20;

    static uint16_t line_led = 0;
    static uint32_t line_count = 0;
    static uint16_t line_color = 0;
    static uint32_t next_led = led_interval;
    static uint32_t next_color = led_interval;
    static uint16_t smoothed_p1 = 0;
    static int display_led = 0;
    static uint8_t fade = 1;
    uint32_t now = uwTick;

    switch (active_demo) {
    case WS2812_DEMO_LINE:
        if (now >= next_led) {
            //zeroLedValues(ws2812);
            setLedValues(ws2812, line_led, led_line_colors[line_color][0], led_line_colors[line_color][1], led_line_colors[line_color][2]);
            ++line_led;
            ++line_count;
            if (line_count % 64 == 0)
                ++line_color;
            if (line_color >= sizeof(led_line_colors) / sizeof(led_line_colors[0]))
                line_color = 0;
            if (line_led >= LEDS)
                line_led = 0;

            next_led = now + led_interval;
        }
        break;
    case 2:
    	if (now >= next_led)
    	{
    		setLedValues(ws2812, line_led,
    				BRIGHTNESS_ADJUST*rainbow_colors[line_color][0],
					BRIGHTNESS_ADJUST*rainbow_colors[line_color][1],
					BRIGHTNESS_ADJUST*rainbow_colors[line_color][2]);
    		setLedValues(ws2812, line_led-8,
    		    				0,
    							0,
    							0);
    		++line_led;
    		++line_count;
			if (line_count % 2 == 0)
				++line_color;
			if (line_color >= sizeof(rainbow_colors) / sizeof(rainbow_colors[0]))
				line_color = 0;
    		if (line_led >= LEDS)
    			line_led = 0;
    		next_led = now + led_interval*(1 + speed);
    	}
        break;
    case 3: {
        smoothed_p1 = p1;
        int temp = ((smoothed_p1 - MINSOUND < 0)? 0:smoothed_p1 - MINSOUND);
        int target_led = temp / 14;
        if (target_led > LEDS) target_led = LEDS;

        if (display_led < target_led)
            display_led += 2;
        else if (display_led > target_led)
            display_led -= 2;
        uint8_t pick = display_led/2;
        pick = ((pick >= 16)? 15 : pick);
            for (int i = 0; i < LEDS; i++) {
                if (i < display_led) {
                    ws2812->led[3 * i + RL] = BRIGHTNESS_ADJUST*blue_to_red[pick][0];
                    ws2812->led[3 * i + GL] = BRIGHTNESS_ADJUST*blue_to_red[pick][1];
                    ws2812->led[3 * i + BL] = BRIGHTNESS_ADJUST*blue_to_red[pick][2];
                } else {
                    ws2812->led[3 * i + RL] = 0;
                    ws2812->led[3 * i + GL] = 0;
                    ws2812->led[3 * i + BL] = 0;
                }
            }

            ws2812->is_dirty = true;
        break;
    }
    case 4:
    {
    	for (int i = 0; i < LEDS; i++)
    	{
    		ws2812->led[3 * i + RL] = BRIGHTNESS_ADJUST*rainbow_colors[line_color][0];
			ws2812->led[3 * i + GL] = BRIGHTNESS_ADJUST*rainbow_colors[line_color][1];
			ws2812->led[3 * i + BL] = BRIGHTNESS_ADJUST*rainbow_colors[line_color][2];
    	}
    	if (now > next_color)
    	{
    		ws2812->is_dirty = true;
    		line_color++;
    		next_color = now + led_interval*10*(1+speed);
    	}
    	if (line_color >= sizeof(rainbow_colors) / sizeof(rainbow_colors[0]))
    		line_color = 0;
    	break;
    }
    case 5:
    {
    	for (int i = 0; i < LEDS; i++)
		{
			ws2812->led[3 * i + RL] = BRIGHTNESS_ADJUST*rainbow_colors[(line_color+i)%(sizeof(rainbow_colors) / sizeof(rainbow_colors[0]))][0];
			ws2812->led[3 * i + GL] = BRIGHTNESS_ADJUST*rainbow_colors[(line_color+i)%(sizeof(rainbow_colors) / sizeof(rainbow_colors[0]))][1];
			ws2812->led[3 * i + BL] = BRIGHTNESS_ADJUST*rainbow_colors[(line_color+i)%(sizeof(rainbow_colors) / sizeof(rainbow_colors[0]))][2];
		}
		if (now > next_led)
		{
			ws2812->is_dirty = true;
			line_color++;
			next_led = now + led_interval*2*(1+speed);
		}
		if (line_color >= sizeof(rainbow_colors) / sizeof(rainbow_colors[0]))
			line_color = 0;
		break;
    }
    case 6:
    {
    	if (now > line_count)
    	{
    		line_count = now + 20*(speed+1);
    		fade = !fade;
    	}
    	for (int i = 0; i < LEDS; i++)
		{
    		ws2812->led[3 * i + RL] = BRIGHTNESS_ADJUST*fade*rainbow_colors[line_color][0];
			ws2812->led[3 * i + GL] = BRIGHTNESS_ADJUST*fade*rainbow_colors[line_color][1];
			ws2812->led[3 * i + BL] = BRIGHTNESS_ADJUST*fade*rainbow_colors[line_color][2];
		}
		if (now > next_led && !fade)
		{
			line_color++;
			next_led = now + led_interval*15;
		}
		else
			ws2812->is_dirty = true;
		if (line_color >= sizeof(rainbow_colors) / sizeof(rainbow_colors[0]))
			line_color = 0;
		break;
    }
    case 7:
    {

        break;
    }
    default:
        // De nothing really
    }
}
