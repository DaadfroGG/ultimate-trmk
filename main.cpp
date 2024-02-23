#include "src/Renderer.hpp"
#include "src/Event.hpp"
#include <cmath>
#include <math.h>

double clamp(double x, double a, double b) {
    return fmax(a, fmin(b, x));
}


    
int interpolateColor(int color1, int color2, double t) {
    int r1 = (color1 >> 16) & 0xFF;
    int g1 = (color1 >> 8) & 0xFF;
    int b1 = color1 & 0xFF;
    int r2 = (color2 >> 16) & 0xFF;
    int g2 = (color2 >> 8) & 0xFF;
    int b2 = color2 & 0xFF;
    int r = (int) (r1 * (1 - t) + r2 * t);
    int g = (int) (g1 * (1 - t) + g2 * t);
    int b = (int) (b1 * (1 - t) + b2 * t);
    return (r << 16) + (g << 8) + b;
}
int main() {
    Renderer renderer(nullptr, SDL_CreateWindow("SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_FULLSCREEN));
    Events events;
    Tex tex(renderer.getRenderer(), renderer.getWindow(), MAP_WIDTH, MAP_HEIGHT);
    // Frame rate
    Time frameTime;
    events.updateMousePosition();
    // Main loop
    while (!events.quit()) {

        // Start the frame time
        frameTime.start();
        // Clear the screen
        renderer.clear();
        // Update mouse position
        events.updateMousePosition();
        // Handle events
        while (events.poll()) {
            if (events.quit()) {
                break;
            }
            if (events.keyDown())
            {
                if (events.keyPressed(SDLK_ESCAPE))
                {
                    return 0;
                }
                if (events.keyPressed(SDLK_s))
                {
                    tex.save("test.ppm");
                }
            }
            if (events.mouseButtonPressed(SDL_BUTTON_LEFT))
            {
                //draw a circle on the texture where the mouse is
                renderer.drawCircle([&tex](int x, int y, int color, SDL_Renderer* r, int __attribute__((unused))flagn) {
                        tex.setPixel(x, y, color, r, NO_OVERLAP | NOISE);}, events.getMouseX(), events.getMouseY(), 10, 0xFF0000, NO_OVERLAP);
            }
        }
        // Adjust the size based on the desired growth rate
        //draw a circle on the texture where the mouse is
//renderer.outlinePolygon([&renderer](int x, int y, int color, SDL_Renderer* r, int __attribute__((unused))flagn) {
      //              renderer.setPixel(x, y, color, r, NO_OVERLAP);
        // Draw the texture
        renderer.drawTex(&tex, WIDTH / 2 - MAP_WIDTH / 2, HEIGHT / 2 - MAP_HEIGHT / 2);
            renderer.drawCircle([&renderer](int x, int y, int color, SDL_Renderer* r, int __attribute__((unused))flagn) {
                    renderer.setPixel(x, y, color, r, NO_OVERLAP | NOISE);}, events.getMouseX(), events.getMouseY(), 10, 0xFF0000, NO_OVERLAP);
           
        // Present the screen
        tex.update(renderer.getRenderer(), renderer.getWindow());
        renderer.update();

        // Limit the frame rate
        frameTime.limit();
    }
    return 0;
}
