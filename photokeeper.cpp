#include "photokeeper.h"

PhotoKeeper::PhotoKeeper(QWidget *parent) : QMainWindow(parent) {
  setWindowIcon(QIcon(":/arts/64/curlew.svg"));
  setWindowTitle("Фотоотчёты на сегодня");
  resize(290, 560);
  auto date = QDate::currentDate();
  auto *cw = new QWidget(this);
  auto *clt = new QVBoxLayout();
  auto *dateLbl = new QLabel(this);
  QFont font;
  font.setBold(true);
  font.setPixelSize(16);
  dateLbl->setFont(font);
  dateLbl->setText(
      firstLetterToUpper(QLocale::system().toString(date, "dddd, d MMMM")));
  dateLbl->setWordWrap(true);
  dateLbl->setAlignment(Qt::AlignCenter);
  clt->addWidget(dateLbl);
  auto *sa = new QScrollArea(this);
  sa->setFrameShape(QScrollArea::NoFrame);
  sa->setContentsMargins(0, 0, 0, 0);
  salt = new QVBoxLayout();
  salt->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
  salt->setSpacing(0);
  salt->setContentsMargins(0, 0, 0, 0);
  auto *addBtn = new QPushButton(this);
  addBtn->setIcon(QIcon(":/arts/16/list-add.svg"));
  connect(addBtn, &QPushButton::clicked, this, &PhotoKeeper::addTask);
  salt->addWidget(addBtn);
  salt->addItem(
      new QSpacerItem(10, 10, QSizePolicy::Fixed, QSizePolicy::Preferred));
  sa->setLayout(salt);
  clt->addWidget(sa);
  cw->setLayout(clt);
  setCentralWidget(cw);
}

void PhotoKeeper::addTask() {
  auto *d = new QDialog(this);
  d->setWindowTitle("Добавить задачу");
  auto *clt = new QHBoxLayout();
  auto *titleLE = new QLineEdit(d);
  titleLE->setPlaceholderText("Фотоотчёт");
  clt->addWidget(titleLE);
  auto *timeEdit = new QTimeEdit(this);
  clt->addWidget(timeEdit);
  bool *saved = new bool(false);
  auto *sBtn = new QPushButton("Сохранить", this);
  connect(sBtn, &QPushButton::clicked, this, [d, saved]() {
    *saved = true;
    d->close();
  });
  clt->addWidget(sBtn);
  auto *cBtn = new QPushButton("Отменить", this);
  connect(cBtn, &QPushButton::clicked, d, &QDialog::close);
  clt->addWidget(cBtn);
  d->setLayout(clt);
  d->exec();
  if (*saved) {
    auto *task = new Task;
    task->accepted = false;
    task->label = titleLE->text();
    task->deadline = timeEdit->time();
    acceptTask(task);
  }
}

void PhotoKeeper::acceptTask(Task *task) {
  tasks.append(task);
  redrawTaskScrollArea();
}

void PhotoKeeper::redrawTaskScrollArea() {
  auto *task = tasks.last();
  auto *w = new QWidget(this);
  auto *hlt = new QHBoxLayout();
  hlt->setContentsMargins(0, 0, 0, 0);
  hlt->setSpacing(3);
  auto *lbl = new QLabel(this);
  lbl->setText(task->label);
  hlt->addWidget(lbl);
  auto *timeLbl = new QLabel(this);
  QFont font;
  font.setBold(true);
  timeLbl->setFont(font);
  timeLbl->setText("Дедлайн: " + task->deadline.toString("HH:mm"));
  hlt->addWidget(timeLbl);
  auto *cb = new QCheckBox(this);
  cb->setText("Выполнено");
  cb->setChecked(task->accepted);
  connect(cb, &QCheckBox::stateChanged, this,
          [cb, task]() { task->accepted = cb->isChecked(); });
  hlt->addWidget(cb);
  w->setLayout(hlt);
  salt->insertWidget(0, w);
}

QString PhotoKeeper::firstLetterToUpper(QString string) {
  string[0] = string[0].toUpper();
  return string;
}

PhotoKeeper::~PhotoKeeper() {}
