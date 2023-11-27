#include <SDL2/SDL.h>

class Game {
  public:
    Game(const char* title, int width, int height);
    ~Game();

    void setup();
    void frameStart();
    void frameEnd();
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running();


  private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;

    int screen_width;
    int screen_height;

    // for frame management
    Uint32 frameStartTimestamp;
    Uint32 frameEndTimestamp;
    float frameDuration;
    float dT; // time in miliseconds since last frame
    // for frame count
    int frameCount;
    Uint32 lastFPSUpdateTime;
    float FPS;
};