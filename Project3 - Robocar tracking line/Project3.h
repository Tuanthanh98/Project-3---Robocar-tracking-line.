#include <16F877A.h>
#device ADC=16

#FUSES WDT                      //Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#device ICD=TRUE
#use delay(crystal=20000000,restart_wdt)
#use fast_io(C)
#use fast_io(B)
#use fast_io(D)

