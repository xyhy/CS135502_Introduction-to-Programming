//
//  main.c
//  Final Project
//
//  Created by 顏浩昀 on 2019/12/14.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

// [main.c]
// this template is provided for the 2D shooter game.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_video.h>
#include <math.h>
#include <time.h>
// If defined, logs will be shown on console and written to file.
// If commented out, logs will not be shown nor be saved.
#define LOG_ENABLED


/* Constants. */


const int FPS = 60;  // Frame rate (frame per second)
const int SCREEN_W = 900+500;  // Display (screen) width.
const int SCREEN_H = 1550;  // Display (screen) height.
const int RESERVE_SAMPLES = 4;  // At most 4 audios can be played at a time.

enum {
    SCENE_MENU = 1,  // const int SCENE_MENU = 1;
    SCENE_START = 2,  // const int SCENE_START = 2;
    SCENE_SECOND_STAGE = 3,
    SCENE_SETTINGS = 4, // const int SCENE_SETTINGS = 4;
    SCENE_SETTINGS_FROM_START = 5,
    SCENE_SETTINGS_FROM_BOSS = 6,
    SCENE_DEATH = 7,
    SCENE_DEATH2 = 8,
    SCENE_HELP = 9,
    SCENE_PASS_STAGE = 10,
    SCENE_FINAL = 11
};

/* Input states */

int active_scene;  // The active scene id.
bool key_state[ALLEGRO_KEY_MAX];  // Key of keyboard is down or not.
bool *mouse_state;  // the key of mouse is down or not.  1 is for left, 2 is for right, 3 is for middle.
int mouse_x, mouse_y;  // Mouse position.

/* Variables for allegro basic routines. */

ALLEGRO_DISPLAY* game_display;
ALLEGRO_EVENT_QUEUE* game_event_queue;
ALLEGRO_TIMER* game_update_timer;

/* Shared resources*/

ALLEGRO_FONT* font_pirulen_72;
ALLEGRO_FONT* font_pirulen_32;
ALLEGRO_SAMPLE* life_1;
ALLEGRO_SAMPLE_ID life_1_id;
ALLEGRO_SAMPLE* life_0;
ALLEGRO_SAMPLE_ID life_0_id;
double now;

/* Menu Scene resources*/
ALLEGRO_BITMAP* main_img_background;
ALLEGRO_BITMAP* img_settings;
ALLEGRO_BITMAP* img_settings2;
ALLEGRO_BITMAP* img_start;
ALLEGRO_BITMAP* img_start2;
ALLEGRO_BITMAP* img_help;
ALLEGRO_BITMAP* img_help2;
ALLEGRO_SAMPLE* main_bgm;
ALLEGRO_SAMPLE_ID main_bgm_id;
ALLEGRO_SAMPLE* choose_bgm;
ALLEGRO_SAMPLE_ID choose_bgm_id;

/* Start Scene resources*/
ALLEGRO_BITMAP* start_img_background;
ALLEGRO_BITMAP* start_img_plane;
ALLEGRO_BITMAP* start_img_enemy;
ALLEGRO_SAMPLE* start_bgm;
ALLEGRO_SAMPLE_ID start_bgm_id;
ALLEGRO_BITMAP* start_img_bullet;
ALLEGRO_BITMAP* start_img_enemy_bullet;
ALLEGRO_SAMPLE* attack_bgm;
ALLEGRO_SAMPLE_ID attack_bgm_id;
ALLEGRO_SAMPLE* fight_bgm;
ALLEGRO_SAMPLE_ID* fight_bgm_id;

/* Second Stage*/
ALLEGRO_BITMAP* boss_stage_background;
ALLEGRO_BITMAP* boss_stage_wennie;
ALLEGRO_BITMAP* boss_stage_boss;
ALLEGRO_BITMAP* img_boss_bullet;
ALLEGRO_BITMAP* img_wennie_bullet;
ALLEGRO_BITMAP* img_black;
ALLEGRO_BITMAP* img_skill_background;
ALLEGRO_BITMAP* img_skill_bullet;
ALLEGRO_SAMPLE* skill_bgm;
ALLEGRO_SAMPLE_ID skill_bgm_id;
ALLEGRO_SAMPLE* boss_stage_bgm;
ALLEGRO_SAMPLE_ID boss_stage_bgm_id;
int count = 0;
/*Other SCENE*/
ALLEGRO_BITMAP* img_help_background;
ALLEGRO_BITMAP* img_big_wennie;
ALLEGRO_BITMAP* img_level_1;
ALLEGRO_BITMAP* img_level_11;
ALLEGRO_BITMAP* img_level_2;
ALLEGRO_BITMAP* img_level_22;
ALLEGRO_BITMAP* img_level_3;
ALLEGRO_BITMAP* img_level_33;
ALLEGRO_BITMAP* img_level_4;
ALLEGRO_BITMAP* img_level_44;
ALLEGRO_BITMAP* img_level_5;
ALLEGRO_BITMAP* img_level_55;


typedef struct {
    float x, y;  // The center coordinate of the image.
    float w, h;  // The width and height of the object.
    float vx, vy;  // The velocity in x, y axes.
    int life;
	int deg;
    bool hidden;  // draw the object if hidden if false. Otherwise, don't draw it.
    ALLEGRO_BITMAP* img;  // The pointer to the object's image.
} MovableObject;  // struct to objects which can move.
void draw_movable_object(MovableObject obj);
#define MAX_ENEMY 5
#define MAX_BULLET 20
#define MAX_ENEMY_BULLET 5
#define MAX_BOSS_BULLET 500
#define MAX_WENNIE_BULLET 30
#define MAX_SKILL_BULLET 20
// player data;
int score;
int SCORE;
float combo = 1.000;  // format 1.001
int dead_times = 0;
int level = 1;
int energy = 0;
// game data
MovableObject plane;
MovableObject enemies[MAX_ENEMY];
MovableObject enemies_right[MAX_ENEMY];
MovableObject bullets[MAX_BULLET];
MovableObject enemies_bullets[MAX_ENEMY][MAX_ENEMY_BULLET*5];  // 5 is max_level
MovableObject enemies_bullets_right[MAX_ENEMY][MAX_ENEMY_BULLET*5];
MovableObject wennie;
MovableObject wennie_bullets[MAX_WENNIE_BULLET];
MovableObject boss;
MovableObject boss_bullets[MAX_BOSS_BULLET*5];  // 5 is max_level
MovableObject black;
MovableObject skill_background;
MovableObject skill_bullet[MAX_SKILL_BULLET];
MovableObject skill_bullet_right[MAX_SKILL_BULLET];
MovableObject wennies[300];
const float MAX_COOLDOWN = 0.2f;  // shoot cd.
const float SKILL_COOLDOWN = 0.1f;
double last_used_skill;
double last_shoot_timestamp;
const float enemy_revive_time = 0.35f;
double last_enemy_deadtime;
double last_enemy_deadtime_right;
const float ENEMY_MAX_COOLDOWN = 0.5f; // enemy shoot cd.
const float BOSS_COOLDOWN = 0.008f;
double enemy_last_shoot_timestamp[MAX_ENEMY];
double enemy_last_shoot_timestamp_right[MAX_ENEMY];
double boss_last_shoot_timestamp;
double TIME;  // game begin.
double TIME_2; // pause time per once time.
double TIME_3 = 0; // total pause time.
double TIME_4;  // pass first stage time.



/* Declare function prototypes. */

void allegro5_init(void);  // Initialize allegro5 library
void game_init(void);  // Initialize variables and resources.
void game_start_event_loop(void);  // Process events inside the event queue using an infinity loop.
void game_update(void);  // Run game logic such as update.
void game_draw(void);  // Draw to display.
void game_destroy(void);  // Release resources.
void game_change_scene(int next_scene); // change scene from one to another.
ALLEGRO_BITMAP *load_bitmap_resized(const char *filename, int w, int h);  // Load resized bitmap and check if failed.
bool pnt_in_rect(int px, int py, int x, int y, int w, int h); // detect (px, py) is in (x~x+w, y~y+h) or not.

/* Event callbacks. */
void on_key_down(int keycode);
void on_mouse_down(int btn, int x, int y);

/* Declare function prototypes for debugging. */

void game_abort(const char* format, ...);  // Display error messages.
void game_log(const char* format, ...);  // Display formatted output messages.
void game_vlog(const char* format, va_list arg);  // Log using va_list.

