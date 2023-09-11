#include <iostream>
#include "game.hpp"

int main( int argc, char** argv) {
    auto game = new Jr::Game;
    game->run( );
    delete game;
    
    return EXIT_SUCCESS;
}