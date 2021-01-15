#include <stdint.h>
#include <Arduino.h>
#include <driver/rmt.h>
#include "rgbColor.hpp"

#ifndef LedsStrip_H_INCLUDED
#define LedsStrip_H_INCLUDED

class LedsStrip {
	public:
		LedsStrip(uint16_t numleds, uint8_t pin, uint16_t rmt_chan);
		~LedsStrip(void);

		void show();
		void clear();
		void setPixelColor(const uint16_t i, const RgbColor color);
		RgbColor getPixelColor(uint16_t i);

        void changeLength(int length);
        int getLength();
		void clearTo(RgbColor color);

		void shiftLeft(int i);
		void shiftRight(int i);

		void rotateLeft(int i);
		void rotateRight(int i);

	private:
		uint16_t numpixels;
		uint16_t numbits;
		rmt_channel_t channel;
		rmt_item32_t* bits;
		uint32_t* colors;
		rmt_item32_t highbit;
		rmt_item32_t lowbit;
		rmt_item32_t termbit;
};

#endif