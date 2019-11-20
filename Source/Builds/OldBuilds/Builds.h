#include "BuildIncludes.h"

void World::texture_build(void){
    // View Plane
    int lw = 400;
    vp = ViewPlane(lw, lw, 1.0, 1.0);
    // Background color
    background_color = GREEN / 10;
    // Tracer
    tracer_ptr = new RayCast(this);
    // Lights
    ambient_ptr = new Ambient(0.5, WHITE);
    Directional* dir_ptr = new Directional(2.5, WHITE, Vector3D(-15, 20, 25));
    add_light(dir_ptr);
    // Camera: Pinhole
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->up = Vector3D(0, -1, 0);
    Vector3D eye1(-20, 10, 20);
    pinhole_ptr->eye = eye1;
    Vector3D lookat1(0, 2, 0);
    pinhole_ptr->lookat = lookat1;
    float distance1 = 1000;
    pinhole_ptr->distance = distance1;
    pinhole_ptr->compute_uvw();
    pinhole_ptr->zoom = 1;
    this->camera_ptr = pinhole_ptr;


    // // image
    // Image* image_ptr = new Image;
    // image_ptr->read_ppm_file("face.ppm");
    // // Mapping
    // RectangularMap* map_ptr = new RectangularMap;
    // // Image texture 
    // ImageTexture* texture_ptr = new ImageTexture(image_ptr, map_ptr);
    // // Spatially Varying Material
    // SV_Matte* sv_matte_ptr = new SV_Matte(0.4, 0.95, texture_ptr);


    // Image texture 
    ConstantColor* texture_ptr = new ConstantColor(RED);
    // Spatially Varying Material
    SV_Matte* sv_matte_ptr = new SV_Matte(0.4, 0.95, texture_ptr);


    // Rectangle  
    Rectangle* rectangle_ptr = new Rectangle(Vector3D(-3,0,0), Vector3D(2,0,0), Vector3D(0,4,0));
    rectangle_ptr->set_material(sv_matte_ptr);
    add_object(rectangle_ptr);
    // Ground Plane 
    Matte* matte_ptr = new Matte(0.25, 0.5, 1.0);
    Plane* plane_ptr = new Plane(Vector3D(0, 0, 0), Vector3D(0, 1, 0));
    plane_ptr->set_material(matte_ptr);
    add_object(plane_ptr);

}

