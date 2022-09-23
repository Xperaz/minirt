#include "minirt.h"

double  inter_cone(t_CamRay *ray, t_objs *co)
{
    double	a;
	double	b;
	double	c;
    double	k;
	double	t1, t2, delta, y0, y1, t;
    t_vec   oc;
    t_vec   normal;

    // double theta = pow(cos(co->p.x), 2.0);
    // normal = get_normalized(co->dir);
    // oc = sub_vec(ray->origin, co->cen);
    // a = pow(dot_product(ray->dir, normal), 2.0) - theta;
    // b = 2 * ((dot_product(ray->dir, normal) * (dot_product(oc, normal))) - dot_product(ray->dir, mult_vec(oc, theta)));
    // c = (pow(dot_product(oc, normal), 2.0)) - (dot_product(oc, mult_vec(oc, theta)));
    
    k = ((co->p.x / 2)  / co->p.y) * ((co->p.x / 2) / co->p.y);
    double u = 2 * co->p.x;
    double tan = sin(u) / (1 + cos(u));
    k = ((tan * M_PI) / 180.0);
    normal = get_normalized(co->dir);
    oc = sub_vec(ray->origin, co->cen);
    a = (dot_product(ray->dir, ray->dir)) - ((1 + k * k) * (pow(dot_product(ray->dir, co->cen), 2.0)));
    b = 2 * ((dot_product(ray->dir, oc)) - ((1 + k * k) * (dot_product(ray->dir, normal)) * (dot_product(oc, normal))));
    c = dot_product(oc, oc) - ((1 + k * k) * (pow(dot_product(oc, normal), 2.0)));

    delta = b * b - 4 * a * c;
	if (delta <  0.0000001)
		return (-1.0);
    if (delta == 0 || delta ==  0.0000001)
        t = -b / (2 * a);
    t1 = (-b + sqrt(delta)) / (2 * a);
    t2 = (-b - sqrt(delta)) / (2 * a);
    if (t1 <  0.0000001)
		return (-1.0);
	if (t1 > t2)
		t = t2;
	else
		t = t1;
    y0 = dot_product(ray->dir,normal) * t2 + dot_product(oc,normal);
	y1 = dot_product(ray->dir,normal) * t1 + dot_product(oc,normal);
    if (y0 >=  0.0000001 && y0 <= co->p.y)
	    return (t2);
	if (y1 >=  0.0000001 && y1 <= co->p.y)
		return (t1);
	return (-1.0);
}

double inter_sphere(t_CamRay *ray, t_objs *sp)
{
	double   a;
    double   b;
    double   c;
    double   discr;
    double   dist1;
    double   dist2;
    t_vec   cam_sphere;

    dist1 = 0;
    dist2 = 0;
    cam_sphere = sub_vec(ray->origin, sp->cen);
    a = dot_product(ray->dir,ray->dir); 
    b = 2.0 * dot_product(cam_sphere,ray->dir);
    c = dot_product(cam_sphere, cam_sphere) - (sp->p.x / 2.0) * (sp->p.x / 2.0);
    discr = b * b - (4 * a * c);
    if (discr < 0.0000001)
        return (-1);
    dist1 = (b * (-1.0) - sqrt(discr)) / (2.0 * a);
    dist2 = (b * (-1.0) + sqrt(discr)) / (2.0 * a);
    if (dist1 * dist2 > 0.0000001)
    {
        if (dist1 > 0.0000001)
            return take_min(dist1, dist2);
        return -1;
    }
    if (dist1 > 0.0000001)
        return dist1;
    return dist2;
}

double inter_plane(t_CamRay *ray, t_objs *pl)
{
    
	t_vec   cam_plane;
	double  dist;
	
	if (fabs(dot_product(pl->dir,ray->dir)) <= 0.000001)
		return -1;
	cam_plane = sub_vec(pl->cen, ray->origin);
	dist = dot_product(pl->dir, cam_plane) / dot_product(pl->dir,ray->dir);
	if (sqrt(dist) >= 0.000001)
		return dist;
	else
		return -1;
}