int main(int argc, char** argv) {
    allegro5_init();
    game_log("Allegro5 initialized");
    game_log("Game begin");
    game_init();  // Initialize game variables.
    game_log("Game initialized");
    game_draw();  // Draw the first frame.
    game_log("Game start event loop");
    game_start_event_loop();  // This call blocks until the game is finished.
    game_log("Game end");
    game_destroy();
    return 0;
}

void allegro5_init(void) {
    if (!al_init())
        game_abort("failed to initialize allegro");
    
    // Initialize add-ons.
    if (!al_init_primitives_addon())
        game_abort("failed to initialize primitives add-on");
    if (!al_init_font_addon())
        game_abort("failed to initialize font add-on");
    if (!al_init_ttf_addon())
        game_abort("failed to initialize ttf add-on");
    if (!al_init_image_addon())
        game_abort("failed to initialize image add-on");
    if (!al_install_audio())
        game_abort("failed to initialize audio add-on");
    if (!al_init_video_addon())
        game_abort("failed to initialize video add-on");
    if (!al_init_acodec_addon())
        game_abort("failed to initialize audio codec add-on");
    if (!al_reserve_samples(RESERVE_SAMPLES))
        game_abort("failed to reserve samples");
    if (!al_install_keyboard())
        game_abort("failed to install keyboard");
    if (!al_install_mouse())
        game_abort("failed to install mouse");
    // TODO: Initialize other addons such as video, ...
    
    // Setup game display.
    game_display = al_create_display(SCREEN_W, SCREEN_H);
    if (!game_display)
        game_abort("failed to create display");
    al_set_window_title(game_display, "I2P(I)_2019 Final Project <108062213>");
    
    // Setup update timer.
    game_update_timer = al_create_timer(1.0f / FPS);
    if (!game_update_timer)
        game_abort("failed to create timer");
    
    // Setup event queue.
    game_event_queue = al_create_event_queue();
    if (!game_event_queue)
        game_abort("failed to create event queue");
    
    // Malloc mouse buttons state according to button counts.
    const unsigned m_buttons = al_get_mouse_num_buttons();
    game_log("There are total %u supported mouse buttons", m_buttons);
    // mouse_state[0] will not be used.
    mouse_state = malloc((m_buttons + 1) * sizeof(bool));
    memset(mouse_state, false, (m_buttons + 1) * sizeof(bool));
    
    // Register display, timer, keyboard, mouse events to the event queue.
    al_register_event_source(game_event_queue, al_get_display_event_source(game_display));
    al_register_event_source(game_event_queue, al_get_timer_event_source(game_update_timer));
    al_register_event_source(game_event_queue, al_get_keyboard_event_source());
    al_register_event_source(game_event_queue, al_get_mouse_event_source());
    // TODO: Register other event sources such as timer, video, ...
    
    // Start the timer to update and draw the game.
    al_start_timer(game_update_timer);
}

void game_init(void) {
    /* Shared resources*/
    font_pirulen_72 = al_load_font("pirulen.ttf", 72, 0);
    if (!font_pirulen_72)
        game_abort("failed to load font: pirulen.ttf with size 72");
    
    font_pirulen_32 = al_load_font("pirulen.ttf", 32, 0);
    if (!font_pirulen_32)
        game_abort("failed to load font: pirulen.ttf with size 32");
	img_black = al_load_bitmap("black_color.jpeg");
 //   life_0 = al_load_sample("life-0.ogg");
  //  if (!life_0)
  //      game_abort("failed to load sample : life_0.ogg");
  //  life_1 = al_load_sample("life-1.ogg");
   // if (!life_1)
     //   game_abort("failed to load sample : life_1.ogg");
    
    /* Menu Scene resources*/
    main_img_background = load_bitmap_resized("start_photo.jpg", SCREEN_W, SCREEN_H);
    img_start = al_load_bitmap("start1.jpg");
    img_start2 = al_load_bitmap("start2.jpg");
    img_help = al_load_bitmap("help1.jpg");
    img_help2 = al_load_bitmap("help2.jpg");
    
    main_bgm = al_load_sample("S31-Night Prowler.ogg");
    if (!main_bgm)
        game_abort("failed to load audio: S31-Night Prowler.ogg");
   // choose_bgm = al_load_sample("choose.ogg");
    
    
    // Load settings images.
    img_settings = al_load_bitmap("settings.jpg");
    if (!img_settings)
        game_abort("failed to load image: settings.jpg");
    img_settings2 = al_load_bitmap("settings2.jpg");
    if (!img_settings2)
        game_abort("failed to load image: settings2.jpg");
    img_level_1 = al_load_bitmap("1.jpg");
    img_level_11 = al_load_bitmap("1-1.jpg");
    img_level_2 = al_load_bitmap("2.jpg");
    img_level_22 = al_load_bitmap("2-2.jpg");
    img_level_3 = al_load_bitmap("3.jpg");
    img_level_33 = al_load_bitmap("3-3.jpg");
    img_level_4 = al_load_bitmap("4.jpg");
    img_level_44 = al_load_bitmap("4-4.jpg");
    img_level_5 = al_load_bitmap("5.jpg");
    img_level_55 = al_load_bitmap("5-5.jpg");
    
    /* Start Scene resources*/
    start_img_background = load_bitmap_resized("universe.jpg", SCREEN_W, SCREEN_H);
    
    start_img_plane = al_load_bitmap("plane.jpg");
    if (!start_img_plane)
        game_abort("failed to load image: plane.jpg");
    
    start_img_enemy = al_load_bitmap("tank.jpg");
    if (!start_img_enemy)
        game_abort("failed to load image: smallfighter0006.jpg");
    
    start_bgm = al_load_sample("mythica.ogg");
    if (!start_bgm)
        game_abort("failed to load audio: mythica.ogg");
    /* Second stage fight resource */
    boss_stage_background = load_bitmap_resized("screen-5.jpg", SCREEN_W, SCREEN_H);
    boss_stage_wennie = al_load_bitmap("wennie.jpg");
    boss_stage_boss = al_load_bitmap("xi.jpg");
    img_boss_bullet = al_load_bitmap("Unknown.jpg");
    img_wennie_bullet = al_load_bitmap("bullect-4-2.jpg");
    img_skill_background = al_load_bitmap("skill_background.jpg");
    img_skill_bullet = al_load_bitmap("skill_bullet.jpg");
    // Initialize bullets.
    start_img_bullet = al_load_bitmap("bullect-4-2.jpg");
    if (!start_img_bullet)
        game_abort("failed to load image: image12.jpg");
    start_img_enemy_bullet = al_load_bitmap("bullet-2.jpg");
    if (!start_img_enemy_bullet)
        game_abort("failed to load image: bullet-2.jpg");
    // initial others
    img_help_background = al_load_bitmap("help_background.jpg");
    img_big_wennie = al_load_bitmap("big_wennie.jpg");
    
    game_change_scene(SCENE_MENU);  // Change to first scene.
}

void game_start_event_loop(void) {
    bool done = false;
    ALLEGRO_EVENT event;
    int redraws = 0;
    while (!done) {
        now = al_get_time();
        al_wait_for_event(game_event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            // Event for clicking the window close button.
            game_log("Window close button clicked");
            done = true;
        }
        else if (event.type == ALLEGRO_EVENT_TIMER) {
            // Event for redrawing the display.
            if (event.timer.source == game_update_timer)
                // The redraw timer has ticked.
                redraws++;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            // Event for keyboard key down.
            game_log("Key with keycode %d down", event.keyboard.keycode);
            key_state[event.keyboard.keycode] = true;
            on_key_down(event.keyboard.keycode);
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            // Event for keyboard key up.
            game_log("Key with keycode %d up", event.keyboard.keycode);
            key_state[event.keyboard.keycode] = false;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            // Event for mouse key down.
            game_log("Mouse button %d down at (%d, %d)", event.mouse.button, event.mouse.x, event.mouse.y);
            mouse_state[event.mouse.button] = true;
            on_mouse_down(event.mouse.button, event.mouse.x, event.mouse.y);
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            // Event for mouse key up.
            game_log("Mouse button %d up at (%d, %d)", event.mouse.button, event.mouse.x, event.mouse.y);
            mouse_state[event.mouse.button] = false;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            if (event.mouse.dx != 0 || event.mouse.dy != 0) {
                // Event for mouse move.
                game_log("Mouse move to (%d, %d)", event.mouse.x, event.mouse.y);
                mouse_x = event.mouse.x;
                mouse_y = event.mouse.y;
            }
            else if (event.mouse.dz != 0) {
                // Event for mouse scroll.
                game_log("Mouse scroll at (%d, %d) with delta %d", event.mouse.x, event.mouse.y, event.mouse.dz);
            }
        }
        // TODO: Process more events and call callbacks by adding more
        // entries inside Scene.
        
        // Redraw
        if (redraws > 0 && al_is_event_queue_empty(game_event_queue)) {
            // if (redraws > 1)
            //     game_log("%d frame(s) dropped", redraws - 1);
            // Update and draw the next frame.
            game_update();
            game_draw();
            redraws = 0;
        }
    }
}

