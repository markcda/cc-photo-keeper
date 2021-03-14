#include "photokeeper.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  PhotoKeeper w;
  w.show();
  return a.exec();
}
