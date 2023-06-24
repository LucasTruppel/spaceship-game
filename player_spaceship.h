#ifndef enemy_spaceship_h
#define enemy_spaceship_h

#include "window.h"
#include "spaceship.h"
#include "thread.h"

class PlayerSpaceShip: public SpaceShip
{
public:

    //PlayerSpaceShip(int x, int y);
    //virtual ~PlayerSpaceShip();

    //Implementando as virtual functions.
    virtual void run();
    virtual void makeMove();

    //Funcoes especificas da PlayerSpaceShip
    
    // O keyboard tá gerenciando as teclas apertadas
    // ver como juntar isso com o PlayerSpaceShip (talvez um atributo ou outra lista)
    // ou talvez chamando funcoes diretamente.
    // E dai precisa de funcoes especificas para tratas cada uma das teclas

   

protected:
    ;
};

#endif
