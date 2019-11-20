#include "BuildIncludes.h"

void World::area_light_build(void){
    // Sampler
    int n = 9;
    int num_samples = n*n;
    int num_sets = 83;
    Sampler* sampler_ptr = new Jittered(num_samples, num_sets);

    // View Plane
    vp = ViewPlane(600, 600, 1.0, 1.0, 8);
    vp.set_sampler(sampler_ptr);

    // Ambient Light
    float light_radiance = 4.0;
    ambient_ptr = new Ambient(light_radiance * 0.5, WHITE);

    // Background color
    background_color = GREEN / 10;

    // Tracer
    tracer_ptr = new AreaLighting(this);

    // Lights
    Emmissive* emmissive_ptr = new Emmissive(40, WHITE);

    float width = 4.0;
    float height= 4.0;
    Vector3D center(0.0, 7.0, -7.0);
    Vector3D p0(-0.5 * width, center.y - 0.5 * height, center.z);
    Vector3D a(width, 0.0, 0.0);
    Vector3D b(0.0, height, 0.0);
    
    Rectangle* rectangle_ptr = new Rectangle(p0, a, b, sampler_ptr->clone());
    rectangle_ptr->set_material(emmissive_ptr);
    add_object(rectangle_ptr);

    AreaLight* area_light_ptr = new AreaLight(rectangle_ptr);
    add_light(area_light_ptr);

    // Point Light (for debugging)
    // Point* point_ptr = new Point(light_radiance * 1.0, WHITE, Vector3D(12, 15, 30));
    // add_light(point_ptr);

    // Camera
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->up = Vector3D(0, -1, 0);
    pinhole_ptr->zoom = 1.0;
    pinhole_ptr->eye = Vector3D(-20, 10, 20);
    pinhole_ptr->lookat = Vector3D(0, 2, 0);
    pinhole_ptr->distance = 1080;
    pinhole_ptr->compute_uvw();
    this->camera_ptr = pinhole_ptr;

    // Materials
    Matte* yellow_ptr = new Matte(0.25, 0.75, YELLOW);
    Matte* green_ptr = new Matte(0.25, 0.75, GREEN);

    // Objects
    Plane* plane_ptr = new Plane(Vector3D(0, 0, 0), Vector3D(0, 1, 0));
    plane_ptr->set_material(yellow_ptr);
    add_object(plane_ptr);

    rectangle_ptr = new Rectangle(Vector3D(-3,0,0), Vector3D(2,0,0), Vector3D(0,4,0), sampler_ptr->clone());
    rectangle_ptr->set_material(green_ptr);
    add_object(rectangle_ptr);

    rectangle_ptr = new Rectangle(Vector3D(-7,0,0), Vector3D(2,0,0), Vector3D(0,4,0), sampler_ptr->clone());
    rectangle_ptr->set_material(green_ptr);
    add_object(rectangle_ptr);

    rectangle_ptr = new Rectangle(Vector3D(-0,0,0), Vector3D(2,0,0), Vector3D(0,4,0), sampler_ptr->clone());
    rectangle_ptr->set_material(green_ptr);
    add_object(rectangle_ptr);
}