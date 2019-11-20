#include "BuildIncludes.h"

void World::cow_mesh_bvh_build(void){
    float light_radiance = 4.0; 

    // View Plane
    vp = ViewPlane(100, 100, 1.0, 1.0);

    // Ambient Light
    ambient_ptr = new Ambient(light_radiance * 0.5, WHITE);

    // Background color
    background_color = GREEN / 10;

    // Tracer
    tracer_ptr = new RayCast(this);

    // Lights
    Point* point_ptr = new Point(light_radiance * 1.0, WHITE, Vector3D(1, 1, 1));
    add_light(point_ptr);

    // Camera
    // // Camera: Pinhole
    // Pinhole* pinhole_ptr = new Pinhole();
    // pinhole_ptr->up = Vector3D(0, -1, 0);
    // Vector3D eye1(0, -10, 0);
    // pinhole_ptr->eye = eye1;
    // Vector3D lookat1(0, 0, 0);
    // pinhole_ptr->lookat = lookat1;
    // float distance1 = 100;
    // pinhole_ptr->distance = distance1;
    // pinhole_ptr->compute_uvw();
    // pinhole_ptr->zoom = 1;
    // this->camera_ptr = pinhole_ptr;

    // Camera: Orthographic
    Orthographic* orthographic_ptr = new Orthographic();
    Vector3D eye1(0, 0, 2);
    orthographic_ptr->eye = eye1;
    Vector3D lookat1(0, 0, -1);
    orthographic_ptr->lookat = lookat1;
    float distance1 = 2;
    orthographic_ptr->distance = distance1;
    orthographic_ptr->up = Vector3D(0, -1, 0);
    orthographic_ptr->zoom = 15;
    orthographic_ptr->compute_uvw();
    this->camera_ptr = orthographic_ptr;

    //Phong* yellow_phong_ptr = new Phong(0.25, 0.75, 0.5, 3.0, YELLOW);

    // Sphere *sphere_ptr = new Sphere(Vector3D(0, 0, 0), 1.0);
    // Matte* red_ptr = new Matte(0.25, 0.75, RED);
    // sphere_ptr->set_material(red_ptr);
    // add_object(sphere_ptr);

    vector<GeometricObject*> bvh_objects;

    Triangle* tri_ptr = new Triangle(Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, 10.0, 0.0), Vector3D(10, 10, 0));
    Matte* green_ptr = new Matte(0.25, 0.75, GREEN);
    tri_ptr->set_material(green_ptr);
    bvh_objects.push_back(tri_ptr);

    Plane* plane_ptr = new Plane(Vector3D(0, 0.0, 0), Vector3D(0.1, 0.1, 0));
    Matte* yellow_ptr = new Matte(0.25, 0.75, YELLOW);
    plane_ptr->set_material(yellow_ptr);
    bvh_objects.push_back(plane_ptr);

    TriangleMesh* mesh = new TriangleMesh("./Resources/cow.obj");
    Matte* blue_ptr = new Matte(0.25, 0.75, BLUE);
    mesh->set_material(blue_ptr);
    bvh_objects.push_back(mesh);


    BVH* bvh = new BVH(bvh_objects, bvh_objects.size(), 0);
    add_object(bvh);
}


void World::cow_mesh_bvh_2_build(void){
    float light_radiance = 4.0; 

    // View Plane
    vp = ViewPlane(300, 300, 1.0, 1.0);

    // Ambient Light
    ambient_ptr = new Ambient(light_radiance * 0.5, WHITE);

    // Background color
    background_color = GREEN / 10;

    // Tracer
    tracer_ptr = new RayCast(this);

    // Lights
    Point* point_ptr = new Point(light_radiance * 1.0, WHITE, Vector3D(1, 1, 1));
    add_light(point_ptr);

    //Camera
    // Camera: Pinhole
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->up = Vector3D(0, -1, 0);
    Vector3D eye1(0, 0, 2);
    pinhole_ptr->eye = eye1;
    Vector3D lookat1(0, 0, -1);
    pinhole_ptr->lookat = lookat1;
    float distance1 = 100;
    pinhole_ptr->distance = distance1;
    pinhole_ptr->compute_uvw();
    pinhole_ptr->zoom = 1;
    this->camera_ptr = pinhole_ptr;

    // // Camera: Orthographic
    // Orthographic* orthographic_ptr = new Orthographic();
    // Vector3D eye1(0, 0, 2);
    // orthographic_ptr->eye = eye1;
    // Vector3D lookat1(0, 0, -1);
    // orthographic_ptr->lookat = lookat1;
    // float distance1 = 2;
    // orthographic_ptr->distance = distance1;
    // orthographic_ptr->up = Vector3D(0, -1, 0);
    // orthographic_ptr->zoom = 15;
    // orthographic_ptr->compute_uvw();
    // this->camera_ptr = orthographic_ptr;

    //Phong* yellow_phong_ptr = new Phong(0.25, 0.75, 0.5, 3.0, YELLOW);

    // Sphere *sphere_ptr = new Sphere(Vector3D(0, 0, 0), 1.0);
    // Matte* red_ptr = new Matte(0.25, 0.75, RED);
    // sphere_ptr->set_material(red_ptr);
    // add_object(sphere_ptr);

    vector<GeometricObject*> bvh_objects;

    // Triangle* tri_ptr = new Triangle(Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, 10.0, 0.0), Vector3D(10, 10, 0));
    // Matte* green_ptr = new Matte(0.25, 0.75, GREEN);
    // tri_ptr->set_material(green_ptr);
    // bvh_objects.push_back(tri_ptr);

    Plane* plane_ptr = new Plane(Vector3D(0, -0.6, 0), Vector3D(0.0, 0.1, 0.02));
    Matte* yellow_ptr = new Matte(0.25, 0.75, YELLOW);
    plane_ptr->set_material(yellow_ptr);
    bvh_objects.push_back(plane_ptr);

    TriangleMesh* mesh = new TriangleMesh("./Resources/cow.obj");
    //Matte* blue_ptr = new Matte(0.25, 0.75, BLUE);
    Phong* blue_ptr = new Phong(0.25, 0.75, 0.5, 3.0, BLUE);
    mesh->set_material(blue_ptr);
    bvh_objects.push_back(mesh);


    BVH* bvh = new BVH(bvh_objects, bvh_objects.size(), 0);
    add_object(bvh);
}