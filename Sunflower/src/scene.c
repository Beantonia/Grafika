#include "scene.h"
#include "app.h"

#include <obj/load.h>
#include <obj/draw.h>

#include <stdio.h>
#include <time.h>

void init_scene(Scene* scene)
{
    scene->texture_id = load_texture("assets/textures/green.jpg");
    load_model(&(scene->model), "assets/models/floor.obj");

    scene->light_level = 10;

    scene->material.diffuse.red = 1.5;
    scene->material.diffuse.green = 1.5;
    scene->material.diffuse.blue = 0.0;

    scene->material.specular.red = 0;
    scene->material.specular.green = 0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;
}

void init_sunflower(Sun_scene* sunflower)
{   

    char garden[42];
    for (int i = 1; i < 70; i++)
    {
        sprintf(garden,"assets/textures/sunflower_jpg/1) (%d).jpg", i);
        sunflower->texture_id[i-1] = load_texture(garden);
        sunflower->index= 0;
        sunflower->time = 0;
    }    
    
    load_model(&(sunflower->model), "assets/models/screen_texture.obj");    
       
    sunflower->material.ambient.red = 0.2;
    sunflower->material.ambient.green = 0.2;
    sunflower->material.ambient.blue = 0.2;

    sunflower->material.diffuse.red = 1.0;
    sunflower->material.diffuse.green = 1.0;
    sunflower->material.diffuse.blue = 1.0;

    sunflower->material.specular.red = 0.2;
    sunflower->material.specular.green = 0.2;
    sunflower->material.specular.blue = 0.2;

    sunflower->material.shininess = 0.0;
    sunflower->time = time(NULL);
}

void init_shovel(Scene* shovel)
{
    shovel->texture_id = load_texture("assets/textures/fem_texture.jpg");
    load_model(&(shovel->model), "assets/models/shovel.obj");    

    shovel->material.ambient.red = 0.5;
    shovel->material.ambient.green = 0.5;
    shovel->material.ambient.blue = 0.5;

    shovel->material.specular.red = 0.5;
    shovel->material.specular.green = 0.5;
    shovel->material.specular.blue = 0.5;

    shovel->material.shininess = 0.0;

    shovel->item_status = 0;
    shovel->rotation = 0;
    shovel->height = 0;
    shovel->rotate_num = 0;
}

void init_seed(Scene* seed)
{
    seed->texture_id = load_texture("assets/textures/seed_texture.png");
    load_model(&(seed->model), "assets/models/seed.obj");    
    
    seed->material.ambient.red = 0.5;
    seed->material.ambient.green = 0.5;
    seed->material.ambient.blue = 0.5;

    seed->material.specular.red = 0.5;
    seed->material.specular.green = 0.5;
    seed->material.specular.blue = 0.5;

    seed->material.shininess = 0.0;

    seed->item_status = 0;
    seed->rotation = 0;
    seed->height = 5;
    seed->rotate_num = 0;
}

void init_bucket(Scene* bucket)
{
    bucket->texture_id = load_texture("assets/textures/bucket_texture.png");
    load_model(&(bucket->model), "assets/models/bucket.obj");    
       
    bucket->material.ambient.red = 0.5;
    bucket->material.ambient.green = 0.5;
    bucket->material.ambient.blue = 0.5;

    bucket->material.specular.red = 0.5;
    bucket->material.specular.green = 0.5;
    bucket->material.specular.blue = 0.5;

    bucket->material.shininess = 0.0;

    bucket->item_status = 0;
    bucket->rotation = 0;
    bucket->height = 0.4;
    bucket->rotate_num = 0;
}

void set_lighting(Scene* scene)
{
    float light_value = scene->light_level/10;

    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    float diffuse_light[] = { light_value, light_value, light_value, 0.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);   
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene)
{
    scene->material.ambient.red = 0.5*scene->light_level;
    scene->material.ambient.green = 0.5*scene->light_level;
    scene->material.ambient.blue = 0.0;
}

void update_sunflower(Sun_scene* sunflower, Scene* shovel, Scene* seed, Scene* bucket)
{
    clock_t start_time = clock();
    clock_t end_time;
    double timer;

    if(shovel->rotate_num < 600)
    {
        sunflower->index = 0;
    }
    else if(seed->rotate_num < 1000)
    {        
        do
        {
            end_time = clock();
            timer = ((double)(end_time-start_time))/CLOCKS_PER_SEC;

        } while(timer < 0.06 && seed->rotate_num == 0);
        
        if(sunflower->index < 11)
        {        
            sunflower->index++;
        }
    }
    else if(bucket->rotate_num < 1000)
    {
        do
        {
            end_time = clock();
            timer = ((double)(end_time-start_time))/CLOCKS_PER_SEC;

        } while(timer < 0.06 && bucket->rotate_num == 0);

        if(sunflower->index < 27)
        {
            sunflower->index++;
        }

    }
    else if(sunflower->index < 67)
    {
        do
        {
            end_time = clock();
            timer = ((double)(end_time-start_time))/CLOCKS_PER_SEC;

        } while(timer < 0.06);


            sunflower->index++;
    }
    else
    {
        sunflower->index = 68;
    }

}

