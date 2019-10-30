#ifndef BBITMAP8_H
#define BBITMAP8_H

#include "BBitmap.h"

class BBitmap8 : public BBitmap {
public:
  BBitmap8(TUint aWidth, TUint aHeight, TUint16 aMemoryFlag = MEMF_SLOW) : BBitmap(aWidth, aHeight, 8, aMemoryFlag) {

  }

  BBitmap8(TAny *aRom, TUint16 aMemoryFlag = MEMF_SLOW) : BBitmap(aRom, aMemoryFlag) {

  }

  ~BBitmap8() {

  }
};

#endif
