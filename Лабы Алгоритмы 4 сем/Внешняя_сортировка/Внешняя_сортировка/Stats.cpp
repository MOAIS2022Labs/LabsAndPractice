#include "Stats.h"

void calculate_stats()
{

	int left = 1; // левое значение икса
	int right = 31; // правое значение икса

	for (int i = left; i <= right; i += 5)
	{

		int count = i * 10000;

		std::string filename = "test.bin";
		std::fstream file(filename);
		fill_file(file, count); // генерим файл 
		file.close();

		auto start_time = std::chrono::steady_clock::now();
		sorting(filename);
		auto end_time = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
		std::cout << i << "0000 elements " << duration.count() << " milliseconds\n";
	}
	std::cout << '\n';
}

void build_graphic()
{
	const int WIDTH = 1602;
	const int HEIGHT = 402;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), L"Зависимость времени выполнения от количества элементов");

	int x0 = 22;
	int y0 = HEIGHT - 100;

	sf::CircleShape point(3.f);
	point.setFillColor(sf::Color::Red);

	int left = 1;
	int right = 50;

	int mass = (right - left) - 5;

	int sc = 30;

	sf::Texture t;
	//t.loadFromFile("Coordinate.png");
	t.loadFromFile("Graphic.jpg");
	sf::Sprite pic(t);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
		window.draw(pic);

		for (int i = 0; i < mass; ++i)
		{
			float x = left + i;



			float count = x * 10000;

			std::string filename = "test.bin";
			std::fstream file(filename);
			fill_file(file, count); // генерим файл 
			file.close();
			//auto start = std::chrono::high_resolution_clock::now();
			//sorting(filename); // Вызов функции сортировки
			//auto end = std::chrono::high_resolution_clock::now();
			//std::chrono::duration<float> duration = end - start;

			auto start_time = std::chrono::steady_clock::now();
			sorting(filename);
			auto end_time = std::chrono::steady_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

			float y = duration.count();
			float x1 = x0 + x * sc;
			float y1 = y0 - y * sc;

			point.setPosition(x1 - 1, y1 - 1);
			window.draw(point);
		}
		window.display();
	}
}