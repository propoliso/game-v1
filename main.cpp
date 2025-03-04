#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include "./Header.h"
#include <sstream>


using namespace sf;


int ground = 295;
float offsetX = 0, offsetY = 0;
double torch = 1;
const int H = 18;
const int W = 150;

String TileMap[H] = {


"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                                                                                                                                                   0",
"0                                                                                                                                                   0",
"0       s                                                                                                                    Y                      0",
"0 Y                                                                                                                                                 0",
"0                                                                             0                                0             0                      0",
"000                                                                                        0        0                                               0",
"0                  0              g 0                                         222                     22       2     2     2222222                  0",
"0                                                    0000             0      2   2     2      2      2  2      2     2    2      2                  0",
"0                                                                     0      2       22222  22222   2    2     2     2    2 222222       d          0",
"0                                                                    00      2         2      2    22222222    2222222     2     2                  0",
"0                                                                   0000     2   2                2        2   2     2    2      2                  0",
"0                                                                  000000     222                2          2  2     2   2       2                  0",
"0                                                                 00000000                                                                          0",
"0                       FF                                       0000000000               O                                                         0",
"0                                                             00000000000000                                                                        0",
"0                                                           000000000000000000000                                                                   0",
"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",


};







class Player
{
public:
    float dx, dy; // �������� 
    FloatRect rect;
    bool onGround;
    bool life;
    Sprite sprite;
    float currentFrame;

    Player(Texture& image);
    ~Player();
    void update(float time);

    void Collision(int temp);

    
  

};

Player::Player(Texture& image)
{
    sprite.setTexture(image);
    rect = FloatRect(7 * 32, 9 * 32, 70, 70);
    sprite.setTextureRect(IntRect(10,0,70,70)); // ��������� ���������
    dx = dy = 0.1;
    currentFrame = 0;

}

Player::~Player()
{
}


void Player::update(float time) // ���������� 
{
    rect.left += dx * time;//�������� dx
    if (!onGround) dy = dy + 0.0005*time;
    Collision(0);

        rect.top += dy * time;
        onGround = false;
        Collision(1);


            currentFrame += 0.005 * time;
            if (currentFrame > 2) currentFrame -= 2;


            if (!life)sprite.setTextureRect(IntRect(174, 0, 85, 70));
            if (dx > 0) sprite.setTextureRect(IntRect(85 * int(currentFrame), 0, 85, 70)); // ������ �������� �� ��������
            if (dx < 0) sprite.setTextureRect(IntRect(85 * int(currentFrame) + 85, 0, -85, 70));
        sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
        dx = 0;
   
}


void Player::Collision(int temp) {

       for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
           for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
           {
               if (TileMap[i][j] == '0')
               {
                   if ((dx > 0) && (temp == 0)) rect.left = j * 32 - rect.width;
                   if ((dx < 0) && (temp == 0)) rect.left = j * 32 + 32;
                   if ((dy > 0) && (temp == 1)) { rect.top = i * 32 - rect.height;  dy = 0;   onGround = true; }
                   if ((dy < 0) && (temp == 1)) { rect.top = i * 32 + 32;   dy = 0; }
               }
               if (TileMap[i][j] == 'F')
               {
                   TileMap[i][j] = ' ';
                   torch+=0.50;

               }

               if (TileMap[i][j] == 'Y')
               {
                   TileMap[i][j] = 'J';
               }


           }


    
}


















class Enemy
{
public:
    float dx, dy; // �������� 
    FloatRect rect;
    Sprite sprite;
    float currentFrame;
    bool life;
    Enemy();
    ~Enemy();
    void set(Texture& image, int x, int y);
    void Collision();
    void update(float time);
    void  update(float time, Enemy& monsters);
};

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::set( Texture& image, int x, int y)
{
    sprite.setTexture(image);
    rect = FloatRect(x, y, 32, 32);
    dx = 0.05;
    currentFrame = 0;
    life = true;



}

void Enemy::update(float time)
{
    rect.left += dx * time;

    Collision();


    currentFrame += time * 0.005;
    if (currentFrame > 2) currentFrame -= 2;
    sprite.setTextureRect(IntRect(80 * int(currentFrame), 0, 80, 70)); // ������ �������� �� ��������
    if (!life) sprite.setTextureRect(IntRect(165, 0, 80, 70));
    sprite.setPosition(rect.left - offsetX, rect.top - offsetY);


}
void Enemy::update(float time, Enemy&monsters)
{
    rect.left += dx * time;
    Collision();
    currentFrame += time * 0.005;
    if (currentFrame > 2) currentFrame -= 2;
    monsters. sprite.setTextureRect(IntRect(125 * int(currentFrame), 0, 121,70 )); // ������ �������� �� ��������
    if (!life) sprite.setTextureRect(IntRect(250, 0, 135, 70));
    monsters. sprite.setPosition(rect.left - offsetX, rect.top - offsetY);


}





void Enemy :: Collision()
{

    for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
        for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
            if (TileMap[i][j] == '0')
            {
                if (dx > 0)
                {
                    rect.left = j * 32 - rect.width; dx *= -1;
                }
                else if (dx < 0)
                {
                    rect.left = j * 32 + 32;  dx *= -1;
                }

            }
}




















