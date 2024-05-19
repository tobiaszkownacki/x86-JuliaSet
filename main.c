#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include "julia_set.h"

int WIDTH = 800;
int HEIGHT = 600;



void draw(ALLEGRO_DISPLAY *display)
{
    al_clear_to_color(al_map_rgb(125, 100, 25));

    ALLEGRO_LOCKED_REGION *locked = al_lock_bitmap(al_get_backbuffer(display), ALLEGRO_PIXEL_FORMAT_RGB_888, ALLEGRO_LOCK_READWRITE);

    // come calucations


    al_unlock_bitmap(al_get_backbuffer(display));
    al_flip_display();

}

int main()
{
    // init allegro and modules
    al_init();
    al_install_mouse();
    al_install_keyboard();

    // create display
    ALLEGRO_DISPLAY *display = al_create_display(WIDTH, HEIGHT);
    al_set_window_title(display, "Julia Set");

    // create event queue
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));

    // create event
    ALLEGRO_EVENT event;

    while(true)
    {
        al_wait_for_event(event_queue, &event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        draw(display);
    }




    return 0;
}