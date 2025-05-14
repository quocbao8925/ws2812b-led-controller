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
const uint8_t rainbow_colors[16][3] = {
	    {10,  0,  0}, {10,  5,  0}, {10, 10,  0}, { 5, 10,  0},
	    { 0, 10,  0}, { 0, 10,  5}, { 0, 10, 10}, { 0,  5, 10},
	    { 0,  0, 10}, { 5,  0, 10}, {10,  0, 10}, {10,  0,  5},
	    {10,  0,  0}, {10,  3,  0}, {10,  6,  0}, {10,  3,  0}
	};

void ws2812_demos_set(ws2812_handleTypeDef *ws2812, uint8_t demo) {
    active_demo = demo;
}

void ws2812_demos_tick(ws2812_handleTypeDef *ws2812, uint16_t p1) {

    static const uint32_t led_interval = 20;

    static uint16_t line_led = 0;
    static uint32_t line_count = 0;
    static uint8_t line_color = 0;
    static uint32_t next_led = led_interval;
    static uint16_t smoothed_p1 = 0;
    static int display_led = 0;

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
    				rainbow_colors[line_color][0],
					rainbow_colors[line_color][1],
					rainbow_colors[line_color][2]);
    		setLedValues(ws2812, line_led-8,
    		    				0,
    							0,
    							0);
    		++line_led;
    		++line_count;
			if (line_count % 2 == 0)
				++line_color;
			if (line_color > 15)
				line_color = 0;
    		if (line_led >= LEDS)
    			line_led = 0;
    		next_led = now + led_interval;
    	}
        break;
    case 3: {
        // Làm mượt tín hiệu âm thanh
        smoothed_p1 = (smoothed_p1+ p1) / 2;
        int temp = (smoothed_p1 > 2000) ? (smoothed_p1 - 2000) : 0;
        int target_led = temp / 10;
        if (target_led > LEDS) target_led = LEDS;

        // Làm mượt display_led: thay đổi tối đa 1 mỗi bước
        if (display_led < target_led)
            display_led++;
        else if (display_led > target_led)
            display_led--;

        if (now >= next_led) {
            for (int i = 0; i < LEDS; i++) {
                if (i < display_led) {
                    ws2812->led[3 * i + RL] = 8;
                    ws2812->led[3 * i + GL] = 8;
                    ws2812->led[3 * i + BL] = 8;
                } else {
                    ws2812->led[3 * i + RL] = 0;
                    ws2812->led[3 * i + GL] = 0;
                    ws2812->led[3 * i + BL] = 0;
                }
            }

            ws2812->is_dirty = true;
            next_led = now + 2; // tốc độ cập nhật: 5ms/lần
        }
        break;
    }
    default:
        // De nothing really
    }
}
