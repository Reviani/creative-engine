#ifdef __MODUS_TARGET_DESKTOP_DISPLAY__
#include "DesktopDisplay.h"

#include <SDL.h>

static SDL_Window   *screen   = ENull;
static SDL_Renderer *renderer = ENull;
static SDL_Texture  *texture  = ENull;



DesktopDisplay::DesktopDisplay() : DisplayBase() {

  // initialize any hardware
  SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

  int flags =  SDL_WINDOW_OPENGL |  SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE| SDL_WINDOW_SHOWN;

  // Create an application window with the following settings:
  screen = SDL_CreateWindow(
    "creative-engine",                // window title
    SDL_WINDOWPOS_UNDEFINED,          // initial resources position
    SDL_WINDOWPOS_UNDEFINED,          // initial y position
    SCREEN_WIDTH * 2,                 // Width in pixels
    SCREEN_HEIGHT * 2,                // Height in pixels
    flags                             // flags - see above
  );

  SDL_SetWindowMinimumSize(screen, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);

  // Check that the window was successfully created
  if (screen == ENull) {
    // In the case that the window could not be made...
    printf("Could not create window: %s\n", SDL_GetError());
    exit(1);
  }

  //  TInt w, h;
//  SDL_GL_GetDrawableSize(screen, &w, &h);

  renderer = SDL_CreateRenderer(screen, -1, 0);
  if (! renderer) {
    printf("Cannot create renderer %s\n", SDL_GetError());
    exit(1);
  }

  SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
  SDL_RenderSetIntegerScale(renderer, SDL_TRUE);

  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH,
                              SCREEN_HEIGHT);
  if (! texture) {
    printf("Cannot create texture %s\n", SDL_GetError());
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  SDL_GL_SetSwapInterval(1);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  // try to move window, to fix SDL2 bug on MacOS (Mojave)
  int x, y;
  SDL_GetWindowPosition(screen, &x, &y);
  SDL_SetWindowPosition(screen, x+1, y+1);
}

DesktopDisplay::~DesktopDisplay() {
  // Close and destroy the window
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(screen);

  // Clean up
  SDL_Quit();

}

static TBool hackInitialized = EFalse;
void DesktopDisplay::Update() {
  // try to move window, to fix SDL2 bug on MacOS (Mojave)
  if (!hackInitialized){
    int x, y;
    SDL_GetWindowPosition(screen, &x, &y);
    SDL_SetWindowPosition(screen, x+1, y+1);
    SDL_SetWindowPosition(screen, x, y);
    hackInitialized = ETrue;
  }
  // swap display and render bitmaps
  SwapBuffers();

  void *screenBuf;
  TInt pitch;

  if (0 == SDL_LockTexture(texture, ENull, &screenBuf, &pitch)) {
    auto *screenBits = (TUint32 *) screenBuf;
    TRGB *palette    = displayBitmap->GetPalette();

    for (TInt16 y = 0; y < SCREEN_HEIGHT; y++) {
      TUint8 *ptr = &displayBitmap->mPixels[y * displayBitmap->GetPitch()];

      for (TInt x = 0; x < SCREEN_WIDTH; x++) {
        TUint8  pixel = *ptr++;
        TUint32 color = palette[pixel].rgb888();
        *screenBits++ = color;
      }
    }

//    (TUint32 *) screenBuf;
//    screenBits = (TUint32 *) screenBuf;
//    Dump(screenBits, renderBitmap->mWidth);
//    Dump(displayBitmap->mPixels, displayBitmap->mWidth, displayBitmap->mHeight);
    SDL_UnlockTexture(texture);
  }
  else {
    printf("Can't lock texture (%s)\n", SDL_GetError());
  }

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, ENull, ENull); // Render texture to entire window
  SDL_RenderPresent(renderer);              // Do update

  NextFrameDelay();
}

#endif