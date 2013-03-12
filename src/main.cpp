#include <QtGui>

#include "code39.h"
#include "context.h"
#include "settings.h"
#include "archivemanagerdialog.h"

//#define DEPLOY

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QApplication::setGraphicsSystem("raster");

  // Some initializations
  Code39::initPatterns();
  Settings::load("config.ini");

  ctx.bg_color = QColor(SETTINGS->get("Color", "BG").toString());

  ArchiveManagerDialog dialog;
  dialog.show();

  return app.exec();
}
