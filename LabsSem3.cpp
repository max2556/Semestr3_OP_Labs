/*Определение области на плоскости, в которую попадает точка,
и площади этой области аналитическим и программным способом
методом криволинейных трапеций.
Рекурсия. Передача имен функций в качестве параметров.*/
#define _USE_MATH_DEFINES

#include<iostream>
#include<math.h>
#include<locale.h>

using namespace std;


typedef double(*Tfun)(double);
double integral(double, double, int, double, Tfun, double);
double fun1(double x);
double fun2(double x);
double fun3(double x);
double fun4(double x);
double fun5(double x);
double fun6(double x);
double fun7(double x);
double fun8(double x);
double fun9(double x);
double fun10(double x);
double fun11(double x);
double fun12(double x);
double fun13(double x);

int main()
{
	int i = 0,                     //номер области
		n = 10;					//начальное число разбиений
	double x, y,					//координаты точки
		s1, s2, s3, s4, s5;        //площади областей
	double eps = .000001,         	//точность вычисления
		s = 0;                     //вычисленная площадь области
	bool M1, M2, M3, M4, M5;           //Принадлежность областям


	setlocale(LC_ALL, "Russian");
	cout << '\n' << "Введите х,у координаты: ";
	cin >> x >> y;

	//M1 лежит между х=0 и x=1, внутри верхней окружности, но вне центральной и правой
	M1 = (x > 0) && (x < 1) && (x * x + (y - 1) * (y - 1) <= 1) &&
		((x - 1) * (x - 1) + y * y > 1) && (x * x + y * y > 1);
	//M2 лежит внутри левой окружности, но вне верхней и нижней
	M2 = ((x + 1) * (x + 1) + y * y <= 1) && (x * x + (y - 1) * (y - 1) > 1)
		&& (x * x + (y + 1) * (y + 1) > 1);
	//M3 лежит правее х=1 и выше у=0, внутри правой окружности, но вне верхней-правой
	M3 = (x > 1) && (y > 0) && ((x - 1) * (x - 1) + y * y <= 1) &&
		((x - 1) * (x - 1) + (y - 1) * (y - 1) > 1);
	//M4 лежит внутри центральной, правой, нижней и правой-нижней окружности
	M4 = (x * x + y * y <= 1) && (x * x + (y + 1) * (y + 1) <= 1) &&
		((x - 1) * (x - 1) + y * y <= 1) && ((x - 1) * (x - 1) + (y + 1) * (y + 1) <= 1);
	//M5 лежит внутри правой-нижней окружности, но вне нижней и правой
	M5 = ((x - 1) * (x - 1) + (y + 1) * (y + 1) <= 1) &&
		(x * x + (y + 1) * (y + 1) > 1) && ((x - 1) * (x - 1) + y * y > 1);




	if (M1)
	{
		cout << "Точка в области M1. " << endl;
		i = 1;
	}
	else if (M2)
	{
		cout << "Точка в области М2. " << endl;
		i = 2;
	}
	else if (M3)
	{
		cout << "Точка в области М3. " << endl;
		i = 3;
	}
	else if (M4)
	{
		cout << "Точка в области М4. " << endl;
		i = 4;
	}
	else if (M5)
	{
		cout << "Точка в области М5. " << endl;
		i = 5;
	}
	else cout << "Точка вне выделенных областей";


	cout.precision(4);		//число знаков после дес. точки
	switch (i)
	{
	case 1:
		s1 = M_PI / 12 + 1 - sqrt(3) / 4;
		cout << "Formula: S1 = " << s1 << endl;
		s1 = integral(0, 1, n, eps, fun1, s)
			- integral(0, 1. / 2, n, eps, fun2, s)
			- integral(1. / 2, 1, n, eps, fun3, s);
		cout << "Integral:S1 = " << s1;
		break;
	case 2:
		s2 = 2;
		cout << "Formula: S2 = " << s2 << endl;
		s2 = integral(-2, -1, n, eps, fun4, s)
			+fabs(integral(-2, -1, n, eps, fun11, s))
			+integral(-1, 0, n, eps, fun5, s)
			+fabs(integral(-1, 0, n, eps, fun12, s));
		cout << "Integral:S2 = " << s2;
		break;
	case 3:
		s3 = sqrt(3) / 4 - M_PI / 12;
		cout << "Formula: S3 = " << s3 << endl;
		s3 = integral(1, 1 + sqrt(3) / 2, n, eps, fun6, s)
			+ integral(1 + sqrt(3) / 2, 2, n, eps, fun3, s);
		cout << "Integral:S3 = " << s3;
		break;
	case 4:
		s4 = M_PI / 3 - sqrt(3) + 1;
		cout << "Formula: S4 = " << s4 << endl;
		s4 = fabs(
			integral(1 - sqrt(3)/2, 1./2, n, eps, fun7, s) - integral(1 - sqrt(3)/2, 1./2, n, eps, fun8, s)
			+ integral( 1. / 2, sqrt(3)/2, n, eps, fun13, s) - integral(1. / 2, sqrt(3) / 2, n, eps, fun12, s));
		cout << "Integral:S4 = " << s4;
		break;
	case 5:
		s5 = M_PI / 12 + sqrt(3) / 2;
		cout << "Formula: S5 = " << s5 << endl;
		s5 = fabs(integral(1./2, 2, n, eps, fun9, s) 
			- integral(1./2, 1, n, eps, fun10, s)
			- integral(1, 1+sqrt(3)/2, n, eps, fun7, s)
			- integral(1 + sqrt(3) / 2, 2, n, eps, fun8, s));
		cout << "Integral:S5 = " << s5;
	}
	return 0;
}