<<<<<<< HEAD

=======
double inter_cone(t_CamRay *ray, t_objs *co)
{
    // double	a;
	// double	b;
	// double	c;
	double	t1, t2, delta, t;
    //  t_vec   oc;
    // t_vec   normal;
    float A = ray->origin.x - co->cen.x;
    float B = ray->origin.z - co->cen.z;
    float D = co->p.y - ray->origin.y + co->cen.y;
   
    float tan = ((co->p.x / 2)  / co->p.y) * ((co->p.x / 2) / co->p.y);
    
    float a = (ray->dir.x * ray->dir.x) + (ray->dir.z * ray->dir.z) - (tan*(ray->dir.y * ray->dir.y));
    float b = (2*A*ray->dir.x) + (2*B*ray->dir.z) + (2*tan*D*ray->dir.y);
    float c = (A*A) + (B*B) - (tan*(D*D));

    // normal = get_normalized(co->dir);
    // oc = sub_vec(ray->origin, co->cen);

    delta = b * b - 4 * a * c;
	if (delta < 0 || fabs(delta)  < 0.0)
		return (-1.0);
    t1 = (-b + sqrt(delta)) / (2 * a);
    t2 = (-b - sqrt(delta)) / (2 * a);
    if (t1 < 0)
		return (-1.0);
	if (t1 > t2)
		t = t2;
	else
		t = t1;
    float r = ray->origin.y + t * ray->dir.y;
    
    if ((r > co->cen.y) && (r < co->cen.y + co->p.y))
        return t;
	return (-1.0);
}
>>>>>>> origin/mandatory

double inter_cylinder(t_CamRay *ray, t_objs *cy)
{
   
	double	a;
	double	b;
	double	c;
	double	t1, t2, delta, y0, y1, t;
    t_vec   oc;
    t_vec   normal;
    
    normal = get_normalized(cy->dir);
    oc = sub_vec(ray->origin, cy->cen);
<<<<<<< HEAD
    a = dot_product(ray->dir, ray->dir) - (dot_product(ray->dir,normal) *
		dot_product(ray->dir,normal));
    b = 2 * (dot_product(ray->dir, oc) -
				(dot_product(ray->dir,normal) *
					dot_product(oc,normal)));
	c = dot_product(oc, oc) -
		(dot_product(oc,normal) * dot_product(oc,normal))
=======
    a = dot_product(ray->dir, ray->dir) - (dot_product(ray->dir, normal) *
		dot_product(ray->dir, normal));
    b = 2 * (dot_product(ray->dir, oc) -
				(dot_product(ray->dir, normal) *
					dot_product(oc, normal)));
	c = dot_product(oc, oc) -
		dot_product(oc, normal) * dot_product(oc,
			normal)
>>>>>>> origin/mandatory
		- (cy->p.x / 2) * (cy->p.x / 2);
    
    delta = b * b - 4 * a * c;
	if (delta <  0.0000001)
		return (-1.0);
    t1 = (-b + sqrt(delta)) / (2 * a);
    t2 = (-b - sqrt(delta)) / (2 * a);
    if (t1 <  0.0000001)
		return (-1.0);
	if (t1 > t2)
		t = t2;
	else
		t = t1;
<<<<<<< HEAD
    y0 = dot_product(ray->dir,normal) * t2 + dot_product(oc,normal);
	y1 = dot_product(ray->dir,normal) * t1 + dot_product(oc,normal);
=======
    y0 = dot_product(ray->dir, normal) * t2 + dot_product(oc, normal);
	y1 = dot_product(ray->dir, normal) * t1 + dot_product(oc, normal);
>>>>>>> origin/mandatory
    if (y0 >=  0.0000001 && y0 <= cy->p.y)
	    return (t2);
	if (y1 >=  0.0000001 && y1 <= cy->p.y)
		return (t1);
	return (-1.0);
}

