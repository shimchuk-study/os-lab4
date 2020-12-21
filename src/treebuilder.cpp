#include "treebuilder.hpp"

#include <QPainter>
#include <cmath>
#include <QDebug>
#include <QLineEdit>
#include <QLabel>
#include <sstream>

TreeBuilder::TreeBuilder(FileNameTree *tree, QWidget *parent)
    : QWidget(parent), m_tree(tree), font("Monaco", FONT_SIZE), metrics(font)
{

}

FileName TreeBuilder::checkInputArea()
{
    FileName fn;

    if (m_edit) {
        auto text = m_edit->text();
        if (text.length()) {
            std::istringstream is(text.toStdString());
            is >> fn;
        }
    }

    return fn;
}

void TreeBuilder::slotInsert()
{
    m_log->clear();

    auto name = checkInputArea();
    if (name.isValid()) {
        if (!m_tree->insert(name))
            m_log->setText("<font colour=red size=24>File already exists</font>");
        else
            update();
    }
    else {
        m_log->setText("<font colour=red size=24>Invalid file name</font>");
    }
}

void TreeBuilder::slotFind()
{
    m_log->clear();

    m_findName = checkInputArea();
    if (m_findName.isValid()) {
        m_find = true;
        update();
    }
    else {
        m_log->setText("<font colour=red size=24>Invalid file name</font>");
    }
}

void TreeBuilder::slotRemove()
{
    m_log->clear();

    auto name = checkInputArea();
    if (name.isValid()) {
        if (!m_tree->remove(name))
            m_log->setText("<font colour=red size=24>File not exists</font>");
        else
            update();
    }
    else {
        m_log->setText("<font colour=red size=24>Invalid file name</font>");
    }
}

void TreeBuilder::timerEvent(QTimerEvent*)
{
}

void TreeBuilder::paintEvent(QPaintEvent *pe)
{
    (void)pe;

    auto tree_depth = m_tree->depth();

    auto [ width, height ] = neededSize(m_tree->depth());

    m_width = width;

    width += SPACING * 2;
    height += SPACING * 2;

    if (this->width() > width)
        setFixedHeight(height + SPACING * 2);
    else
        setFixedSize(width, height);

    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setPen(QPen(Qt::black, 3));
    painter.setFont(font);
    paintNode(m_tree->root(), painter, tree_depth, 0, QPoint(this->width() / 2, SPACING), width, false, false);

    m_find = false;
}

void TreeBuilder::paintNode(FileNameTreeIt& it, QPainter& painter,
                            int depth, int level, QPoint prev_down,
                            int width, bool left, bool drawLine, bool searchWay)
{
    if (it == m_tree->end())
        return;

    if (drawLine) {
        QPoint next;
        next.ry() = prev_down.y() + LINE_HEIGHT;

        int el_per_level = std::pow(2, level);
        if (left)
            next.rx() = prev_down.x() - width / (el_per_level * 2);
        else
            next.rx() = prev_down.x() + width / (el_per_level * 2);

        painter.drawLine(prev_down, next);
        prev_down = next;
    }
    prev_down.ry() += NODE_RADIUS;

    painter.setBrush(Qt::magenta);
    if (m_find && searchWay) {
        if (m_findName == *it) {
            painter.setBrush(Qt::green);
            m_find = false;
        }
        else if (it.right() == it.left())
            painter.setBrush(Qt::red);
        else
            painter.setBrush(Qt::yellow);
    }

    painter.drawEllipse(prev_down, NODE_RADIUS, NODE_RADIUS);

    auto std_str = QString().fromStdString(it->get());

    painter.setBrush(Qt::black);
    painter.drawText(QRect(prev_down.x() - NODE_RADIUS, prev_down.y() - NODE_RADIUS, NODE_RADIUS * 2, NODE_RADIUS * 2),  Qt::AlignCenter, std_str);

    prev_down.ry() += NODE_RADIUS;

    bool searchWayLeft = m_findName < *it ? true : false;

    paintNode(it.left(), painter, depth, level + 1, prev_down, width, true, true, searchWayLeft && searchWay);
    paintNode(it.right(), painter, depth, level + 1, prev_down, width, false, true, !searchWayLeft && searchWay);
}

/* static */ auto TreeBuilder::neededSize(int depth) -> std::pair<int, int>
{
    static constexpr auto nd = NODE_RADIUS * 2;

    int treeWidth = std::pow(2, depth - 1);
    int width = treeWidth * (nd + MIN_NODE_SPACING - 1);
    int height = LINE_HEIGHT * (depth - 1) + nd * (depth);

    return { width, height };
}
