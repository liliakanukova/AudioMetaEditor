#include "openfilebutton.h"


void OpenFileButton::chooseFiles() {
    QFileDialog dialog(this);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec()) {
        QStringList files = dialog.selectedFiles();
        QSet<QString> s(files.begin(), files.end());
        emit filesChosen(s);
    }
}


