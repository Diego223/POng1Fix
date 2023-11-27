#include <iostream>
#include <SDL2/SDL.h>
#include "print.h"
#include "Game.h"

SDL_Rect ball;
SDL_Rect paddle;
SDL_Rect secondPaddle;

Game::Game(const char* title, int width, int height)
{
  int maxFPS = 60;
  frameDuration = (1.0f / maxFPS) * 1000.0f;

  frameCount = 0;
  lastFPSUpdateTime = 0;
  FPS = 0;
  frameStartTimestamp = 0;
  frameEndTimestamp = 0;

  SDL_Init(SDL_INIT_EVERYTHING);
  
  window = SDL_CreateWindow(title, 0, 0, width, height, 0);
  renderer = SDL_CreateRenderer(window, -1, 0);
  
  SDL_SetRenderDrawColor(renderer, 200, 255, 255, 1);
  print("Game Start!");

  screen_width = width;
  screen_height = height;

  isRunning = true;
}

Game::~Game()
{}

void Game::setup()
{
  ball.x = 20;
  ball.y = 20;
  ball.w = 15;
  ball.h = 15;

  paddle.x = 20;
  paddle.y = (screen_height / 2) - 50;
  paddle.w = 20;
  paddle.h = 100;

  secondPaddle.x = screen_width - 40;
  secondPaddle.y = (screen_height / 2) - 50;
  secondPaddle.w = 20;
  secondPaddle.h = 100;
}

void Game::frameStart()
{
  frameStartTimestamp = SDL_GetTicks();
  if (frameEndTimestamp)
  {
    dT = (frameStartTimestamp - frameEndTimestamp) / 1000.0f;
  }
  else
  {
    dT = 0;
  }
}

void Game::frameEnd()
{
  frameEndTimestamp = SDL_GetTicks();

  float actualFrameDuration = frameEndTimestamp - frameStartTimestamp;

  if (actualFrameDuration < frameDuration)
  {
    SDL_Delay(frameDuration - actualFrameDuration);
  }
  
  frameCount++;
  Uint32 currentTime = SDL_GetTicks();
  if (currentTime - lastFPSUpdateTime > 1000)
  {
    FPS = frameCount / ((currentTime - lastFPSUpdateTime) / 1000.0f);
    lastFPSUpdateTime = currentTime;
    frameCount = 0;
  }

  print();
}

void Game::handleEvents()
{
  print("Game Handling events...");

  SDL_Event event;
  while (SDL_PollEvent(&event) != 0)
  {
    if (event.type == SDL_QUIT)
    {
      isRunning = false;
    }

    if (event.type == SDL_KEYDOWN)
    {
      switch (event.key.keysym.sym)
      {
        case SDLK_UP:
          paddle.y -= 10;
          break;
        case SDLK_DOWN:
          paddle.y += 10;
          break;
        case SDLK_w:
          secondPaddle.y -= 10;  // Mover el segundo paddle hacia arriba con "W".
          break;
        case SDLK_s:
          secondPaddle.y += 10;  // Mover el segundo paddle hacia abajo con "S".
          break;
      }
    }
  }
}


int sx = 2;
int sy = 2;

void Game::update()
{
  print("Game Updating...");

  // Colisión con los bordes laterales (juego termina)
  if (ball.x <= 0)
  {
    std::cout << "GANA JUGADOR 2" << std::endl;
    isRunning = false;  // Terminar el juego y mostrar "GANA JUGADOR 2" cuando la pelota toca el borde izquierdo.
  }
  else if (ball.x + ball.w >= screen_width)
  {
    std::cout << "GANA JUGADOR 1" << std::endl;
    isRunning = false;  // Terminar el juego y mostrar "GANA JUGADOR 1" cuando la pelota toca el borde derecho.
  }

  // Colisiones con la parte superior e inferior (aumentar velocidad y rebote)
  if (ball.y <= 0 || ball.y + ball.h >= screen_height)
  {
    sy *= -1.1;  // Invertir la dirección en Y y aumentar la velocidad cuando rebota en la parte superior e inferior.
    sx *= 1.1;    // Aumentar la velocidad en X cuando rebota en la parte superior e inferior.
  }

  // Colisión con el primer paddle (izquierda)
  if (ball.y + ball.h >= paddle.y && ball.y <= paddle.y + paddle.h && ball.x <= paddle.x + paddle.w)
  {
    sx *= -1.1;
    sy *= 1.1;
  }

  // Colisión con el segundo paddle (derecha)
  if (ball.y + ball.h >= secondPaddle.y && ball.y <= secondPaddle.y + secondPaddle.h && ball.x + ball.w >= secondPaddle.x)
  {
    sx *= -1.1;
    sy *= -1.1;
  }

  // Mover la pelota
  ball.x += sx;
  ball.y += sy;
}




void Game::render()
{
  print("Game Rendering...");

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255 ,255, 1);
  SDL_RenderFillRect(renderer, &ball);
  SDL_RenderFillRect(renderer, &paddle);
  SDL_RenderFillRect(renderer, &secondPaddle);

  SDL_RenderPresent(renderer);

  vprint(FPS);
}

void Game::clean()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  if (ball.x <= 0)
  {
    std::cout << "GANA JUGADOR 2" << std::endl;
  }
  else if (ball.x + ball.w >= screen_width)
  {
    std::cout << "GANA JUGADOR 1" << std::endl;
  }
}



bool Game::running()
{
  return isRunning;
}

