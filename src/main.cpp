#include <QApplication>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include "treebuilder.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FileNameTree tree;

    QWidget wgt;

    QLineEdit * pEdit = new QLineEdit;
    QLabel * pInfo = new QLabel;


    QPushButton * pCmdInsert = new QPushButton("Insert");
    QPushButton * pCmdFind   = new QPushButton("Find");
    QPushButton * pCmdRemove = new QPushButton("Remove");

    TreeBuilder * pBuilder = new TreeBuilder(&tree);
    pBuilder->setInputArea(pEdit);
    pBuilder->setLogLabel(pInfo);
    QObject::connect(pCmdInsert, &QPushButton::clicked, pBuilder, &TreeBuilder::slotInsert);
    QObject::connect(pCmdFind  , &QPushButton::clicked, pBuilder, &TreeBuilder::slotFind);
    QObject::connect(pCmdRemove, &QPushButton::clicked, pBuilder, &TreeBuilder::slotRemove);

    QHBoxLayout * pControlLay = new QHBoxLayout;
    pControlLay->addWidget(pEdit);
    pControlLay->addWidget(pCmdInsert);
    pControlLay->addWidget(pCmdFind);
    pControlLay->addWidget(pCmdRemove);

    QScrollArea * pArea = new QScrollArea;
    pArea->setWidgetResizable(true);
    pArea->setAlignment(Qt::AlignCenter);
    pArea->setWidget(pBuilder);

    QVBoxLayout * pMainLay = new QVBoxLayout;
    pMainLay->addWidget(pArea);
    pMainLay->addLayout(pControlLay);
    pMainLay->addWidget(pInfo);

    wgt.setLayout(pMainLay);
    wgt.show();

    return app.exec();
}
