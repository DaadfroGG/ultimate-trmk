# ultimate-trmk

A minimalistic and flexible C++ SDL2 wrapper built for personal game and graphics experiments. `ultimate-trmk` abstracts rendering, event handling, and timing logic to make prototyping SDL projects faster and easier.

## Features

- Simple event system with key/mouse utilities  
- Frame timing and FPS limiting  
- Renderer class with drawing primitives (points, lines, circles, triangles, polygons)  
- `Tex` class for off-screen rendering with pixel manipulation and basic image operations  
- Clean API for separating drawing logic between screen and texture  
- Compile-time flags to control rendering behavior (e.g., `NO_OVERLAP`, `NOISE`)

## Example Usage

```cpp
// Draw a red point on the screen
renderer.drawPoint(renderdraw_noflag, 100, 100, 0xFF0000, 0);

// Draw a red triangle on a texture
renderer.fillTriangle(texdraw_noflag, 100, 100, 200, 200, 300, 100, 0xFF0000, 0);

// Display a texture at position (100,100)
renderer.drawTex(&tex, 100, 100);
```

## Components

### Renderer
Encapsulates all low-level SDL drawing operations.

- `drawPoint`, `drawLine`, `drawCircle`  
- `fillTriangle`, `fillPolygon`, `outlinePolygon`  
- Can draw directly to screen or to an off-screen `Tex` object  
- Pixel drawing uses flags to control behavior (e.g., overlap, noise)

### Tex
A texture abstraction for pixel-level manipulation and drawing.

- Modify all pixels with color adjustments using `operateAllCanva()`  
- Save to file, update to screen, or clear contents  
- Pixel-safe with bounds and optional noise

### Events
Simplified wrapper around `SDL_Event`.

- Detects quit, key press/release, mouse press/release  
- Mouse position tracking and scroll wheel input  
- Clean API like `keyPressed(SDLK_ESCAPE)` or `mouseButtonPressed(SDL_BUTTON_LEFT)`

### Time
Keeps track of ticks, handles pause/unpause, and enforces frame rate.

- Adjustable frame delay  
- Easily plug into your main loop with `limit()` for FPS control

## Requirements

- C++ compiler  
- SDL2 library  

## Build

Include the `src/` folder in your project and link with SDL2:

```bash
g++ -o myproject main.cpp -lSDL2
```

Or use your own Makefile or CMake setup.

## Demo

A simple interactive demo is included in the repository (`main.cpp`).  
To build and run it, you can use the provided Makefile:

```bash
make
./ultimate-trmk
```

This demo showcases basic usage of the Renderer, Tex, Events, and Time classes — including drawing primitives, event handling, and frame limiting.
