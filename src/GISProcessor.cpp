#include <iostream>
#include <ogrsf_frmts.h>
#include <limits>
#include "GISProcessor.H"

using namespace std;

GISData GISProcessor::load(const std::string& filename)
{
    GISData data;

    GDALAllRegister();

    GDALDataset* dataset = static_cast<GDALDataset*>(
        GDALOpenEx(
            filename.c_str(), GDAL_OF_VECTOR, nullptr, nullptr, nullptr
        )
    );

    if (dataset == nullptr)
    {
        cerr << "Failed to open GeoJson file\n";
        return data;
    }

    OGRLayer* layer = dataset->GetLayer(0);

    if (layer == nullptr)
    {
        cerr << "Failed to load layer from dataset\n";
        GDALClose(dataset);
        return data;
    }

    OGRSpatialReference sourceCRS;
    sourceCRS.importFromEPSG(4326);
    sourceCRS.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

    OGRSpatialReference targetCRS;
    targetCRS.importFromEPSG(32615);
    targetCRS.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

    OGRCoordinateTransformation* transform = OGRCreateCoordinateTransformation(&sourceCRS, &targetCRS);

    if (transform == nullptr)
    {
        cerr << "Failed to create coordinate tranformation.\n";
        GDALClose(dataset);
        return data;
    }

    const OGRSpatialReference* spatial_ref = layer->GetSpatialRef();
    if (spatial_ref == nullptr)
    {
        cerr << "No coordinate reference system found.\n";
    }
    else
    {
        const char* authorityName = spatial_ref->GetAuthorityName(nullptr);
        const char* authorityCode = spatial_ref->GetAuthorityCode(nullptr);

        if (authorityName != nullptr && authorityCode != nullptr)
        {
            cout << "Coordinate system: " << authorityName << ":" << authorityCode << "\n";
        }
    }

    layer->ResetReading();
    
    OGRFeature* feature;
    while ((feature = layer->GetNextFeature()) != nullptr)
    {
        OGRGeometry* geometry = feature->GetGeometryRef();
        if (geometry == nullptr)
        {
            OGRFeature::DestroyFeature(feature);
            continue;
        }
        cout << "Geometry Type: " << OGRGeometryTypeToName(geometry->getGeometryType()) << endl;
        
        if (wkbFlatten(geometry->getGeometryType()) != wkbPolygon)
        {
            cout << "Skipping non-polygon geometry\n";
            OGRFeature::DestroyFeature(feature);
            continue;
        }

        OGRPolygon* polygon = geometry->toPolygon();
        OGRLinearRing* ring = polygon->getExteriorRing();
        vector<Building> buildings;

        if (ring == nullptr)
        {
            cerr << "Polygon has no exterior ring\n";
            OGRFeature::DestroyFeature(feature);
            continue;
        }

        Building building;
        auto num_points = ring->getNumPoints();

        for (auto i = 0; i < num_points; ++i)
        {
            double x = ring->getX(i);
            double y = ring->getY(i);

            if (!transform->Transform(1, &x, &y))
            {
                continue;
            }
            building.footprint.push_back({x, y});
        }

        if (!building.footprint.empty())
        {
            data.buildings.push_back(building);
        }

        OGRFeature::DestroyFeature(feature);
    }

    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double maxY = std::numeric_limits<double>::lowest();

    for (const Building& building : data.buildings)
    {
        for (const Point2D& point : building.footprint)
        {
            if (point.x < minX)
            {
                minX = point.x;
            }
            if (point.y < minY)
            {
                minY = point.y;
            }
            if (point.x > maxX)
            {
                maxX = point.x;
            }
            if (point.y > maxY)
            {
                maxY = point.y;
            }
        }
    }

    if (!data.buildings.empty())
    {
        data.minX = minX;
        data.minY = minY;
        data.maxX = maxX;
        data.maxY = maxY;

        data.width = maxX - minX;
        data.height = maxY - minY;

        for (Building& building : data.buildings)
        {
            for (Point2D& point : building.footprint)
            {
                point.x -= minX;
                point.y -= minY;
            }
        }
    }

    OCTDestroyCoordinateTransformation(transform);
    GDALClose(dataset);

    return data;
}

