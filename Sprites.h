#ifndef SPRITES
#define SPRITES
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

//  Shapes & sprites declaration:
extern CircleShape bullet;
extern CircleShape ring;
extern RectangleShape wall1;
extern RectangleShape wall2;
extern RectangleShape wall3;
extern RectangleShape wall4;
extern RectangleShape box;
extern RectangleShape walls[];

struct Bullet {
    CircleShape bulletBody;
    Vector2f bulletDirection;
    Clock clock;
};

extern vector<Bullet>bullets;

void sprites();




struct Character {
    bool flip;
    sf::Texture head_texture;
    sf::Texture body_texture;
    sf::Sprite head;
    sf::Sprite body;
    sf::Sprite left_arm1;
    sf::Sprite left_arm2;
    sf::Sprite right_arm1;
    sf::Sprite right_arm2;
    sf::Sprite left_leg1;
    sf::Sprite left_leg2;
    sf::Sprite right_leg1;
    sf::Sprite right_leg2;
    sf::RectangleShape gun;
    bool dead = false;
    bool alive = true;
    bool has_gun = false;
};

void character_set_position(Character &character, sf::Vector2f pos);
void character_set_scale(Character &character, float scale);
void character_init(Character &character, std::string head_path, std::string body_path, bool flip);
void character_draw(Character &character, sf::RenderWindow &window);
void character_rotate_arm(Character &character, sf::Vector2i mouse_position);
#endif
