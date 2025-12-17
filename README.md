# STM32F4 WS2812B Controller (DMA + PWM)

Efficient WS2812B LED driver for STM32F4 utilizing **Timer PWM** and **DMA** for zero CPU overhead.

Based on the original implementation by [MaJerle](https://github.com/MaJerle/stm32-ws2811-ws2812-ws2812b-ws281x-tim-pwm-dma-timer).

## ⚙️ CubeMX Configuration (Crucial)

To achieve the precise **800kHz** timing required by WS2812B:

* **Timer:** Set Channel to `PWM Generation`.
* **Prescaler (PSC):** `0`.
* **Counter Period (ARR):** `(Timer_Clock / 800000) - 1`.
    * *Example:* If Timer Clock is **84MHz** $\rightarrow$ ARR = `104`.
* **DMA Settings:**
    * Request: `TIMx_CHx` (Corresponding to your PWM channel).
    * Direction: `Memory To Peripheral`.
    * Priority: `High`.
