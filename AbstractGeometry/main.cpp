#define _USE_MATH_DEFINES
#include<Windows.h>
#include<iostream>
#include<math.h>

using namespace std;


namespace Geometry
{
	enum Color  // enum (Enumeration) - это перечисление. Перечисление - это набор целочисленных констант
	{
		YELLOW = 0x0000FFFF,
		CONSOLE_BLUE = 0x09,
		CONSOLE_GREEN = 0xAA,
		CONSOLE_RED = 0xCC,
		CONSOLE_DEFAULT = 0x07,
		RGB_RED = (0xFF0000), //Добавляем RGB цвета
		RGB_GREEN = (0x00FF00),
		RGB_BLUE = (0xFFFF00),
		RGB_WHITE = (0xFFFFFF)
	};
#define SHAPE_TAKE_PARAMETERS unsigned int start_x, unsigned start_y,unsigned int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width,color

	class Shape
	{
	protected: //защищенные поля, доступны только внутри класса и внутри его дочерних классов
		//благодаря protected  к этим полям можно обращаться напрямую в дочерниъ классах
		Color color;
		//координаты по которым будет выводиться фигура
		unsigned int start_x;
		unsigned int start_y;
		//в любой графической оболочке координаты задаются в пикселях
		// Начало координат всегда находится в левом верхнем углу
		unsigned int line_width; //толщина линии, которой будет рисоваться контур фигуры
	public:
		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);

		}  
		//КОНСТРУКТОР И ВИРТ.ДЕСТРУКТОР
		virtual ~Shape() {}   // {}пустая реализация, если ставить ; то нужно где то реализовывать
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		Color get_color()const { return color; }  //Geters
		void set_color(Color color) { this->color = color; }  //Seters
		unsigned int get_start_x()const
		{
			return start_x;
		}
		unsigned int get_start_y()const
		{
			return start_y;
		}
		unsigned int get_line_width()const
		{
			return line_width;
		}

		void set_start_x(unsigned int star_x)
		{
			this->start_x = start_x;
		}
		void set_start_y(unsigned int star_y)
		{
			this->start_y = start_y;
		}
		void set_line_width(unsigned int line_width)
		{
			this->line_width = line_width;
		}
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	class Rectangle :public Shape
	{
		double width;
		double height;
	public:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_height(height);
		}
		virtual ~Rectangle() {};
		double get_area()const override
		{
			return width * height;
		}
		double get_perimeter()const override
		{
			return(width + height) * 2;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow(); //1)Получаем дескриптор окна консоли. Переменная в которой хранится описание чего-то.
			//description 
			//HWND - Handler to Window(обработчик или дескриптор окна)
			HDC hdc = GetDC(hwnd); //2) получаем контекст устройства (Device context) окна консоли
			//DC - это то на чем мы будем рисовать
			HPEN hPen = CreatePen(PS_SOLID, 5, get_color());
			//3) Создаем карандаш, Pen рисует контур фигуры
			//PS_SOLID - сплошная линия
			//5-толщина линии в пикселях
			// 4) cоздаем кисточку
			HBRUSH hBrush = CreateSolidBrush(Geometry::Color::RGB_BLUE);
			//5) Выбираем чем и на чем рисовать
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			//6) Рисуем прямоугольник:
			//::Rectangle(hdc, 250, 50, 400, 150);
			::Rectangle(hdc, start_x,start_y,start_x+width,start_y+height);
			//start_x,start_y -- координаты верхнего левого угла
			// 800,350 -- размеры
			//чтобы показать что это глобальная функция надо поставить двойное двоеточие без операнда слева.
			//7) Освобождаем ресурсы:
			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
			/*for (int i = 0; i < height; i++)
			{
				for (int i = 0; i < width; i++)
				{
					cout << "* ";
				}
				cout << endl;
			}*/
		}
		double get_width()const
		{
			return width;
		}
		double get_height()const
		{
			return height;
		}
		void set_width(double width)
		{
			this->width = width;
		}
		void set_height(double height)
		{
			this->height = height;
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина: " << get_width() << endl;
			cout << "Высота: " << get_height() << endl;
			Shape::info();
		}
	};

	class Square :public Rectangle
	{
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
	};

	class Circle :public Shape
	{
		double radius;
	public:
		double get_radius()const
		{
			return radius;

		}

		void set_radius(double radius)
		{
			this->radius = radius;
		}
		Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);
		}
		~Circle() {}
		double get_area()const override
		{
			return  M_PI * radius * radius;
		}
		double get_perimeter()const override
		{
			return M_PI * get_diameter();
		}
		void draw()const override
		{
			HWND hvnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);

			HPEN hpen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd,hdc)
		}
	};
}

void main() 
{
	setlocale(LC_ALL, "Rus");
	
	Geometry::Square square(50, 300,50,5, Geometry::Color::CONSOLE_BLUE);
	square.info();

	Geometry::Rectangle rect{ 150, 80,500,50,3, Geometry::Color::CONSOLE_BLUE };
	rect.info();
	//Geometry::Square rect(10, 6, Geometry::Color::CONSOLE_DEFAULT);
	//rect.info();

	Geometry::Circle circle(75, 700, 50, 5, Geometry::Сolor::YELLOW);
	circle.info();
}