void fight(Player& player, Enemy& monster) {
 
    if (player.life)
    {
        if (player.rect.intersects(monster.rect))
        {
            if (monster.life) {
                if (player.dy > 0) {
                    monster.dx = 0;
                    player.dy = -0.2;
                    monster.life = false;
                }
                else
                {
                  

                        torch -= 0.01;
                        if (torch < 0)
                        {
                            player.life = false;
                            torch = 0;
                        }
                    
                }
            }
        }
    }
}














int main()
{

    RenderWindow window(sf::VideoMode(1000, 800), "Karakulya"); // �������� ���� 
    menu(window);
    CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);
    

    Texture tileSet;
    tileSet.loadFromFile("source/v1.png");


    Texture tileSet2;
    tileSet2.loadFromFile("source/monsters.png");


    Texture tileSet3;
    tileSet3.loadFromFile("source/cloud.png");

    Texture tileSet4;
    tileSet4.loadFromFile("source/win.png");


    Texture t; 
    t.loadFromFile("source/casper.png"); // �������� ��������
   // t.setTextureRect(IntRect(0,0, 183, 167));
    float currentFrame = 0; // �������� ��������


    Music music;//������� ������ ������
    music.openFromFile("source/music.ogg");//��������� ����
    music.play();//������������� ������


    //Sprite s; 
    //s.setTexture(t); // sprite = texture + rect
    //s.setTextureRect(IntRect(359,0,182,167)); // ������������� ���������� ��������
    //s.setPosition(50, 100);

    Enemy monsters;
    monsters.set(tileSet2, 30 * 32, 15 * 32);
    Enemy monsters2;
    monsters2.set(tileSet2, 32 * 32, 12 * 32);
    Enemy monsters3;
    monsters3.set(tileSet3, 5 * 32, 5 * 32);


    Player p(t);
    Clock clock;
   // RectangleShape rectangle(Vector2f(32, 32));

    Sprite tile(tileSet);

    Sprite tilewin(tileSet4);



            Font font;
            	font.loadFromFile("source/sansation.ttf");
            
            	Text mytext("Hello!", font, 50);
            	mytext.setFillColor(sf::Color::Red);
            	mytext.setPosition(10, 10);
            
          









    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asMicroseconds(); // ������ ������� ��� ������� ��������� ��������
        clock.restart();

        time = time / 400;




        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (p.life)
        {

            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                p.dx = -0.1;
                if (Keyboard::isKeyPressed(Keyboard::RShift))
                {
                    p.dx = -0.5;
                }

            }

            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                p.dx = 0.1;
                if (Keyboard::isKeyPressed(Keyboard::LShift))
                {
                    p.dx = 0.5;
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::W))
            {

                if (p.onGround)
                {
                    p.dy = -0.35;
                    p.onGround = false;
                }
          
            }
        }



         p.update(time);
         monsters.update(time);
         monsters2.update(time);
         monsters3.update(time, monsters3);




         offsetX = p.rect.left - 1000/2; // �������� ������ 
         offsetY = p.rect.top- 800 /2;


        // window.clear(Color(128, 128, 128));
         window.clear(Color::White);




        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++)
            {
                if (TileMap[i][j] == '0')  tile.setTextureRect(IntRect(0, 0, 32, 32));

                if (TileMap[i][j] == 'F')  tile.setTextureRect(IntRect(38, 2, 9, 32));

                if (TileMap[i][j] == '2')  tile.setTextureRect(IntRect(58, 0, 32, 32));

                if (TileMap[i][j] == 'g')  tile.setTextureRect(IntRect(15, 68, 251, 148));

                if (TileMap[i][j] == 's')  tile.setTextureRect(IntRect(254, 216, 364, 264));

                if (TileMap[i][j] == 'd')  tile.setTextureRect(IntRect(287, 0, 353, 230));

                if (TileMap[i][j] == 'O')  tile.setTextureRect(IntRect(61, 228, 70, 114));

                if (TileMap[i][j] == 'Y')  tile.setTextureRect(IntRect(97, 0, 45, 45));

                if (TileMap[i][j] == 'J')  tile.setTextureRect(IntRect(7, 383, 150, 70));




                if (TileMap[i][j] == ' ') continue;

                tile.setPosition(j * 32 - offsetX , i * 32 - offsetY );
                window.draw(tile);

  
            }
        }



        fight(p,monsters);
      
        fight(p, monsters2);

        fight(p, monsters3);


     



         //window.draw(s); // ��������� sprite

        Text mytext("Hello!", font, 50);
        mytext.setFillColor(sf::Color::Black);
        mytext.setPosition(10, 10);
        std::ostringstream ss;    // #include <sstream>
        ss << torch;
        mytext.setString(ss.str());
        window.draw(mytext);



     

        window.draw(p.sprite); // ��������� sprite
        window.draw(monsters.sprite);      
        window.draw(monsters2.sprite);
        window.draw(monsters3.sprite);




        window.display();
    }

    return 0;
}