void game_update(void) {
    srand(al_get_time()+time(NULL));
    if (active_scene == SCENE_START) {
        plane.vx = plane.vy = 0;
        if (key_state[ALLEGRO_KEY_UP] || key_state[ALLEGRO_KEY_W])
            plane.vy -= 1;
        if (key_state[ALLEGRO_KEY_DOWN] || key_state[ALLEGRO_KEY_S])
            plane.vy += 1;
        if (key_state[ALLEGRO_KEY_LEFT] || key_state[ALLEGRO_KEY_A])
            plane.vx -= 1;
        if (key_state[ALLEGRO_KEY_RIGHT] || key_state[ALLEGRO_KEY_D])
            plane.vx += 1;
        // 0.71 is (1/sqrt(2)).
        plane.y += plane.vy * 7 * (plane.vx ? 0.71f : 1);
        plane.x += plane.vx * 7 * (plane.vy ? 0.71f : 1);
        // Limit the plane inside the screen.
        if (plane.x < 0)
            plane.x = 0;
        else if (plane.x> 900-plane.w)
            plane.x = 900-plane.w;
        if (plane.y < plane.h)
            plane.y = plane.h;
        else if (plane.y > SCREEN_H-plane.h)
            plane.y = SCREEN_H-plane.h;
        if (plane.life <= 0) {
            plane.hidden = true;
            dead_times++;
            active_scene = SCENE_DEATH;
        }
        
        // Update bullet coordinates.
        int i;
        for (i = 0; i < MAX_BULLET; i++) {
            if (bullets[i].hidden) continue;
            bullets[i].y += bullets[i].vy;
			bullets[i].deg = rand();
            if (bullets[i].y < 0){
                bullets[i].hidden = true;
            }
            if(bullets[i].life <= 0){
                bullets[i].hidden = true;
            }
        }
        
        // Shoot
        if (key_state[ALLEGRO_KEY_Z] && (now - last_shoot_timestamp >= MAX_COOLDOWN)) {
            for (i = 0; i < MAX_BULLET; i++) {
                if (bullets[i].hidden) break;
            }
            if (i < MAX_BULLET && (!plane.hidden)) {
                last_shoot_timestamp = now;
                bullets[i].hidden = false;
                bullets[i].x = plane.x;
                bullets[i].y = plane.y;
                bullets[i].vx = 0;
                bullets[i].vy = -10;
                bullets[i].life = 1;
            }
        }
        
        //Enemies
        int j;
        for(j = 0; j < MAX_ENEMY; j++){
            if(enemies[j].hidden) continue;
            enemies[j].vx = 4;
            if((enemies[j].x >= -100) && (enemies[j].x < 100)){
                enemies[j].vy = 4;
            }else if((enemies[j].x >= 100) && (enemies[j].x < 200)){
                enemies[j].vy = 3.8;
            }else if ((enemies[j].x >= 200) && (enemies[j].x < 300)){
                enemies[j].vy = 3.6;
            }else if ((enemies[j].x >= 300) && (enemies[j].x < 400)){
                enemies[j].vy = 3.4;
            }else if ((enemies[j].x >= 400) && (enemies[j].x < 500)){
                enemies[j].vy = 3.2;
            }else if ((enemies[j].x >= 500) && (enemies[j].x < 600)){
                enemies[j].vy = 3;
            }else if ((enemies[j].x >= 600) && (enemies[j].x < 700)){
                enemies[j].vy = 2.8;
            }else if ((enemies[j].x >= 700) && (enemies[j].x < 800)){
                enemies[j].vy = 2.6;
            }else if ((enemies[j].x >= 800) && (enemies[j].x < 900)){
                enemies[j].vy = 2.5;
            }else if (enemies[j].x+enemies[j].w >= 900){
                enemies[j].hidden = true;
            }
            enemies[j].x += enemies[j].vx;
            enemies[j].y += enemies[j].vy;
        }
        //create new enemies
        for(j = 0; j < MAX_ENEMY; j++){
            if((now - last_enemy_deadtime) > enemy_revive_time){
                if(enemies[j].hidden){
                    enemies[j].x = -10-10*j;
                    enemies[j].y = -10-10*j;
                    enemies[j].life = level;
                    enemies[j].hidden = false;
                    last_enemy_deadtime = now;
                }
            }
        }
        // enemies bullets
        int k;
        for(j = 0; j < MAX_ENEMY; j++){
            for (k = 0; k < MAX_ENEMY_BULLET*level; k++) {
                if (enemies_bullets[j][k].hidden) continue;
                enemies_bullets[j][k].x += enemies_bullets[j][k].vx;
                enemies_bullets[j][k].y += enemies_bullets[j][k].vy;
                if ((enemies_bullets[j][k].y > SCREEN_H) || (enemies_bullets[j][k].x < enemies_bullets[j][k].w/2) || (enemies_bullets[j][k].x > 900-enemies_bullets[j][k].w/2)){
                    enemies_bullets[j][k].hidden = true;
                }
                if(enemies_bullets[j][k].life == 0){
                    enemies_bullets[j][k].hidden = true;
                }
            }
        }
        for (j = 0; j < MAX_ENEMY; j++){
            if(!enemies[j].hidden){
                if((now - enemy_last_shoot_timestamp[j]) > ENEMY_MAX_COOLDOWN){
                    for(k = 0; k < MAX_ENEMY_BULLET*level; k++){
                        if (enemies_bullets[j][k].hidden) break;
                    }
                    if (k < MAX_ENEMY_BULLET*level) {
                        enemy_last_shoot_timestamp[j] = now;
                        enemies_bullets[j][k].hidden = false;
                        enemies_bullets[j][k].x = enemies[j].x;
                        enemies_bullets[j][k].y = enemies[j].y;
                        enemies_bullets[j][k].vx = rand()/RAND_MAX * level * 5;
                        enemies_bullets[j][k].vy = 6;
                        enemies_bullets[j][k].life = 1;
                    }
                }
            }
        }
        
        //Enemies_right
        for(j = 0; j < MAX_ENEMY; j++){
            if(enemies_right[j].hidden) continue;
            enemies_right[j].vx = -4;
            if(enemies_right[j].x-enemies_right[j].w/2 < 0){
                enemies_right[j].hidden = true;
            }else if((enemies_right[j].x >= 0) && (enemies_right[j].x < 200)){
                enemies_right[j].vy = 2.4;
            }else if ((enemies_right[j].x >= 200) && (enemies_right[j].x < 300)){
                enemies_right[j].vy = 2.6;
            }else if ((enemies_right[j].x >= 300) && (enemies_right[j].x < 400)){
                enemies_right[j].vy = 2.8;
            }else if ((enemies_right[j].x >= 400) && (enemies_right[j].x < 500)){
                enemies_right[j].vy = 3;
            }else if ((enemies_right[j].x >= 500) && (enemies_right[j].x < 600)){
                enemies_right[j].vy = 3.2;
            }else if ((enemies_right[j].x >= 600) && (enemies_right[j].x < 700)){
                enemies_right[j].vy = 3.4;
            }else if ((enemies_right[j].x >= 700) && (enemies_right[j].x < 800)){
                enemies_right[j].vy = 3.6;
            }else if ((enemies_right[j].x >= 800) && (enemies_right[j].x < 900)){
                enemies_right[j].vy = 3.8;
            }else if (enemies_right[j].x >= 900){
                enemies_right[j].vy = 4;
            }
            enemies_right[j].x += enemies_right[j].vx;
            enemies_right[j].y += enemies_right[j].vy;
        }
        //create new enemies_right
        for(j = 0; j < MAX_ENEMY; j++){
            if((now - last_enemy_deadtime_right) > enemy_revive_time){
                if(enemies_right[j].hidden){
                    enemies_right[j].x = 890+10*j;
                    enemies_right[j].y = -10-10*j;
                    enemies_right[j].life = level;
                    enemies_right[j].hidden = false;
                    last_enemy_deadtime_right = now;
                }
            }
        }
        // enemies_right bullets
        for(j = 0; j < MAX_ENEMY; j++){
            for (k = 0; k < MAX_ENEMY_BULLET*level; k++) {
                if (enemies_bullets_right[j][k].hidden) continue;
                enemies_bullets_right[j][k].x += enemies_bullets_right[j][k].vx;
                enemies_bullets_right[j][k].y += enemies_bullets_right[j][k].vy;
                if ((enemies_bullets_right[j][k].y > SCREEN_H) || (enemies_bullets_right[j][k].x < enemies_bullets_right[j][k].w/2) || (enemies_bullets_right[j][k].x > 900-enemies_bullets_right[j][k].w/2)){
                    enemies_bullets_right[j][k].hidden = true;
                }
                if(enemies_bullets_right[j][k].life <= 0){
                    enemies_bullets_right[j][k].hidden = true;
                }
            }
        }
        for (j = 0; j < MAX_ENEMY; j++){
            if(!enemies_right[j].hidden){
                if((now - enemy_last_shoot_timestamp_right[j]) > ENEMY_MAX_COOLDOWN){
                    for(k = 0; k < MAX_ENEMY_BULLET*level; k++){
                        if (enemies_bullets_right[j][k].hidden) break;
                    }
                    if (k < MAX_ENEMY_BULLET*level) {
                        enemy_last_shoot_timestamp_right[j] = now;
                        enemies_bullets_right[j][k].hidden = false;
                        enemies_bullets_right[j][k].x = enemies_right[j].x;
                        enemies_bullets_right[j][k].y = enemies_right[j].y;
                        enemies_bullets_right[j][k].vx = -(rand()/RAND_MAX * level * 5);
                        enemies_bullets_right[j][k].vy = 5;
                        enemies_bullets_right[j][k].life = 1;
                    }
                }
            }
        }
        
        // Hit enemies
        for(int i = 0; i< MAX_BULLET; i++){
            for(int j = 0; j < MAX_ENEMY; j++){
                if((bullets[i].x <= (enemies[j].x+enemies[j].w/2)) && (bullets[i].x >= (enemies[j].x-enemies[j].w/2)) && (bullets[i].y <= (enemies[j].y+enemies[j].h/2)) && (bullets[i].y >= (enemies[j].y-enemies[j].h/2)) && (!bullets[i].hidden) && (!enemies[j].hidden)){
                    bullets[i].life--;
                    enemies[j].life--;
                    combo += 0.030;
                    score += 10 * combo;
                }
            }
        }
        
        //hit enemies_right
        for(int i = 0; i< MAX_BULLET; i++){
            for(int j = 0; j < MAX_ENEMY; j++){
                if((bullets[i].x <= (enemies_right[j].x+enemies_right[j].w/2)) && (bullets[i].x >= (enemies_right[j].x-enemies_right[j].w/2)) && (bullets[i].y <= (enemies_right[j].y+enemies_right[j].h/2)) && (bullets[i].y >= (enemies_right[j].y-enemies_right[j].h/2)) && (!bullets[i].hidden) && (!enemies_right[j].hidden)){
                    bullets[i].life--;
                    enemies_right[j].life--;
                    combo += 0.030;
                    score += 10 * combo;
                }
            }
        }
        
        //Hit player
        for(j = 0; j < MAX_ENEMY; j++){
            for(int k = 0; k < MAX_ENEMY_BULLET*level; k++){
                if((enemies_bullets[j][k].x+enemies_bullets[j][k].w/2 >= plane.x) && (enemies_bullets[j][k].x-enemies_bullets[j][k].w/2 <= plane.x) && (enemies_bullets[j][k].y+enemies_bullets[j][k].h/2 >= plane.y) && (enemies_bullets[j][k].y-enemies_bullets[j][k].w/2 <= plane.y) && !(enemies_bullets[j][k].hidden) && !(plane.hidden)){
                    enemies_bullets[j][k].life--;
                    plane.life--;
                    combo = 1.000;
                }
            }
        }
        
        for(j = 0; j < MAX_ENEMY; j++){
            for(int k = 0; k < MAX_ENEMY_BULLET*level; k++){
                if((enemies_bullets_right[j][k].x+enemies_bullets_right[j][k].w/2 >= plane.x) && (enemies_bullets_right[j][k].x-enemies_bullets_right[j][k].w/2 <= plane.x) && (enemies_bullets_right[j][k].y+enemies_bullets_right[j][k].h/2 >= plane.y) && (enemies_bullets_right[j][k].y-enemies_bullets_right[j][k].w/2 <= plane.y) && !(enemies_bullets_right[j][k].hidden) && !(plane.hidden)){
                    enemies_bullets_right[j][k].life--;
                    plane.life--;
                    combo = 1.000;
                }
            }
        }
    }
    
    else if(active_scene == SCENE_SECOND_STAGE){
        //wennie
        wennie.vx = wennie.vy = 0;
        if (key_state[ALLEGRO_KEY_UP] || key_state[ALLEGRO_KEY_W])
            wennie.vy -= 1;
        if (key_state[ALLEGRO_KEY_DOWN] || key_state[ALLEGRO_KEY_S])
            wennie.vy += 1;
        if (key_state[ALLEGRO_KEY_LEFT] || key_state[ALLEGRO_KEY_A])
            wennie.vx -= 1;
        if (key_state[ALLEGRO_KEY_RIGHT] || key_state[ALLEGRO_KEY_D])
            wennie.vx += 1;
        wennie.y += wennie.vy * 7 * (wennie.vx ? 0.71f : 1);
        wennie.x += wennie.vx * 7 * (wennie.vy ? 0.71f : 1);
        // Limit the wennie inside the screen.
        if (wennie.x < wennie.w)
            wennie.x = wennie.w;
        else if (wennie.x> 900-wennie.w)
            wennie.x = 900-wennie.w;
        if (wennie.y < wennie.h)
            wennie.y = wennie.h;
        else if (wennie.y > SCREEN_H-wennie.h)
            wennie.y = SCREEN_H-wennie.h;
        if (wennie.life <= 0) {
            wennie.hidden = true;
            dead_times++;
            active_scene = SCENE_DEATH2;
        }
       
        //boss
        if(boss.life >= (2500*level)){  //normal
            if (boss.x >= (900 - 3*boss.w)) {
				boss.vx = -0.1;
			}
			else if (boss.x <= 3*boss.w) {
				boss.vx = 0.1;
			}
            else{
                boss.vx = ((float)rand() / RAND_MAX - 0.5) * level;
            }
            boss.x += boss.vx;
			if (boss.y >= -100 && boss.y < 100) {
                boss.y += 10;
            }else if(boss.y >= 100 && boss.y < 200){
                boss.y += 9;
            }else if(boss.y >= 200 && boss.y < 300){
                boss.y += 8;
            }else if(boss.y >= 300 && boss.y < 400){
                boss.y += 7;
            }else if(boss.y >= 400 && boss.y < 500){
                boss.y += 6;
            }else if(boss.y >= 500 && boss.y < 700){
                boss.y += 5;
            }else if(boss.y >= 700){
                boss.y = 700;
            }
		}   
		else if(boss.life < 2500*level){  // rampage
            boss.vx = 5*sin(rand());
            boss.vy = 5*cos(rand());
            boss.x += boss.vx;
            boss.y += boss.vy;
            if(boss.x+boss.w/2 > 900) {
                boss.x = 900 - boss.w;
            }
            if(boss.x-boss.w/2 < 0){
                boss.x = boss.w/2;
            }
            if(boss.y+boss.h/2 > SCREEN_H) {
                boss.y = SCREEN_H - boss.h;
            }
            if(boss.y - boss.h/2 < 0){
                boss.y = boss.h/2;
            }
        }
        else if(boss.life <= 0){
            boss.hidden = true;
        }
        //player bullet
        int i;
        for (i = 0; i < MAX_WENNIE_BULLET; i++) {
            if (wennie_bullets[i].hidden) continue;
            wennie_bullets[i].y += wennie_bullets[i].vy;
			wennie_bullets[i].deg = rand();
            if (wennie_bullets[i].y < 0){
                wennie_bullets[i].hidden = true;
            }
            if(wennie_bullets[i].life <= 0){
                wennie_bullets[i].hidden = true;
            }
        }
        
        if (key_state[ALLEGRO_KEY_Z] && (now - last_shoot_timestamp >= MAX_COOLDOWN)) {
            for (i = 0; i < MAX_WENNIE_BULLET; i++) {
                if (wennie_bullets[i].hidden) break;
            }
            if (i < MAX_WENNIE_BULLET && (!wennie.hidden)) {
                last_shoot_timestamp = now;
                wennie_bullets[i].hidden = false;
                wennie_bullets[i].x = wennie.x;
                wennie_bullets[i].y = wennie.y;
                wennie_bullets[i].vx = 0;
                wennie_bullets[i].vy = -15;
                wennie_bullets[i].life = 1;
            }
        }
        // skill
        for(i = 0; i < MAX_SKILL_BULLET; i++){
            if(skill_bullet[i].hidden) continue;
            skill_bullet[i].vy = -10;
            if (skill_bullet[i].y <= boss.y+boss.h/2){
                skill_bullet[i].y = boss.y+boss.h/2;
                skill_bullet[i].vy = 0;
                if(skill_bullet[i].x <= (boss.x+boss.w/2)){
                    skill_bullet[i].vx = 10;
                }else if(skill_bullet[i].x > (boss.x-boss.w/2)){
                    skill_bullet_right[i].vx = -10;
                }
            }
            if(skill_bullet[i].x <= 0){
                skill_bullet[i].vx = 10;
            }
            skill_bullet[i].x += skill_bullet[i].vx;
            skill_bullet[i].y += skill_bullet[i].vy;
            if(skill_bullet[i].life <= 0){
                skill_bullet[i].hidden = true;
            }
        }
        
        for(i = 0; i < MAX_SKILL_BULLET; i++){
            if(skill_bullet_right[i].hidden) continue;
            skill_bullet_right[i].vy = -10;
            if (skill_bullet_right[i].y <= boss.y+boss.h/2){
                skill_bullet_right[i].y = boss.y+boss.h/2;
                skill_bullet_right[i].vy = 0;
                if(skill_bullet_right[i].x > (boss.x-boss.w/2)){
                    skill_bullet_right[i].vx = -10;
                }else if(skill_bullet_right[i].x < (boss.x+boss.w/2)){
                    skill_bullet_right[i].vx = 10;
                }
            }
            if (skill_bullet_right[i].x >= 900){
                skill_bullet_right[i].vx = -10;
            }
            skill_bullet_right[i].x += skill_bullet_right[i].vx;
            skill_bullet_right[i].y += skill_bullet_right[i].vy;
            if(skill_bullet_right[i].life <= 0){
                skill_bullet_right[i].hidden = true;
            }
        }
        if(key_state[ALLEGRO_KEY_X] && (energy >= 5000) && ((now - last_used_skill) >= 0.1f)){
            for(i = 0; i < MAX_SKILL_BULLET; i++){
                if(skill_bullet[i].hidden && skill_bullet_right[i].hidden){
                    break;
                }
            }
            if(i < MAX_SKILL_BULLET && (!wennie.hidden) && (count <= 50)){
                last_used_skill = now;
                skill_bullet[i].hidden = false;
                skill_bullet_right[i].hidden = false;
                skill_bullet[i].x = skill_bullet_right[i].x = wennie.x;
                skill_bullet[i].y = skill_bullet_right[i].y = wennie.y;
                skill_bullet[i].vx = -10;
                skill_bullet[i].vy = -10;
                skill_bullet_right[i].vx = 10;
                skill_bullet_right[i].vy = -10;
                skill_bullet[i].life = skill_bullet_right[i].life = 1;
                count++;
            }else if(count > 50){
                count = 0;
                energy = 0;
            }
        }
        if(energy >= 5000){
            skill_background.hidden = false;
        }else
            skill_background.hidden = true;
        
        // boss bullet
        int k;
        for (k = 0; k < MAX_BOSS_BULLET*level; k++) {
			int degree = k % 12;
			const double rad = 0.5235988;
            if (boss_bullets[k].hidden) continue;
			boss_bullets[k].vx = 4 * cos(rad * degree);
			boss_bullets[k].vy = 4 * sin(rad * degree);
			boss_bullets[k].deg = rad * degree;
            boss_bullets[k].x += boss_bullets[k].vx;
            boss_bullets[k].y += boss_bullets[k].vy;
            if ((boss_bullets[k].y < 0) || (boss_bullets[k].y > SCREEN_H - boss_bullets[k].h/2) || (boss_bullets[k].x < 0) || (boss_bullets[k].x > 900-boss_bullets[k].w/2)){
                boss_bullets[k].hidden = true;
            }
            if(boss_bullets[k].life == 0){
                boss_bullets[k].hidden = true;
            }
        }
        if (!boss.hidden &&  ((now - boss_last_shoot_timestamp) >= BOSS_COOLDOWN)) {
            for (k = 0; k < MAX_BOSS_BULLET*level; k++){
                if (boss_bullets[k].hidden) break;
            }
            if (k < MAX_BOSS_BULLET*level) {
                boss_last_shoot_timestamp = now;
                boss_bullets[k].hidden = false;
                boss_bullets[k].x = boss.x + boss.w/2;
                boss_bullets[k].y = boss.y + boss.h/2;
                boss_bullets[k].life = 1;
            }
        }
        
        // Hit boss
        for(int i = 0; i< MAX_WENNIE_BULLET; i++){
            if((wennie_bullets[i].x <= (boss.x+boss.w/2)) && (wennie_bullets[i].x >= (boss.x-boss.w/2)) && (wennie_bullets[i].y <= (boss.y+boss.h/2)) && (wennie_bullets[i].y >= (boss.y-boss.h/2)) && (!wennie_bullets[i].hidden) && (!boss.hidden)){
                wennie_bullets[i].life--;
                boss.life--;
                combo += 0.030;
                score += 10 * combo;
                energy += 10* combo*0.1;
            }
        }
        
        for(int i = 0; i< MAX_SKILL_BULLET; i++){
            if((skill_bullet[i].x <= (boss.x+boss.w/2)) && (skill_bullet[i].x >= (boss.x-boss.w/2)) && (skill_bullet[i].y <= (boss.y+boss.h/2)) && (skill_bullet[i].y >= (boss.y-boss.h/2)) && (!skill_bullet[i].hidden) && (!boss.hidden)){
                skill_bullet[i].life--;
                boss.life--;
                combo += 0.030;
                score += 10 * combo*0.1;
            }
        }
        
        for(int i = 0; i< MAX_SKILL_BULLET; i++){
            if((skill_bullet_right[i].x <= (boss.x+boss.w/2)) && (skill_bullet_right[i].x >= (boss.x-boss.w/2)) && (skill_bullet_right[i].y <= (boss.y+boss.h/2)) && (skill_bullet_right[i].y >= (boss.y-boss.h/2)) && (!skill_bullet_right[i].hidden) && (!boss.hidden)){
                skill_bullet_right[i].life--;
                boss.life--;
                combo += 0.030;
                score += 10 * combo;
            }
        }
        //Hit player
        for(int k = 0; k < MAX_BOSS_BULLET*level; k++){
            if((boss_bullets[k].x+boss_bullets[k].w/2 >= wennie.x) && (boss_bullets[k].x-boss_bullets[k].w/2 <= wennie.x) && (boss_bullets[k].y+boss_bullets[k].h/2 >= wennie.y) && (boss_bullets[k].y-boss_bullets[k].h/2 <= wennie.y) && !(boss_bullets[k].hidden) && !(wennie.hidden)){
                boss_bullets[k].life--;
                wennie.life--;
                combo = 1.000;
            }
        }
    }
    else if(active_scene == SCENE_PASS_STAGE){
        if(plane.y > (SCREEN_H/2+80)) plane.y-=3;
        else plane.y = (SCREEN_H/2+80);
    }
    
    else if (active_scene == SCENE_FINAL){
        for(int i = 0; i < 26; i++){
            if(wennies[i].y > 900) wennies[i].y+=3; else wennies[i].y = 900;
            if(wennies[i+26].y > 800) wennies[i].y+=2.6; else wennies[i].y = 800;
            if(wennies[i+52].y > 700) wennies[i].y+=2.3; else wennies[i].y = 700;
            if(wennies[i+78].y > 600) wennies[i].y+=2; else wennies[i].y = 600;
        }
    }
}

