#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Sprites.h"
#include "Physics.h"
#include "Levels.h"
#include "1v1.h"
#include "Menus.h"
#include "Events.h"
#include "Sounds.h"
#include "1v1.h"
//#include "Levels.cpp"
#include "win-lose-logic.h"

sf::RenderWindow window(sf::VideoMode(1920, 1080), "Mr bullet", sf::Style::Fullscreen);
bool in_level;
bool shot;
int currentLvl = 0;


// Menus test
int main() {
    sprites();
    BufferSounds();
    SetSounds();
    window.setFramerateLimit(60);
    crosshairTx.loadFromFile("assets/Textures/crosshair.png");

    Texture_loading();
    SFX_click.setBuffer(SFX_click_soundbuffer);
    shoot.setBuffer(shoot_soundbuffer);
    Restart_sound.setBuffer(Restart_soundbuffer);

    mainmenu_music.openFromFile("assets/sounds/main_music.ogg");
    mainmenu_music.setVolume(volume_value[0]);
    mainmenu_music.play();
    mainmenu_music.setLoop(true);
    for (int i = 0; i < 15; i++) {
        lev[i].killer.has_gun = true;
    }
    constructlev1(window);
    constructlev2(window);
    constructlev3(window);
    constructlev4(window);
    constructlev5(window);
    constructlev6(window);
    constructlev7(window);
    constructlev8(window);
    constructlev9(window);
    constructlev10(window);
    constructlev11(window);
    constructlev12(window);
    constructlev13(window);
    constructlev14(window);
    constructlev15(window);

    constructOneVSone_one(window);
    constructOneVSone_two(window);
    constructOneVSone_three(window);
    constructOneVSone_four(window);
    
    
    bool level_complete = false;
    int currentLvl;
    bool drawLine = true;



    while (window.isOpen())
    {
        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

        line[0].position = lev[level_index].killer.bullet_pos;
        line[1].position = sf::Vector2f(mouse_position.x, mouse_position.y);

        //gunPos = lev[level_index].killer.bullet_pos;
        if (current_menu >= static_cast<menu_type>(0) && current_menu <= static_cast<menu_type>(14) || current_menu == Dules_1)
        {
            if (bullets.size() != 0)
            {
                //if (current_menu == Duels)
                //{
                //    lev[level_index].num_of_bullets = 1;
                //}
                if (playerOne.turn) {
                    line[0].position = playerOne.bullet_pos;
                    line[1].position = sf::Vector2f(mouse_position.x, mouse_position.y);
                }
                else {
                    line[0].position = playerTwo.bullet_pos;
                    line[1].position = sf::Vector2f(mouse_position.x, mouse_position.y);
                }

                if (current_menu == Dules_1)
                {
                    for (int i = bullets.size() - 1; i > 0; i--)
                    {
                        Time elapsed = bullets[i].clock.getElapsedTime();
                        level_complete = false;
                        if (elapsed >= seconds(5.f))
                        {
                            bullets[i].clock.restart();
                            bullets.erase(bullets.begin() + i);

                            level_complete = true;

                            shot = false;
                            collided = true;
                            playerOne.turn = !playerOne.turn;
                            if (playerOne.turn) {
                                character_show_player_arrow(playerOne, true);
                                character_show_player_arrow(playerTwo, false);
                            }
                            else {
                                character_show_player_arrow(playerOne, false);
                                character_show_player_arrow(playerTwo, true);
                            }
                        }
                    }
                }
                else {
                    for (int i = bullets.size() - 1; i >= 0; i--)
                    {
                        Time elapsed = bullets[i].clock.getElapsedTime();
                        level_complete = false;
                        if (elapsed >= seconds(5.f))
                        {
                            bullets[i].clock.restart();
                            bullets.erase(bullets.begin() + i);

                            level_complete = true;

                            shot = false;
                            collided = true;
                        }
                    }
                }
            }

            for (int i = 0; i < bullets.size(); i++) {
                //bullets[i].bulletBody.setPosition(bullets[i].bulletBody.getPosition() - bullets[i].bulletDirection * 20.f);
                bullets[i].b.setPosition(bullets[i].bulletBody.getPosition());

            }
        }

        // drawing

        window.clear();

        if (current_menu == main_menu)
        {
            in_level = false;
            Main_menu();

        }

        else if (current_menu == play_menu)
        {
            in_level = false;
            Play_menu();
            lev[level_index].num_of_bullets = 1;

        }

        else if (current_menu == player_one_MENU)
        {
            player_one_menu();
        }

        else if (current_menu == player_two_MENU)
        {
            player_two_menu();
        }

        else if (current_menu == maps_1v1)
        {
            MAPS_1v1();
        }

        else if (current_menu == duelsPause)
        {
            duelsPauseMenu();
        }

        else if (current_menu == duelsOption)
        {
            duelsOptionMenu();
        }

        else if (current_menu == options_menu)
        {
            in_level = false;
            Options_menu();
        }

        else if (current_menu == pause_MENU)
        {
            in_level = false;
            PAUSE_MENU();
        }

        else if (current_menu == OPTIONS_MENU_PAUSE)
        {
            in_level = false;
            Options_menu_Pause();
        }

        else if (current_menu == classic_Mode)
        {
            in_level = false;
            Classic_menu();
        }

        else if (current_menu == achievements_menu)
        {
            in_level = false;
            Achievements_menu();
        }

        else if (current_menu == won_panel)
        {
            for (int i = bullets.size() - 1; i >= 0; i--)
            {
                bullets[i].clock.restart();
                bullets.erase(bullets.begin() + i);

                level_complete = true;

            }
            Win_panel(lev[level_index].view.Level_evaluation);
        }

        else if (current_menu == lost_panel)
        {
            Lose_panel(currentLvl);
        }


        else if (current_menu == level_1)
        {
            drawLine = true;
            character_rotate_arm(lev[0].killer, sf::Mouse::getPosition());
            int enemies_num = 1;
            levels_eventloop(enemies_num);
            if (current_menu >= static_cast<menu_type>(0) && current_menu <= static_cast<menu_type>(14))
            {
                DrawingLevels(0, window);
                in_level = true;
                currentLvl = 0;

                for (int i = 0; i < bullets.size(); i++) {
                    HandlePhysics(lev[0], bullets[i]);
                }
                for (int i = 0; i < bullets.size(); i++) {
                    CollideEnemies(lev[0], bullets[i]);
                }




                for (int i = 0; i < enemies_num; i++)
                {
                    if (lev[level_index].target[i].alive && lev[level_index].target[i].dead)
                    {
                        dead_enemies++;
                        lev[level_index].target[i].alive = false;
                    }
                }




                if (dead_enemies == enemies_num)
                {
                    lev[0].is_finished = true;
                    achievements[0].is_open = true;
                    Achievements_checking();
                    stars_system(3, 2, 1, 0);
                    current_menu = won_panel;
                    drawLine = false;

                }

                else if (lev[level_index].num_of_bullets == 0 && level_complete && bullets.size() == 0)  ///32131563
                {
                    current_menu = lost_panel;
                }

            }
        }
        else if (current_menu == level_2)
        {
            drawLine = true;
            int enemies_num = 8;
            levels_eventloop(enemies_num);
            if (current_menu >= static_cast<menu_type>(0) && current_menu <= static_cast<menu_type>(14))
            {
                DrawingLevels(1, window);
                in_level = true;
                currentLvl = 2;

                for (int i = 0; i < bullets.size(); i++) {
                    HandlePhysics(lev[1], bullets[i]);
                }
                for (int i = 0; i < bullets.size(); i++) {
                    CollideEnemies(lev[1], bullets[i]);
                }




                for (int i = 0; i < enemies_num; i++)
                {
                    if (lev[level_index].target[i].alive && lev[level_index].target[i].dead)
                    {
                        dead_enemies++;
                        lev[level_index].target[i].alive = false;
                    }
                }




                if (dead_enemies == enemies_num)
                {
                    stars_system(3, 2, 1, 0);
                    current_menu = won_panel;
                    drawLine = false;

                }

                else if (lev[level_index].num_of_bullets == 0 && level_complete && bullets.size() == 0)  ///32131563
                {
                    current_menu = lost_panel;
                }

            }
        }
        else if (current_menu == level_3)
        {
            drawLine = true;
            int enemies_num = 1;
            levels_eventloop(enemies_num);
            if (current_menu >= static_cast<menu_type>(0) && current_menu <= static_cast<menu_type>(14))
            {
                DrawingLevels(2, window);
                in_level = true;
                currentLvl = 2;

                for (int i = 0; i < bullets.size(); i++) {
                    HandlePhysics(lev[2], bullets[i]);
                }
                for (int i = 0; i < bullets.size(); i++) {
                    CollideEnemies(lev[2], bullets[i]);
                }




                for (int i = 0; i < enemies_num; i++)
                {
                    if (lev[level_index].target[i].alive && lev[level_index].target[i].dead)
                    {
                        dead_enemies++;
                        lev[level_index].target[i].alive = false;
                    }
                }




                if (dead_enemies == enemies_num)
                {
                    stars_system(3, 2, 1, 0);
                    current_menu = won_panel;
                    drawLine = false;

                }

                else if (lev[level_index].num_of_bullets == 0 && level_complete && bullets.size() == 0)  ///32131563
                {
                    current_menu = lost_panel;
                }

            }
        }
        else if (current_menu == level_4)
        {
            drawLine = true;
            int enemies_num = 3;
            levels_eventloop(enemies_num);
            if (current_menu >= static_cast<menu_type>(0) && current_menu <= static_cast<menu_type>(14))
            {
                DrawingLevels(3, window);
                in_level = true;
                currentLvl = 3;

                for (int i = 0; i < bullets.size(); i++) {
                    HandlePhysics(lev[3], bullets[i]);
                }
                for (int i = 0; i < bullets.size(); i++) {
                    CollideEnemies(lev[3], bullets[i]);
                }




                for (int i = 0; i < enemies_num; i++)
                {
                    if (lev[level_index].target[i].alive && lev[level_index].target[i].dead)
                    {
                        dead_enemies++;
                        lev[level_index].target[i].alive = false;
                    }
                }




                if (dead_enemies == enemies_num)
                {
                    stars_system(3, 2, 1, 0);
                    current_menu = won_panel;
                    //for (int i = bullets.size() - 1; i > 0; i--)
                    //{
                    //        bullets[i].clock.restart();
                    //        bullets.erase(bullets.begin() + i);
                    //        std::cout << "erased";

                    //        level_complete = true;
                    //        if (current_menu == Duels)
                    //        {
                    //            playerOne.turn = !playerOne.turn;
                    //            shot = false;
                    //            collided = true;
                    //        }
    
                    //}
                    drawLine = false;
                }

                else if (lev[level_index].num_of_bullets == 0 && level_complete && bullets.size() == 0)  ///32131563
                {
                    current_menu = lost_panel;
                }

            }
        }
        else if (current_menu == level_5)
        {
        drawLine = true;
        int enemies_num = 2;
        character_rotate_arm(lev[4].killer, sf::Mouse::getPosition());

        levels_eventloop(enemies_num);
        if (current_menu >= static_cast<menu_type>(0) && current_menu <= static_cast<menu_type>(14))
        {
            DrawingLevels(4, window);
            in_level = true;
            currentLvl = 5;

            for (int i = 0; i < bullets.size(); i++) {
                HandlePhysics(lev[4], bullets[i]);
            }
            for (int i = 0; i < bullets.size(); i++) {
                CollideEnemies(lev[4], bullets[i]);
            }


            for (int i = 0; i < enemies_num; i++)
            {
                if (lev[level_index].target[i].alive && lev[level_index].target[i].dead)
                {
                    dead_enemies++;
                    lev[level_index].target[i].alive = false;
                }
            }




            if (dead_enemies == enemies_num)
            {
                stars_system(3, 2, 1, 0);
                current_menu = won_panel;
                drawLine = false;
            }

            else if (lev[level_index].num_of_bullets == 0 && level_complete && bullets.size() == 0)  ///32131563
            {
                current_menu = lost_panel;
            }

        }
 }
        else if (current_menu == level_6)
        {
        drawLine = true;
        int enemies_num = 15;
        character_rotate_arm(lev[5].killer, sf::Mouse::getPosition());

        levels_eventloop(enemies_num);
        if (current_menu >= static_cast<menu_type>(0) && current_menu <= static_cast<menu_type>(14))
        {
            DrawingLevels(5, window);
            in_level = true;
            currentLvl = 6;

            for (int i = 0; i < bullets.size(); i++) {
                HandlePhysics(lev[5], bullets[i]);
            }
            for (int i = 0; i < bullets.size(); i++) {
                CollideEnemies(lev[5], bullets[i]);
            }


            for (int i = 0; i < enemies_num; i++)
            {
                if (lev[level_index].target[i].alive && lev[level_index].target[i].dead)
                {
                    dead_enemies++;
                    lev[level_index].target[i].alive = false;
                }
            }




            if (dead_enemies == enemies_num)
            {
                stars_system(3, 2, 1, 0);
                current_menu = won_panel;
                drawLine = false;
            }

            else if (lev[level_index].num_of_bullets == 0 && level_complete && bullets.size() == 0)  ///32131563
            {
                current_menu = lost_panel;
            }

        }

        }
        else if (current_menu == level_7)
        {
        drawLine = true;
        int enemies_num = 1;
        character_rotate_arm(lev[6].killer, sf::Mouse::getPosition());

        levels_eventloop(enemies_num);
        if (current_menu >= static_cast<menu_type>(0) && current_menu <= static_cast<menu_type>(14))
        {
            DrawingLevels(6, window);
            in_level = true;
            currentLvl = 7;

            for (int i = 0; i < bullets.size(); i++) {
                HandlePhysics(lev[6], bullets[i]);
            }
            for (int i = 0; i < bullets.size(); i++) {
                CollideEnemies(lev[6], bullets[i]);
            }


            for (int i = 0; i < enemies_num; i++)
            {
                if (lev[level_index].target[i].alive && lev[level_index].target[i].dead)
                {
                    dead_enemies++;
                    lev[level_index].target[i].alive = false;
                }
            }




            if (dead_enemies == enemies_num)
            {
                stars_system(3, 2, 1, 0);
                current_menu = won_panel;
                drawLine = false;
            }

            else if (lev[level_index].num_of_bullets == 0 && level_complete && bullets.size() == 0)  ///32131563
            {
                current_menu = lost_panel;
            }

        }

        }
        else if (current_menu == level_8)
        {
        drawLine = true;
        int enemies_num = 15;
        character_rotate_arm(lev[7].killer, sf::Mouse::getPosition());

        levels_eventloop(enemies_num);
        if (current_menu >= static_cast<menu_type>(0) && current_menu <= static_cast<menu_type>(14))
        {
            DrawingLevels(7, window);
            in_level = true;
            currentLvl = 8;

            for (int i = 0; i < bullets.size(); i++) {
                HandlePhysics(lev[7], bullets[i]);
            }
            for (int i = 0; i < bullets.size(); i++) {
                CollideEnemies(lev[7], bullets[i]);
            }


            for (int i = 0; i < enemies_num; i++)
            {
                if (lev[level_index].target[i].alive && lev[level_index].target[i].dead)
                {
                    dead_enemies++;
                    lev[level_index].target[i].alive = false;
                }
            }




            if (dead_enemies == enemies_num)
            {
                stars_system(3, 2, 1, 0);
                current_menu = won_panel;
                drawLine = false;
            }

            else if (lev[level_index].num_of_bullets == 0 && level_complete && bullets.size() == 0)  ///32131563
            {
                current_menu = lost_panel;
            }

        }

        }
        else if (current_menu == level_9)
        {
        drawLine = true;
        int enemies_num = 4;
        character_rotate_arm(lev[8].killer, sf::Mouse::getPosition());

        levels_eventloop(enemies_num);
        if (current_menu >= static_cast<menu_type>(0) && current_menu <= static_cast<menu_type>(14))
        {
            DrawingLevels(8, window);
            in_level = true;
            currentLvl = 9;

            for (int i = 0; i < bullets.size(); i++) {
                HandlePhysics(lev[8], bullets[i]);
            }
            for (int i = 0; i < bullets.size(); i++) {
                CollideEnemies(lev[8], bullets[i]);
            }


            for (int i = 0; i < enemies_num; i++)
            {
                if (lev[level_index].target[i].alive && lev[level_index].target[i].dead)
                {
                    dead_enemies++;
                    lev[level_index].target[i].alive = false;
                }
            }




            if (dead_enemies == enemies_num)
            {
                stars_system(3, 2, 1, 0);
                current_menu = won_panel;
                drawLine = false;
            }

            else if (lev[level_index].num_of_bullets == 0 && level_complete && bullets.size() == 0)  ///32131563
            {
                current_menu = lost_panel;
            }

        }

        }
        else if (current_menu == level_10)
        {
        drawLine = true;
        int enemies_num = 1;
        character_rotate_arm(lev[9].killer, sf::Mouse::getPosition());

        levels_eventloop(enemies_num);
        if (current_menu >= static_cast<menu_type>(0) && current_menu <= static_cast<menu_type>(14))
        {
            DrawingLevels(9, window);
            in_level = true;
            currentLvl = 10;

            for (int i = 0; i < bullets.size(); i++) {
                HandlePhysics(lev[9], bullets[i]);
            }
            for (int i = 0; i < bullets.size(); i++) {
                CollideEnemies(lev[9], bullets[i]);
            }


            for (int i = 0; i < enemies_num; i++)
            {
                if (lev[level_index].target[i].alive && lev[level_index].target[i].dead)
                {
                    dead_enemies++;
                    lev[level_index].target[i].alive = false;
                }
            }




            if (dead_enemies == enemies_num)
            {
                stars_system(3, 2, 1, 0);
                current_menu = won_panel;
                drawLine = false;
            }

            else if (lev[level_index].num_of_bullets == 0 && level_complete && bullets.size() == 0)  ///32131563
            {
                current_menu = lost_panel;
            }

        }

        }
        else if (current_menu == level_11)
        {
            drawLine = true;
            int enemies_num = 3;
            character_rotate_arm(lev[10].killer, sf::Mouse::getPosition());

            levels_eventloop(enemies_num);
            if (current_menu >= static_cast<menu_type>(0) && current_menu <= static_cast<menu_type>(14))
            {
                DrawingLevels(10, window);
                in_level = true;
                currentLvl = 11;

                for (int i = 0; i < bullets.size(); i++) {
                    HandlePhysics(lev[10], bullets[i]);
                }
                for (int i = 0; i < bullets.size(); i++) {
                    CollideEnemies(lev[10], bullets[i]);
                }


                for (int i = 0; i < enemies_num; i++)
                {
                    if (lev[level_index].target[i].alive && lev[level_index].target[i].dead)
                    {
                        dead_enemies++;
                        lev[level_index].target[i].alive = false;
                    }
                }




                if (dead_enemies == enemies_num)
                {
                    stars_system(3, 2, 1, 0);
                    current_menu = won_panel;
                    drawLine = false;
                }

                else if (lev[level_index].num_of_bullets == 0 && level_complete && bullets.size() == 0)  ///32131563
                {
                    current_menu = lost_panel;
                }

            }

        }
        else if (current_menu == level_12)
        {
            drawLine = true;
            int enemies_num = 4;
            character_rotate_arm(lev[11].killer, sf::Mouse::getPosition());

            levels_eventloop(enemies_num);
            if (current_menu >= static_cast<menu_type>(0) && current_menu <= static_cast<menu_type>(14))
            {
                DrawingLevels(11, window);
                in_level = true;
                currentLvl = 12;

                for (int i = 0; i < bullets.size(); i++) {
                    HandlePhysics(lev[11], bullets[i]);
                }
                for (int i = 0; i < bullets.size(); i++) {
                    CollideEnemies(lev[11], bullets[i]);
                }


                for (int i = 0; i < enemies_num; i++)
                {
                    if (lev[level_index].target[i].alive && lev[level_index].target[i].dead)
                    {
                        dead_enemies++;
                        lev[level_index].target[i].alive = false;
                    }
                }




                if (dead_enemies == enemies_num)
                {
                    stars_system(3, 2, 1, 0);
                    current_menu = won_panel;
                    drawLine = false;
                }

                else if (lev[level_index].num_of_bullets == 0 && level_complete && bullets.size() == 0)  ///32131563
                {
                    current_menu = lost_panel;
                }

            }

        }
        else if (current_menu == level_13)
        {
            drawLine = true;
            int enemies_num = 4;
            character_rotate_arm(lev[12].killer, sf::Mouse::getPosition());

            levels_eventloop(enemies_num);
            if (current_menu >= static_cast<menu_type>(0) && current_menu <= static_cast<menu_type>(14))
            {
                DrawingLevels(12, window);
                in_level = true;
                currentLvl = 13;

                for (int i = 0; i < bullets.size(); i++) {
                    HandlePhysics(lev[12], bullets[i]);
                }
                for (int i = 0; i < bullets.size(); i++) {
                    CollideEnemies(lev[12], bullets[i]);
                }


                for (int i = 0; i < enemies_num; i++)
                {
                    if (lev[level_index].target[i].alive && lev[level_index].target[i].dead)
                    {
                        dead_enemies++;
                        lev[level_index].target[i].alive = false;
                    }
                }




                if (dead_enemies == enemies_num)
                {
                    stars_system(3, 2, 1, 0);
                    current_menu = won_panel;
                    drawLine = false;
                }

                else if (lev[level_index].num_of_bullets == 0 && level_complete && bullets.size() == 0)  ///32131563
                {
                    current_menu = lost_panel;
                }

            }

        }
        else if (current_menu == level_14)
        {
            drawLine = true;
            int enemies_num = 1;
            character_rotate_arm(lev[13].killer, sf::Mouse::getPosition());

            levels_eventloop(enemies_num);
            if (current_menu >= static_cast<menu_type>(0) && current_menu <= static_cast<menu_type>(14))
            {
                DrawingLevels(13, window);
                in_level = true;
                currentLvl = 14;

                for (int i = 0; i < bullets.size(); i++) {
                    HandlePhysics(lev[13], bullets[i]);
                }
                for (int i = 0; i < bullets.size(); i++) {
                    CollideEnemies(lev[13], bullets[i]);
                }


                for (int i = 0; i < enemies_num; i++)
                {
                    if (lev[level_index].target[i].alive && lev[level_index].target[i].dead)
                    {
                        dead_enemies++;
                        lev[level_index].target[i].alive = false;
                    }
                }




                if (dead_enemies == enemies_num)
                {
                    stars_system(3, 2, 1, 0);
                    current_menu = won_panel;
                    drawLine = false;
                }

                else if (lev[level_index].num_of_bullets == 0 && level_complete && bullets.size() == 0)  ///32131563
                {
                    current_menu = lost_panel;
                }

            }

        }
        else if (current_menu == level_15)
        {
            drawLine = true;
            int enemies_num = 1;
            character_rotate_arm(lev[14].killer, sf::Mouse::getPosition());

            levels_eventloop(enemies_num);
            if (current_menu >= static_cast<menu_type>(0) && current_menu <= static_cast<menu_type>(14))
            {
                DrawingLevels(14, window);
                in_level = true;
                currentLvl = 15;

                for (int i = 0; i < bullets.size(); i++) {
                    HandlePhysics(lev[14], bullets[i]);
                }
                for (int i = 0; i < bullets.size(); i++) {
                    CollideEnemies(lev[14], bullets[i]);
                }


                for (int i = 0; i < enemies_num; i++)
                {
                    if (lev[level_index].target[i].alive && lev[level_index].target[i].dead)
                    {
                        dead_enemies++;
                        lev[level_index].target[i].alive = false;
                    }
                }




                if (dead_enemies == enemies_num)
                {
                    stars_system(3, 2, 1, 0);
                    current_menu = won_panel;
                    drawLine = false;
                }

                else if (lev[level_index].num_of_bullets == 0 && level_complete && bullets.size() == 0)  ///32131563
                {
                    current_menu = lost_panel;
                }

            }

        }


        else if (current_menu == Dules_1)
        {
            if (bullets.size() == 0) {
                Bullet newBullet;
                newBullet.bulletBody.setFillColor(sf::Color::Black);
                newBullet.bulletBody.setRadius(50.f);
                newBullet.bulletBody.setOrigin(newBullet.bulletBody.getLocalBounds().width / 2, newBullet.bulletBody.getLocalBounds().height / 2);
                newBullet.b.setRadius(10.f);
                newBullet.b.setOrigin(newBullet.b.getLocalBounds().width / 2, newBullet.b.getLocalBounds().height / 2);
                newBullet.b.setPosition(newBullet.bulletBody.getPosition());
                newBullet.b.setFillColor(Color::Black);
                bullets.push_back(newBullet);
            }
            //lev[level_index].num_of_bullets = 1;
            window.draw(Pause_menu_button);
            levels_background();
            if (playerOne.turn)
            {
                character_rotate_arm(playerOne, sf::Mouse::getPosition());
            }
            else {
                character_rotate_arm(playerTwo, sf::Mouse::getPosition());

            }
            for (int i = 0; i < bullets.size(); i++) {
                bullets[i].bulletBody.setPosition(bullets[i].bulletBody.getPosition() - bullets[i].bulletDirection * 25.f);
            }
            DrawingLevels(16, window);
            for (int i = 0; i < bullets.size(); i++) {
                HandlePhysics(lev[16], bullets[i]);
            }
            duels();
            healthBar(playerOne, playerTwo);
            Duels_eventLoop();
            if (playerOne.turn)
            {
                if (collided)
                {
                    collision(bullets[bullets.size() - 1], playerTwo);
                }
            }
            else
            {
                if (collided)
                {
                    collision(bullets[bullets.size() - 1], playerOne);
                }
            }
        }

        else if (current_menu == Dules_2)
        {
        if (bullets.size() == 0) {
            Bullet newBullet;
            newBullet.bulletBody.setFillColor(sf::Color::Black);
            newBullet.bulletBody.setRadius(50.f);
            newBullet.bulletBody.setOrigin(newBullet.bulletBody.getLocalBounds().width / 2, newBullet.bulletBody.getLocalBounds().height / 2);
            newBullet.b.setRadius(10.f);
            newBullet.b.setOrigin(newBullet.b.getLocalBounds().width / 2, newBullet.b.getLocalBounds().height / 2);
            newBullet.b.setPosition(newBullet.bulletBody.getPosition());
            newBullet.b.setFillColor(Color::Black);
            bullets.push_back(newBullet);
        }
        //lev[level_index].num_of_bullets = 1;
        window.draw(Pause_menu_button);
        levels_background();
        if (playerOne.turn)
        {
            character_rotate_arm(playerOne, sf::Mouse::getPosition());
        }
        else {
            character_rotate_arm(playerTwo, sf::Mouse::getPosition());

        }
        for (int i = 0; i < bullets.size(); i++) {
            bullets[i].bulletBody.setPosition(bullets[i].bulletBody.getPosition() - bullets[i].bulletDirection * 25.f);
        }
        DrawingLevels(17, window);
        for (int i = 0; i < bullets.size(); i++) {
            HandlePhysics(lev[16], bullets[i]);
        }
        duels();
        healthBar(playerOne, playerTwo);
        Duels_eventLoop();
        if (playerOne.turn)
        {
            if (collided)
            {
                collision(bullets[bullets.size() - 1], playerTwo);
            }
        }
        else
        {
            if (collided)
            {
                collision(bullets[bullets.size() - 1], playerOne);
            }
        }
        }

        else if (current_menu == Dules_3)
        {
        if (bullets.size() == 0) {
            Bullet newBullet;
            newBullet.bulletBody.setFillColor(sf::Color::Black);
            newBullet.bulletBody.setRadius(50.f);
            newBullet.bulletBody.setOrigin(newBullet.bulletBody.getLocalBounds().width / 2, newBullet.bulletBody.getLocalBounds().height / 2);
            newBullet.b.setRadius(10.f);
            newBullet.b.setOrigin(newBullet.b.getLocalBounds().width / 2, newBullet.b.getLocalBounds().height / 2);
            newBullet.b.setPosition(newBullet.bulletBody.getPosition());
            newBullet.b.setFillColor(Color::Black);
            bullets.push_back(newBullet);
        }
        //lev[level_index].num_of_bullets = 1;
        window.draw(Pause_menu_button);
        levels_background();
        if (playerOne.turn)
        {
            character_rotate_arm(playerOne, sf::Mouse::getPosition());
        }
        else {
            character_rotate_arm(playerTwo, sf::Mouse::getPosition());

        }
        for (int i = 0; i < bullets.size(); i++) {
            bullets[i].bulletBody.setPosition(bullets[i].bulletBody.getPosition() - bullets[i].bulletDirection * 25.f);
        }
        DrawingLevels(18, window);
        for (int i = 0; i < bullets.size(); i++) {
            HandlePhysics(lev[16], bullets[i]);
        }
        duels();
        healthBar(playerOne, playerTwo);
        Duels_eventLoop();
        if (playerOne.turn)
        {
            if (collided)
            {
                collision(bullets[bullets.size() - 1], playerTwo);
            }
        }
        else
        {
            if (collided)
            {
                collision(bullets[bullets.size() - 1], playerOne);
            }
        }
        }

        else if (current_menu == Dules_4)
        {
        if (bullets.size() == 0) {
            Bullet newBullet;
            newBullet.bulletBody.setFillColor(sf::Color::Black);
            newBullet.bulletBody.setRadius(50.f);
            newBullet.bulletBody.setOrigin(newBullet.bulletBody.getLocalBounds().width / 2, newBullet.bulletBody.getLocalBounds().height / 2);
            newBullet.b.setRadius(10.f);
            newBullet.b.setOrigin(newBullet.b.getLocalBounds().width / 2, newBullet.b.getLocalBounds().height / 2);
            newBullet.b.setPosition(newBullet.bulletBody.getPosition());
            newBullet.b.setFillColor(Color::Black);
            bullets.push_back(newBullet);
        }
        //lev[level_index].num_of_bullets = 1;
        window.draw(Pause_menu_button);
        levels_background();
        if (playerOne.turn)
        {
            character_rotate_arm(playerOne, sf::Mouse::getPosition());
        }
        else {
            character_rotate_arm(playerTwo, sf::Mouse::getPosition());

        }
        for (int i = 0; i < bullets.size(); i++) {
            bullets[i].bulletBody.setPosition(bullets[i].bulletBody.getPosition() - bullets[i].bulletDirection * 25.f);
        }
        DrawingLevels(19, window);
        for (int i = 0; i < bullets.size(); i++) {
            HandlePhysics(lev[16], bullets[i]);
        }
        duels();
        healthBar(playerOne, playerTwo);
        Duels_eventLoop();
        if (playerOne.turn)
        {
            if (collided)
            {
                collision(bullets[bullets.size() - 1], playerTwo);
            }
        }
        else
        {
            if (collided)
            {
                collision(bullets[bullets.size() - 1], playerOne);
            }
        }
        }



        if (in_level) {
            //if (lev[level_index + 1].view.Level_evaluation < 0) {
            //    lev[level_index + 1].view.Level_evaluation = 0;
            //}
            character_rotate_arm(lev[level_index].killer, sf::Mouse::getPosition());
            levels_background();
            //if (drawLine)
                //window.draw(line);

        }

        if (current_menu >= static_cast<menu_type>(0) && current_menu <= static_cast<menu_type>(14) || current_menu == Dules_1 || current_menu == Dules_2 || current_menu == Dules_3 || current_menu == Dules_4)
        {
            for (int i = 0; i < bullets.size(); i++) {
                //window.draw(bullets[i].bulletBody);
                window.draw(bullets[i].b);
            }
        }
        window.display();
    }

	return 0;
}


