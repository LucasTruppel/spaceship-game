#include "shot.h"

Shot::Shot(float x, float y, sf::Texture &image, Direction direction, Info is_enemy) {
    shot_sprite.setTexture(image);
    shot_sprite.setPosition(x, y);
    shot_sprite.scale(0.5, 0.5);

    _direction = direction;
}

void Shot::updatePosition() {
    //TODO: Calcula a proxima posicao
    //TODO: Atualiza a posicao do sprite
    // shot_sprite.getPosition();
}