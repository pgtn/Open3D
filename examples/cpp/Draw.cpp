// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

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
                    "Open3D", 1280, 720);


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
