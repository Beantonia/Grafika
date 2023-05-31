#ifndef APP_H
#define APP_H

#include "camera.h"
#include "scene.h"
#include "texture.h"
#include <SDL2/SDL.h>

#include <stdbool.h>

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

typedef struct App
{
    SDL_Window* window;
    SDL_GLContext gl_context;
    bool is_running;
    double uptime;
    Camera camera;
    Scene scene;
    Sun_scene sunflower;
    Scene shovel;
    Scene bucket;
    Scene seed;
    int chosen_item;
    int bottom;
    int status;
} App;

/**
 * Initialize the application.
 */
void init_app(App* app, int width, int height);

/**
 * Initialize the OpenGL context.
 */
void init_opengl();

/**
 * Reshape the window.
 */
void reshape(GLsizei width, GLsizei height);

/**
 * Handle the events of the application.
 */
void handle_app_events(App* app, Scene* bucket, Scene* shovel, Scene* seed, Scene* scene);

/**
 * Update the application.
 */
void update_app(App* app);

/**
 * Render the application.
 */
void render_app(App* app);

/**
 * Destroy the application.
 */
void destroy_app(App* app);


/**
 * Show the chosen item.
*/

void lighted_item(Scene* shovel, Scene* bucket, Scene* seed, Scene* scene, App* app);

/**
 * Change the status of choosen_item depending on the bottom (Q or E);
*/

void change_chosen_item(App* app);

/**
 * Change the status of the app and the items.
*/
void change_status(App* app, Scene* bucket, Scene* shovel, Scene* seed);

/**
 * Increase the light level.
*/

void increase_light_level(Scene* scene);

/**
 * Decrease the light level.
*/

void decrease_light_level(Scene* scene);

#endif /* APP_H */