void game_draw(void) {
    if (active_scene == SCENE_MENU) {
        score = 0;
        combo = 1.00;
        al_draw_bitmap(main_img_background, 0, 0, 0);
        al_draw_text(font_pirulen_72, al_map_rgb(0, 255, 255), 100, SCREEN_H/2-200, 0, "Civil War : Be A Winnie?");
        // start button
        if(pnt_in_rect(mouse_x, mouse_y, 600, SCREEN_H/2, 200, 56))
            al_draw_bitmap(img_start2, 600, SCREEN_H/2, 0);
        else
            al_draw_bitmap(img_start, 600, SCREEN_H/2, 0);
        // help button
        if(pnt_in_rect(mouse_x, mouse_y, 600, SCREEN_H/2+150, 200, 66))
            al_draw_bitmap(img_help2, 600, SCREEN_H/2+150, 0);
        else
            al_draw_bitmap(img_help, 600, SCREEN_H/2+150, 0);
        // Draw settings images.
        if (pnt_in_rect(mouse_x, mouse_y, SCREEN_W - 48, 10, 38, 38))
            al_draw_bitmap(img_settings2, SCREEN_W - 48, 10, 0);
        else
            al_draw_bitmap(img_settings, SCREEN_W - 48, 10, 0);
    }
    else if (active_scene == SCENE_START){
        int i;
        al_draw_bitmap(start_img_background, 0, 0, 0);
		draw_movable_object(black);
        // player information
        al_draw_textf(font_pirulen_32, al_map_rgb(0, 0, 255), 900, 10, 0, "Score : %08d",score);
        al_draw_textf(font_pirulen_32, al_map_rgb(0, 0, 255), 900, 50, 0, "Target : %08d", 10000*level);
        al_draw_textf(font_pirulen_32, al_map_rgb(255, 0, 0), 900, 90, 0, "Life : %d", plane.life);
        al_draw_textf(font_pirulen_32, al_map_rgb(255, 0, 0),  900, 130, 0, "combo : %lf", combo);
        al_draw_textf(font_pirulen_32, al_map_rgb(0, 255, 0), 900, 190, 0, "Time : %.1lf", now - TIME - TIME_3);
        // Draw bullets.
        for (i = 0; i < MAX_BULLET; i++)
            draw_movable_object(bullets[i]);
        // Draw plane
        draw_movable_object(plane);
        // Draw enemies
        for(i = 0; i < MAX_ENEMY; i++){
            draw_movable_object(enemies[i]);
            draw_movable_object(enemies_right[i]);
        }
        for (i = 0; i < MAX_ENEMY; i++){
            for(int j = 0; j < MAX_ENEMY_BULLET*level; j++){
                draw_movable_object(enemies_bullets[i][j]);
                draw_movable_object(enemies_bullets_right[i][j]);
            }
        }
    }
    // Draw Second stage fight
    else if (active_scene == SCENE_SECOND_STAGE) {
        int i;
        al_draw_bitmap(boss_stage_background, 0, 0, 0);
        draw_movable_object(black);
        al_draw_textf(font_pirulen_32, al_map_rgb(0, 0, 255), 900, 10, 0, "Score : %08d", score);
        al_draw_textf(font_pirulen_32, al_map_rgb(255, 0, 0), 900, 50, 0, "Life : %d", wennie.life);
        al_draw_textf(font_pirulen_32, al_map_rgb(255, 0, 0),  900, 90, 0, "combo : %.3lf", combo);
        al_draw_textf(font_pirulen_32, al_map_rgb(0, 255, 0), 900, 130, 0, "Time : %.1lf", now - TIME - TIME_3 + TIME_4);
        if(energy < 5000)
            al_draw_textf(font_pirulen_32, al_map_rgb(255, 0, 0), 900, 170,0, "Energy : %d/5000", energy);
        else{
            if(!key_state[ALLEGRO_KEY_X])
                al_draw_textf(font_pirulen_32, al_map_rgb(255, 0, 0), 900, 170, 0, "Energy : FULL");
            else
                al_draw_textf(font_pirulen_32, al_map_rgb(255, 0, 0), 900, 170, 0, "Energy : USING");
        }
        al_draw_textf(font_pirulen_32, al_map_rgb(255, 0, 0), 900, 210, 0, "BOSS : %d / %d",boss.life, 5000*level);
        draw_movable_object(wennie);
        draw_movable_object(boss);
        for(i = 0; i < MAX_WENNIE_BULLET; i++)
            draw_movable_object(wennie_bullets[i]);
        for(i = 0; i < MAX_BOSS_BULLET*level; i++)
            draw_movable_object(boss_bullets[i]);
        for(i = 0; i < MAX_SKILL_BULLET; i++){
            draw_movable_object(skill_bullet[i]);
            draw_movable_object(skill_bullet_right[i]);
        }
        draw_movable_object(skill_background);
    }
    // Draw setting scene.
    else if (active_scene == SCENE_SETTINGS) {
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font_pirulen_32, al_map_rgb(255, 255, 255), SCREEN_W/2-200, SCREEN_H/2, 0, "[B]Back to Menu");
       
        if(pnt_in_rect(mouse_x, mouse_y, 20, 100, 200, 55))
            al_draw_bitmap(img_level_11, 20, 100, 0);
        else
            al_draw_bitmap(img_level_1, 20, 100, 0);
       
        if(pnt_in_rect(mouse_x, mouse_y, 220, 100, 200, 55))
            al_draw_bitmap(img_level_22, 220, 100, 0);
        else
            al_draw_bitmap(img_level_2, 220, 100, 0);
       
        if(pnt_in_rect(mouse_x, mouse_y, 420, 100, 200, 55))
            al_draw_bitmap(img_level_33, 420, 100, 0);
        else
            al_draw_bitmap(img_level_3, 420, 100, 0);
        
        if(pnt_in_rect(mouse_x, mouse_y, 620, 100, 200, 55))
            al_draw_bitmap(img_level_44, 620, 100, 0);
        else
            al_draw_bitmap(img_level_4, 620, 100, 0);
       
        if(pnt_in_rect(mouse_x, mouse_y, 820, 100, 200, 55))
            al_draw_bitmap(img_level_55, 820, 100, 0);
        else
            al_draw_bitmap(img_level_5, 820, 100, 0);
    }
    else if(active_scene == SCENE_SETTINGS_FROM_START){
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font_pirulen_32, al_map_rgb(255, 255, 255), SCREEN_W/2-200, SCREEN_H/2, 0, "[C]Continue");
        al_draw_text(font_pirulen_32, al_map_rgb(255, 255, 255), SCREEN_W/2-200, SCREEN_H/2+100, 0, "[B]Back to Menu");
    }
    else if (active_scene == SCENE_SETTINGS_FROM_BOSS){
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font_pirulen_32, al_map_rgb(255, 255, 255), SCREEN_W/2-200, SCREEN_H/2, 0, "[C]Continue");
        al_draw_text(font_pirulen_32, al_map_rgb(255, 255, 255), SCREEN_W/2-200, SCREEN_H/2+100, 0, "[B]Back to Menu");
    }
    else if (active_scene == SCENE_DEATH){
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font_pirulen_72, al_map_rgb(255, 0, 0), SCREEN_W/2-150, SCREEN_H/2 - 100, 0, "Game Over");
        al_draw_text(font_pirulen_32, al_map_rgb(255, 255, 255), SCREEN_W/2-150, SCREEN_H/2, 0, "Press R to retry");
        al_draw_textf(font_pirulen_32, al_map_rgb(255, 255, 255), SCREEN_W/2-150, SCREEN_H/2+100, 0, "Dead Times : %d", dead_times);
    }
    else if(active_scene == SCENE_DEATH2){
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font_pirulen_72, al_map_rgb(255, 0, 0), SCREEN_W/2-150, SCREEN_H/2 - 100, 0, "Game Over");
        al_draw_text(font_pirulen_32, al_map_rgb(255, 255, 255), SCREEN_W/2-150, SCREEN_H/2, 0, "Press R to retry");
        al_draw_textf(font_pirulen_32, al_map_rgb(255, 255, 255), SCREEN_W/2-150, SCREEN_H/2+100, 0, "Dead Times : %d", dead_times);
    }
    else if(active_scene == SCENE_HELP){
        al_draw_bitmap(img_help_background, 0, 0, 0);
        al_draw_text(font_pirulen_32, al_map_rgb(255, 255, 255), 450, 1200, 0, "[B] Back to Menu");
    }
    else if(active_scene == SCENE_PASS_STAGE){
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(img_big_wennie, SCREEN_W/4, SCREEN_H/4, 0);
        draw_movable_object(plane);
        al_draw_text(font_pirulen_32, al_map_rgb(255, 255, 0), 10, 1300, 0, "Thank you to reorganize me, sir. I'm Winnie.");
        al_draw_text(font_pirulen_32, al_map_rgb(255, 255, 0), 7, 1400, 0, "Please help me again to defeat the man who BAN me!!");
        al_draw_text(font_pirulen_32, al_map_rgb(255, 255, 0), 20, 1500, 0, "press enter to continue.");
    }
    else if(active_scene == SCENE_FINAL){
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font_pirulen_72, al_map_rgb(255, 255, 255), 100, SCREEN_H/2, 0, "Congratulation!");
        al_draw_textf(font_pirulen_32, al_map_rgb(255, 255, 255), 200, SCREEN_H/2+100, 0, "Your Score : %08d , Time : %.1f , Dead Times : %d", score, TIME_4, dead_times);
        for(int i = 0; i< 104; i++){
            draw_movable_object(wennies[i]);
        }
        al_draw_text(font_pirulen_32, al_map_rgb(255, 255, 0), 20, 1400, 0, "Press Enter to Play Again.");
    }
    al_flip_display();
}