//нахождение определенного интеграла методом левого прямоугольника
double integral(double a, double b, int n, double eps, Tfun fun, double s1)
{
	double x, h, s = 0;
	int i;

	h = (b - a) / n; //delta

	for (i = 0; i < n; i++)
	{
		x = a + i * h;
		s += fun(x);
	}
	s *= h;
	if (fabs(s - s1) > eps)
		s = integral(a, b, 2 * n, eps, fun, s);
	return s;
}

/*описание вида интегрируемой функции №1 для линии: x^2+(y-1)^2=1 (верхняя полуокружность)*/
double fun1(double x)
{
	return(sqrt(1 - x * x) + 1);
}

/*описание вида интегрируемой функции №2 для линии: x^2+y^2=1 (верхняя полуокружность)*/
double fun2(double x)
{
	return(sqrt(1 - x * x));
}

/*описание вида интегрируемой функции №3 для линии: (x-1)^2+y^2=1 (верхняя полуокружность)*/
double fun3(double x)
{
	return(sqrt(-x * x + 2 * x));
}

//описание вида интегрируемой функции №4 для линии: (x+1)^2+y^2=1 (верхняя полуокружность)
double fun4(double x)
{
	return(sqrt(-x * x - 2 * x));
}

/*описание вида интегрируемой функции №5 для линии: x^2+(y-1)^2=1 (нижняя полуокружность)*/
double fun5(double x)
{
	return(-sqrt(1 - x * x) + 1);
}

/*описание вида интегрируемой функции №6 для линии: (x-1)^2+(y-1)^2=1 (нижняя полуокружность)*/
double fun6(double x)
{
	return(-sqrt(-x * x + 2 * x) + 1);
}

//описание вида интегрируемой функции №7 для линии: (x-1)^2+y^2=1 (нижняя полуокружность)
double fun7(double x)
{
	return(-sqrt(-x * x + 2 * x));
}

//описание вида интегрируемой функции №8 для линии: (x-1)^2+(y+1)^2=1 (верхняя полуокружность)
double fun8(double x)
{
	return(sqrt(-x * x + 2 * x) - 1);
}

/*описание вида интегрируемой функции №9 для линии: (x-1)^2+(y+1)^2=1 (нижняя полуокружность)*/
double fun9(double x)
{
	return(-sqrt(-x * x + 2 * x) - 1);
}

/*описание вида интегрируемой функции №10 для линии: x^2+(y+1)^2=1 (нижняя полуокружность)*/
double fun10(double x)
{
	return(-sqrt(1-x*x)-1);
}

//описание вида интегрируемой функции №4 для линии: (x+1)^2+y^2=1 (нижняя полуокружность)
double fun11(double x)
{
	return(-sqrt(-x * x - 2 * x));
}

/*описание вида интегрируемой функции №10 для линии: x^2+(y+1)^2=1 (верхняя полуокружность)*/
double fun12(double x)
{
	return(sqrt(1 - x * x) - 1);
}

/*описание вида интегрируемой функции №2 для линии: x^2+y^2=1 (нижняя полуокружность)*/
double fun13(double x)
{
	return(-sqrt(1 - x * x));
}