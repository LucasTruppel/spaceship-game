#include "system.h"
#include "traits.h"
#include "debug.h"
#include <iostream>

__BEGIN_API


    void System::init() {
        setvbuf(stdout, 0, _IONBF, 0);
        db<System>(TRC) << "System::init() chamado\n";
    }
  
    
    
__END_API
