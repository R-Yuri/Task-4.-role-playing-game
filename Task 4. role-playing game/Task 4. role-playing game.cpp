//контрльная версия для cline
#include <iostream>                  //ну, это понятно
#include <fstream>                   //библиотека потоков записи в файл и загрузки из файла
#include <cstdlib>                   //стандартная библиотека...хмммм, пока непонятно для чего
#include <ctime>                     //библиотека времени для рандомного генератора
#include <conio.h>                   //для считывания символа без enter  _getch() function
#include <cstdlib>                   //Хммм....

struct Coordinates {                 //структура координаты
    int x = 0;
    int y = 0;
};

struct Player {                      //структура игрока
    std::string name;                //имя
    int life=0;                      //жизнь
    int armor=0;                     //броня
    int damage=0;                    //урон
    Coordinates positionP;           //координаты
};

struct Enemy {                       //структура врагов
    int life=0;                      //жизнь
    int armor=0;                     //броня
    int damage=0;                    //урон
    Coordinates positionE;           //координаты
};

struct Igra {                        //структура игры, наверное для записи в  файл
    Player player;
    Enemy enemy[5];
};

//функция генератора random чисел по заданному познее диапазону min, max
int generateRN(int min, int max) {
    static bool initialized = false;
    if (!initialized) {
        srand(time(NULL));
        initialized = true;
    }
    int randomNumber = min + rand() % (max - min + 1);
    return randomNumber;
}

//функция инициализации врагов в начале игры
void enemyInt(Igra& game, Enemy enemy[5]) {                      
 for (int i = 0; i < 5; i++) {                                   //возможны одинаковые координаты!!!!!!!!!!!!!!

        game.enemy[i].life = generateRN(50, 150);                //жизнь
        game.enemy[i].armor = generateRN(0, 50);                 //броня
        game.enemy[i].damage = generateRN(15, 30);               //урон
        
        //новые координаты
        game.enemy[i].positionE.x = generateRN(1, 20);
        game.enemy[i].positionE.y = generateRN(1, 20);
        
        bool isDuplicateE = true;                                //применяем лог переменную для выхода из цикла
        while (isDuplicateE) {
            

            //std::cout << "enemy x= "<< enemy[i].positionE.x <<" y= " <<enemy[i].positionE.y<< std::endl;   //chek point
            //проверяем на совпадения
            isDuplicateE = false;
            for (int j = 0; j < i; j++) {
                if (game.enemy[i].positionE.x == game.enemy[j].positionE.x && game.enemy[i].positionE.y == game.enemy[j].positionE.y) {
                    std::cout << "enemy sovpadenie!!!!" << std::endl;
                    game.enemy[i].positionE.x = generateRN(1, 20);
                    game.enemy[i].positionE.y = generateRN(1, 20);

                    isDuplicateE = true;
                    break;
                }
            }
        }
    }
}

//функция валидации ввода int player
int valid(int value, int vMin, int vMax) {
    while (true) {
        if (std::cin.fail()) {
            std::cin.clear();                           // Clear the error flag
            std::cin.ignore(1000, '\n');                // Ignore up to 1000 characters or until a newline is found
        }
        else if (value >= vMin && value <= vMax) {
            break;
        }
        else {
            std::cout << "error...input life (" << vMin << "-" << vMax << ")" << std::endl;
            std::cin >> value;
        }
    }
    return value;
}

