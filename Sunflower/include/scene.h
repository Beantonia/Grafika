#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

#include<time.h>

typedef struct Scene
{
    Model model; 
    Material material;
    GLuint texture_id;
    float light;
    int item_status;
    int rotation;
    float height;
    int rotate_num;
    float light_level;
} Scene;

typedef struct Sun_scene
{
    Model model; 
    Material material;
    GLuint texture_id[69];
    int index;
    time_t time;
} Sun_scene;

/**
 * Initialize the scenes by loading models.
 */
void init_scene(Scene* scene);
void init_sunflower(Sun_scene* sunflower);
void init_shovel(Scene* shovel);
void init_bucket(Scene* bucket);
void init_seed(Scene* seed);

/**
 * Set the lighting of the scene.
 */
void set_lighting(Scene* scene);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scenes.
 */
void update_scene(Scene* scene);
void update_sunflower(Sun_scene* sunflower, Scene* shovel, Scene* seed, Scene* bucket);
void update_shovel(Scene* shovel);
void update_bucket(Scene* bucket);
void update_seed(Scene* seed);

/**
 * Render the scene objects.
 */
void render_scene(Scene* scene);
void render_sunflower(Sun_scene* sunflower, Scene* shovel, Scene* seed, Scene* bucket, Scene* scene);
void render_shovel(Scene* shovel, Scene* scene);
void render_bucket(Scene* bucket, Scene* scene);
void render_seed(Scene* seed, Scene* scene);


/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

#endif /* SCENE_H */
