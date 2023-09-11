#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <SFML/Graphics.hpp>


namespace Jr {
    constexpr int SIZE = 64;
    constexpr int MARGING = 2;
    constexpr int SCREEN_SIZE = ( SIZE + MARGING ) * 4;

    class Game {
        struct Position {
            int x;
            int y;
        };
        enum class Direction {
            UP, DOWN, LEFT, RIGHT
        };

        public :
            Game( );
            ~Game( );
            void run( );

        private :
            bool gameOver;
            std::vector<int> data;
            Position posZero ;
            sf::RenderWindow window;

            void set_posZero( );
            void move( const Direction& );
            bool isWinning( );
            void reset( );
            void draw( );
    };
}