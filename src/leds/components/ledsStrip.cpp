#include "ledsStrip.hpp"


//To reenable the first pixel: replace numleds+1 by numleds; remove this->colors[0] = 0; replace i+1 by i in setPixelColor() and getPixelColor()  

LedsStrip::LedsStrip(uint16_t numleds, uint8_t pin, uint16_t rmt_chan) {

	this->numpixels = numleds+1;
	this->numbits = (this->numpixels * 24) + 1;
	this->channel = (rmt_channel_t)rmt_chan;

	// I need 24 bits per led, plus a terminator
	this->bits = new rmt_item32_t[this->numbits];
	this->colors = new uint32_t[this->numpixels];
	this->clear();

	pinMode(pin, OUTPUT);

	/*
	 *	typedef struct {
	 *		union {
	 *			struct {
	 *				uint32_t duration0 :15;
	 *				uint32_t level0 :1;
	 *				uint32_t duration1 :15;
	 *				uint32_t level1 :1;
	 *			};
	 *			uint32_t val;
	 *		};
	 *	} rmt_item32_t;
	 */
	// all the timing is done here.
	// the clk_div is 8, so we are working with 100ns units in duration
	this->highbit.duration0 = 8; // should be 0.8 us
	this->highbit.level0 = 1;
	this->highbit.duration1 = 5; // shouod be .45 us, but we have .15 wiggle room
	this->highbit.level1 = 0;

	this->lowbit.duration0 = 4;	// should be 0.4 us
	this->lowbit.level0 = 1;
	this->lowbit.duration1 = 8; // should be 0.85 us, but we have .15 us wiggle room
	this->lowbit.level1 = 0;

	this->termbit.val = 0;


	rmt_config_t config;
	config.rmt_mode = RMT_MODE_TX;
	config.channel = this->channel;
	config.gpio_num = (gpio_num_t)pin;
	// number of memory blocks used for now just take as many as we can get
	config.mem_block_num = 8 - rmt_chan;
	// range of pulse len generated. Source clock is typically 80Mhz.
	// So div by 8 means each tick is at 100ns
	config.clk_div = 8;
	config.tx_config.loop_en = 0;
	config.tx_config.carrier_en      = 0;
	config.tx_config.idle_output_en  = 1;
	config.tx_config.idle_level      = (rmt_idle_level_t)0;
	// we disabled the carrier, but fill it out anyway
	config.tx_config.carrier_freq_hz = 10000;
	config.tx_config.carrier_level   = (rmt_carrier_level_t)1;
	config.tx_config.carrier_duty_percent = 50;

	rmt_config(&config);
	// no rx buf, default flags
	rmt_driver_install(this->channel, 0, 0);

	//Disable the first pixel by default
	this->colors[0] = 0;
}

LedsStrip::~LedsStrip(void) {
	delete[] this->colors;
	delete[] this->bits;
}

void LedsStrip::show() {
	rmt_item32_t* cur;
	uint16_t i;
	int bt;
	uint32_t c;
	bool bitset;

	cur = this->bits;

	for (i=0; i<this->numpixels; i++) {
		c = this->colors[i];

		// ok we have the color, we need to set up our bits from MSB to LSB in GRB

		// set up G
		for (bt = 15; bt >= 8; bt--) {
			bitset = c & (1 << bt);
			*cur = (bitset) ? this->highbit : this->lowbit;
			cur++;
		}
		// set up R
		for (bt = 23; bt >= 16; bt--) {
			bitset = c & (1 << bt);
			*cur = (bitset) ? this->highbit : this->lowbit;
			cur++;
		}
		// set up B
		for (bt = 7; bt >= 0; bt--) {
			bitset = c & (1 << bt);
			*cur = (bitset) ? this->highbit : this->lowbit;
			cur++;
		}

	}
	// set terminator
	*cur = this->termbit;

	// tell the rmt to write it out
	rmt_write_items(this->channel, this->bits, this->numbits, 1); // wait_tx_done
}

void LedsStrip::clear() {
	this->clearTo(0);
}

void LedsStrip::setPixelColor(const uint16_t i, const RgbColor color) {
	if (i > this->numpixels) {
		return;
	}
	
	// Store GRB
	this->colors[i+1] = ((color.R&0x0ff)<<16)|((color.G&0x0ff)<<8)|(color.B&0x0ff); //i+1 because we need disable the first pixel
}

RgbColor LedsStrip::getPixelColor(const uint16_t i) {
	return RgbColor(colors[i+1]);
}

void LedsStrip::changeLength(int length){
    this->clear();
    this->show();
    
    this->numpixels = length;
	this->numbits = (length * 24) + 1;
	this->channel = (rmt_channel_t)channel;

	// I need 24 bits per led, plus a terminator
	this->bits = new rmt_item32_t[this->numbits];
	this->colors = new uint32_t[length];
	rmt_write_items(this->channel, this->bits, this->numbits, 1); // wait_tx_done
    this->clear();
}

int LedsStrip::getLength(){
    return this->numpixels;
}

void LedsStrip::clearTo(RgbColor color){
	for(int x = 0;x<this->numpixels;x++){
		setPixelColor(x, color);
	}
}

void LedsStrip::rotateLeft(int i){

	for(int x = 0;x<this->numpixels;x++){		
		if(x+i>=this->numpixels){
			setPixelColor(x, getPixelColor(x+i-this->numpixels));
		} else {
			setPixelColor(x, getPixelColor(x+i));
		}
	}

}

void LedsStrip::rotateRight(int i){
	for(int x = this->numpixels;x>=0;x--){		
		if(x-i<0){
			setPixelColor(x, getPixelColor(x-i+this->numpixels));
		} else {
			setPixelColor(x, getPixelColor(x-i));
		}
	}
}

void LedsStrip::shiftLeft(int i){

	for(int x = 0;x<this->numpixels;x++){		
		if(x+i>=this->numpixels){
			setPixelColor(x, 0);
		} else {
			setPixelColor(x, getPixelColor(x+i));
		}
	}

}

void LedsStrip::shiftRight(int i){
	for(int x = this->numpixels;x>=0;x--){		
		if(x-i<0){
			setPixelColor(x, 0);
		} else {
			setPixelColor(x, getPixelColor(x-i));
		}
	}
}