//функция инициализации игрока
void playerInt(Igra& game,Enemy enemy[5], Player& player) {

    //заполняем информацию по игроку
    std::cout << "name player: ";
    std::cin >> game.player.name;

    std::cout << "input life (50-200): ";
    int value = 0;
    int vMin = 50;
    int vMax = 200;
    std::cin >> value;
    valid(value, vMin, vMax);                       //вызов функции валидации ввода player
    game.player.life = value;

    std::cout << "input armor (1-100)";
    value = 0;
    vMin = 1;                  //должен быть ноль, но тогда проверка диапазона не работает, можно конечно заморочиться и +1 для проверки.....
    vMax = 100;
    std::cin >> value;
    valid(value, vMin, vMax);                       //проверка диапазона
    game.player.armor = value;

    std::cout << "input damage (15-30)";
    value = 0;
    vMin = 15;
    vMax = 30;
    std::cin >> value;
    valid(value, vMin, vMax);
    game.player.damage = value;

    bool isDuplicateP = true;                                //применяем лог переменную для выхода из цикла
    while (isDuplicateP) {
        //новые координаты игрока

        game.player.positionP.x = generateRN(1, 20);         //начальные координаты x
        game.player.positionP.y = generateRN(1, 20);         //начальные координаты y

        //проверяем на совпадения
        isDuplicateP = false;
        for (int i = 0; i < 5; i++) {
            if (game.enemy[i].positionE.x == game.player.positionP.x && game.enemy[i].positionE.y == game.player.positionP.y) {
                std::cout << "igrok sovpadenie!!!!!!" << std::endl;
                isDuplicateP = true;
                break;
            }
        }
    }
}

//функция вывода игрового поля с живыми персонажами 
void PlayingField(Igra& game,Enemy enemy[5],Player& player) {  // std::vector<Enemy> enemies не стал применять
    const int FIELD_SIZE = 20;                                 //размер поля 20x20 клеток
    std::cout << "==============================================================" << std::endl;
    for (int i = 0; i <= FIELD_SIZE; i++) {
        if (i == 0) {
            std::cout << "    ";                     //смещаем по строке цифру 1 на три пробела, что бы попасть в начало поля
            for (int j = 1; j <= FIELD_SIZE; j++) {  //печатаем цифры по горизонтали с пробелами для выравнивания
                if (j<10) {
                std::cout << j << "  ";              //с двумя пробелами для выравнивания
                }
                else  std::cout << j << " ";         //с одним пробелом  для выравнивания
            }
        }
        else {
            if (i < 10) {                            //печатаем вертикальные цифры
                std::cout << " ";                    //печатаем слева пробел перед 123456789 для выравнивания
            }
            std::cout << i << " ";
        }

        //выводим положение player и enemies, иначе выводим "."
        
        for (int j = 1; j <= FIELD_SIZE; j++) {
            
            if ((i == game.player.positionP.x) && (j == game.player.positionP.y)) {  
                
                std::cout << " P ";
            }
            else if ((i== game.enemy[0].positionE.x) && (j== game.enemy[0].positionE.y) && (game.enemy[0].life>0)) {         
               std::cout << " E1";
            }
            else if ((i == game.enemy[1].positionE.x) && (j == game.enemy[1].positionE.y) && (game.enemy[1].life > 0)) {
               std::cout << " E2";
            }
            else if ((i == game.enemy[2].positionE.x) && (j == game.enemy[2].positionE.y) && (game.enemy[2].life > 0)) {
               std::cout << " E3";
            }
            else if ((i == game.enemy[3].positionE.x) && (j == game.enemy[3].positionE.y) && (game.enemy[3].life > 0)) {
               std::cout << " E4";
            }
            else if ((i == game.enemy[4].positionE.x) && (j == game.enemy[4].positionE.y) && (game.enemy[4].life > 0)) {
               std::cout << " E5";
            }
               else if (i > 0)                                 //что бы печатать со второй строки точки
               std::cout << " . ";
        }
        std::cout << std::endl;
    }
    std::cout << "==============================================================" << std::endl;
}

//функция вывода инфы по игрокам под полем
void info(Igra& game,Enemy enemy[5], Player& player) {   // std::vector<Enemy> enemies
    // Print out the player information
    std::cout << "Player: " << game.player.name << "\t life: " << game.player.life << "\t  armor: " << game.player.armor << "\t    damage: " << game.player.damage << std::endl;

    std::cout << "==============================================================" << std::endl;
    
    for (int i = 0; i < 5; i++) {  //enemies.size()  если использовать разное кол-во плохишей
        std::cout << "Enemy " << i + 1 << "\t         life: " << game.enemy[i].life << "\t  armor: " << game.enemy[i].armor << "\t    damage: " << game.enemy[i].damage << std::endl;

    }
    std::cout << "==============================================================" << std::endl;
}

