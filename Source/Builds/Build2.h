#include "BuildIncludes.h"

void World::build_2(void){
    // View Plane
    int size = 800;
    vp = ViewPlane(size, size, 1.0, 1.0, 8);

    // Sampler
    int n = 10;
    int num_samples = n*n;
    int num_sets = 83;
    Sampler* sampler_ptr = new Jittered(num_samples, num_sets);
    vp.set_sampler(sampler_ptr);

    // Background color
    background_color = GREEN / 10;

    // Tracer
    tracer_ptr = new AreaLighting(this);

    // Ambient Light
    float light_radiance = 5.0;
    ambient_ptr = new Ambient(light_radiance * 0.5, WHITE);

    // Area Light
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

    // Camera: Pinhole
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
    Matte* red_ptr = new Matte(0.25, 0.75, RED);
    Matte* blue_ptr = new Matte(0.25, 0.75, BLUE);

    // Ground Plane
    Plane* plane_ptr = new Plane(Vector3D(0, 0, 0), Vector3D(0, 1, 0));
    plane_ptr->set_material(yellow_ptr);
    add_object(plane_ptr);

    // Rectangles
    rectangle_ptr = new Rectangle(Vector3D(0,0,0), Vector3D(2,0,0), Vector3D(0,4,0), sampler_ptr->clone());
    rectangle_ptr->set_material(green_ptr->clone()->clone());
    add_object(rectangle_ptr);

    // Triangles
    Triangle* tri_ptr = new Triangle(Vector3D(5,0,0), Vector3D(7,0,0), Vector3D(5,4,0));
    tri_ptr->set_material(red_ptr->clone());
    add_object(tri_ptr);

    // Spheres
    Sphere* sphere_ptr = new Sphere(Vector3D(-5, 2, 0), 2.0);
    sphere_ptr->set_material(blue_ptr);
    add_object(sphere_ptr);
}
