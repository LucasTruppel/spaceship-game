#include "thread.h"
#include "system.h"
#include "game.h"
#include "window.h"

__USING_API 

int main(void)
{
    System::init(&Game::run);
}