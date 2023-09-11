#include "game.hpp"

namespace Jr {
    Game::Game( ) {
        gameOver = false;
        srand(time(nullptr));
        
        for (int i=1; i <= 16; ++i)
            data.push_back(i);
        
        reset( );
        set_posZero( );
        draw( );

        window.create( sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Puzzle Game" );
    }

    /* ******************************************** */

    Game::~Game	( ) {

    }

    /* ******************************************** */

    void Game::set_posZero( ) {
        for (int i=0; i < 4; ++i ) 
            for (int j=0; j < 4; ++j ) 
                if ( data[ i * 4 + j ] == 16 ){
                    posZero.x = i;
                    posZero.y = j;
                }
    }

    /* ******************************************** */

    void Game::run( ) {
        
        while( window.isOpen( ) ) {
            sf::Event event;
            while( window.pollEvent( event ) ) {
                if ( event.type == sf::Event::Closed )
                    window.close( );

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
                    move( Direction::DOWN );
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
                    move( Direction::UP );
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
                    move( Direction::RIGHT );
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )
                    move( Direction::LEFT );
                if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ){
                    reset();
                    set_posZero( );
                }
            }
            draw( );
        }
    }

    /* ******************************************** */

    void Game::move( const Direction& dir ) {
        switch( dir ) {
            case Direction::UP :
                if ( posZero.x > 0) {
                    std::swap(  data[ posZero.x * 4 + posZero.y ],
                                data[ (posZero.x - 1) * 4 + posZero.y ] );
                    posZero.x--;                           
                }
                    
                break;

            case Direction::DOWN :
                if ( posZero.x < 3) {
                    std::swap(  data[ posZero.x * 4 + posZero.y ],
                                data[ (posZero.x + 1) * 4 + posZero.y ] );
                    posZero.x++;             
                }   
                break;

            case Direction::LEFT :
                if ( posZero.y > 0) {
                    std::swap(  data[ posZero.x * 4 + posZero.y ],
                                data[ posZero.x * 4 + posZero.y - 1] );
                    posZero.y--;
                }
                    
                break;

            case Direction::RIGHT :
                if ( posZero.y < 3 ) {
                    std::swap(  data[ posZero.x * 4 + posZero.y ], 
                                data[ posZero.x * 4 + posZero.y + 1] );
                    posZero.y++;
                }
                break;

            default: break;
        }
    }

    /* ******************************************** */

    bool Game::isWinning( ) {
        return std::is_sorted( data.begin(), data.end() );
    }

    /* ******************************************** */

    void Game::reset( ) {
        std::random_shuffle(data.begin(), data.end());
        while ( isWinning( ) ) {
            std::random_shuffle(data.begin(), data.end());
        }
    }

    /* ******************************************** */

    void Game::draw( ) {
        sf::Texture texture;
        sf::Sprite sprite;
        window.clear( );
        for (int i = 0; i < 4; ++i ) {
            for ( int j = 0; j<4; ++j) {
                std::string path = "./img/" + std::to_string( data [i*4+j]) + ".png";
                texture.loadFromFile( path.c_str() );
                texture.setSmooth(true);
                sprite.setPosition( sf::Vector2f( (SIZE + MARGING) * j , (SIZE + MARGING) * i ));
                sprite.setTexture( texture );
                window.draw( sprite );
            }
        }
        window.display( );
    }
}