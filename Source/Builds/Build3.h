#include "BuildIncludes.h"

void World::build_3(void){
    // View Plane
    int lw = 800;
    vp = ViewPlane(lw, lw, 1.0, 1.0, 10);

    // Sampler
    int n = 10;
    int num_samples = n*n;
    int num_sets = 83;
    Sampler* sampler_ptr = new Jittered(num_samples, num_sets);
    vp.set_sampler(sampler_ptr);

    // Ambient Light
    float light_radiance = 4.0;
    ambient_ptr = new Ambient(light_radiance * 1.0, WHITE);

    // Background color
    background_color = CYAN / 3;

    // Tracer
    tracer_ptr = new Whitted(this);

    // Lights
    Point* point_ptr = new Point(light_radiance * 2.0, WHITE, Vector3D(10,10,10));
    add_light(point_ptr);

    // Camera: Pinhole
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->up = Vector3D(0,-1,0);
    Vector3D eye1(10,2,-3);
    pinhole_ptr->eye = eye1;
    Vector3D lookat1(0,0,0);
    pinhole_ptr->lookat = lookat1;
    float distance1 = 20;
    pinhole_ptr->distance = distance1;
    pinhole_ptr->compute_uvw();
    pinhole_ptr->zoom = 80;
    this->camera_ptr = pinhole_ptr;

    vector<GeometricObject*> bvh_objects;

    Plane* plane_ptr = new Plane(Vector3D(0, -0.6, 0), Vector3D(0, 1, 0));
    Matte* yellow_ptr = new Matte(0.25, 0.75, GREEN / 2);
    plane_ptr->set_material(yellow_ptr);
    bvh_objects.push_back(plane_ptr);

    // Transparent
    // Sphere* sphere_ptr = new Sphere(Vector3D(5, 1, -1), .4);
    // Transparent* trans_ptr = new Transparent(0.0, 0.0, 0.2, 200, BLACK, 0.8, 0.9, .95);
    // sphere_ptr->set_material(trans_ptr);
    // bvh_objects.push_back(sphere_ptr);

    // COWS
    GeometricObject* mesh;
    mesh = new SmoothMesh("./Resources/cow.obj");

    Instance* instance = new Instance(mesh);
    instance->set_material(new Phong(0.25, 0.75, 0.5, 3.0, WHITE/2.0));
    instance->translate(Vector3D(0,0,0));
    instance->set_bounding_box();
    bvh_objects.push_back(instance);

    instance = new Instance(mesh);
    instance->set_material(new Matte(0.25, 0.75, RED / 2));
    instance->translate(Vector3D(0,0,-1));
    instance->set_bounding_box();
    bvh_objects.push_back(instance);

    instance = new Instance(mesh);
    instance->set_material(new Phong(0.25, 0.25, 0.8, 2.0, BLACK/2.0));
    instance->translate(Vector3D(2,0,-1));
    instance->set_bounding_box();
    bvh_objects.push_back(instance);

    instance = new Instance(mesh);
    instance->set_material(new Phong(0.25, 0.75, 0.5, 3.0, Vector3D(.4,.2,.2)));
    instance->translate(Vector3D(2,0,1));
    instance->set_bounding_box();
    bvh_objects.push_back(instance);

    // Mirror
    instance = new Instance(mesh);
    instance->set_material(new Reflective(0.0, 0.0, 0.0, 1.0, Vector3D(.8, 1, .8), .8));
    instance->translate(Vector3D(0,0,1));
    instance->set_bounding_box();
    bvh_objects.push_back(instance);

    // Glass
    instance = new Instance(mesh);
    instance->set_material(new Transparent(0.0, 0.0, 0.2, 200, BLACK, 0.8, 0.9, .95));
    instance->translate(Vector3D(2,0,0));
    instance->set_bounding_box();
    bvh_objects.push_back(instance);

    // BVH
    BVH* bvh = new BVH(bvh_objects, bvh_objects.size(), 0);
    add_object(bvh);
}
