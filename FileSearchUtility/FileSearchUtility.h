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
#include "Structs.h"

#define REGEXP_PARSING_DELAY 1000 // delay before starting to parse regexp after user input
#define REGEXP_IS_VALID_COLOR Qt::GlobalColor::green
#define REGEXP_IS_INVALID_COLOR Qt::GlobalColor::darkYellow
//#define ALLOW_EMPTY_CONDIION

class FileSearchUtility : public QMainWindow
{
	Q_OBJECT

public:
	FileSearchUtility(QWidget *parent = Q_NULLPTR);
	~FileSearchUtility();

public slots:
	void setStatus(const QString& text);
	void regexpValidated(RegexpValidateData data);
	void haveSomeFile(const QString& path, const quint64& size);
	void searchFinished();

private slots:
	void conditionTextChanged();
	void selectFolderButtonClicked();
	void searchButtonClicked();
	void testRegex();

private:
	Ui::FileSearchUtilityClass ui;
	bool searchState = false;
	void updateTranslations();
	QVector<quint64> pendigRegexps;
	QPointer<QTimer> regexpParseTimer;
	quint64 lastId = 0;
	RegexpValidateData currentRegexp;

	// path
	QPointer<QGroupBox> folderGroupBox; 
	QPointer<QLineEdit> searchPathEdit;
	QPointer<QPushButton> selectPathButton;

	// condition
	QPointer<QGroupBox> conditionGroupBox;
	QPointer<QPlainTextEdit> conditionEdit;
	QPointer<QPushButton> searchButton;
	void setConditionFieldColor(const QColor& v);
	void updateSearchButtonText();

	// results
	QPointer<QGroupBox> resultsGroupBox;
	QPointer<QTableView> resultsTable;

	// status bar
	QPointer<QStatusBar> statusBar;

signals:
	void validateRegexp(RegexpValidateData data);
	void searchForFiles(const QString& path, const RegexpValidateData& regexp);
	void stopSearch();
};

