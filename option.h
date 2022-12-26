#ifndef OPTION_H
#define OPTION_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QDebug>



#include "commonvariable.h"
#include "output.h"

class Option : public QWidget
{
    Q_OBJECT

private:
    QPushButton *crossButton;
    QPushButton *zeroButton ;
    QPushButton *startGame  ;
    CommonVariable* comVar;



public:
    Option( QWidget* ptr,  const Output* obj_2, CommonVariable* _comVar);

private:
    const Output* gameField;
    void startSettingButton ( QPushButton* start  );
    void ticTacSettingButton( QPushButton* cross, QPushButton *zero);

public slots:
    void thisStartSlotButton();
    void choiseTicTacSlot();

};

#endif // OPTION_H
