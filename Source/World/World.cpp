#include "World.h"
// Utilities
#include <iostream>
#include <fstream>
#include <string>
#include "string.h"
#include <vector>
#include "Constants.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "Image.h"
// Tracers
#include "RayCast.h"
#include "Whitted.h"
#include "AreaLighting.h"
// GeometricObjects
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "TriangleMesh.h"
#include "Rectangle.h"
#include "FastTriMesh.h"
#include "Instance.h"
#include "Deformed.h"
#include "CSG.h"
#include "SmoothMesh.h"
// Cameras
#include "Pinhole.h"
#include "Orthographic.h"
// Materials
#include "Matte.h"
#include "Phong.h"
#include "Reflective.h"
#include "Transparent.h"
#include "Emmissive.h"
#include "SV_Matte.h"
// Lights
#include "Ambient.h"
#include "Directional.h"
#include "Point.h"
#include "AreaLight.h"
// Acceleration
#include "BVH.h"
// Samplers
#include "Jittered.h"
// Mappings
#include "RectangularMap.h"
// Textures
#include "ImageTexture.h"
#include "ConstantColor.h"
#include "Checker.h"
#include "Noise.h"

#include "Builds.h"

using namespace std;

// Big 6
World::World(void):
    vp(), 
    background_color(BLACK), 
    tracer_ptr(NULL), 
    ambient_ptr(new Ambient), 
    camera_ptr(NULL),
    num_rays(0) {}
World::~World(void){
    delete_tracer();
    delete_ambient();
    delete_lights();
    delete_objects();
    delete_camera();
}
void World::delete_tracer(void){
    if(tracer_ptr){
        delete tracer_ptr;
        tracer_ptr = NULL;
    }
}
void World::delete_ambient(){
    if (ambient_ptr){
        delete ambient_ptr;
        ambient_ptr = NULL;
    }
}
void World::delete_lights(){
    for (int j = 0; j < lights.size(); j++) {
        if(lights[j]){
            delete lights[j];
            lights[j] = NULL;
        }
	}
    lights.erase(lights.begin(), lights.end());
}
void World::delete_objects(void) {
	for (int j = 0; j < objects.size(); j++) {
        if(objects[j]){
            delete objects[j];
            objects[j] = NULL;
        }
	}
	objects.erase(objects.begin(), objects.end());
}
void World::delete_camera(void){
    if(camera_ptr){
        delete camera_ptr;
        camera_ptr = NULL;
    }
}

// Getters & Setters
void World::set_tracer_ptr(Tracer* tracer_ptr){
    this->tracer_ptr = tracer_ptr;
}
const Tracer* World::get_tracer_ptr(void) const{
    return tracer_ptr;
}
void World::set_ambient(Light* ambient_ptr){
    this->ambient_ptr = ambient_ptr;
}
const Light* World::get_ambient(void) const{
    return ambient_ptr;
}
void World::set_camera(Camera* camera_ptr){
    this->camera_ptr = camera_ptr;
}
// const Camera* World::get_camera(void) const{
//     return camera_ptr;
// }
const vector<Light*>& World::get_lights(void) const{
    return lights;
}
// const vector<GeometricObject*>& World::get_objects(void) const{
//     return objects;
// }
void World::set_background_color(const Vector3D& color){
    this->background_color = color;
}
Vector3D World::get_background_color(void) const{
    return background_color;
}
void World::set_vp(const ViewPlane& vp){
    this->vp = vp;
}
ViewPlane World::get_vp(void) const{
    return vp;
}

// Functions
void World::add_object(GeometricObject* object_ptr){
    objects.push_back(object_ptr);
}
void World::add_light(Light* light){
    lights.push_back(light);
}
void World::render_scene(void) const{
    if (camera_ptr){
        camera_ptr->render_scene(*this);
        return;
    }
    Vector3D color;
    Ray ray;
    ray.d = Vector3D(0, 0, -1);
    double x, y, zw = 100.0;

    ofstream file;
    file.open("image.ppm");
    file << "P3 " << vp.hres << " " << vp.vres << " " << 255.0 << "\n";

    for (int r = 0; r < vp.vres; r++){
        for (int c = 0; c < vp.hres; c++){
            x = vp.pixelSize * (c - 0.5 * (vp.hres - 1.0));
            y = vp.pixelSize * (r - 0.5 * (vp.vres - 1.0));
            ray.o = Vector3D(x, y, zw);
            color = max_to_one(tracer_ptr->trace_ray(ray));
            color = color * 255;
            file << (int) color.x << " " << (int) color.y << " " << (int) color.z << "\t";
        }
        file << "\n";
    }
    file.close();
}
Vector3D World::max_to_one(const Vector3D& c) const{
    double max_value = MAX(c.x, MAX(c.y, c.z));
    if (max_value > 1.0){
        return (c / max_value);
    } else {
        return c;
    }
}
Vector3D World::clamp_to_color(const Vector3D& color) const{
    Vector3D c(color);
    if (c.x > 1.0 || c.y > 1.0 || c.z > 1.0){
        c = RED;
    }
    return c;
}
ShadeRec World::hit_objects(const Ray& ray){
    ShadeRec sr(*this);
    double t;
    Vector3D normal;
    Vector3D local_hit_point;
    double tmin = KHUGEVALUE;
    int numObjects = objects.size();

    for (int j = 0; j < numObjects; j++){
        num_rays++;
        if ( objects[j]->hit(ray, t, sr) && (t < tmin) ){
            sr.hit_an_object = true;
            tmin = t;
            sr.material_ptr = objects[j]->get_material();
            sr.hit_point = ray.o + t * ray.d;
            normal = sr.normal;
            local_hit_point = sr.local_hit_point;
        }
    }
    if (sr.hit_an_object){
        sr.t = tmin;
        sr.normal = normal;
        sr.local_hit_point = local_hit_point;
    }
    return sr;
}

void World::build(void){
    // orthographic_build();
    // cow_mesh_bvh_build();
    //shadow_bvh_build();
    //spheres_bvh_build();
    //cow_mesh_bvh_2_build();
    //cow_mesh_no_bvh_2_build();
    // spheres_bvh_build();
    // mirror_build();
    //transparent_build();
    //area_light_build();
    //face_mesh_bvh_build();
    //fast_mesh_build();
    //texture_build();
    //checker_build();
    // glass_face_build();
    build1();
}