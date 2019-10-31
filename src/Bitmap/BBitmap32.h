#ifndef BBITMAP32_H
#define BBITMAP32_H

#include "BBitmap.h"

class BBitmap32 : public BBitmap {
public:
  BBitmap32(TUint aWidth, TUint aHeight, TUint16 aMemoryFlag = MEMF_SLOW) : BBitmap(aWidth, aHeight, 32, aMemoryFlag) {
    mPitch = mWidth * 4;
    mPixels = (TUint32 *)AllocMem(mPitch * mHeight * sizeof(TUint32), aMemoryFlag);
  }

  BBitmap32(TAny *aRom, TUint32 aMemoryFlag = MEMF_SLOW) : BBitmap(aRom, aMemoryFlag) {
  }

  ~BBitmap32() {
  }

  TUint32 *mPixels;
};

#endif