void game_destroy(void) {
    // Destroy everything you have created.
    al_destroy_font(font_pirulen_72);
    al_destroy_font(font_pirulen_32);
 //   al_destroy_sample(life_1);
  //  al_destroy_sample(life_0);
    
    /* Menu Scene resources*/
    al_destroy_bitmap(main_img_background);
    al_destroy_bitmap(img_help2);
    al_destroy_bitmap(img_help);
    al_destroy_bitmap(img_start2);
    al_destroy_bitmap(img_start);
    al_destroy_sample(main_bgm);
   // al_destroy_sample(choose_bgm);
    /* The 2 settings images*/
    al_destroy_bitmap(img_settings);
    al_destroy_bitmap(img_settings2);
    al_destroy_bitmap(img_level_1);
    al_destroy_bitmap(img_level_11);
    al_destroy_bitmap(img_level_2);
    al_destroy_bitmap(img_level_22);
    al_destroy_bitmap(img_level_3);
    al_destroy_bitmap(img_level_33);
    al_destroy_bitmap(img_level_4);
    al_destroy_bitmap(img_level_44);
    al_destroy_bitmap(img_level_5);
    al_destroy_bitmap(img_level_55);
    /* Start Scene resources*/
    al_destroy_bitmap(start_img_background);
    al_destroy_bitmap(start_img_plane);
    al_destroy_bitmap(start_img_enemy);
    al_destroy_sample(start_bgm);
    al_destroy_sample(attack_bgm);
    /* Second stage fight*/
    al_destroy_bitmap(boss_stage_background);
    al_destroy_bitmap(boss_stage_wennie);
    al_destroy_bitmap(boss_stage_boss);
    al_destroy_bitmap(img_boss_bullet);
    al_destroy_bitmap(img_wennie_bullet);
    al_destroy_bitmap(img_skill_bullet);
    al_destroy_bitmap(img_skill_background);
    /* Bullet image*/
    al_destroy_bitmap(start_img_bullet);
    al_destroy_bitmap(start_img_enemy_bullet);
    //others
    al_destroy_bitmap(img_help_background);
    al_destroy_bitmap(img_big_wennie);
    
    al_destroy_timer(game_update_timer);
    al_destroy_event_queue(game_event_queue);
    al_destroy_display(game_display);
    free(mouse_state);
}

