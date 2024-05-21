#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include "julia_set.h"

int HEIGHT_AND_WIDTH = 500;
double c_real = 0, c_imag = 0;
double x_centre = 0, y_centre = 0;
double change_c = 20;
double scale = 0.005;


void draw(ALLEGRO_DISPLAY *display)
{
    // come calculations
    double disp_x_left = x_centre - HEIGHT_AND_WIDTH / 2.0 * scale;
    double disp_y_up = y_centre + HEIGHT_AND_WIDTH / 2.0 * scale;

    ALLEGRO_LOCKED_REGION *bitmap = al_lock_bitmap(al_get_backbuffer(display), ALLEGRO_PIXEL_FORMAT_RGB_888, ALLEGRO_LOCK_READWRITE);

    // debug stuff
    //printf("c_real: %f, c_imag: %f\n", c_real, c_imag);
    //printf("x_centre: %f, y_centre: %f\n", x_centre, y_centre);
    //printf("disp_x_left: %f, disp_y_up: %f\n", disp_x_left, disp_y_up);
    //printf("scale: %f\n", scale);
    //printf("locked->pitch: %d\n", bitmap->pitch);

    julia_set(bitmap->data, bitmap->pitch, HEIGHT_AND_WIDTH, c_real, c_imag, scale, disp_x_left, disp_y_up);

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
    ALLEGRO_DISPLAY *display = al_create_display(HEIGHT_AND_WIDTH, HEIGHT_AND_WIDTH);
    al_set_window_title(display, "Julia Set");

    // create event queue
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));

    // create event
    ALLEGRO_EVENT event;

    int mouse_buttom = 0;

    while(true)
    {
        al_wait_for_event(event_queue, &event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;  // quit if click X on display

        if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE
            && event.type == ALLEGRO_EVENT_KEY_DOWN )
            break;  // quit if press escape

        // mouse operations
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)    // 1 is left click, 2 is right click
            mouse_buttom = event.mouse.button;
        // end interact with mouse
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            mouse_buttom = 0;

        // left click to change x_centre and y_centre
        if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            if(mouse_buttom == 1) // left click
            {
                x_centre -= event.mouse.dx * scale;
                y_centre += event.mouse.dy * scale;
            }
            // scroll, zoom in - positive, zoom out - negative
            if(event.mouse.dz != 0)
                scale -= scale * event.mouse.dz * 0.1;
            if(scale < 1.7e-100)
                scale = 1.7e-100;

        }
        // change c_real and c_imag
        if(event.type == ALLEGRO_EVENT_KEY_CHAR)
        {
            if(event.keyboard.keycode == ALLEGRO_KEY_W)
                c_imag += change_c * scale;
            if(event.keyboard.keycode == ALLEGRO_KEY_S)
                c_imag -= change_c * scale;
            if(event.keyboard.keycode == ALLEGRO_KEY_A)
                c_real -= change_c * scale;
            if(event.keyboard.keycode == ALLEGRO_KEY_D)
                c_real += change_c * scale;
        }
        draw(display);
    }

    al_destroy_display(display);
    al_uninstall_keyboard();
    al_uninstall_mouse();

    return 0;
}