//функция перемещения игрока при нажатии клавиш
void movePlayer(Igra& game,Player& player,char key) {
    //проверка текущих кординат игрока для невыхода за пределы карты
    if (key=='a' && game.player.positionP.y > 1) {                  //вверх      
        game.player.positionP.y--;
    }
    else if (key == 'd'&& game.player.positionP.y < 20) {           //вниз
        game.player.positionP.y++;
    }
    else if (key=='w' && game.player.positionP.x > 1) {             //влево
        game.player.positionP.x--;
    }
    else if (key=='s'  && game.player.positionP.x < 20) {           //вправо
        game.player.positionP.x++;
    }   
}

//функция  random перемещения плохишей в игре с поверкой выхода за поля, 
//и на попадание в ранее занятые координаты
void moveEnemy(Igra& game,Enemy enemy[5]) {   
    
    for (int i = 0; i < 5;i++) {

        bool isDuplicateE = true;                               //применяем лог переменную для выхода из цикла while
        while (isDuplicateE) {

            int dx = generateRN(-1, 1);                         //генерация шага в пределах -1,0,+1, что бы ходили и по диагонали
            int dy = generateRN(-1, 1);

            if (game.enemy[i].positionE.x + dx <= 1) {          //корекция координат с целью отодвинуть от границы поля                                               
                dx += 1;                                        //а то прилипает к границе и там стоит                             
            }
            else if (game.enemy[i].positionE.y + dy <= 1) {
                dy += 1;
            }
            else if (game.enemy[i].positionE.x + dx >= 20) {
                dx -= 1;                            
            }
            else if (game.enemy[i].positionE.y + dy >= 20) {
                dy -= 1;
            }
            else {
                game.enemy[i].positionE.x += dx;                 //или новые координаты
                game.enemy[i].positionE.y += dy;

                isDuplicateE = false;
                for (int j = 0; j < i; j++) {

                    if (game.enemy[i].positionE.x == game.enemy[j].positionE.x && game.enemy[i].positionE.y == game.enemy[j].positionE.y) {
                        isDuplicateE = true;
                        break;
                    } 

                }

            }
  
        } //конец цикла while---------------------------------------------------------      
    
    }

}

//функция вычисления нанесенного урона [i] плохишу
void playerSteppedOnEnemy(Igra& game,Enemy enemy[5], Player& player) {  
    for (int i = 0; i < 5; i++) {
    if (game.enemy[i].positionE.x == game.player.positionP.x && game.enemy[i].positionE.y == game.player.positionP.y) {
        //считаем урон плохишу
        if (game.enemy[i].armor>= game.player.damage) {
            game.enemy[i].armor -= game.player.damage;
        }
        else if (game.enemy[i].armor< game.player.damage&& game.enemy[i].armor!=0) {
            int osttatokUrona = game.player.damage - game.enemy[i].armor;
            game.enemy[i].life-=osttatokUrona;
            game.enemy[i].armor = 0;
        }
        else if (game.enemy[i].armor==0) {
            game.enemy[i].life -= game.player.damage;
            if (game.enemy[i].life <= 1) {
                game.enemy[i].life = 0;
            }
        }

    }
}



}

//функция вычисления нанесенного урона игроку
void enemySteppedOnPlayer(Igra& game,Enemy enemy[5], Player& player) {

    for (int i = 0; i < 5; i++) {
        if (game.enemy[i].positionE.x == game.player.positionP.x && game.enemy[i].positionE.y == game.player.positionP.y) {
            //считаем урон игроку
            if (game.player.armor >= game.enemy[i].damage) {
                game.player.armor -= game.enemy[i].damage;
            }
            else if (game.player.armor < game.enemy[i].damage && game.player.armor != 0) {
                int osttatokUrona = game.enemy[i].damage - game.player.armor;
                game.player.life -= osttatokUrona;
                game.player.armor = 0;
            }
            else if (game.player.armor == 0) {
                game.player.life -= game.enemy[i].damage;
                if (game.player.life <= 1) {
                    game.player.life = 0;
                }
            }

        }

    }
}