void game_change_scene(int next_scene) {
    game_log("Change scene from %d to %d", active_scene, next_scene);
    // TODO: Destroy resources initialized when creating scene.
    if (active_scene == SCENE_MENU) {
        al_stop_sample(&main_bgm_id);
        game_log("stop audio (bgm)");
    }
    else if (active_scene == SCENE_START) {
        al_stop_sample(&start_bgm_id);
        game_log("stop audio (bgm)");
    }
    active_scene = next_scene;
    
    // TODO: Allocate resources before entering scene.
    if (active_scene == SCENE_MENU){
        if (!al_play_sample(main_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &main_bgm_id)){
            game_abort("failed to play audio (bgm)");
        }
    }
    else if (active_scene == SCENE_START) {
        srand(time(NULL) + al_get_time());
		black.img = img_black;
		black.x = 900;
		black.y = 0;
        int i;
        plane.img = start_img_plane;
        plane.w = al_get_bitmap_width(plane.img);
        plane.h = al_get_bitmap_height(plane.img);
        for (i = 0; i < MAX_ENEMY; i++) {
            enemies[i].img = start_img_enemy;
            enemies[i].w = al_get_bitmap_width(start_img_enemy);
            enemies[i].h = al_get_bitmap_height(start_img_enemy);
            enemies[i].life = level;
            enemies[i].hidden = true;
            
            enemies_right[i].img = start_img_enemy;
            enemies_right[i].w = al_get_bitmap_width(start_img_enemy);
            enemies_right[i].h = al_get_bitmap_height(start_img_enemy);
            enemies_right[i].life = level;
            enemies_right[i].hidden = true;
            // Initialize Enemies bullets.
            for(int j = 0; j < MAX_ENEMY_BULLET*level; j++){
                enemies_bullets[i][j].img = start_img_enemy_bullet;
                enemies_bullets[i][j].w = al_get_bitmap_width(start_img_enemy_bullet);
                enemies_bullets[i][j].h = al_get_bitmap_height(start_img_enemy_bullet);
                enemies_bullets[i][j].life = 1;
                enemies_bullets[i][j].hidden = true;
                
                enemies_bullets_right[i][j].img = start_img_enemy_bullet;
                enemies_bullets_right[i][j].w = al_get_bitmap_width(start_img_enemy_bullet);
                enemies_bullets_right[i][j].h = al_get_bitmap_height(start_img_enemy_bullet);
                enemies_bullets_right[i][j].life = 1;
                enemies_bullets_right[i][j].hidden = true;
            }
        }
        // Initialize bullets.
        for (i = 0; i < MAX_BULLET; i++) {
            bullets[i].img = start_img_bullet;
            bullets[i].w = al_get_bitmap_width(start_img_bullet);
            bullets[i].h = al_get_bitmap_height(start_img_bullet);
            bullets[i].life = 1;
            bullets[i].hidden = true;
        }

        if (!al_play_sample(start_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &start_bgm_id))
            game_abort("failed to play audio (bgm)");
    }
    else if (active_scene == SCENE_PASS_STAGE){
        wennie.x = 450;
        wennie.y = 1450;
        wennie.life = 1;
        boss.x = 450;
        boss.y = 3*boss.h;
        boss.life = 5000 * level;
        boss.hidden = false;
        skill_background.x = 910;
        skill_background.y = SCREEN_H-600;
        skill_background.hidden = true;
    }
    else if (active_scene == SCENE_SECOND_STAGE){
        int i;
        //player
        wennie.img = boss_stage_wennie;
        wennie.w = al_get_bitmap_width(boss_stage_wennie);
        wennie.h = al_get_bitmap_height(boss_stage_wennie);
        //boss
        boss.img = boss_stage_boss;
        boss.w = al_get_bitmap_width(boss_stage_boss);
        boss.h = al_get_bitmap_height(boss_stage_boss);
        //bullets
        for(i = 0; i < MAX_WENNIE_BULLET; i++){
            wennie_bullets[i].img = img_wennie_bullet;
            wennie_bullets[i].w = al_get_bitmap_width(img_wennie_bullet);
            wennie_bullets[i].h = al_get_bitmap_height(img_wennie_bullet);
            wennie_bullets[i].life = 1;
            wennie_bullets[i].hidden = true;
        }
        for(i = 0; i < MAX_BOSS_BULLET*level; i++){
            boss_bullets[i].img = img_boss_bullet;
            boss_bullets[i].w = al_get_bitmap_width(img_boss_bullet);
            boss_bullets[i].h = al_get_bitmap_height(img_boss_bullet);
            boss_bullets[i].life = 1;
        }
        for(i = 0; i < MAX_SKILL_BULLET; i++){
            skill_bullet[i].img = img_skill_bullet;
            skill_bullet_right[i].img = img_skill_bullet;
            skill_bullet[i].w = skill_bullet_right[i].w = al_get_bitmap_width(img_skill_bullet);
            skill_bullet[i].h = skill_bullet_right[i].h = al_get_bitmap_height(img_skill_bullet);
            skill_bullet[i].life = skill_bullet_right[i].life = 1;
        }
        skill_background.img = img_skill_background;
        skill_background.w = al_get_bitmap_width(img_skill_background);
        skill_background.h = al_get_bitmap_height(img_skill_background);
    }else if(active_scene == SCENE_FINAL){
        for(int i = 0; i< 104; i++){
            wennies[i].img = boss_stage_wennie;
            wennies[i].w = al_get_bitmap_width(boss_stage_wennie);
            wennies[i].h = al_get_bitmap_height(boss_stage_wennie);
            wennies[i].y = 0;
            wennies[i].x = 10 + 20*(i%26);
        }
    }
}

