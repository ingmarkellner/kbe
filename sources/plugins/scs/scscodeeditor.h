/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#ifndef SCSCODEEDITOR_H
#define SCSCODEEDITOR_H

#include <QPlainTextEdit>
#include <QModelIndex>
#include <QGridLayout>
#include <QLabel>

class SCsCodeAnalyzer;
class SCsCodeAnalyzer;
class SCsCodeCompleter;
class SCsFindWidget;
class SCsErrorTableWidget;
class SCsCodeErrorAnalyzer;

class SCsCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    SCsCodeEditor(QWidget* parent = 0, SCsErrorTableWidget *errorTable = 0);
    void lineNumberAreaPaintEvent(QPaintEvent* event);
    int lineNumberAreaWidth();

    void setDocumentPath(const QString &path);
   
protected:
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *e);
    inline bool isLineWithError(int line);

    QString textUnderCursor();

    void updateErrorAnalyzer();

private slots:
	void setErrorsLines(QSet<int> lines);
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
    void insertCompletion(QModelIndex index);
    void updateAnalyzer();
	void moveTextCursor(int line, int charPos);

private:
    QWidget *mLineNumberArea;
	SCsCodeAnalyzer *mAnalyzer;
    SCsCodeCompleter *mCompleter;
    SCsErrorTableWidget *mErrorTable;
	SCsCodeErrorAnalyzer *mErrorAnalyzer;

    QSet<int> mErrorLines;
    QPixmap mErrorPixmap;
	int mLastCursorPosition;
	bool mIsTextInsert;
};

class SCsLineNumberArea : public QWidget
{
public:
    SCsLineNumberArea(SCsCodeEditor *editor) : QWidget(editor)
    {
        mCodeEditor = editor;
    }

    QSize sizeHint() const
    {
        return QSize(mCodeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event)
    {
        mCodeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    SCsCodeEditor *mCodeEditor;
    int mStartSelectionBlockNumber;
    int mEndSelectionBlockNumber;

};
#endif // SCSCODEEDITOR_H
