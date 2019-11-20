#include "BuildIncludes.h"

void World::build_0(void){
    // View Plane
    int size = 800;
    vp = ViewPlane(size, size, 0.05, 1.0);

    // Background color
    background_color = GREEN / 10;

    // Light
    float light_radiance = 4.0;
    Directional* directional_ptr = new Directional(light_radiance, WHITE, Vector3D(-1,-1,1));
    add_light(directional_ptr);

    // Camera: Orthographic
    Orthographic* orthographic_ptr = new Orthographic();
    Vector3D eye1(0,0,100);
    orthographic_ptr->eye = eye1;
    this->camera_ptr = orthographic_ptr;

    // Tracer
    tracer_ptr = new RayCast(this);

    // Materials
    Phong* red_ptr = new Phong(0.25, 0.75, 0.5, 3.0, RED);
    Phong* green_ptr = new Phong(0.25, 0.75, 0.5, 3.0, GREEN);
    Phong* blue_ptr = new Phong(0.25, 0.75, 0.5, 3.0, BLUE);
    Phong* cyan_ptr = new Phong(0.25, 0.75, 0.5, 3.0, CYAN);
    Phong* magenta_ptr = new Phong(0.25, 0.75, 0.5, 3.0, MAGENTA);
    Phong* yellow_ptr = new Phong(0.25, 0.75, 0.5, 3.0, YELLOW);

    // Geometric Objects
    GeometricObject* obj_ptr;

    // Spheres
    float radius = 10.0;
    obj_ptr = new Sphere(Vector3D(radius*sin(0), radius*cos(0), 0), 1.5);
    obj_ptr->set_material(red_ptr);
    add_object(obj_ptr);

    obj_ptr = new Sphere(Vector3D(radius*sin(PI/3.0), radius*cos(PI/3.0), 0), 1.5);
    obj_ptr->set_material(magenta_ptr);
    add_object(obj_ptr);

    obj_ptr = new Sphere(Vector3D(radius*sin(2.0*PI/3.0), radius*cos(2.0*PI/3.0), 0), 1.5);
    obj_ptr->set_material(blue_ptr);
    add_object(obj_ptr);

    obj_ptr = new Sphere(Vector3D(radius*sin(PI), radius*cos(PI), 0), 1.5);
    obj_ptr->set_material(cyan_ptr);
    add_object(obj_ptr);

    obj_ptr = new Sphere(Vector3D(radius*sin(4.0*PI/3.0), radius*cos(4.0*PI/3.0), 0), 1.5);
    obj_ptr->set_material(green_ptr);
    add_object(obj_ptr);

    obj_ptr = new Sphere(Vector3D(radius*sin(5.0*PI/3.0), radius*cos(5.0*PI/3.0), 0), 1.5);
    obj_ptr->set_material(yellow_ptr);
    add_object(obj_ptr);

    obj_ptr = new Sphere(Vector3D(radius*sin(PI/6.0 + 0), radius*cos(PI/6.0 + 0), 0), 1.5);
    obj_ptr->set_material(new Phong(0.25, 0.75, 0.5, 3.0, RED + MAGENTA));
    add_object(obj_ptr);

    obj_ptr = new Sphere(Vector3D(radius*sin(PI/6.0 + PI/3.0), radius*cos(PI/6.0 + PI/3.0), 0), 1.5);
    obj_ptr->set_material(new Phong(0.25, 0.75, 0.5, 3.0, BLUE + MAGENTA));
    add_object(obj_ptr);

    obj_ptr = new Sphere(Vector3D(radius*sin(PI/6.0 + 2.0*PI/3.0), radius*cos(PI/6.0 + 2.0*PI/3.0), 0), 1.5);
    obj_ptr->set_material(new Phong(0.25, 0.75, 0.5, 3.0, BLUE + CYAN));
    add_object(obj_ptr);

    obj_ptr = new Sphere(Vector3D(radius*sin(PI/6.0 + PI), radius*cos(PI/6.0 + PI), 0), 1.5);
    obj_ptr->set_material(new Phong(0.25, 0.75, 0.5, 3.0, GREEN + CYAN));
    add_object(obj_ptr);

    obj_ptr = new Sphere(Vector3D(radius*sin(PI/6.0 + 4.0*PI/3.0), radius*cos(PI/6.0 + 4.0*PI/3.0), 0), 1.5);
    obj_ptr->set_material(new Phong(0.25, 0.75, 0.5, 3.0, GREEN + YELLOW));
    add_object(obj_ptr);

    obj_ptr = new Sphere(Vector3D(radius*sin(PI/6.0 + 5.0*PI/3.0), radius*cos(PI/6.0 + 5.0*PI/3.0), 0), 1.5);
    obj_ptr->set_material(new Phong(0.25, 0.75, 0.5, 3.0, RED + YELLOW));
    add_object(obj_ptr);

    radius = 6;
    for (int i = 0; i < 12; i++){
        float angle = 2*PI*(i/12.0);
        obj_ptr = new Sphere(Vector3D(radius*sin(angle), radius*cos(angle), radius*(sin(angle))), 1.0);
        obj_ptr->set_material(new Phong(0.25, 0.75, 0.5, 3.0, WHITE*(i/12.0)));
        add_object(obj_ptr);
    }

    // Triangles
    Triangle* tri_ptr = new Triangle(Vector3D(15,0,0), Vector3D(0,15,0), Vector3D(15,15,-25));
    tri_ptr->set_material(green_ptr->clone());
    add_object(tri_ptr);

    tri_ptr = new Triangle(Vector3D(-15,0,0), Vector3D(0,-15,0), Vector3D(-15,-15,25));
    tri_ptr->set_material(red_ptr->clone());
    add_object(tri_ptr);

    // Rectangles
    Rectangle* rectangle_ptr = new Rectangle(Vector3D(5,-15,0), Vector3D(10,0,0), Vector3D(0,5,0));
    rectangle_ptr->set_material(blue_ptr->clone());
    add_object(rectangle_ptr);

    rectangle_ptr = new Rectangle(Vector3D(-15,5,0), Vector3D(5,0,0), Vector3D(0,10,0));
    rectangle_ptr->set_material(yellow_ptr->clone());
    add_object(rectangle_ptr);

}