void on_key_down(int keycode) {
    if (active_scene == SCENE_START){
        if(keycode == ALLEGRO_KEY_P || keycode == ALLEGRO_KEY_ESCAPE){
            TIME_2 = now;
            game_change_scene(SCENE_SETTINGS_FROM_START);
        }
        if (score >= 10000*level) {
            SCORE = score;
            TIME_4 = now - TIME - TIME_3;
            plane.x = SCREEN_W/4+200;
            plane.y = SCREEN_H-plane.h;
            game_change_scene(SCENE_PASS_STAGE);
        }
    }else if (active_scene == SCENE_SECOND_STAGE){
        if(keycode == ALLEGRO_KEY_P || keycode == ALLEGRO_KEY_ESCAPE){
            TIME_2 = now;
            game_change_scene(SCENE_SETTINGS_FROM_BOSS);
        }
        if(boss.life <= 0){
            TIME_4 = now - TIME - TIME_3 + TIME_4;
            game_change_scene(SCENE_FINAL);
        }
    }else if(active_scene == SCENE_SETTINGS){
        if(keycode == ALLEGRO_KEY_B)
            game_change_scene(SCENE_MENU);
    }else if(active_scene == SCENE_SETTINGS_FROM_START){
        if(keycode == ALLEGRO_KEY_C){
            TIME_2 = now - TIME_2;
            TIME_3 += TIME_2;
            game_change_scene(SCENE_START);
        }
        if(keycode == ALLEGRO_KEY_B)
            game_change_scene(SCENE_MENU);
    }else if (active_scene == SCENE_SETTINGS_FROM_BOSS){
        if(keycode ==ALLEGRO_KEY_C){
            TIME_2 = now - TIME_2;
            TIME_3 += TIME_2;
            game_change_scene(SCENE_SECOND_STAGE);
        }
        if(keycode == ALLEGRO_KEY_B)
            game_change_scene(SCENE_MENU);
    }else if (active_scene == SCENE_DEATH){
        for(int j = 0; j < MAX_ENEMY; j++){
            for (int k = 0; k < MAX_ENEMY_BULLET*level; k++) {
                enemies_bullets[j][k].hidden = true;
                enemies_bullets_right[j][k].hidden = true;
            }
        }
        for (int j = 0; j < MAX_ENEMY; j++) {
            enemies[j].hidden = true;
            enemies_right[j].hidden = true;
        }
        score = 0;
        combo = 1.00;
        if (keycode == ALLEGRO_KEY_R) {
            TIME_3 = 0;
            TIME = now;
            plane.x = 450;
            plane.y = 1450;
            plane.life = 4;
            plane.hidden = false;
            game_change_scene(SCENE_START);
        }
    }else if(active_scene == SCENE_DEATH2){
        if (keycode == ALLEGRO_KEY_R) {
            TIME_3 = 0;
            TIME = now;
            wennie.x = 450;
            wennie.y = 1450;
            wennie.life = 1;
            boss.x = 450;
            boss.y = 3*boss.h;
            boss.life = 5000 * level;
            wennie.hidden = false;
            boss.hidden = false;
            for (int k = 0; k < MAX_BOSS_BULLET*level; k++) {
                boss_bullets[k].hidden = true;
            }
            score = SCORE;
            combo = 1.00;
            game_change_scene(SCENE_SECOND_STAGE);
        }
        else if(keycode == ALLEGRO_KEY_B){
            game_change_scene(SCENE_MENU);
        }
    }
    else if(active_scene == SCENE_PASS_STAGE){
        if(keycode == ALLEGRO_KEY_ENTER){
            al_rest(0.5);
            game_change_scene(SCENE_SECOND_STAGE);
        }
    }else if (active_scene == SCENE_FINAL){
        if(keycode == ALLEGRO_KEY_ENTER){
            game_change_scene(SCENE_MENU);
        }
    }
}

