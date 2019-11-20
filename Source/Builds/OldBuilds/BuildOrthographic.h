#include "BuildIncludes.h"

void World::orthographic_build(void){
        float light_radiance = 4.0;

    // View Plane
    int size = 600;
    vp = ViewPlane(size, size, 1.0, 1.0);

    // Ambient Light
    ambient_ptr = new Ambient(light_radiance * 0.5, WHITE);

    // Background color
    background_color = GREEN / 10;

    // Tracer
    tracer_ptr = new RayCast(this);

    // Lights
    // Directional* directional_ptr = new Directional(light_radiance, WHITE, Vector3D(1, 1, 2));
    // add_light(directional_ptr);
    Point* point_ptr = new Point(light_radiance * 1.0, WHITE, Vector3D(-12, 15, 30));
    add_light(point_ptr);

    // Camera: Orthographic
    Orthographic* orthographic_ptr = new Orthographic();
    Vector3D eye1(10, 0, 0);
    orthographic_ptr->eye = eye1;
    Vector3D lookat1(0, 0, -1);
    orthographic_ptr->lookat = lookat1;
    float distance1 = 100;
    orthographic_ptr->distance = distance1;
    orthographic_ptr->compute_uvw();
    this->camera_ptr = orthographic_ptr;

    // Materials
    //Matte* emissive_ptr = new Matte(1, 1, WHITE);
    Matte* yellow_ptr = new Matte(0.25, 0.75, YELLOW);
    Matte* red_ptr = new Matte(0.25, 0.75, RED);
    Matte* green_ptr = new Matte(0.25, 0.75, GREEN);
    //Phong* yellow_phong_ptr = new Phong(0.25, 0.75, 0.5, 3.0, YELLOW);

    // Light
    Sphere* sphere_ptr = new Sphere(Vector3D(-12, 15, 30), 0.1);
    // sphere_ptr->set_material(emissive_ptr);
    // add_object(sphere_ptr);

    sphere_ptr = new Sphere(Vector3D(0.0, 2.4, 0), 1.5);
    sphere_ptr->set_material(red_ptr);
    add_object(sphere_ptr);

    Triangle* tri_ptr = new Triangle(Vector3D(1.5, -0.5, 1.8), Vector3D(7.5, -0.5, -9.00), Vector3D(2.35, 5.8, 1.4));
    tri_ptr->set_material(green_ptr);
    add_object(tri_ptr);

    Plane* plane_ptr = new Plane(Vector3D(0, -0.5, 0), Vector3D(0, 1, 0));
    plane_ptr->set_material(yellow_ptr);
    add_object(plane_ptr);

}