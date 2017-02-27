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

    void on_ElementNameButton_accepted();

    void on_ElementNameButton_rejected();

    void on_LineEditorBox_accepted();

    void on_LineEditorBox_rejected();

    void on_TexteditBox_accepted();

    void on_TexteditBox_rejected();

    void on_comboButton_accepted();

    void on_comboButton_rejected();

    void on_ApproveNewFile_clicked();

    void on_DeleteFile_clicked();

private:
    Ui::MainWindow *ui;
    QModelIndex cur_elem;
    void RefreshEditorType();
    void AcceptChange();
};

#endif // MAINWINDOW_HPP
