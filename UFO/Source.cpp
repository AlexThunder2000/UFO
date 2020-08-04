#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<cmath>
#include<sstream>



using namespace sf;

////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class UFO { // класс Игрока
public:
	float x, y, w, h, dx, dy, speed = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	int dir = 0; //направление (direction) движения игрока

	String File; //файл с расширением
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт
};

class updator : public UFO {
public:
	virtual void move(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	{
		switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
		{
		case 0: dx = speed; dy = 0;   break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
		case 1: dx = -speed; dy = 0;   break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
		case 2: dx = 0; dy = speed;   break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
		case 3: dx = 0; dy = -speed;   break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
		case 4: dx = 0; dy = -speed;   break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
		}
		x += dx * time;
		y += dy * time;
		
		speed = 0;//зануляем скорость, чтобы персонаж остановился.
		sprite.setPosition(x, y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
	}
	virtual void move(float time, int type,float rot) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	{

		switch (type)
		{
		case 0: x += 0 * time; y += 0.1 * time; break;
		case 1:x += 0 * time;
			y += 0.1 * time;
			
			break;
		case 3:  y -= 0.5 * time; x = 570 + ((y - 770) * tan((-rot) / 180)*4); break;
		}

		sprite.setPosition(x, y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.

	}

};

class tarelka : public updator {
public:
	tarelka(String F, float X, float Y, float W, float H) {  //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту

		File = F;//имя файла+расширение
		w = W; h = H;//высота и ширина
		image.loadFromFile("images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
		texture.loadFromImage(image);//закидываем наше изображение в текстуру
		sprite.setTexture(texture);//заливаем спрайт текстурой

		x = X; y = Y;//координата появления спрайта
		sprite.setTextureRect(IntRect(0, 0, w, h));  //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
	}
};

int main()
{


	
	SoundBuffer back_music;
	if (!back_music.loadFromFile("sound/music.wav"))
		return -1;
	Sound sound;
	sound.setBuffer(back_music);
	
	sound.play();

	
	SoundBuffer mshot;
	if (!mshot.loadFromFile("sound/shot.wav"))
		return -1;
	Sound sound2;
	sound2.setBuffer(mshot);
	sound2.setVolume(80);

	SoundBuffer mboom;
	if (!mboom.loadFromFile("sound/boom.wav"))
		return -1;
	Sound sound3;
	sound3.setBuffer(mboom);
	sound3.setVolume(40);
	
	
	Clock clock;
	Clock clock2;
	srand(time(0));
	RenderWindow window(sf::VideoMode(1200, 800), "UFO");

	tarelka back("back.png", 0, 0, 1200, 800);
	tarelka starter("start2.png", 0, 0, 1200, 800);
	tarelka lose("lose.png", 0, 0, 1280, 800);
	tarelka gun("gun.png", 550, 677, 100, 250);
	tarelka shot("shot.png", 560, 670, 44, 40);
	tarelka tarelka1("tarelka1.png", 0, 0, 250, 92);
	tarelka tarelka2("tarelka2.png", 0, 0, 200, 76);

	bool play = false;
	bool target = false;
	bool start = false;
	gun.sprite.setPosition(600, 677+125);
	float rot = 0;
	float k = 0;
	float dr = 0;

	while (window.isOpen())
	{
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			
			start = true;
			play = true;
		}
		if (!start) {
			window.draw(starter.sprite);
			clock.restart();
		}
		if (start) {
			float time = clock.getElapsedTime().asMicroseconds();
			float time2 = clock2.getElapsedTime().asMicroseconds();
			time = time / 800;
			clock.restart();


			if (play) {
				tarelka1.move(time, 1, 0);
				tarelka2.move(time, 1, 0);

			}
			if ((Keyboard::isKeyPressed(Keyboard::Escape))) {

				play = true;
				
				tarelka1.x = rand() % 1200 - tarelka1.w;
				if (tarelka1.x < 0)tarelka1.x = 0;
				tarelka1.y = -200;
				tarelka2.x = rand() % 1200 - tarelka2.w;
				if (tarelka2.x < 0)tarelka2.x = 0;
				tarelka2.y = -200;

			}
			gun.sprite.setOrigin(50, 125);
			if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
				dr = 0.1 * time;
				rot -= dr;
				if (rot < -75)rot = -75;
				gun.sprite.setRotation(rot);
			}
			if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
				dr = 0.1 * time;
				rot += dr;
				if (rot > 75)rot = 75;
				gun.sprite.setRotation(rot);
			}

			if (Keyboard::isKeyPressed(Keyboard::Space) && shot.y < 0) { //если нажата клавиша стрелка влево или англ буква А
				sound2.play();
				shot.x = 570;
				shot.y = 770;
				k = rot;
			}
			shot.move(time, 3, k);




			window.draw(back.sprite);
			window.draw(gun.sprite);
			window.draw(shot.sprite);
			window.draw(tarelka1.sprite);
			window.draw(tarelka2.sprite);






			if ((shot.x > tarelka1.x&& shot.x < tarelka1.x + tarelka1.w || shot.x + shot.w>tarelka1.x&& shot.x + shot.w < tarelka1.x + tarelka1.w) && (shot.y > tarelka1.y&& shot.y < tarelka1.y + tarelka1.h || shot.y + shot.h>tarelka1.y&& shot.y + shot.h < tarelka1.y + tarelka1.h)) {

				sound3.play();
				
				shot.y = -100;
				tarelka1.x = rand() % 1280 - tarelka1.w;
				if (tarelka1.x < 0)tarelka1.x = 0;
				tarelka1.y = -200;

			}
			if ((shot.x > tarelka2.x&& shot.x < tarelka2.x + tarelka2.w || shot.x + shot.w>tarelka2.x&& shot.x + shot.w < tarelka2.x + tarelka2.w) && (shot.y > tarelka2.y&& shot.y < tarelka2.y + tarelka2.h || shot.y + shot.h>tarelka2.y&& shot.y + shot.h < tarelka2.y + tarelka2.h)) {

				sound3.play();
				
				shot.y = -100;
				tarelka2.x = rand() % 1280 - tarelka2.w;
				if (tarelka2.x < 0)tarelka2.x = 0;
				tarelka2.y = -200;

			}
			
			

			if (tarelka1.y > 700 || tarelka2.y > 700) {
				play = false;
				window.draw(lose.sprite);
			}

		}
			
		window.display();
	}
	return 0;
}