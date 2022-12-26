#include "option.h"

Option::Option ( QWidget* ptr, const Output* _gameField, CommonVariable* _comVar) : QWidget (ptr)
{



    comVar = _comVar;
    gameField = _gameField;

    QLabel      *TicTac      = new QLabel("<H1><CENTER>ITC: TicTac</CENTER></H1>"); //<H1><CENTER>ITC: TicTac</CENTER></H1>
    // add not active text(label)

    crossButton = new QPushButton("X");
    zeroButton  = new QPushButton("0");
    startGame   = new QPushButton("Start");


    /// Seting Buttons
    startSettingButton (startGame);
    ticTacSettingButton(crossButton, zeroButton);

    ///Layout setup
    QVBoxLayout *vbxLayout = new QVBoxLayout();
    QHBoxLayout *hbxLayout = new QHBoxLayout();
    hbxLayout->addWidget(crossButton);
    hbxLayout->addWidget(zeroButton) ;

    vbxLayout->setSpacing(10);
    vbxLayout->addWidget (TicTac);
    vbxLayout->addWidget (startGame);
    vbxLayout->addLayout (hbxLayout);
    vbxLayout->setContentsMargins(50,190,50,400);

    this->setLayout(vbxLayout);

}


void Option::startSettingButton( QPushButton* start )
{

    connect(start, SIGNAL( clicked() ), gameField, SLOT( startSlotButton() ));
    //connect(start, SIGNAL( clicked() ), this, SLOT( thisStartSlotButton() ));
}

void Option::ticTacSettingButton(QPushButton *cross, QPushButton *zero)
{

    cross->setCheckable(true);
    zero ->setCheckable(true);

    cross->setChecked( comVar->tictacPlayer );   // true - cross(1), false - zero(0)
    zero ->setChecked( !(comVar->tictacPlayer) );

    connect(cross, SIGNAL( clicked() ), this, SLOT( choiseTicTacSlot() ));
    connect(zero,  SIGNAL( clicked() ), this, SLOT( choiseTicTacSlot() ));

}

void Option::thisStartSlotButton()
{


    qDebug() << "2Jobs";
}

void Option::choiseTicTacSlot()
{
    if( (comVar->playerLocked) ){

        comVar->tictacPlayer = !(comVar->tictacPlayer);
        crossButton->setChecked(comVar->tictacPlayer);
        zeroButton ->setChecked(!(comVar->tictacPlayer));
    }
    else{
        crossButton->setChecked(comVar->tictacPlayer);
        zeroButton ->setChecked(!(comVar->tictacPlayer));
    }
}


