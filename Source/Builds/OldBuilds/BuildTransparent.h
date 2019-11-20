#include "BuildIncludes.h"

void World::transparent_build(void){
    float light_radiance = 4.0;

    // View Plane
    vp = ViewPlane(1000, 1000, 1.0, 1.0, 8);

    // Ambient Light
    ambient_ptr = new Ambient(light_radiance * 0.5, WHITE);

    // Background color
    background_color = GREEN / 10;

    // Tracer
    tracer_ptr = new Whitted(this);

    // Lights
    // Directional* directional_ptr = new Directional(light_radiance, WHITE, Vector3D(1, 1, 2));
    // add_light(directional_ptr);
    Point* point_ptr = new Point(light_radiance * 1.0, WHITE, Vector3D(12, 15, 30));
    add_light(point_ptr);

    // Camera
    // Camera: Pinhole
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->up = Vector3D(0, -1, 0);
    pinhole_ptr->zoom = 0.5;
    Vector3D eye1(2, 2.5, 15);
    pinhole_ptr->eye = eye1;
    Vector3D lookat1(0 + 3, 2.5, 0);
    pinhole_ptr->lookat = lookat1;
    float distance1 = 700;
    pinhole_ptr->distance = distance1;
    pinhole_ptr->compute_uvw();
    this->camera_ptr = pinhole_ptr;

    // Materials
    Matte* yellow_ptr = new Matte(0.25, 0.75, YELLOW);
    Phong* red_ptr = new Phong(0.25, 0.75, 0.5, 3.0, RED);
    Matte* green_ptr = new Matte(0.25, 0.75, GREEN);
    //Matte* blue_ptr = new Matte(0.25, 0.75, BLUE);

    // BVH Objects
    vector<GeometricObject*> bvh_objects;

    // Objects

    int num = 10;
    for (int i = 0; i < num; i++){
        for (int j = 0; j < num; j++){
            for (int k = 0; k < num; k++){
                Sphere* sphere_ptr = new Sphere(Vector3D(2*i, 2*j - num/2, -2*k), 0.3);
                if (i > num/2){
                    sphere_ptr->set_material(green_ptr->clone());
                } else {
                    sphere_ptr->set_material(red_ptr->clone());
                }
                bvh_objects.push_back(sphere_ptr);
            }
        }
    }

    Sphere* sphere_ptr = new Sphere(Vector3D(0.0, 2.4, 0), 1.5);
    sphere_ptr->set_material(red_ptr);
    bvh_objects.push_back(sphere_ptr);

    Triangle* tri_ptr = new Triangle(Vector3D(1.5, -0.5, 1.8), Vector3D(7.5, -0.5, -9.00), Vector3D(2.35, 5.8, 1.4));
    tri_ptr->set_material(green_ptr);
    bvh_objects.push_back(tri_ptr);

    // tri_ptr = new Triangle(Vector3D(-10, 0, 0), Vector3D(10, 0, 0), Vector3D(0, 10, 0));
    // tri_ptr->set_material(blue_ptr);
    // bvh_objects.push_back(tri_ptr);

    Plane* plane_ptr = new Plane(Vector3D(0, -0.5, 0), Vector3D(0, 1, 0));
    plane_ptr->set_material(yellow_ptr);
    bvh_objects.push_back(plane_ptr);

    // GLASS/TRANSPARENT SPHERE
    sphere_ptr = new Sphere(Vector3D(2.0, 5, 6), 2);
    Transparent* trans_ptr = new Transparent(0.0, 0.0, 0.2, 2000, BLACK, 0.1, 0.9, .75);
    sphere_ptr->set_material(trans_ptr);
    bvh_objects.push_back(sphere_ptr);

    // GLASS/TRANSPARENT SPHERE 2
    sphere_ptr = new Sphere(Vector3D(8.0, 5, 6), 2);
    trans_ptr = new Transparent(0.0, 0.0, 0.2, 2000, BLACK, 0.1, 0.9, 1.5);
    sphere_ptr->set_material(trans_ptr);
    bvh_objects.push_back(sphere_ptr);

    BVH* bvh = new BVH(bvh_objects, bvh_objects.size(), 0);
    add_object(bvh);
}