char pobeda(Igra& game,Enemy enemy[5], Player& player,char key) {
    if (game.player.life==0) {
        std::cout << "Igrok proigral" << std::endl;
        return key = 'x';
    }
    else {
        for (int i = 0; i < 5; i++) {
            if (game.enemy[0].life == 0 && game.enemy[1].life == 0 && game.enemy[2].life == 0 && game.enemy[3].life == 0 && game.enemy[4].life == 0) {

                std::cout << "Pobeda!!!!!!" << std::endl;
                return key = 'x';
            }

        }

    }
        
}

//функция записи в файл 
void saveGame(Igra game,Enemy enemy[5], Player& player) {                      

    //проверка на наличие файла
    std::ifstream infile("game.bin", std::ios::binary);
    if (infile) {
        // если файл открыт , прелагаем его перезаписать
        std::cout << "The file 'game.bin' already exists. Overwrite? (y/n): ";
        char response;
        std::cin >> response;
        if (response != 'y' && response != 'Y') {
            // если нет, то выход
            std::cout << "Save aborted." << std::endl;
            return;
        }
    }
    infile.close();  //закрытие , открытого на чтение потока или файла?

    std::ofstream outfile("game.bin", std::ios::binary);  //открытие файла .bin на запись 
    //std::ofstream outfile("game.bin");
    if (!outfile) {
        std::cout << "Failed to create the file 'game.bin'" << std::endl;
        return;
    }
    //записываем информацию по игроку
    int len = game.player.name.length();                                              //вычисляем длину строки имени игрока
    outfile.write((char*)&len, sizeof (len));                                         //записали в поток переменную счётчик
    outfile.write(game.player.name.c_str(), len);                                     //записали саму переменную
    outfile.write((char*)&game.player.life,sizeof(game.player.life));                 //записали жизнь
    outfile.write((char*)&game.player.armor, sizeof(game.player.armor));              //записали броню
    outfile.write((char*)&game.player.damage, sizeof(game.player.damage));            //записали урон
    outfile.write((char*)&game.player.positionP.x, sizeof(game.player.positionP.x));  //координаты правильно x
    outfile.write((char*)&game.player.positionP.y, sizeof(game.player.positionP.y));  //координаты правильно y

    //записываем инфу по плохишам в цикле
    for (int i = 0; i < 5; i++) {
        outfile.write((char*)&game.enemy[i].life, sizeof(game.enemy[i].life));
        outfile.write((char*)&game.enemy[i].armor, sizeof(game.enemy[i].armor));
        outfile.write((char*)&game.enemy[i].damage, sizeof(game.enemy[i].damage));
        outfile.write((char*)&game.enemy[i].positionE.x, sizeof(game.enemy[i].positionE.x));
        outfile.write((char*)&game.enemy[i].positionE.y, sizeof(game.enemy[i].positionE.y));
    }
    outfile.close();
    std::cout << "Game saved to file 'game.bin'" << std::endl;
}

//функция чтения из файла
bool loadGame(Igra& game,Enemy enemy[5], Player& player ) {  //, bool loadFile

    std::ifstream infile("game.bin", std::ios::binary);              
    if (!infile) {
        std::cout << "Failed to open the file 'game.bin'" <<std:: endl;
        //loadFile = false;
        //std::cout << "loadFile : " << loadFile << std::endl  //выдаёт правильное значение false 
        return false;
    }
    
    int len;                                                                        //загружаем длину имени игрока
    infile.read((char*)&len, sizeof(len));
    game.player.name.resize(len);                                                   //буфер для символов

    infile.read((char*)game.player.name.c_str(), len);                              //имя
    //std::cout << "load name " << game.player.name << std::endl;                   //test point
    infile.read((char*)&game.player.life,sizeof(game.player.life));                 //жизнь
    infile.read((char*)&game.player.armor, sizeof(game.player.armor));
    infile.read((char*)&game.player.damage, sizeof(game.player.damage));
    infile.read((char*)&game.player.positionP.x, sizeof(game.player.positionP.x));
    infile.read((char*)&game.player.positionP.y, sizeof(game.player.positionP.y));
    
    for (int i = 0; i < 5; i++) {
        infile.read((char*)&game.enemy[i].life, sizeof(game.enemy[i].life));
        infile.read((char*)&game.enemy[i].armor, sizeof(game.enemy[i].armor));
        infile.read((char*)&game.enemy[i].damage, sizeof(game.enemy[i].damage));
        infile.read((char*)&game.enemy[i].positionE.x, sizeof(game.enemy[i].positionE.x));
        infile.read((char*)&game.enemy[i].positionE.y, sizeof(game.enemy[i].positionE.y));
    }
    infile.close();
    std::cout << "File load ok" << std::endl;
    //return true;
}

