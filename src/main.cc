#include "thread.h"
#include "system.h"
#include "main_class.h"
#include "game.h"
#include "window.h"

__USING_API 

int main(void)
{
    System::init(&Game::run);
}