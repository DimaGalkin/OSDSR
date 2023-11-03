#include "renderer.hpp"

Renderer::Renderer(Display& display) : vga_driver_(display) {}

void Renderer::drawline(const Line& line) {
    int dx = abs(line.b.x - line.a.x);
    int sx = line.a.x < line.b.x ? +1 : -1;
    int dy = -abs(line.b.y - line.a.y);
    int sy = line.a.y < line.b.y ? +1 : -1;
    int e = dx + dy;
    
	int x = line.a.x;
	int y = line.a.y;
	
    while (true) {
        vga_driver_.draw_pixel(x, y, 0xFFFFFF);

        if (x == line.b.x && y == line.b.y) break;
        int e2 = 2 * e;
        if (e2 >= dy) {
            if (x == line.b.x) break;
            e += dy;
            x += sx;
        }
        if (e2 <= dx) {
            if (y == line.b.y) break;
            e += dx;
            y += sy;
        }
    }
}

void Renderer::drawtriangle(const Triangle& triangle) {
    drawline({triangle.a, triangle.b});
    drawline({triangle.b, triangle.c});
    drawline({triangle.a, triangle.c});
}

Triangle Renderer::project(const GlobalSpaceTriangle& triangle) {
    const GlobalSpaceVertex* vertecies[3] = {&triangle.a, &triangle.b, &triangle.c};
    ScreenSpaceVertex vertecies_screen[3]; int index = 0;

    for (const auto& vertex : vertecies) {
        GlobalSpaceVertex vtx = camera_transform_matrix_ * (*vertex - camera_);

        // 250 gives fov of ≈60 degrees
        double t = 250 / (vtx.z); // z = 1 plane so t = 1/z as camera is always at 0, 0, 0
        int y = t * vtx.y; // y = p + ty p is 0 as camera is always at 0, 0, 0
        int x = t * vtx.x; // x = p + tx p is 0 as camera is always at 0, 0, 0

        // set center of screen to 0, 0
        y += vga_driver_.height_ / 2;
        x += vga_driver_.width_ / 2;

        vertecies_screen[index++] = ScreenSpaceVertex {x, y};
    }

    return Triangle {vertecies_screen[0], vertecies_screen[1], vertecies_screen[2]};
}

bool Renderer::backfacecull(const GlobalSpaceTriangle& triangle) {
    // calcualte lines leaving right angle of triangle
    GlobalSpaceVector LineA = {triangle.a.x - triangle.b.x, triangle.a.y - triangle.b.y, triangle.a.z - triangle.b.z};
    GlobalSpaceVector LineB = {triangle.a.x - triangle.c.x, triangle.a.y - triangle.c.y, triangle.a.z - triangle.c.z};

    // calculate cross product of triangle
    int Nx = (LineA.y * LineB.z) - (LineA.z * LineB.y);
    int Ny = (LineA.z * LineB.x) - (LineA.x * LineB.z);
    int Nz = (LineA.x * LineB.y) - (LineA.y * LineB.x);

    // if dot product of camera->triangle and cross product is less than 0 then return false
    int Vx = triangle.a.x - camera_.x;
    int Vy = triangle.a.y - camera_.y;
    int Vz = triangle.a.z - camera_.z;

    int dot = (Vx * Nx) + (Vy * Ny) + (Vz * Nz);

    return dot > 0;
}

void Renderer::calculate_camera_transform_matrix(double x, double y) {
    double cos_theta = dot(camera_dir_, Vector3{0, 0, 1});
    Vector3 prod = camera_dir_ * Vector3{0, 0, 1};
    double sin_theta = sqrt(pow(prod.x) + pow(prod.y) + pow(prod.z));

    camera_transform_matrix_ = {
        x, 0, y,
        0, 1, 0,
        -y, 0, x
    };
}