#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QFileInfo>
#include <QLabel>
#include <redasm/support/utils.h>
#include <redasm/redasm.h>
#include "actions/toolbaractions.h"
#include "widgets/disassemblerview/disassemblerview.h"
#include "dialogs/loaderdialog/loaderdialog.h"

namespace Ui {
class MainWindow;
}

struct RDBuffer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    protected:
        void closeEvent(QCloseEvent* e) override;
        void dragEnterEvent(QDragEnterEvent* e) override;
        void dragMoveEvent(QDragMoveEvent* e) override;
        void dropEvent(QDropEvent* e) override;
        bool eventFilter(QObject* obj, QEvent* e) override;

    private slots:
        void onOpenClicked();
        void onSaveClicked();
        void onSaveAsClicked();
        void onRecentFileClicked(const QString& filepath);
        void onExitClicked();
        void onSignaturesClicked();
        void onResetLayoutClicked();
        void onSettingsClicked();
        void onBlocksClicked();
        void onFunctionGraphsClicked();
        void onAboutClicked();
        void checkDisassemblerStatus();
        void showProblems();
        void closeFile();

    private:
        DisassemblerView* currentDisassemblerView() const;
        RDDisassembler* currentDisassembler() const;
        void initializeLibrary();
        void loadWindowState();
        bool loadDatabase(const QString& filepath);
        void load(const QString &filepath);
        void checkCommandLine();
        void showDisassemblerView(RDDisassembler* disassembler);
        void selectLoader(const QString& filepath, RDBuffer* buffer);
        void setViewWidgetsVisible(bool b);
        void configureWebEngine();
        bool canClose();

    private:
        Ui::MainWindow *ui;
        ToolBarActions *m_tbactions;
        QLabel *m_lblstatus, *m_lblprogress, *m_lblstatusicon;
        QFileInfo m_fileinfo;
        QStringList m_recents;
        QPushButton* m_pbproblems;
};
