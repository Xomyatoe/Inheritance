#define _USE_MATH_DEFINES
#include<Windows.h>
#include<iostream>
#include<math.h>
#include<winuser.h>
//#include <cstdlib> //��� ���������� ������ ������ ������������
using namespace std;


namespace Geometry
{
	enum Color  // enum (Enumeration) - ��� ������������. ������������ - ��� ����� ������������� ��������
	{
		RED = 0x000000FF,
		DARK_RED = 0x00000077,
		GREEN = 0x0000FF00,
		BLUE = 0x00FF0000,
		YELLOW = 0X0000FFFF,
		PURPLE = 0X00FF00FF,
		CONSOLE_BLUE = 0x09,
		CONSOLE_GREEN = 0xAA,
		CONSOLE_RED = 0xCC,
		CONSOLE_DEFAULT = 0x07,
	};
#define SHAPE_TAKE_PARAMETERS unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color
#define delimiter "\n--------------------------\n"
	class Shape
	{
	protected: //���������� ����, �������� ������ ������ ������ � ������ ��� �������� �������//��������� protected � ���� ����� ����� ����� ���������� �������� � �������� �������(��� ���/��� �������)
		Color color;
		unsigned int start_x; //���������� �� ������� ����� ���������� ������
		unsigned int start_y; //� ����� ������ �������� ���������� �������� � ��������
		//������ ��������� ������ ��������� � ����� ������� ����.
		unsigned int line_width; //������� �����, �����o� ����� ���������� ������ ������
		static const int MIN_START_X = 100;  //����������� ��������� 
		static const int MAX_START_X = 1000;
		static const int MIN_START_Y = 50;
		static const int MAX_START_Y = 900;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 3;
		static const int MIN_SIZE = 5;
		static const int MAX_SIZE = 60;
		//static const int MIN_RADIUS = 10;
		//static const int MAX_RADIUS = 50;
		static int count;
	public:
		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
			count++;
		}  //����������� � ����.����������
		virtual ~Shape()
		{
			count--;
		}   // {}������ ����������, ���� ������� ; �� ����� ��� �� �������������
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		static int get_count()
		{
			return count;
		}

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
		void set_start_x(unsigned int start_x)
		{
			if (start_x < MIN_START_X)start_x = MIN_START_X;
			if (start_x > MAX_START_X)start_x = MAX_START_X;
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			if (start_x < MIN_START_Y)start_x = MIN_START_Y;
			if (start_x > MAX_START_Y)start_x = MAX_START_Y;
			this->start_y = start_y;
		}
		void set_line_width(unsigned int line_width)
		{
			if (line_width < MIN_LINE_WIDTH)line_width = MIN_LINE_WIDTH;
			if (line_width > MAX_LINE_WIDTH)line_width = MAX_LINE_WIDTH;
			this->line_width = line_width;
		}
		double filter_size(double size)
		{
			if (size < MIN_SIZE) size = MIN_SIZE;
			if (size > MAX_SIZE) size = MAX_SIZE;
			return size;
		}
		virtual void info()const
		{
			cout << "������� ������: " << get_area() << endl;
			cout << "�������� ������: " << get_perimeter() << endl;
			draw();
		}
	};
	class Shapes  // ����� ������
	{
	public:
		virtual double area() const = 0;
		virtual double perimeter() const = 0;
		virtual void draw()const = 0;
	};
	int Shape::count = 0;
	/*class Square :public Shape
	{
		double side;
	public:
		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
		virtual ~Square() {}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return side * 4;
		}
		void draw()const override
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, get_color());
			for (int i = 0; i < side; i++)
			{
				for (int i = 0; i < side; i++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::CONSOLE_DEFAULT);
		}
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			this->side = side;
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "������ �������: " << side << endl;
			Shape::info();
		}


	};*/

	class Rectangle :public Shape
	{
		double width;
		double height;
	public:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS) // ����������� ��������� - GIVE
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
			HWND hwnd = FindWindowA(NULL, "Inheritance - Microsoft Visual Studio"); //������ � ���� VS
			//HWND hwnd = GetConsoleWindow(); ������ � ���� ������
			//HWND hwnd = GetConsoleWindow(); 1)�������� ���������� ���� �������. ���������� � ������� �������� �������� ����-��.
			//description 
			//HWND - Handler to Window(���������� ��� ���������� ����)
			HDC hdc = GetDC(hwnd); //2) �������� �������� ���������� (Device context) ���� �������
			//DC - ��� �� �� ��� �� ����� ��������
			HPEN hPen = CreatePen(PS_SOLID, 5, get_color());
			//3) ������� ��������, Pen ������ ������ ������
			//PS_SOLID - �������� �����
			//5-������� ����� � ��������
			// 4) c������ ��������
			HBRUSH hBrush = CreateSolidBrush(get_color());
			//5) �������� ��� � �� ��� ��������
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			//6) ������ �������������:
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);
			//start_x, start_y -���������� �������� ������ ����
			// 800, 350 - ���������� ������� ������� ����
			//����� �������� ��� ��� ���������� ������� ���� ��������� ������� ��������� ��� �������� �����.
			//7) ����������� �������:
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
			this->width = filter_size(width);
		}
		void set_height(double height)
		{
			this->height = filter_size(height);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "������: " << get_width() << endl;
			cout << "������: " << get_height() << endl;
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
	private:
		double rad;
	public:
		
		Circle(double rad, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_rad(rad);
		}
		virtual ~Circle() {}
		double get_rad()const
		{
			return rad;
		}
		void set_rad(double rad)
		{
		
			this->rad = filter_size(rad);
		}
		double get_area()const override
		{
			return M_PI * rad * rad;
		}
		double get_perimeter()const override
		{
			return(M_PI * rad) * 2;
		}
		void draw()const override
		{
			HWND hwnd = FindWindowA(NULL, "Inheritance - Microsoft Visual Studio"); 
			
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 9, get_color());
			HBRUSH hBrush = CreateSolidBrush(get_color());
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			Ellipse(hdc, start_x, start_y, start_x + rad * 2, start_y + rad * 2);
			
			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}

		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "������: " << get_rad() << endl;
			Shape::info();
		}

	};
	class Triangle : public Shape  //����������
	{
	private:
		double a;
		double b;
		double c;
	public:
		const double get_a()const
		{
			return a;
		}
		void set_a(double a)
		{
			this->a = a;
		}
		const double get_b()const
		{
			return b;
		}
		void set_b(double b)
		{
			this->b = b;
		}
		const double get_c()const
		{
			return c;
		}
		void set_c(double c)
		{
			this->c = c;
		}
		Triangle(double a, double b, double c, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_a(a);
			set_b(b);
			set_c(c);
		}
		virtual ~Triangle() {};
		double get_area()const override
		{
			return sqrt((a + b + c) / 2 * (((a + b + c) / 2 - a) * ((a + b + c) / 2 - b) * ((a + b + c) / 2 - c)));
		}
		double get_perimeter()const override
		{
			return (a+b+c);
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 9, get_color()); //Solid -������� �����
			HBRUSH hBrush = CreateSolidBrush( get_color());
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			//���������� ���������� ������������
			double x1 = a;
			double y1 = a;
			double x2 = x1 + a * cos(a/b);
			double y2 = y1 + a * sin(a/b);
			double x3 = x1 + c;
			double y3 = y1;
			//���������� ������ ����� ������� �������� �����������
			POINT point[] =
			{
				{(int)x1+ start_x, (int)y1+ start_y},
				{(int)x2+ start_x, (int)y2+ start_y},
				{(int)x3+ start_x, (int)y3+ start_y}
			};
			// ������ �����������:
			Polygon(hdc,point, 3);
			//7) ����������� �������:
			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "������� a: " << get_a() << endl;
			cout << "������� b: " << get_b() << endl;
			cout << "������� c: " << get_c() << endl;
			Shape::info();
		}
	};

	class Triangle :public Shape  //��������y��
	{
	public:
		virtual double get_height()const = 0;
		Triangle(SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS) {}
		//Triangle(double get_height(), SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS) {}
		virtual~Triangle() {};
		void info()const override
		{
			cout << "������ ������������: " << get_height() << endl;
			Shape::info();
		}
	};
	class EquilateralTriangle :public Triangle
	{
		double side;
	public:
		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		virtual ~EquilateralTriangle() {};
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		double get_height()const override
		{
			return sqrt(side * side - side / 2 * side / 2);
		}
		double get_area()const override
		{
			return side / 2 * get_height();
		}
		double get_perimeter()const override
		{
			return side * 3;
		}
		void draw() const override
		{
			HWND hwnd = FindWindowA(NULL, "Inheritance - Microsoft Visual Studio");

			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

		
			POINT point[] =
			{
				{start_x, start_y + side},
				{start_x + side, start_y + side},
				{start_x + side / 2, start_y + side - get_height()}
			};
			// ������ �����������:
			Polygon(hdc, point, 3);
			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "����� ������ �, b, c : " << get_side() << endl;
			cout << "������ ������������ : " << get_height() << endl;
			Shape::info();
		}
	};
	class IsoscelesTriangle :public Triangle
	{
		double side;
		double base;
	public:
		IsoscelesTriangle(double side, double base, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
			set_base(base);
		}
		virtual ~IsoscelesTriangle() {};
		double get_side()const
		{
			return side;
		}
		double get_base()const
		{
			return base;
		}
		void set_side(double side)
		{
			this->side = side;
		}
		void set_base(double base)
		{
			this->base = base;
		}
		double get_height()const override
		{
			return sqrt(side * side - base / 2 * base / 2);
		}
		double get_area()const override
		{
			return base / 2 * get_height();
		}
		double get_perimeter()const override
		{
			return side * 2 + base;
		}
		void draw() const override
		{
			HWND hwnd = FindWindowA(NULL, "Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

		
			POINT point[] =
			{
				{start_x, start_y + base},
				{start_x + base, start_y + base},
				{start_x + base / 2, start_y + base - get_height()}
			};
			// ������ �����������:
			::Polygon(hdc, point, 3);
			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "������� � � c : " << get_side() << endl;
			cout << "��������� � : " << get_base() << endl;
			cout << "������ ������������ : " << get_height() << endl;
			Shape::info();
		}

	};
	class A_right_angled_Triangle : public Triangle
	{
		double side;
		double base;
	public:
		A_right_angled_Triangle(double side, double base, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
			set_base(base);
		}
		virtual ~A_right_angled_Triangle() {};
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			this->side = side;
		}
		double get_base()const
		{
			return base;
		}
		void set_base(double base)
		{
			this->base = base;
		}
		double get_height()const override
		{
			return sqrt(side * side - base * base);
		}
		double get_area()const override
		{
			return base / 2 * get_height();
		}
		double get_perimeter()const override
		{
			return side + base + get_height();
		}
		void draw()const override
		{
			HWND hwnd = FindWindow(NULL, "Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			double x1 = 0;
			double y1 = get_height();
			double x2 = x1 + base;
			double y2 = get_height();
			double x3 = 0;
			double y3 = 0;
			POINT point[] =
			{
				{start_x, start_y + base},
				{start_x + base, start_y + base},
				{start_x + base, start_y + base - get_height()}
			};
			// ������ �����������:
			Polygon(hdc, point, 3);
			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "���������� : " << get_side() << endl;
			cout << "����� � ��������� : " << get_base() << endl;
			cout << "������ � ������ ����� ������������ : " << get_height() << endl;
			Shape::info();
		}
	};

}
void main() 
{
	setlocale(LC_ALL, "Russian");
	Geometry::Square square(50, 220, 90, 5, Geometry::Color::DARK_RED);
	square.info();
	cout << delimiter << endl;
	Geometry::Rectangle rect(80, 40, 300, 70, 3, Geometry::Color::BLUE);
	rect.info();
	cout << delimiter << endl;
	Geometry::Circle circle(150, 390, 65, 3, Geometry::Color::YELLOW);
	circle.info();
	cout << delimiter << endl;
	Geometry::EquilateralTriangle equ_triangle(120, 550, 50, 3, Geometry::Color::GREEN);
	equ_triangle.info();
	cout << delimiter << endl;
	Geometry::IsoscelesTriangle iso_triangle(120, 100, 700, 75, 2, Geometry::Color::RED);
	iso_triangle.info();
	cout << delimiter << endl;
	Geometry::A_right_angled_Triangle ara_triangle(160, 120, 820, 50, 60, Geometry::Color::PURPLE);
	ara_triangle.info();

	cout << "���������� �����: " << equ_triangle.get_count() << endl;
	cout << "���������� �����: " << Geometry::Shape::get_count() << endl;