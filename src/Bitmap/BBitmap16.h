#ifndef BBITMAP16_H
#define BBITMAP16_H

#include "BBitmap.h"

class BBitmap16 : public BBitmap {
public:
  BBitmap16(TUint aWidth, TUint aHeight, TUint16 aMemoryFlag = MEMF_SLOW) : BBitmap(aWidth, aHeight, 16, aMemoryFlag) {
    mPitch = mWidth * 2;
    // mPixels = (TUint16 *)AllocMem(mWidth * mHeight * sizeof(TUint16), aMemoryFlag);
  }

  BBitmap16(TAny *aRom, TUint16 aMemoryFlag = MEMF_SLOW) : BBitmap(aRom, aMemoryFlag) {
  }

  ~BBitmap16() {
  }
};

#endif
