#include "minirt.h"

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
    a = dot_product(ray->dir, ray->dir) - (dot_product(ray->dir, normal) *
		dot_product(ray->dir, normal));
    b = 2 * (dot_product(ray->dir, oc) -
				(dot_product(ray->dir, normal) *
					dot_product(oc, normal)));
	c = dot_product(oc, oc) -
		dot_product(oc, normal) * dot_product(oc,
			normal)
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
    y0 = dot_product(ray->dir, normal) * t2 + dot_product(oc, normal);
	y1 = dot_product(ray->dir, normal) * t1 + dot_product(oc, normal);
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
                t_vec cb = make_vec(obj->cen.x, 0, obj->cen.z - inter.hit.z);
                inter.norm = get_normalized(cb);
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
                t_vec bc = make_vec(obj->cen.x, 0, obj->cen.z - inter.hit.z);
                inter.norm = get_normalized(bc);
                hold = inter;
            }
        }
        obj = obj->next;
    }
    return (hold);
}