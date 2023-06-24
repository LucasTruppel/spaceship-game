#include "shot.h"


Shot::Shot(int x, int y, sf::Texture image, Direction direction) {
    shot_sprite.setTexture(image);
    shot_sprite.setPosition(x, y);
    shot_sprite.scale(-0.5, -0.5);

    _direction = direction;
}

void Shot::updatePosition() {
    //TODO: Calcula a proxima posicao
    //TODO: Atualiza a posicao do sprite
}