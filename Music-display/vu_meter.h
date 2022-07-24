#ifndef VU_METER_H
#define VU_METER_H
#include <FastLED.h>
#include <pixeltypes.h>

void normalVU(int volume);
void mirrorVU(int volume);

void my_fill_rainbow( struct CRGB * pFirstLED, 
                  int start,
                  int numToFill,
                  uint8_t initialhue,
                  uint8_t deltahue );
void reverse_fill_rainbow( struct CRGB * pFirstLED, 
                  int end,
                  int begin,
                  uint8_t initialhue,
                  uint8_t deltahue );

#endif
