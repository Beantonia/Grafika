#include "app.h"

#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <scene.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <obj/model.h>

void init_app(App* app, int width, int height)
{
    int error_code;
    int inited_loaders;
    app->chosen_item = 0;
    app->status = 0;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "Sunflower",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));
    init_sunflower(&(app->sunflower));
    
    init_bucket(&(app->bucket));
    init_shovel(&(app->shovel));
    init_seed(&(app->seed));
    

    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum
    (
        -.08, .08,
        -.06, .06,
        .1, 50
    );
}

void handle_app_events(App* app, Scene* bucket, Scene* shovel, Scene* seed, Scene* scene)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;   
    

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
            case SDL_SCANCODE_W:
                set_camera_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), -1);
                break;
            case SDL_SCANCODE_A:
                set_camera_side_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), -1);
                break;
            case SDL_SCANCODE_Q:
                app->bottom = 0; 
                change_chosen_item(app);
                break;                
            case SDL_SCANCODE_E:
                app->bottom = 1;
                change_chosen_item(app);
                break;
            case SDL_SCANCODE_RETURN:
            change_status(app, bucket, shovel, seed);
            break;
            case SDL_SCANCODE_UP:
            increase_light_level(scene);
            break;
            case SDL_SCANCODE_DOWN:
            decrease_light_level(scene);
            break;
            case SDL_SCANCODE_H:
            change_interface_is_on(&(app->camera));
            break;
            default:
            break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_Q:
            case SDL_SCANCODE_E:
                break;
            case SDL_SCANCODE_RETURN:
                break;
            case SDL_SCANCODE_UP:
                break;
            case SDL_SCANCODE_DOWN:
                break;
            case SDL_SCANCODE_H:
                break;
            default:
                break;        
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if (is_mouse_down) {
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
            }
            mouse_x = x;
            mouse_y = y;
            break;
        case SDL_MOUSEBUTTONUP:
            is_mouse_down = false;
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void change_status(App* app, Scene* bucket, Scene* shovel, Scene* seed)
{
    if(app->status == 0)
    {
        if(app->chosen_item == 1)
        {
            app->status = 1;
            shovel->item_status = 1;
        }
        else
        {
            printf("Wrong item!\n");
            return;
        }
        return;
    }
    else if(app->status == 1 && shovel->item_status == 0)
    {        
        if(app->chosen_item == 2)
        {
            app->status = 2;
            seed->item_status = 1;
        }
        else
        {
            printf("Wrong item!\n");
            return;
        }
        return;
        
    }
    else if(app->status == 2 && seed->item_status == 0)
    {
        
        if(app->chosen_item == 0)
        {
            app->status = 3;
            bucket->item_status = 1;
        }
        else
        {
            printf("Wrong item!\n");
            return;
        }
        return;
    }
    else
    {
        printf("ERROR\n");
        return;
    }
}

void increase_light_level(Scene* scene)
{
    scene->light_level++;
    if(scene->light_level > 10)
    {
        scene->light_level = 10;
    }
}

void decrease_light_level(Scene* scene)
{
    scene->light_level--;
    if(scene->light_level < 2)
    {
        scene->light_level = 2;
    }
}


void change_chosen_item(App* app)
{
    if(app->bottom == 0)
    {    
        app->chosen_item--;
        if(app->chosen_item < 0)    
        {
            app->chosen_item = 0;
        }        
    }

    else if(app->bottom == 1)
    {
        app->chosen_item++;
        if(app->chosen_item > 2)
        {
            app->chosen_item = 2;
        }
    }

}


void lighted_item(Scene* shovel, Scene* bucket, Scene* seed, Scene* scene, App* app)
{
   if (app->chosen_item == 0)
   {
        bucket->light = 1; 
        shovel->light = 0.3;
        seed->light = 0.3;
   }
   else if (app->chosen_item == 1)
   {
        bucket->light = 0.3;
        shovel->light = 1;
        seed->light = 0.3;
   }
   else if (app->chosen_item == 2)
   {
        bucket->light = 0.3;
        shovel->light = 0.3;
        seed->light = 1;
   }
   else
   {
        bucket->light = 0.0;
        shovel->light = 0.0;
        seed->light = 0.0;
   }

}


void update_app(App* app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    update_scene(&(app->scene));
    update_shovel(&(app->shovel));
    update_bucket(&(app->bucket));
    update_seed(&(app->seed));
    update_sunflower(&(app->sunflower),&(app->shovel),&(app->seed),&(app->bucket));
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene));
    render_sunflower(&(app->sunflower),&(app->shovel),&(app->seed),&(app->bucket),&(app->scene));
    render_shovel(&(app->shovel),&(app->scene));
    render_bucket(&(app->bucket),&(app->scene));
    render_seed(&(app->seed),&(app->scene));
    glPopMatrix();

    if(app->camera.interface_is_on)
    {
        show_texture_preview(&(app->camera));
    }

    SDL_GL_SwapWindow(app->window);
}


void destroy_app(App* app)
{
    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}