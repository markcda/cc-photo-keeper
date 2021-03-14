#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QTime>

struct Task {
  QString label;
  QTime deadline;
  bool accepted;
};

#endif
