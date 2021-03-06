#include "lambertian.h"

lambertian::lambertian(const color &albedo)
    : m_albedo(std::make_shared<solid_color>(albedo)) {}

lambertian::lambertian(std::shared_ptr<texture> albedo)
    : m_albedo(std::move(albedo)) {}

bool lambertian::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const {
    vec3 scatter_direction = rec.normal + random_unit_vector();

    if (scatter_direction.near_zero())
        scatter_direction = rec.normal;

    scattered = ray(rec.p, scatter_direction, r_in.time());
    attenuation = m_albedo->value(rec.u, rec.v, rec.p);

    return true;
}