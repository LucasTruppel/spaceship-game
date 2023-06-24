#ifndef player_spaceship_h
#define player_spaceship_h

#include "thread.h"
#include "spaceship.h"

using namespace SOLUTION;

class PlayerSpaceShip: public SpaceShip {
public:

    PlayerSpaceShip(int x, int y);
    //virtual ~PlayerSpaceShip();

    //Implementando as virtual functions.
    static void run(PlayerSpaceShip* playerSpaceShip);

    //Funcoes especificas da PlayerSpaceShip
    /*
    void makeMoveUP();
    void makeMoveDOWN();
    void makeMoveRIGHT();
    void makeMoveLEFT();
    */
    
    // O keyboard tá gerenciando as teclas apertadas
    // ver como juntar isso com o PlayerSpaceShip (talvez um atributo ou outra lista)
    // ou talvez chamando funcoes diretamente.
    // E dai precisa de funcoes especificas para tratas cada uma das teclas

};

#endif
