#pragma once

#include <QtWidgets/QMainWindow>
#include <QPointer>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QPlainTextEdit>
#include <QTableView>
#include <QFileDialog>
#include <QTimer>
#include "ui_FileSearchUtility.h"

#define REGEXP_PARSING_DELAY 1000 // delay before starting to parse regexp after user input

class FileSearchUtility : public QMainWindow
{
	Q_OBJECT

public:
	FileSearchUtility(QWidget *parent = Q_NULLPTR);
	~FileSearchUtility();

public slots:
	void setStatus(const QString& text);

private slots:
	void selectFolderButtonClicked();
	void searchButtonClicked();
	//void conditionEntered();
	void testRegex();

private:
	Ui::FileSearchUtilityClass ui;
	bool searchState = false;
	void updateTranslations();
	QStringList pendigRegexps;
	QPointer<QTimer> regexpParseTimer;

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

signals:
	void checkRegexp(const QString& text);
};

