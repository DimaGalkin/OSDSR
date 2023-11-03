#pragma once

#include "../display/display.hpp"
#include "../maths/matlib.hpp"

using ScreenSpaceVertex = Vector2;
using GlobalSpaceVertex = Vector3;

using GlobalSpaceVector = Vector3;

struct Line {
    ScreenSpaceVertex a;
    ScreenSpaceVertex b;
};

struct Triangle {
    ScreenSpaceVertex a;
    ScreenSpaceVertex b;
    ScreenSpaceVertex c;
};

struct GlobalSpaceTriangle {
    GlobalSpaceVertex a;
    GlobalSpaceVertex b;
    GlobalSpaceVertex c;
};

class Renderer {
    public:
        Renderer(Display& display);
        ~Renderer() = default;

        void calculate_camera_transform_matrix(double x, double y);
        void drawline(const Line& line); // Bresenham's algorithm
        void drawtriangle(const Triangle& triangle);
        Triangle project(const GlobalSpaceTriangle& triangle);
        bool backfacecull(const GlobalSpaceTriangle& triangle);

        void inccam(int dir) {
            camera_.x += dir;
        }

    private:
        Display& vga_driver_;

        GlobalSpaceVertex camera_ = { 0, 0, -250 };
        GlobalSpaceVertex camera_dir_ = {0, 0, 1};
        GlobalSpaceVertex distance_to_plane_ = {0, 0, 0.5};

        Matrix3x3 camera_transform_matrix_ = {
            1, 0, 0,
            0, 1, 0,
            0, 0, 1
        };
};