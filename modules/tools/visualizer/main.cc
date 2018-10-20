/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include <QApplication>
#include <QFile>
#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QSurfaceFormat>
<<<<<<< HEAD
#include "cyber/init.h"
=======
#include <sstream>
#include "cybertron/init.h"
>>>>>>> Modules: add OpenGL version checking function
#include "modules/tools/visualizer/main_window.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  int major, minor;
  {
    QOffscreenSurface surf;
    surf.create();

    QOpenGLContext ctx;
    ctx.create();
    ctx.makeCurrent(&surf);

    std::stringstream strStreamObj;
    strStreamObj << (const char*)ctx.functions()->glGetString(
                     GL_SHADING_LANGUAGE_VERSION);
    double version;
    strStreamObj >> version;
    major = static_cast<int>(version);
    minor = static_cast<int>(version * 10.0 - major * 10);
    if(major < 3 && minor < 3){
        std::cout << "Shading Language Version ( " << version << ") is much lower than 3.3" << std::endl;
        return -1;
    }
  }
  QSurfaceFormat format;

  format.setVersion(major, minor);
  format.setRenderableType(QSurfaceFormat::RenderableType::OpenGL);
  format.setSwapBehavior(QSurfaceFormat::SwapBehavior::DoubleBuffer);
  QSurfaceFormat::setDefaultFormat(format);

  a.setStyleSheet(
      "QSplitter::handle {"
      "   background: lightGray;"
      "   border-radius: 2px; "
      "}");

  apollo::cyber::Init(argv[0]);

  MainWindow w;

  auto topologyCallback =
      [&w](const apollo::cyber::proto::ChangeMsg& change_msg) {
        w.TopologyChanged(change_msg);
      };

<<<<<<< HEAD
  auto channelManager = apollo::cyber::service_discovery::TopologyManager::Instance()
      ->channel_manager();
=======
  auto channelManager =
      apollo::cybertron::service_discovery::TopologyManager::Instance()
          ->channel_manager();
>>>>>>> Modules: add OpenGL version checking function
  channelManager->AddChangeListener(topologyCallback);

  std::vector<apollo::cyber::proto::RoleAttributes> role_attr_vec;
  channelManager->GetWriters(&role_attr_vec);
  for (auto& role_attr : role_attr_vec) {
    w.FindNewWriter(role_attr);
  }

  w.show();

  return a.exec();
}