void on_mouse_down(int btn, int x, int y) {
    // Click and switch to settings scene.
    if (active_scene == SCENE_MENU) {
        if (btn == 1) {
            if (pnt_in_rect(x, y, SCREEN_W - 48, 10, 38, 38)){
                game_change_scene(SCENE_SETTINGS);
            }
            else if (pnt_in_rect(x, y, 600, SCREEN_H/2, 200, 56)){
                TIME = now;
                al_set_timer_count(game_update_timer, 0);
                plane.x = 450;
                plane.y = 1450;
                plane.life = 4;
                game_change_scene(SCENE_START);
            }
            else if (pnt_in_rect(x, y, 600, SCREEN_H/2+150, 200, 66))
                game_change_scene(SCENE_HELP);
        }
    }
    else if(active_scene == SCENE_SETTINGS){
        if(btn == 1){
            if (pnt_in_rect(x, y, 20, 100, 200, 55)){
                level = 1;
                game_change_scene(SCENE_MENU);
            }else if (pnt_in_rect(x , y, 220, 100, 200, 55)){
                level = 2;
                game_change_scene(SCENE_MENU);
            }else if (pnt_in_rect(x , y, 420, 100, 200, 55)){
                level = 3;
                game_change_scene(SCENE_MENU);
            }else if (pnt_in_rect(x , y, 620, 100, 200, 55)){
                level = 4;
                game_change_scene(SCENE_MENU);
            }else if (pnt_in_rect(x , y, 820, 100, 200, 55)){
                level = 5;
                game_change_scene(SCENE_MENU);
            }
        }
    }
}

void draw_movable_object(MovableObject obj) {
    if (obj.hidden)
        return;
    al_draw_rotated_bitmap(obj.img, obj.w/2, obj.h/2, round(obj.x + obj.w / 2), round(obj.y + obj.h / 2), obj.deg, 0);
}

ALLEGRO_BITMAP *load_bitmap_resized(const char *filename, int w, int h) {
    ALLEGRO_BITMAP* loaded_bmp = al_load_bitmap(filename);
    if (!loaded_bmp)
        game_abort("failed to load image: %s", filename);
    ALLEGRO_BITMAP *resized_bmp = al_create_bitmap(w, h);
    ALLEGRO_BITMAP *prev_target = al_get_target_bitmap();
    
    if (!resized_bmp)
        game_abort("failed to create bitmap when creating resized image: %s", filename);
    al_set_target_bitmap(resized_bmp);
    al_draw_scaled_bitmap(loaded_bmp, 0, 0,
                          al_get_bitmap_width(loaded_bmp),
                          al_get_bitmap_height(loaded_bmp),
                          0, 0, w, h, 0);
    al_set_target_bitmap(prev_target);
    al_destroy_bitmap(loaded_bmp);
    
    game_log("resized image: %s", filename);
    
    return resized_bmp;
}
//Define bool pnt_in_rect(int px, int py, int x, int y, int w, int h)
bool pnt_in_rect(int px, int py, int x, int y, int w, int h) {
    if ((px > x && px < (x + w)) && (py > y && py < (y + h)))
        return true;
    else
        return false;
}


// +=================================================================+
// | Code below is for debugging purpose, it's fine to remove it.    |
// | Deleting the code below and removing all calls to the functions |
// | doesn't affect the game.                                        |
// +=================================================================+

void game_abort(const char* format, ...) {
    va_list arg;
    va_start(arg, format);
    game_vlog(format, arg);
    va_end(arg);
    fprintf(stderr, "error occured, exiting after 2 secs");
    // Wait 2 secs before exiting.
    al_rest(2);
    // Force exit program.
    exit(1);
}

void game_log(const char* format, ...) {
#ifdef LOG_ENABLED
    va_list arg;
    va_start(arg, format);
    game_vlog(format, arg);
    va_end(arg);
#endif
}

void game_vlog(const char* format, va_list arg) {
#ifdef LOG_ENABLED
    static bool clear_file = true;
    vprintf(format, arg);
    printf("\n");
    // Write log to file for later debugging.
    FILE* pFile = fopen("log.txt", clear_file ? "w" : "a");
    if (pFile) {
        vfprintf(pFile, format, arg);
        fprintf(pFile, "\n");
        fclose(pFile);
    }
    clear_file = false;
#endif
}

