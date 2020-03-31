#pragma once

#include <QtWidgets/QMainWindow>
#include <QPointer>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QPlainTextEdit>
#include <QTableView>
#include <QFileDialog>
#include "ui_FileSearchUtility.h"

class FileSearchUtility : public QMainWindow
{
	Q_OBJECT

public:
	FileSearchUtility(QWidget *parent = Q_NULLPTR);

private slots:
	void selectFolderButtonClicked();
	void searchButtonClicked();

private:
	Ui::FileSearchUtilityClass ui;
	bool searchState = false;
	void updateTranslations();

	// path
	QPointer<QGroupBox> folderGroupBox; 
	QPointer<QLineEdit> searchPathEdit;
	QPointer<QPushButton> selectPathButton;

	// condition
	QPointer<QGroupBox> conditionGroupBox;
	QPointer<QPlainTextEdit> conditionEdit;
	QPointer<QPushButton> searchButton;

	// results
	QPointer<QGroupBox> resultsGroupBox;
	QPointer<QTableView> resultsTable;

	// status bar
	QPointer<QStatusBar> statusBar;

	
};

