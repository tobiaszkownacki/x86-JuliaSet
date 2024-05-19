#ifndef JULIA_SET_H
#define JULIA_SET_H

void julia_set(
    void* data,
    int pitch,
    int width,
    int height,
    double c_real,
    double c_imag,
    double scale,
    double disp_x_left,
    double disp_y_up
);

#endif