int main() {

    Player player;
    Enemy enemy[5];
    Igra  game;
    //bool loadFile = true;         //функция loadGame работает с этой переменной, выдает правильно false  когда нет файла
    
    // загружаем файл или создаём новый -----------------------------------------------------------------------
    std::string instruction;
    std::cout << "vvedite komandu 'load' or 'no'" << std::endl;
    std::cin >> instruction;

    while (true)                                           //цикл валидации ввода
    {
        if (instruction == "load" || instruction == "no") {
            break;
        }
        std::cout << "error, input move ";
        std::cin >> instruction;
    }
    if (instruction == "load") {
        loadGame(game, enemy, player);
        if (!loadGame(game, enemy, player)) {   //(!loadGame)  здесь почему-то равна  true    //а через функцию некрасиво получается , второй раз выводит сообщение
            instruction = "no";
        }else std::cout << "Fail load ok" << std::endl;;
    }
    if (instruction=="no") {
        std::cout << "playing a new game...." << std::endl;
        //заполняем  первую информацию по врагам и игроку
        enemyInt(game,enemy);                   
        playerInt(game, enemy, player);
    }

    std::cout << std::endl;
    std::cout << "\x1b[2J\x1b[1;1H";                    //очищает консоль и перемещает курсор в начало координат
    PlayingField(game,enemy,player);                    //вызов фукции отрисовки карты c игроками
    info(game, enemy,player);                           //вызов функции отрисовки инфы

    //ИГРА-----------------------------------------------------------------------------------
    char key = '0';
    while (key != 'x') {
        std::cout << "igrok input SAVE=v, LOAD=l, UP=w,RIGHT=a,DOWN=s,RIGHT=d,EXIT=x" << std::endl;
        char key = _getch();                            //применяем _getch() для считывания и выполнения  клавиши без enter
        while (true)
        {
            if (key == 'w' || key == 'a' || key == 's' || key == 'd' || key == 'x' || key == 'v' || key == 'l') {
                break;
            }
            std::cout << "error, input move ";
            std::cin >> key;
        }
        if (key == 'v') {
            saveGame(game, enemy, player);
            //std::cout << "test v" << std::endl; 
        }
        else if (key == 'l') {
            loadGame(game, enemy, player);
            PlayingField(game, enemy, player);           
            info(game, enemy, player);                   
            //std::cout << "test l" << std::endl;
        }
        else if (key == 'x') {
            break;
        }
        else {
        movePlayer(game, player, key);                   //вызов функции расчёта координат игрока
        std::cout << "\x1b[2J\x1b[1;1H";                 
        PlayingField(game, enemy, player);               
        info(game, enemy, player);                       
        //считаем урон если попали на плохиша-----------------------------------------------------------------------
        playerSteppedOnEnemy(game, enemy, player);
        //перемещение врагов - каждый по одному ходу на -1,0 или +1 по x y то есть может ходить по диагонали
        moveEnemy(game, enemy);
        //считаем урон, если плохиш попал на игрока---------------------------------------------------------------
        enemySteppedOnPlayer(game, enemy, player);
        std::cout << "\x1b[2J\x1b[1;1H";                 
        PlayingField(game, enemy, player);               
        info(game, enemy, player);                       

            if (pobeda(game, enemy, player, key ) == 'x') {    //выводим результат победы и выходим из игры
                break;
            }                
        }
    }                                                    //конец цикла игры

    return 0;
}
