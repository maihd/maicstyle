int main()
{
    Node* node = Sprite::create("player.png");
    node->beginTween()
        .tweenCreator()
            .moveTo()
            .scale()
        .tweenCreator()
        .actSpawn(MoveTo::create(0, 0))
        .actSpawn(ScaleTo::create(0, 0))
        .actNext()
        .actNext()
        .start();

    return 0;
}

//! EOF
