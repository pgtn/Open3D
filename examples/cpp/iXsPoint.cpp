#include <cstdlib>

#include "open3d/Open3D.h"

using namespace open3d;


int main(int argc, const char* argv[]) {
    auto& app = open3d::visualization::gui::Application::GetInstance();
    app.Initialize(argc, argv);

    if (argc == 1) {
        open3d::utility::LogError("{} filename...", argv[0]);
        return 1;
    }

    auto vis =
            std::make_shared<open3d::visualization::visualizer::O3DVisualizer>(
                    "iXsPoint", 1280, 720);


    for (auto i = 1; i < argc; i++) {
        auto path = argv[i];
        auto ext = std::string(strrchr(path, '.'));        

        if ( ext == ".ply") {        
            auto obj = std::make_shared<open3d::geometry::TriangleMesh>();
            open3d::io::ReadTriangleMesh(path, *obj);
            if (obj->vertices_.empty()) {
                open3d::utility::LogError("Could not open {}", path);
                return 1;
            }
            vis->AddGeometry("Object " + std::to_string(i), obj);
            vis->ShowGeometry("Object " + std::to_string(i), true);
        } else if (ext == ".pcd") {
            auto obj = std::make_shared<open3d::geometry::PointCloud>();
            open3d::io::ReadPointCloud(path, *obj);
            if (obj->points_.empty()) {
                open3d::utility::LogError("Could not open {}", path);
                return 1;
            }
            vis->AddGeometry("Object " + std::to_string(i), obj);
            vis->ShowGeometry("Object " + std::to_string(i), true);        
        }
    }

    vis->ResetCameraToDefault();
    vis->ShowSettings(true);

    open3d::visualization::gui::Application::GetInstance().AddWindow(vis);

    vis.reset();

    app.Run();

    return 0;
}
