#include<Windows.h>
#include<iostream>
#include<math.h>
using namespace std;


namespace Geometry
{
	enum Color  // enum (Enumeration) - ��� ������������. ������������ - ��� ����� ������������� ��������
	{
		CONSOLE_BLUE = 0x09,
		CONSOLE_GREEN = 0xAA,
		CONSOLE_RED = 0xCC,
		CONSOLE_DEFAULT = 0x07,
		RGB_RED = (0xFF0000), //��������� RGB �����
		RGB_GREEN = (0x00FF00),
		RGB_BLUE = (0xFFFF00),
		RGB_WHITE = (0xFFFFFF)
	};

	class Shape
	{
		Color color;
	public:
		Shape(Color color) :color(color) {}  //����������� � ����.����������
		virtual ~Shape() {}   // {}������ ����������, ���� ������� ; �� ����� ��� �� �������������
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		Color get_color()const { return color; }  //Geters
		void set_color(Color color) { this->color = color; }  //Seters
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

	class Square :public Shape
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


	};

	class Rectangle :public Shape
	{
		double width;
		double height;
	public:
		Rectangle(double width, double height, Color color) :Shape(color)
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
			HWND hwnd = GetConsoleWindow(); //1)�������� ���������� ���� �������. ���������� � ������� �������� �������� ����-��.
			//description 
			//HWND - Handler to Window(���������� ��� ���������� ����)
			HDC hdc = GetDC(hwnd); //2) �������� �������� ���������� (Device context) ���� �������
			//DC - ��� �� �� ��� �� ����� ��������
			HPEN hPen = CreatePen(PS_SOLID, 5, get_color());
			//3) ������� ��������, Pen ������ ������ ������
			//PS_SOLID - �������� �����
			//5-������� ����� � ��������
			// 4) c������ ��������
			HBRUSH hBrush = CreateSolidBrush(Geometry::Color::RGB_BLUE);
			//5) �������� ��� � �� ��� ��������
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			//6) ������ �������������:
			::Rectangle(hdc, 250, 50, 400, 150);
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
			this->width = width;
		}
		void set_height(double height)
		{
			this->height = height;
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "������: " << get_width() << endl;
			cout << "������: " << get_height() << endl;
			Shape::info();
		}
	};
	class Circle :public Shape
	{
	private:
		double rad = 50;
	public:
		const double Pi = 3.14;
		const double get_rad()const
		{
			return rad;
		}
		void set_rad(double rad)
		{
			this->rad = rad;
		}
		Circle(double rad, Color color) :Shape(color)
		{
			set_rad(rad);
		}
		virtual ~Circle() {};
		double get_area()const override
		{
			return Pi * rad * rad;
		}
		double get_perimeter()const override
		{
			return(Pi * rad) * 2;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 9, get_color());
			HBRUSH hBrush = CreateSolidBrush(Geometry::Color::CONSOLE_DEFAULT);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Ellipse(hdc, 320, 320, 320 + rad, 320 + rad);

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
		double a = 90;
		double b = 90;
		double c = 90;
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
		Triangle(double a, double b, double c, Color color) :Shape(color)
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
			return (a + b + c);
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 9, get_color());
			HBRUSH hBrush = CreateSolidBrush(Geometry::Color::RGB_GREEN);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			double x1 = a;
			double y1 = a;
			double x2 = x1 + a * cos(a / b);
			double y2 = y1 + a * sin(a / b);
			double x3 = x1 + c;
			double y3 = y1;
			POINT point[] =
			{
				{(int)x1 + 160, (int)y1 + 160},
				{(int)x2 + 160, (int)y2 + 160},
				{(int)x3 + 160, (int)y3 + 160}
			};
			
			Polygon(hdc, point, 3);
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

}

void main() 
{
	setlocale(LC_ALL, "Rus");
	
	Geometry::Square square(5, Geometry::Color::CONSOLE_RED);
	
	square.info();

	Geometry::Rectangle rect(10, 6, Geometry::Color::CONSOLE_DEFAULT);
	rect.info();

	Geometry::Circle circle(60, Geometry::Color::RGB_BLUE);
	circle.info();

	Geometry::Triangle triangle(90, 90, 90, Geometry::Color::CONSOLE_GREEN);
	triangle.info();
}