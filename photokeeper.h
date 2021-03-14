#ifndef PHOTOKEEPER_H
#define PHOTOKEEPER_H

#include "task.h"
#include <QCheckBox>
#include <QDate>
#include <QDialog>
#include <QFont>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QLocale>
#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QSpacerItem>
#include <QTimeEdit>
#include <QToolButton>

class PhotoKeeper : public QMainWindow {
  Q_OBJECT

public:
  // Конструкторы:
  PhotoKeeper(QWidget *parent = nullptr);
  ~PhotoKeeper();

private:
  // Объекты:
  QVBoxLayout *salt = nullptr;
  QList<Task *> tasks;
  // Методы:
  void addTask();
  void acceptTask(Task *task);
  QString firstLetterToUpper(QString string);
  void redrawTaskScrollArea();
};
#endif