void World::animate(void){
    float light_radiance = 6.0; 

    // View Plane
    int lw = 300;
    vp = ViewPlane(lw, lw, 1.0, 1.0);

    // Ambient Light
    ambient_ptr = new Ambient(light_radiance * 0.5, WHITE);

    // Background color
    background_color = GREEN / 10;

    // Tracer
    tracer_ptr = new RayCast(this);

    // Lights
    Point* point_ptr = new Point(light_radiance * 1.0, WHITE, Vector3D(0, 1, -2));
    add_light(point_ptr);
    point_ptr = new Point(light_radiance * 1.0, WHITE, Vector3D(0, 1, 2));
    add_light(point_ptr);

    //Camera
    // Camera: Pinhole
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->up = Vector3D(0, -1, 0);
    Vector3D eye1(0, 0, 0);
    pinhole_ptr->eye = eye1;
    Vector3D lookat1(0, 0, -1);
    pinhole_ptr->lookat = lookat1;
    float distance1 = 100;
    pinhole_ptr->distance = distance1;
    pinhole_ptr->compute_uvw();
    pinhole_ptr->zoom = 1;
    this->camera_ptr = pinhole_ptr;

    vector<GeometricObject*> bvh_objects;

    Plane* plane_ptr = new Plane(Vector3D(0, -0.6, 0), Vector3D(0.0, 0.1, 0.0));
    Matte* yellow_ptr = new Matte(0.25, 0.75, YELLOW);
    plane_ptr->set_material(yellow_ptr);
    bvh_objects.push_back(plane_ptr);

    Deformed* mesh1 = new Deformed("./Resources/face.obj");
    Phong* blue_ptr = new Phong(0.25, 0.75, 0.5, 3.0, BLUE);
    mesh1->set_material(blue_ptr);
    // bvh_objects.push_back(mesh1);

    // Instance* face = new Instance(mesh1);
    // Matte* green_ptr = new Matte(0.25, 0.75, GREEN);
    // face->set_material(green_ptr);
    // face->translate(Vector3D(0, 0, -0.3));
    // face->scale(1.5);
    // face->set_bounding_box();
    // bvh_objects.push_back(face);

    // face = new Instance(mesh1);
    // Matte* r_ptr = new Matte(0.25, 0.75, RED);
    // face->set_material(r_ptr);
    // face->translate(Vector3D(0, 0, 0.3));
    // face->scale(1.5);
    // face->set_bounding_box();
    // bvh_objects.push_back(face);

    
    // Create Materials
    vector<Material*> materials;
    Material* material_ptr = new Matte(0.25, 0.75, RED);
    materials.push_back(material_ptr);
    material_ptr = new Matte(0.25, 0.75, YELLOW);
    materials.push_back(material_ptr);
    material_ptr = new Matte(0.25, 0.75, GREEN);
    materials.push_back(material_ptr);
    material_ptr = new Matte(0.25, 0.75, BLUE);
    materials.push_back(material_ptr);
    material_ptr = new Matte(0.25, 0.75, CYAN);
    materials.push_back(material_ptr);
    material_ptr = new Matte(0.25, 0.75, MAGENTA);
    materials.push_back(material_ptr);
    material_ptr = new Matte(0.25, 0.75, BLACK);
    materials.push_back(material_ptr);
    material_ptr = new Matte(0.25, 0.75, WHITE);
    materials.push_back(material_ptr);

    // Load mesh
    // FastTriMesh* mesh = new FastTriMesh("./Resources/face.obj");
    // mesh->set_material(material_ptr);

    Sphere* mesh = new Sphere(Vector3D(0,0,0), 0.1);

    // Create instances
    int ni = 10;
    vector<Instance*> instances(ni);
    // for (int i = 0; i < ni; i++){
    //     Instance* instance = new Instance(mesh);
    //     instance->set_material(materials[rand() % materials.size()]);
    //     instance->translate(Vector3D(i*.1,0,0.4));
    //     //instance->scale(1);
    //     //float theta = ((float)i / ni) * 2 * PI;
    //     //instance->rotate_y(theta);
    //     instance->set_bounding_box();
    //     bvh_objects.push_back(instance);
    // }

    for (int x = 0; x < ni; x++){
        for (int y = 0; y < ni; y++){
            for (int z = 0; z < ni; z++){
                Instance* instance = new Instance(mesh);
                instance->set_material(materials[rand() % materials.size()]);
                float z_coor = 0.4;
                if (z > (float)ni/2){
                    z_coor = -0.4;
                }
                instance->translate(Vector3D(x*.1,y*.1,z_coor));
                //instance->scale(1);
                //float theta = ((float)i / ni) * 2 * PI;
                //instance->rotate_y(theta);
                instance->set_bounding_box();
                bvh_objects.push_back(instance);
            }
        }
    }

    // Generate BVH build and add to world
    BVH* bvh = new BVH(bvh_objects, bvh_objects.size(), 0);
    add_object(bvh);

    // Animation settings
    int num_frames = 200;
    string folder = "anim/";
    string ppm = ".ppm";
    string frame_name = "0.ppm";

    // Generate camera traversal
    vector<Vector3D> cam_pos(num_frames);
    cam_pos[0] = eye1;
    vector<Vector3D> look_pos(num_frames);
    look_pos[0] = lookat1;
    for (int i = 1; i < num_frames; i++){
        float theta = ((float)i / num_frames) * 2 * PI;
        Matrix rot = Matrix();
        rot.set_to_rot(theta, "y");
        // cam_pos[i] = rot * cam_pos[0];
        look_pos[i] = rot * look_pos[0];
    }

    // Render images
    for (int i = 0; i < num_frames; i++){
        // Change camera position
        //pinhole_ptr->eye = cam_pos[i];
        pinhole_ptr->lookat = look_pos[i];
        pinhole_ptr->compute_uvw();

        // Render and save scene
        this->render_scene();
        rename("image.ppm", frame_name.c_str());
        frame_name = folder + to_string(i) + ppm;
        cout << frame_name << endl;
    }

}

