#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <limits.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <SDL2/SDL.h>
#include <functional>
#include <stdbool.h>
#include <math.h>
#include <set>
#define WIDTH 1920
#define HEIGHT 1080
#define POINT_RADIUS 5
#define MAP_WIDTH 1920
#define MAP_HEIGHT 1080
// #define MAP_WIDTH 2580
// #define MAP_HEIGHT 1440

    /* 
        // Example usage:
        // Draw a point on screen
        // Draw a point on a texture
        renderer.drawPoint([&tex](int x, int y, int color, SDL_Renderer* renderer, int flag) {
        tex.setPixel(x, y, color, renderer, flag);
        }, 100, 100, 0xFF0000, 0);
        // Draw a line on screen
        renderer.drawLine([&renderer](int x1, int y1, int x2, int y2, int color, SDL_Renderer* renderer, int flag) {
            renderer.setPixel(x1, y1, color, renderer, flag);
        }, 100, 100, 200, 200, 0xFF0000, 0);
        // Draw a line on a texture
        renderer.drawLine([&tex](int x1, int y1, int x2, int y2, int color, SDL_Renderer* renderer, int flag) {
            tex.setPixel(x1, y1, color, renderer, flag);
        }, 100, 100, 200, 200, 0xFF0000, 0);
        // Draw a circle on screen
        renderer.drawCircle([&renderer](int x, int y, int radius, SDL_Renderer* renderer, int flag) {
            renderer.setPixel(x, y, 0xFF0000, renderer, flag);
        }, 100, 100, 50, 0xFF0000, 0);
        // Draw a circle on a texture
        renderer.drawCircle([&tex](int x, int y, int radius, SDL_Renderer* renderer, int flag) {
            tex.setPixel(x, y, 0xFF0000, renderer, flag);
        }, 100, 100, 50, 0xFF0000, 0);
        // Fill a triangle on screen
        renderer.fillTriangle([&renderer](int x, int y, int color, SDL_Renderer* renderer, int flag) {
            renderer.setPixel(x, y, color, renderer, flag);
        }, 100, 100, 200, 200, 300, 100, 0xFF0000, 0);
        // Fill a triangle on a texture
        renderer.fillTriangle([&tex](int x, int y, int color, SDL_Renderer* renderer, int flag) {
            tex.setPixel(x, y, color, renderer, flag);
        }, 100, 100, 200, 200, 300, 100, 0xFF0000, 0);
        // Fill a polygon on screen
        renderer.fillPolygon([&renderer](int x, int y, int color, SDL_Renderer* renderer, int flag) {
            renderer.setPixel(x, y, color, renderer, flag);
        }, {Point(100, 100), Point(200, 200), Point(300, 100)}, 0xFF0000, 0);
        // Fill a polygon on a texture
        renderer.fillPolygon([&tex](int x, int y, int color, SDL_Renderer* renderer, int flag) {
            tex.setPixel(x, y, color, renderer, flag);
        }, {Point(100, 100), Point(200, 200), Point(300, 100)}, 0xFF0000, 0);
        // Outline a polygon on screen
        renderer.outlinePolygon([&renderer](int x, int y, int color, SDL_Renderer* renderer, int flag) {
            renderer.setPixel(x, y, color, renderer, flag);
        }, {Point(100, 100), Point(200, 200), Point(300, 100)}, 0xFF0000, 0);
        // Outline a polygon on a texture
        renderer.outlinePolygon([&tex](int x, int y, int color, SDL_Renderer* renderer, int flag) {
            tex.setPixel(x, y, color, renderer, flag);
        }, {Point(100, 100), Point(200, 200), Point(300, 100)}, 0xFF0000, 0);
        // Draw a texture on screen
        renderer.drawTex(&tex, 100, 100);
    */

class Point {
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

class Edge {
public:
    Point* start;
    Point* end;
    Edge(Point* start, Point* end) : start(start), end(end) {}
};
enum flag{
    NO_OVERLAP = (1 << 0),
    NOISE = (1 << 1),
};

class Tex {
    private:
        Uint32* pixels;
        SDL_Surface* surface;
        SDL_Texture* texture;
        int width;
        int height;
        double noise;
    public:
        Tex(SDL_Renderer* renderer, SDL_Window* window, int width, int height, int noise = 1);
        ~Tex();
        SDL_Texture* getTexture();
        Uint32* getPixels();
        int getWidth();
        int getHeight();
        void setPixel(int x, int y, int color , SDL_Renderer* renderer, int flag);
        void setNoise(double noise);
        void update(SDL_Renderer* renderer, SDL_Window* window);
        void clear();
        void save(const char* filename);
};

typedef void (*drawFunction)(int, int, int, SDL_Renderer*, int);
#define drawFunc std::function<void(int, int, int, SDL_Renderer*, int)>
class Renderer {
    private:
        SDL_Renderer* renderer;
        SDL_Window* window;
    public:
        Renderer(SDL_Renderer* renderer, SDL_Window* window);
        ~Renderer();
        void toggleFullscreen();
        SDL_Renderer* getRenderer();
        SDL_Window* getWindow();
        void drawPoint(drawFunc drawFunction, int x, int y, int color, int flag);
        void drawLine(drawFunc drawFunction, int x1, int y1, int x2, int y2, int color, int flag);
        void drawCircle(drawFunc drawFunction, int x, int y, int radius, int color, int flag);
        void fillTriangle(drawFunc drawFunction, int x1, int y1, int x2, int y2, int x3, int y3, int color, int flag);
        void fillPolygon(drawFunc drawFunction, std::vector<Point> vertices, int color, int flag);
        void outlinePolygon(drawFunc drawFunction, std::vector<Point> vertices, int color, int flag);
        void drawTex(Tex* tex, int x, int y);

        void setPixel(int x, int y, int color , SDL_Renderer* renderer, int flag) ;
        // those are the functions that update the screen
        void update();
        void clear();
};

#endif
