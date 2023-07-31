#include <iostream>
#include <vector>

template<typename T>
class Array
{
private:
	T* array;
	int bound;
	int grow;
	int size;

public:
	Array() : array(nullptr), bound(0), grow(1), size(0) {}

	int getSize() const
	{
		return size;
	}

	void setSize(int newSize, int newGrow = 1)
	{
		if (newSize <= 0)
		{
			removeAll();
			this->grow = newGrow < 1 ? 1 : newGrow;
			return;
		}

		T* tmp = new T[newSize];
		int minSize = (size < newSize) ? size : newSize;
		for (int i = 0; i < minSize; i++)
		{
			tmp[i] = array[i];
		}
		delete[] array;

		array = tmp;
		size = newSize;
		bound = newSize;
		this->grow = newGrow < 1 ? 1 : newGrow;
	}

	int getUpperBound() const
	{
		return size - 1;
	}

	bool isEmpty() const
	{
		return size <= 0;
	}

	void freeExtra()
	{
		if (size == 0 || bound == size)
		{
			return;
		}

		T* tmp = new T[size];
		for (int i = 0; i < size; i++)
		{
			tmp[i] = array[i];
		}

		delete[] array;
		array = tmp;
		bound = size;
	}

	void removeAll()
	{
		delete[] array;
		array = nullptr;
		size = 0;
		bound = 0;
	}

	T GetAt(int index) const
	{
		if (index >= 0 && index < size)
		{
			return array[index];
		}
		throw std::out_of_range("Invalid index");
	}

	void SetAt(int index, const T& value)
	{
		if (index >= 0 && index < size)
		{
			array[index] = value;
		}
		else
		{
			throw std::out_of_range("Invalid index");
		}
	}

	T& operator[](int index)
	{
		if (index >= 0 && index < size)
		{
			return array[index];
		}
		else
		{
			throw std::out_of_range("Invalid index");
		}
	}

	const T& operator[](int index) const
	{
		if (index >= 0 && index < size)
		{
			return array[index];
		}
		else
		{
			throw std::out_of_range("Invalid index");
		}
	}

	void add(T value)
	{
		if (size >= bound)
		{
			setSize(size + grow);
		}
		array[size] = value;
		size++;
	}

	void Append(const Array& other)
	{
		int newSize = size + other.size;

		if (newSize > bound)
		{
			setSize(newSize);
		}
		for (int i = 0; i < other.size; i++)
		{
			array[size + i] = other.array[i];
		}
		size = newSize;
	}

	Array& operator=(const Array& other)
	{
		if (this == &other)
		{
			return *this;
		}

		delete[] array;
		bound = other.bound;
		grow = other.grow;
		size = other.size;
		array = new T[bound];
		for (int i = 0; i < size; i++)
		{
			array[i] = other.array[i];
		}
		return *this;
	}

	const T* GetData() const
	{
		return array;
	}

	void InsertAt(int index, const T& value)
	{
		if (array != nullptr && index >= 0 && index <= size)
		{
			if (size >= bound)
			{
				setSize(size + grow);
			}

			for (int i = size; i > index; i--)
			{
				array[i] = array[i - 1];
			}

			array[index] = value;
			size++;
		}
	}

	void RemoveAt(int index)
	{
		if (array != nullptr && index >= 0 && index < size)
		{
			for (int i = index; i < size - 1; i++)
			{
				array[i] = array[i + 1];
			}
			size--;
		}
	}

	~Array()
	{
		delete[] array;
	}
};

int main()
{
	Array<int> arr;

	arr.add(5);
	arr.add(10);
	arr.add(15);

	std::cout << "arr[0]: " << arr[0] << std::endl;
	std::cout << "arr[1]: " << arr[1] << std::endl;
	std::cout << "arr[2]: " << arr[2] << std::endl;

	arr.SetAt(1, 20);
	std::cout << "arr[1] after SetAt: " << arr[1] << std::endl;

	Array<int> anotherArr;
	anotherArr.add(30);
	anotherArr.add(35);
	arr.Append(anotherArr);

	std::cout << "arr[3]: " << arr[3] << std::endl;
	std::cout << "arr[4]: " << arr[4] << std::endl;

	arr.InsertAt(1, 25);
	std::cout << "arr[1] after InsertAt: " << arr[1] << std::endl;

	arr.RemoveAt(0);
	std::cout << "arr[0] after RemoveAt: " << arr[0] << std::endl;

	return 0;
}