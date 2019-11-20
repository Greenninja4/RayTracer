#include "BuildIncludes.h"

void World::fast_mesh_build(void){
    float light_radiance = 4.0; 

    // View Plane
    int lw = 800;
    vp = ViewPlane(lw, lw, 1.0, 1.0);

    // Ambient Light
    ambient_ptr = new Ambient(light_radiance * 0.5, WHITE);

    // Background color
    background_color = GREEN / 10;

    // Tracer
    tracer_ptr = new RayCast(this);

    // Lights
    Point* point_ptr = new Point(light_radiance * 1.0, WHITE, Vector3D(0, 0, -2));
    add_light(point_ptr);

    //Camera
    // Camera: Pinhole
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->up = Vector3D(0, -1, 0);
    Vector3D eye1(0, 0, -2);
    pinhole_ptr->eye = eye1;
    Vector3D lookat1(0, 0, -1);
    pinhole_ptr->lookat = lookat1;
    float distance1 = 100;
    pinhole_ptr->distance = distance1;
    pinhole_ptr->compute_uvw();
    pinhole_ptr->zoom = 8*4;
    this->camera_ptr = pinhole_ptr;


    vector<GeometricObject*> bvh_objects;

    Plane* plane_ptr = new Plane(Vector3D(0, -0.6, 0), Vector3D(0.0, 0.1, 0.02));
    Matte* yellow_ptr = new Matte(0.25, 0.75, YELLOW);
    plane_ptr->set_material(yellow_ptr);
    bvh_objects.push_back(plane_ptr);

    FastTriMesh* mesh = new FastTriMesh("./Resources/face.obj");
    Phong* blue_ptr = new Phong(0.25, 0.75, 0.5, 3.0, BLUE);
    mesh->set_material(blue_ptr);
    bvh_objects.push_back(mesh);

    BVH* bvh = new BVH(bvh_objects, bvh_objects.size(), 0);
    add_object(bvh);
}