/*t_CamRay	ray(t_vec orig, t_vec dir)
{
    t_CamRay ray;

    ray.origin = orig;
    ray.dir = get_normalized(dir);
    return (ray);
}

t_vec	ray_at(t_CamRay *ray, double t)
{
    t_vec	at;

    at = add_vec(ray->origin, mult_vec(ray->dir, t));
    return (at);
}

t_camera    camera(t_canvas *canvas, t_scene *sc)
{
    t_camera    cam;
    
    double      focal_len;
    double      viewport_height;
    double      theta;
    double      h;

    theta = sc->cam.fov * M_PI / 180.0;
    h = tan(theta / 2);
    viewport_height = h * 2.0;
    focal_len = 1.0;
    cam.orig = sc->cam.cen; 
    cam.viewport_h = viewport_height;
    cam.viewport_w = viewport_height * canvas->aspect_ratio;
    cam.focal_len = focal_len;
    cam.horizontal = make_vec(cam.viewport_w, 0, 0);
    cam.vertical = make_vec(0, cam.viewport_h, 0);
    // lower left corner point coordinates, origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length)
    cam.left_bottom = sub_vec(sub_vec(sub_vec(cam.orig, div_vect(cam.horizontal, 2)),
                                div_vect(cam.vertical, 2)), make_vec(0, 0, focal_len));
    return (cam);
}

t_CamRay       ray_primary(t_camera *cam, double u, double v)
{
    t_CamRay   ray;

    ray.origin = cam->orig;
    //unit vector
    ray.dir = get_normalized(sub_vec(add_vec(add_vec(cam->left_bottom, mult_vec(cam->horizontal, u)), mult_vec(cam->vertical, v)), cam->orig));
    return (ray);
}

t_vec	color(double r, double g, double b)
{
	t_vec color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}

t_vec	ray_color(t_CamRay *r, t_scene *sc)
{
    double  t;
    
    t = 0.5 * (r->dir.y + 1.0);
    return (add_vec(mult_vec(color(sc->objs->col.x, sc->objs->col.y, sc->objs->col.z), 1.0 - t), mult_vec(color(0.5, 0.7, 1.0), t)));
}

*/