void World::checker_build(void){
    
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
    // point_ptr = new Point(light_radiance * 1.0, WHITE, Vector3D(7, 2, 6));
    // add_light(point_ptr);

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

    // geometric Objects

    Sphere* sphere_ptr = new Sphere(Vector3D(0.0, 2.4, 0), 1.5);
    sphere_ptr->set_material(red_ptr);
    bvh_objects.push_back(sphere_ptr);

    Triangle* tri_ptr = new Triangle(Vector3D(1.5, -0.5, 1.8), Vector3D(7.5, -0.5, -9.00), Vector3D(2.35, 5.8, 1.4));
    tri_ptr->set_material(green_ptr);
    bvh_objects.push_back(tri_ptr);

    Plane* plane_ptr = new Plane(Vector3D(0, -0.5, 0), Vector3D(0, 1, 0));
    plane_ptr->set_material(yellow_ptr);
    bvh_objects.push_back(plane_ptr);

    // CHECKER SPHERE
    sphere_ptr = new Sphere(Vector3D(-4.0, 5, 6), 2);
    Checker* checker_ptr = new Checker(WHITE, BLACK, .2);
    SV_Matte* sv_matte = new SV_Matte(.5, .5, checker_ptr);
    sphere_ptr->set_material(sv_matte);
    bvh_objects.push_back(sphere_ptr);

    // // NOISE SPHERE
    // sphere_ptr = new Sphere(Vector3D(0.0, 8, 6), 3);
    // Noise* noise_ptr = new Noise(WHITE, BLACK, 30, sphere_ptr->get_bounding_box());
    // sv_matte = new SV_Matte(.5, .5, noise_ptr);
    // sphere_ptr->set_material(sv_matte);
    // bvh_objects.push_back(sphere_ptr);

    // CSG
    Sphere* s1 = new Sphere(Vector3D(8, 10, 6), 1);
    Phong* mat = new Phong(0.25, 0.75, 0.5, 3.0, RED);
    s1->set_material(mat);
    Sphere* s2 = new Sphere(Vector3D(7, 10, 6), 1);
    mat = new Phong(0.25, 0.75, 0.5, 3.0, GREEN);
    s2->set_material(mat);
    CSG* csg = new CSG(s1, s2, 0);
    csg->set_material(mat->clone());
    bvh_objects.push_back(csg);

    s1 = new Sphere(Vector3D(8, 7, 6), 1);
    mat = new Phong(0.25, 0.75, 0.5, 3.0, RED);
    s1->set_material(mat);
    s2 = new Sphere(Vector3D(7, 7, 6), 1);
    mat = new Phong(0.25, 0.75, 0.5, 3.0, GREEN);
    s2->set_material(mat);
    csg = new CSG(s1, s2, 1);
    csg->set_material(mat->clone());
    bvh_objects.push_back(csg);

    s1 = new Sphere(Vector3D(8, 4, 6), 1);
    mat = new Phong(0.25, 0.75, 0.5, 3.0, RED);
    s1->set_material(mat);
    s2 = new Sphere(Vector3D(7, 4, 6), 1);
    mat = new Phong(0.25, 0.75, 0.5, 3.0, GREEN);
    s2->set_material(mat);
    csg = new CSG(s2, s1, 2);
    csg->set_material(mat->clone());
    bvh_objects.push_back(csg);

    // s2 = new Sphere(Vector3D(7, 4, 6), 1);
    // mat = new Phong(0.25, 0.75, 0.5, 3.0, GREEN);
    // s2->set_material(mat);
    // bvh_objects.push_back(s2);

    BVH* bvh = new BVH(bvh_objects, bvh_objects.size(), 0);
    add_object(bvh);
}

void World::glass_face_build(void){

    float light_radiance = 4.0; 

    // View Plane
    int lw = 800;
    vp = ViewPlane(lw, lw, 1.0, 1.0);

    // Sampler
    int n = 3;
    int num_samples = n*n;
    int num_sets = 83;
    Sampler* sampler_ptr = new Jittered(num_samples, num_sets);
    vp.set_sampler(sampler_ptr);

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
    pinhole_ptr->zoom = (lw/100)*4;
    this->camera_ptr = pinhole_ptr;


    vector<GeometricObject*> bvh_objects;

    Plane* plane_ptr = new Plane(Vector3D(0, -0.6, 0), Vector3D(0.0, 0.1, 0.02));
    Matte* yellow_ptr = new Matte(0.25, 0.75, YELLOW);
    plane_ptr->set_material(yellow_ptr);
    bvh_objects.push_back(plane_ptr);

    // GLASS/TRANSPARENT
    Transparent* trans_ptr = new Transparent(0.0, 0.0, 0.2, 2000, BLACK, 0.1, 0.9, .75);

    // FastTriMesh* mesh = new FastTriMesh("./Resources/face.obj");
    SmoothMesh* mesh = new SmoothMesh("./Resources/face.obj");
    //Phong* blue_ptr = new Phong(0.25, 0.75, 0.5, 3.0, BLUE);
    mesh->set_material(trans_ptr);
    bvh_objects.push_back(mesh);

    // Background Spheres
    Matte* blue_ptr = new Matte(0.25, 0.75, BLUE);
    Phong* red_ptr = new Phong(0.25, 0.75, 0.5, 3.0, RED);
    Matte* green_ptr = new Matte(0.25, 0.75, GREEN);

    Sphere* sphere_ptr = new Sphere(Vector3D(-0.3, -0.2, 2.5), .2);
    sphere_ptr->set_material(red_ptr);
    bvh_objects.push_back(sphere_ptr);

    sphere_ptr = new Sphere(Vector3D(0.3, -0.2, 2.5), .2);
    sphere_ptr->set_material(blue_ptr);
    bvh_objects.push_back(sphere_ptr);

    sphere_ptr = new Sphere(Vector3D(0.0, 0.4, 2.5), .2);
    sphere_ptr->set_material(green_ptr);
    bvh_objects.push_back(sphere_ptr);

    BVH* bvh = new BVH(bvh_objects, bvh_objects.size(), 0);
    add_object(bvh);
}
