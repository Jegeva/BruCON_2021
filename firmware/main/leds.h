#ifndef BRUCON_LEDS_H
#define BRUCON_LEDS_H

void init_leds(void);
void set_rgb(unsigned short r,unsigned short g,unsigned short b);
void set_rgb8(unsigned char r,unsigned char g,unsigned char b);
void set_rgb32(unsigned int c) ;
void setwheel(void);
void set_wheelrank(unsigned int rank);
void nextwheelpow(int inc);
void nextwheel(unsigned int inc);
void  set_pow(unsigned int pow);
void taskColorWheel();
void taskColorAdvertise();
void starttaskColorAdvertise(unsigned int v);
void stoptaskColorAdvertise();
#endif
