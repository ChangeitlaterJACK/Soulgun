#include "HUD.h"

HUD::HUD(SDL_Renderer *renderer, Humanoid *player, TextureManager *txMan): renderer(renderer), txMan(txMan), player(player), lastTime(0), elapsedTime(0), isPaused(false) {
    fontBold = TTF_OpenFont("assets/fonts/Courier New Bold.ttf", FONT_SIZE);
    fontNormal = TTF_OpenFont("assets/fonts/Courier New.ttf", FONT_SIZE);
}

HUD::~HUD(void) {
    renderer = NULL;
    player = NULL;
    elapsedTime = 0;
    isPaused = false;
    TTF_CloseFont(fontNormal);
    TTF_CloseFont(fontBold);
}

void HUD::refresh(void) {
    int lastX = 0;

    if (!isPaused) {
        elapsedTime += SDL_GetTicks() - lastTime;
        lastTime = SDL_GetTicks();

        // Prepare the timer info
        TimeUnits t = getTime();
        std::string ms = std::to_string(t.ms);
        std::string s = std::to_string(t.seconds);
        std::string m = std::to_string(t.minutes);

        m.insert(m.begin(), 2 - m.length(), '0');
        s.insert(s.begin(), 2 - s.length(), '0');
        ms.insert(ms.begin(), 3 - ms.length(), '0');
        std::string time = m + ":" + s + "." + ms;

        lastX = renderText("Time: ", true, lastX + TEXT_GAP);
        lastX = renderText(time, false, lastX);

        lastX = renderText("Health: ", true, lastX + TEXT_GAP);
        lastX = renderText(std::to_string(player->getHealth()), false, lastX);
    }
}

/**
 * Renders text to the HUD
 * 
 * @param text The text to render
 * @param isBold If true, render text in bold
 * @param offsetX The x-coordinate to start rendering at
 * @returns An integer indicating the smallest X offset where the next text should be rendered
 */
int HUD::renderText(std::string text, bool isBold, int offsetX) {
    TTF_Font *font = (isBold) ? fontBold: fontNormal;
    SDL_Color color = { 0, 0, 0 };
    SDL_Rect pos;

    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
    pos.x = offsetX;
    pos.y = 0;
    SDL_RenderCopy(renderer, texture, NULL, &pos);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

    return offsetX + pos.w;
}

void HUD::startTimer(void) {
    isPaused = false;
}

void HUD::stopTimer(void) {
    isPaused = true;
    elapsedTime += SDL_GetTicks() - lastTime;
    lastTime = SDL_GetTicks();
}

void HUD::resetTimer(void) {
    elapsedTime = 0;
    lastTime = 0;
}

TimeUnits HUD::getTime(void) {
    TimeUnits t;
    
    t.hours = elapsedTime / (60 * 60 * 1000) % 24;
    t.minutes = t.seconds / (60 * 1000) % 60;
    t.seconds = (elapsedTime / 1000) % 60;
    t.ms = elapsedTime % 1000;

    return t;
}