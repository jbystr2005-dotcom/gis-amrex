#include "GeometryUtils.H"

// standard ray tracing algorithm

bool pointInPolygon(double x, double y, const Building& building)
{
    const auto& points = building.footprint;

    // polygon cant exist with fewer than 3 vertices
    if (points.size() < 3)
    {
        return false;
    }

    bool inside = false;

    for (std::size_t i = 0, j = points.size() - 1; i < points.size(); j = i++)
    {
        const Point2D& pi = points[i];
        const Point2D& pj = points[j];
        bool crosses = ((pi.y > y) != (pj.y > y)) && (x < (pj.x - pi.x) * (y - pi.y) / (pj.y - pi.y) + pi.x);
        if (crosses)
        {
            inside = !inside;
        }
    }
    return inside;
}