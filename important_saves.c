                t_vec nr = make_vec(inter.hit.x / sqrt(pow(inter.hit.x, 2.0) + pow(inter.hit.y, 2.0)), inter.hit.y / sqrt(pow(inter.hit.x, 2.0) + pow(inter.hit.y, 2.0)), 0);


typedef struct triangle {
    double eps;
    t_vec   edge1;
    t_vec   edge2;
    t_vec   h;
    t_vec   s;
    t_vec   q;
    double  f;
    double  u;
    double  v;
    double  a;
    double  t;

} t_triangle;

t_triangle	ft_calcule_triangle(t_CamRay *ray, t_objs *triangle)
{
	t_triangle tr;

	tr.eps = 0.0000001;
	tr.edge1 = sub_vec(triangle->dir, triangle->cen);
	tr.edge2 = sub_vec(triangle->point, triangle->cen);
	tr.h = vect_cross(ray->dir, tr.edge2);
	tr.a = dot_product(tr.edge1, tr.h);
	return (tr);
}

double					inter_triangle(t_CamRay *ray, t_objs *triangle)
{
	t_triangle	tr;

	tr = ft_calcule_triangle(ray, triangle);
	if (fabs(tr.a) < tr.eps)
		return (-1.0);
	tr.f = 1.0 / tr.a;
	tr.s = sub_vec(ray->origin, triangle->cen);
	tr.u = dot_product(tr.s, tr.h);
	tr.u = tr.f * tr.u;
	if (tr.u < 0.0 || tr.u > 1.0)
		return (-1.0);
	tr.q = vect_cross(tr.s, tr.edge1);
	tr.v = dot_product(ray->dir, tr.q);
	tr.v = tr.f * tr.v;
	if (tr.v < 0.0 || tr.u + tr.v > 1.0)
		return (0);
	tr.t = dot_product(tr.q, tr.edge2);
	tr.t = tr.f * tr.t;
	if (tr.t > tr.eps)
		return (tr.t);
	else
		return (-1.0);
}


/* cone */

// double inter_cone(t_CamRay *ray, t_objs *co)
// {
// 	double				t;
//     t_vec               p;
//     t_vec               u;
//     double               r;
//     t_vec               scale;

// 	t = inter_plane(ray, co);
// 	if (t >= 0.000001)
// 	{
// 		scale = mult_vec(ray->dir, t);
// 		p = add_vec(ray->origin, scale);
// 		u = sub_vec(p, co->cen);
// 		r = co->p.x / 2;
// 		if (fabs(u.x) > r || fabs(u.y) > r || fabs(u.z) > r)
// 			return (-1.0);
// 		return (t);
// 	}
// 	return (-1.0);
    // double	a;
	// double	b;
	// double	c;
	// double	t1, t2, delta, t;
    //  t_vec   oc;
    // t_vec   normal;
    // float A = ray->origin.x - co->cen.x;
    // float B = ray->origin.z - co->cen.z;
    // float D = co->p.y - ray->origin.y + co->cen.y;
   
    // float tan = ((co->p.x / 2)  / co->p.y) * ((co->p.x / 2) / co->p.y);
    
    // float a = (ray->dir.x * ray->dir.x) + (ray->dir.z * ray->dir.z) - (tan*(ray->dir.y * ray->dir.y));
    // float b = (2*A*ray->dir.x) + (2*B*ray->dir.z) + (2*tan*D*ray->dir.y);
    // float c = (A*A) + (B*B) - (tan*(D*D));

    // normal = get_normalized(co->dir);
    // oc = sub_vec(ray->origin, co->cen);

    // delta = b * b - 4 * a * c;
	// if (delta < 0 || fabs(delta)  < 0.0)
	// 	return (-1.0);
    // t1 = (-b + sqrt(delta)) / (2 * a);
    // t2 = (-b - sqrt(delta)) / (2 * a);
    // if (t1 < 0)
	// 	return (-1.0);
	// if (t1 > t2)
	// 	t = t2;
	// else
	// 	t = t1;
    // float r = ray->origin.y + t * ray->dir.y;
    
    // if ((r > co->cen.y) && (r < co->cen.y + co->p.y))
    //     return t;
	// return (-1.0);
// }