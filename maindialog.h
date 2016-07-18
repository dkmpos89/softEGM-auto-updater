#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QProcess>
#include <QDialog>
#include <QProgressBar>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QDir>

QT_BEGIN_NAMESPACE

namespace Ui {
class mainDialog;
}
QT_END_NAMESPACE

class Console;

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    ~mainDialog();
    void initComponents();
    void initProcess();
    void cleanConsole(Console *console);
public slots:
    void readOutput();
    void readError();
private:
    Ui::mainDialog *ui;
    QLabel *status;
    QLabel *labelStatus;
    Console *console;
    QProcess *batProce;
    QProgressBar *proBar;

    bool result_state = false;

    const QString UPDATER = QString("cmd");
    const QStringList ARGUMENTS = ( QStringList()<<"" );
    const QString WORKING_DIR = QString("'"+QDir::currentPath()+"'\n");

};

#endif // MAINDIALOG_H
