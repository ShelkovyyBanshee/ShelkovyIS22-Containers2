#include <iomanip> 
#include <iostream> 
#include <string> 
#include <cmath>

using namespace std;

class ZeroDivide {};
class Array
{
private:
	unsigned int size;
	double* data;
	int indexStart;

public:
	friend void printArrayInfo(Array& a, int size, string name, double number);
	friend void printArray(Array& a, int size, string name);
	friend Array inputArray(int size, int indexStart);

	Array(unsigned int  size, int indexStart = 0, double k = 0.0) throw(bad_alloc)
	{
		this->size = size;
		this->indexStart = indexStart;
		data = new double[this->size];
		for (int i = 0; i < this->size; i++)
		{
			data[i] = k;
		}
	}

	Array(const double* start, const double* end, int indexStart = 0) throw(bad_alloc, invalid_argument)
	{
		if (start < end)
		{
			size = (end - start);
			data = new double[size];

			for (int i = 0; i < size; i++)
			{
				data[i] = *(start + i);
			}
		}
		else throw invalid_argument("Invalid argument...");
	}

	Array(const Array& a) throw(bad_alloc)
		:size(a.size), indexStart(a.indexStart), data(new double[size])
	{
		for (int i = 0; i < size; i++)
			data[i] = a.data[i];
	}

	~Array() throw()
	{
		delete[] data;
	}

	Array& operator = (const Array& a)
	{
		if (this == &a)
			return *this;
		else
		{
			size = a.size;
			double* newData = new double[size];
			for (int i = 0; i < size; i++)
				newData[i] = a.data[i];
			delete[] data;
			data = newData;
		}
	}

	double& operator[] (int index) throw(out_of_range)
	{
		index = index - indexStart;
		if (index < size)
			return data[index];
		else
			throw out_of_range("Out of range error...");
	}

	const double& operator[] (int index) const throw(out_of_range)
	{
		index = index - indexStart;
		if (index < size)
			return data[index];
		else
			throw out_of_range("Out of range error...");
	}

	Array AddNumber(double number)
	{
		Array result = *this;
		for (int i = 0; i < result.size; i++)
		{
			result.data[i] = data[i] + number;
		}

		return result;
	}

	Array SubstractNumber(double number)
	{
		Array result = *this;
		for (int i = 0; i < result.size; i++)
		{
			result.data[i] = data[i] - number;
		}

		return result;
	}

	Array MultiplyNumber(double number)
	{
		Array result = *this;
		for (int i = 0; i < result.size; i++)
		{
			result.data[i] = data[i] * number;
		}

		return result;
	}

	Array DivideNumber(double number) throw(ZeroDivide)
	{
		if (number == 0) throw ZeroDivide();
		Array result = *this;
		for (int i = 0; i < result.size; i++)
		{
			result.data[i] = data[i] / number;
		}

		return result;
	}

	Array operator+ (const Array& other)
	{
		if (other.size != size) throw out_of_range("Out of range error...");

		Array result = *this;
		for (int i = 0; i < size; i++)
		{
			result.data[i] += other.data[i];
		}

		return result;
	}

	Array operator- (const Array& other)
	{
		if (other.size != size) throw out_of_range("Out of range error...");

		Array result = *this;
		for (int i = 0; i < size; i++)
		{
			result.data[i] -= other.data[i];
		}

		return result;
	}

	Array operator* (const Array& other)
	{
		if (other.size != size) throw out_of_range("Out of range error...");

		Array result = *this;
		for (int i = 0; i < size; i++)
		{
			result.data[i] *= other.data[i];
		}

		return result;
	}

	Array operator/ (const Array& other) throw(ZeroDivide)
	{
		if (other.size != size) throw out_of_range("Out of range error...");

		Array result = *this;
		for (int i = 0; i < size; i++)
		{
			if (other.data[i] == 0) throw ZeroDivide();
			result.data[i] /= other.data[i];
		}

		return result;
	}

	double GetMax()
	{
		double max = data[0];
		for (int i = 0; i < size; i++)
			if (max < data[i])
				max = data[i];
		return max;
	}

	double GetMin()
	{
		double min = data[0];
		for (int i = 0; i < size; i++)
			if (min > data[i])
				min = data[i];
		return min;
	}

	double GetSum()
	{
		double sum = 0;
		for (int i = 0; i < size; i++)
			sum += data[i];
		return sum;
	}

	double GetMiddle()
	{
		return GetSum() / size;
	}

	Array SortBase(double k)
	{
		Array result = *this;
		for (int i = 1; i < size; i++)
		{
			for (int j = size - 1; j >= i; j--)
			{
				if (result.data[j - 1] * k > result.data[j] * k)
				{
					double temp = result.data[j - 1];
					result.data[j - 1] = result.data[j];
					result.data[j] = temp;
				}
			}
		}

		return result;
	}

	Array SortUp()
	{
		return SortBase(1.0);
	}

	Array SortDown()
	{
		return SortBase(-1.0);
	}
};

void printArray(Array& a, int size, string name)
{
	cout << name << ' ';
	cout << a.data[0];
	for (int i = 1; i < a.size; i++)
	{
		cout << ' ' << a.data[i];
	}
	cout << endl;
}

void printArrayInfo(Array& a, int size, string name, double number)
{
	printArray(a, size, name + "=");
	cout << "min= " << a.GetMin();
	cout << " max= " << a.GetMax();
	cout << " summa= " << a.GetSum();
	cout << " srar= " << a.GetMiddle() << endl;
	Array info[6]{ a.AddNumber(number), a.SubstractNumber(number), a.MultiplyNumber(number), a.DivideNumber(number), a.SortUp(), a.SortDown() };
	string keys[6]{ name + "+const", name + "-const", name + "*const", name + "/const", "sort up " + name, "sort down " + name };
	for (int i = 0; i < 6; i++)
	{
		printArray(info[i], size, keys[i] + "=");
	}
}

Array inputArray(int size, int indexStart)
{
	Array a = Array(size, indexStart);
	for (int i = 0; i < size; i++)
	{
		cin >> a.data[i];
	}
	return a;
}

int main()
{
	int start, end;
	cin >> start >> end;
	int size = abs(start - end) + 1;
	Array a = inputArray(size, start);
	Array b = inputArray(size, start);
	double constNumber;
	cin >> constNumber;
	printArrayInfo(a, size, "Array1", constNumber);
	printArrayInfo(b, size, "Array2", constNumber);

	Array results[3]{ a + b, a - b, a * b };
	string keys[3]{ "summa", "raznost", "proizv " };

	for (int i = 0; i < 3; i++)
	{
		printArray(results[i], size, keys[i] + "=");
	}

	try
	{
		Array d = a / b;
		printArray(d, size, "delenie= ");
	}
	catch (ZeroDivide)
	{
		cout << "delenie na 0\n";
	}

	int op, index;
	while (true)
	{
		cin >> op;
		if (op == 0)
			break;

		cout << "Array" << op;
		cin >> index;
		try
		{
			cout << "[" << index << "]= " << (op == 1 ? a[index] : b[index]) << endl;
		}
		catch (out_of_range)
		{
			cout << " wrong index " << index << endl;
		}

	}
}