void update_shovel(Scene* shovel)
{
    clock_t start_time = clock();
    clock_t end_time;
    double timer;

    shovel->material.diffuse.red = shovel->light;
    shovel->material.diffuse.green = shovel->light;
    shovel->material.diffuse.blue = shovel->light;

    if(shovel->item_status == 0)
    {
        shovel->rotation = 0;
        shovel->height = 0;  
    } 
    else
    {      
        do
        {
            end_time = clock();
            timer = ((double)(end_time-start_time))/CLOCKS_PER_SEC;

        } while(timer < 0.001);

        shovel->rotate_num++;       
        shovel->rotation++;
        shovel->height = shovel->height + 0.3;
        if(shovel->rotation > 612)
        {           
            shovel->item_status = 0;
        }

    }
}

void update_seed(Scene* seed)
{
    clock_t start_time = clock();
    clock_t end_time;
    double timer;

    seed->material.diffuse.red = seed->light;
    seed->material.diffuse.green = seed->light;
    seed->material.diffuse.blue = seed->light;

    if(seed->item_status == 0)
    {
        seed->rotation = 0;
        seed->height = 5;
    }
    else
    {
        do
        {
            end_time = clock();
            timer = ((double)(end_time-start_time))/CLOCKS_PER_SEC;

        } while(timer < 0.001);

        seed->rotate_num++;
        seed->rotation++;
        seed->height = seed->height + 0.03;
        if(seed->rotation > 1017)
        {           
            seed->item_status = 0;
        }   
    }
}

void update_bucket(Scene* bucket)
{
    clock_t start_time = clock();
    clock_t end_time;
    double timer;

    bucket->material.diffuse.red = bucket->light;
    bucket->material.diffuse.green = bucket->light;
    bucket->material.diffuse.blue = bucket->light;

    if(bucket->item_status == 0)
    {
        bucket->rotation = 0;
        bucket->height = 0.4;
    }
    else
    {
        do
        {
            end_time = clock();
            timer = ((double)(end_time-start_time))/CLOCKS_PER_SEC;

        } while(timer < 0.001);
        
        bucket->rotate_num++;
        bucket->rotation++;
        bucket->height = bucket->height + 0.003;
        if(bucket->rotation > 1300)
        {           
            bucket->item_status = 0;
        }
    }   
}

void render_scene(Scene* scene)
{
    glBindTexture(GL_TEXTURE_2D, scene->texture_id);
    set_material(&(scene->material));
    set_lighting(scene);
    draw_origin();
    draw_model(&(scene->model));
    glScalef(0.04,0.04,0.04);
   
}

void render_sunflower(Sun_scene* sunflower, Scene* shovel, Scene* seed, Scene* bucket, Scene* scene)
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, sunflower->texture_id[sunflower->index]);
    set_material(&(sunflower->material));
    set_lighting(scene);
    draw_origin();
    glTranslatef(120,0,55);
    glRotatef(90,0,1,0);
    glRotatef(-90,0,0,1);
    draw_model(&(sunflower->model));
    glPopMatrix();  
}

void render_shovel(Scene* shovel, Scene* scene)
{
    glBindTexture(GL_TEXTURE_2D, shovel->texture_id);
    set_material(&(shovel->material));
    set_lighting(scene);
    draw_origin();
    glScalef(0.30,0.3,0.3);
    glPushMatrix();        
    glTranslatef(170,-8,shovel->height);
    glRotatef(shovel->rotation,0,0,1);
    draw_model(&(shovel->model));
    glPopMatrix(); 
}

void render_seed(Scene* seed, Scene* scene)
{
    glBindTexture(GL_TEXTURE_2D, seed->texture_id);
    set_material(&(seed->material));
    set_lighting(scene);
    draw_origin();
    glScalef(0.1,0.1,0.1);   
    glPushMatrix();
    glTranslatef(25,-10,seed->height);
    glRotatef(seed->rotation,0,0,1);
    draw_model(&(seed->model));
    glPopMatrix();
}

void render_bucket(Scene* bucket, Scene* scene)
{  
    glBindTexture(GL_TEXTURE_2D, bucket->texture_id);
    set_material(&(bucket->material));
    set_lighting(scene);
    draw_origin();
    glScalef(70,70,70);
    glPushMatrix();
    glTranslatef(2.4,1,bucket->height);   
    glRotatef(bucket->rotation,0,0,1); 
    draw_model(&(bucket->model));
    glPopMatrix();        
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}
