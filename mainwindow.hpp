#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "FilesystemContainer.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_NameEditor_editingFinished();

private:
    Ui::MainWindow *ui;
    Dea::Element* cur_elem;
    void RefreshEditorType();
};

#endif // MAINWINDOW_HPP
