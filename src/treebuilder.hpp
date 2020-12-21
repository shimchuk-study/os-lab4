#pragma once

#ifndef TREEBUILDER_HPP
#define TREEBUILDER_HPP

#include <QWidget>
#include <utility>

#include "filenametree.hpp"

class QLabel;
class QLineEdit;

class TreeBuilder : public QWidget
{
    Q_OBJECT

    static constexpr auto NODE_RADIUS = 40;
    static constexpr auto LINE_HEIGHT = 60;
    static constexpr auto SPACING = 20;
    static constexpr auto FONT_SIZE = 24;
    static constexpr auto MIN_NODE_SPACING = 5;
    static constexpr auto NODE_COLOUR = Qt::green;
    static constexpr auto NODE_SELECTED_COLOR = Qt::red;

public:
    TreeBuilder(FileNameTree *tree, QWidget *parent = nullptr);
    ~TreeBuilder() override = default;

    inline void setLogLabel(QLabel* lbl) { m_log = lbl; }
    inline void setInputArea(QLineEdit *input) { m_edit = input; }
protected:

    void paintEvent(QPaintEvent* pe) override;
    void timerEvent(QTimerEvent* pe) override;
private:
    bool m_find = false;
    QLabel       *m_log = nullptr;
    QLineEdit    *m_edit = nullptr;
    FileNameTree *m_tree;
    QFont font;
    QFontMetrics metrics;
    FileName m_findName;
    int m_width;
    int timerId;

    void paintNode(FileNameTreeIt& it, QPainter& painter,
                   int depth, int level, QPoint prev_down, int width, bool left, bool drawLine = true, bool searchWay = true);
    static std::pair<int, int> neededSize(int depth);

    FileName checkInputArea();

public slots:
    void slotInsert();
    void slotFind();
    void slotRemove();
};

#endif // TREEBUILDER_HPP