t_inter find_inter(t_CamRay *ray, t_scene *sc)
{
    t_inter hold;
    t_inter inter;
    hold.t = -1;
    t_objs  *obj;
    obj = sc->objs;
    double m;

    while (obj)
    {
        if (obj->type == SP)
        {
            inter.t = inter_sphere(ray,obj);
            if (((hold.t > inter.t || hold.t == -1)  && inter.t > 0.0000001))
            {
                inter.col = obj->col;
                inter.hit = add_vec(ray->origin, mult_vec(ray->dir,inter.t));
                inter.norm = get_normalized(sub_vec(inter.hit, obj->cen));
                hold = inter;
            }
        }
        if (obj->type == PL)
        {
            inter.t = inter_plane(ray, obj);
            if (((hold.t > inter.t || hold.t == -1)  && inter.t > 0.0000001))
            {
                inter.col = obj->col;
                inter.hit = add_vec(ray->origin, mult_vec(ray->dir,inter.t));
<<<<<<< HEAD
                inter.norm = get_normalized(inter.hit);
                if (dot_product(ray->dir, obj->dir) < 0.0000001)
                    inter.norm = mult_vec(obj->dir, -1);
=======
                t_vec cb = make_vec(obj->cen.x, 0, obj->cen.z - inter.hit.z);
                inter.norm = get_normalized(cb);
>>>>>>> origin/mandatory
                hold = inter;
            }
        }

        if (obj->type == CY)
        {
             inter.t = inter_cylinder(ray, obj);
            if (((hold.t > inter.t || hold.t == -1)  && inter.t > 0.0000001))
            {
                inter.col = obj->col;
                inter.hit = add_vec(ray->origin, mult_vec(ray->dir,inter.t));
<<<<<<< HEAD
                t_vec oc = get_normalized(obj->dir);
                m = dot_product(ray->dir, mult_vec(oc, inter.t)) + dot_product(sub_vec(ray->origin, obj->cen), oc);
                inter.norm = get_normalized(sub_vec(sub_vec(inter.hit, obj->cen), mult_vec(oc, m)));
                hold = inter;
            }
        }
        if (obj->type == CO)
        {
            inter.t = inter_cone(ray, obj);
            if (((hold.t > inter.t || hold.t == -1)  && inter.t > 0.0000001))
            {
                inter.col = obj->col;
                inter.hit = add_vec(ray->origin, mult_vec(ray->dir,inter.t));
                double n = dot_product(ray->dir, mult_vec(obj->dir, inter.t)) + dot_product(sub_vec(ray->origin, obj->cen), obj->dir);
                inter.norm = get_normalized(sub_vec(sub_vec(inter.hit, obj->cen), mult_vec(obj->dir, n)));
=======
                t_vec bc = make_vec(obj->cen.x, 0, obj->cen.z - inter.hit.z);
                inter.norm = get_normalized(bc);
>>>>>>> origin/mandatory
                hold = inter;
            //     inter.col = obj->col;
            //     inter.hit = add_vec(ray->origin, mult_vec(ray->dir,inter.t));
            //     double m = dot_product(ray->dir, mult_vec(obj->dir, inter.t)) + dot_product(sub_vec(ray->origin, obj->cen), obj->dir);
            //    // double a = m * pow(tan(obj->p.x * M_PI / 180.0), 2.0);
            //     double scale = 1 + pow((((obj->p.x / 2)  / obj->p.y) * ((obj->p.x / 2) / obj->p.y)), 2.0);
            //     inter.norm = get_normalized(sub_vec(sub_vec(inter.hit, obj->cen), mult_vec(obj->dir, m * scale)));
            //     hold = inter;
            }
        }
        obj = obj->next;
    }
    return (hold);
}