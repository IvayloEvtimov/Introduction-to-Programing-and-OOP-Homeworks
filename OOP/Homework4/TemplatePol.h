#ifndef TEMPLATE_H_INCLUDED
#define TEMPLATE_H_INCLUDED

const double EPS = 0.00001;

template <typename Type>
class Polynom
{
public:
	explicit Polynom(); //Default Constructor
	explicit Polynom(const int&); //Constructor which generates empty polynom
	Polynom(const Polynom&); //Copy Contructor
	Polynom& operator=(const Polynom&); //Assignment Operator for polynoms
	~Polynom(); //Destructor

	Polynom& operator+=(const Polynom&); //Addings 2 polynoms
	Polynom& operator-=(const Polynom&); //Reduces 2 polynoms
	Polynom& operator*=(const Polynom&); //Multiplies 2 polynom
	Polynom& operator/=(const Polynom&); //Long devides 2 polynoms
	Polynom& operator%=(const Polynom&); //Long devides 2 polynoms and return the remainder

	Polynom& operator*=(const Type&); //Multiplies a polynom with a same type as the polynom and changes the current one
	Polynom operator*(const Type&);  //Multiplies a polynom with a same type as the polynom

	Polynom& operator/=(const Type&); //Devides a polynom with a same type as the polynom and changes the current one
	Polynom operator/(const Type&); //Multiplies a polynom with a same type as the polynom a polynom with a same type as the polynom

	const Type operator[](const int&) const;
	Type& operator[](const int&);

	Type operator()(const Type&) const; //Finds the value at a given point
	Type operator() (const Type&, const Type&); //Finds the integrel from given range

	Polynom& operator++(); //Finds the integral
	const Polynom operator++(int); //Finds the integral

	Polynom& operator--(); //Finds the derivative of a polynom
	const Polynom operator--(int); //Finds the derivative of a polynom

	bool operator==(const Polynom&) const; //Equivalence operator
	bool operator!= (const Polynom&) const;

	//template<class Type> //Equivalence operatpor for double type polynoms
	//bool operator==(const TemplatePol<double>&) const;

	//template <class Type> //Equivalence operator for float type polynoms
	//bool operator==(const TemplatePol<float>&)const;

	bool operator>(const Polynom&) const; //Finds if the current polynom is biggers that other polynom
	bool operator<=(const Polynom&) const; //Finds if the current polynom is smaller or equal that other polynom
	bool operator>=(const Polynom&) const; //Finds if the current polynom is biggers or equal that other polynom

	int asInt() const; //Returns the degree
	explicit operator bool() const; //Checks if polynom is zero
	bool operator!() const; //Checks if polynom is zero

	friend bool operator<(const Polynom<Type>&lhs, const Polynom<Type>&rhs) //Smaller operator
	{
		return lhs.size < rhs.size ? true : false;
	}

	friend std::ostream& operator<<(std::ostream& output, const Polynom<Type>&poly) //Friend method for output operator 
	{
		for (int count = poly.size - 1; count >= 0; --count)
		{
			if ( count != 0) //If the value is different than zero and isn't zero degree
				output << poly[count] << "x^" << count << " "; //ex. if value of poly[count] is 4 then "4x^(degree)"
			else if (count == 0) //For the value at the last degree there is no need for 'x'
				output << poly[count];

			if (count != 0 ) //Adds pluses
				output << "+ ";

		}
		output << std::endl;
		return output;
	}

	friend std::istream& operator>>(std::istream& input, Polynom<Type>&other) //Friend method for input operator
	{
		char temp[10]; //Used for storing number
		int tempCount = 0;

		bool exit = false; //For when '\n' symbol is encountered
		bool error = false; //For when a invalid input is entered

		do
		{
			tempCount = 0;
			while (true)
			{
				input.get(temp[tempCount++]); //Takes 1 symbol from input
				if (temp[tempCount - 1] == ' ' || temp[tempCount-1]=='\t') //If whitespace or TAB is encountered stops the cycle
					break;

				if (temp[tempCount - 1] == '\n') //If there is new line 
				{
					exit = true;
					break;
				}
				else if ((temp[tempCount - 1]<'0' || temp[tempCount - 1]>'9') && (temp[tempCount-1] != '.' && temp[tempCount-1]!='-'))
				{															//If the last symbol is not a number or is not a either '.' nor '-'
					error = true;											//The whole input is considered invalid
					break;
				}
			}
			temp[tempCount - 1] = 0; //Puts a terminatering symbol

			if (!error) //If a input is valid adds a new value to the polynom
			{
				other.resizeRev(other.size + 1);
				other[0] = atof(temp);
			}
			else //If it isn't then cleans the entire polynom
			{
				std::cout << "Invalid input detected. Deleteing all of the inputed data" << std::endl;
				other.clean();
			}
		} while (!exit);

		return input;
	}


public:
	class Iterator //Iterator class for moving through polynom
	{
	public:
		Iterator(Type* other) :itr(other) {};

		void operator++() { ++itr; } //Moves the iterator foward
		void operator--() { --itr; } //Moves the iterator backwards

		bool operator!=(const Iterator& other)const { return itr != other.itr; }; //Checks if 2 iterators aren't the same
		bool operator==(const Iterator& other)const { return !(*this != other); } //Checks if 2 iterators aren the same
		bool operator>(const Iterator& other)const { return itr > other.itr; } //Checks if a iterator is bigger than another 
		bool operator>=(const Iterator& other)const { return *this > other || *this == other; } //Checks if a iterator is bigger or equal than another
		bool operator<(const Iterator& other)const { return !(*this > other); } //Checks if a iterator is smaller than another
		bool operator<=(const Iterator& other)const { return !(*this > other) || *this == other; } //Checks if a iterator is smaller or equal than another

		Type& operator*() const { return *itr; } //Returns the pointer value
		Iterator* operator->() { return &this; } //Returns the adress of the iterator
	private:
		Type * itr;
	};

	Iterator begin() {  return Iterator(polynom);} //Returns the begining of the polynom
	Iterator end() //Return the end of the polynom
	{
		Iterator it(polynom + size-1);
		return  it;
	}

private:
	int zeroAtFirst() const;
	void simplify(); //Simplifies it by removing the zero value at the first degrees
	void resize(const int); //Increases or decreases a polynom
	void resizeRev(const int); //Increases the size of a polynom and makes the first positions empty instead of the last 
	void clean(); //Clean an entire polynom

private:
	int size;
	Type* polynom;
};

template<typename Type> //Default Constructor
inline Polynom<Type>::Polynom() :size(0), polynom(nullptr)
{

}

template<typename Type> //Constructor with 1 argument for empty polynom with predetermined size
inline Polynom<Type>::Polynom(const int &size):size(size),polynom(nullptr)
{
	if (size < 0)
		throw std::invalid_argument("Size must be positive number");

	polynom = new Type[size];
	for (int count = 0; count < size; ++count)
		polynom[count] = 0;
}

template<typename Type> //Copy Constructor
inline Polynom<Type>::Polynom(const Polynom<Type> &other) : size(other.size), polynom(nullptr)
{
	if (other.polynom != nullptr)
	{
		polynom = new Type[size];
		for (int count = 0; count < size; ++count)
			polynom[count] = other.polynom[count];
	}
}

template<typename Type> //Asignment Operator
inline Polynom<Type> & Polynom<Type>::operator=(const Polynom<Type> &other)
{
	if (this != &other)
	{
		if (this != nullptr)
		{
			clean();
			size = other.size;
			polynom = new Type[size];
			for (int count = 0; count < size; ++count)
				polynom[count] = other.polynom[count];

		}
	}
	return *this;
}

template<typename Type> //Destructor
inline Polynom<Type>::~Polynom()
{
	clean();
}


template<typename Type> //Adds 2 polynoms and 
inline Polynom<Type> & Polynom<Type>::operator+=(const Polynom<Type> &rhs)
{
	if (size< rhs.size) //If *this has smaller degree than rhs polynom
	{				   //resizes the *this polynom so that the 2 polynoms have the same size
		int oldSize = size; 
		resize(rhs.size);
		for (int count = oldSize; count < size; ++count) //The new bigger degrees have values set to 0
			polynom[count] = 0;
	}

	for (int count = 0; count < rhs.size; ++count) //Regular adding of 2 polynom
		this->polynom[count] += rhs.polynom[count];

	return *this;
}

template<typename Type> //Reduces 2 polynom and changing the current one
inline Polynom<Type> & Polynom<Type>::operator-=(const Polynom<Type> &rhs)
{	//Same as += operator but here the values are being reduced
	if (size< rhs.size)
	{
		int oldSize = size;
		resize(rhs.size);
		for (int count = oldSize; count < size; ++count)
			polynom[count] = 0;
	}

	for (int count = 0; count < rhs.size; ++count)
		this->polynom[count] -= rhs.polynom[count];

	return *this;
}

template<typename Type> 
inline Polynom<Type> & Polynom<Type>::operator*=(const Polynom<Type> &rhs)
{
	Polynom<Type> temp(this->size+rhs.size-1); //Creates a temp polynom for storing the multiplied values
	
	for (int tempCount = 0; tempCount < temp.size; ++tempCount) //Before the actual multiplication begins the temp polynom's values are set 0
		temp.polynom[tempCount] = 0;

	for (int countThis = 0; countThis < this->size; ++countThis) //Takes 1 element from the left polynom
		for (int countRhs = 0; countRhs < rhs.size; ++countRhs) //And multiplies it with every elemnt from the right polynom at the correct degree 
			temp.polynom[countThis + countRhs] += this->polynom[countThis] * rhs.polynom[countRhs];
			//The degree at which the multiplied value is saved is found by adding the left and right degree of the 2 polynoms

	resize(this->size + rhs.size-1); //The current polynom is resized

	for (int count = 0; count < size; ++count) //And the contents of the temp is put into the current polynom
		this->polynom[count] = temp.polynom[count];

	return *this;
}

template<typename Type> //Dividing 2 polynoms
inline Polynom<Type> & Polynom<Type>::operator/=(const Polynom<Type> &rhs)
{
	if (size < rhs.size) //The left polynom must have bigger power in order for the operation to be valid
		throw std::invalid_argument("Left size must have larger power");
	if (size == 0) //Also the left polynom must not be zero
		throw std::invalid_argument("Left side must be larger than 0");

	int degLeft = size - 1,
		degRight = rhs.size - 1;
	int powDiff = degLeft - degRight;

	Polynom<Type> Q(degLeft-degRight+1); //Used for quatant
	Polynom<Type> R = *this; //Used for remainder
	Polynom temp(rhs.size + powDiff); //Used for the operation


	while (powDiff >= 0) //At every step the degree diffenrence is reduced until the remainder has smaller degree then the right polynom
	{
		Q.polynom[powDiff] = R.polynom[degLeft] / rhs.polynom[degRight];
		int countRhs = rhs.size - 1;

		for (int countTemp = temp.size - 1; countTemp >= 0; --countTemp)
		{
/*1*/		if (countTemp > powDiff + rhs.size - 1) //If the current temp size is bigger than the combined size than 
				temp.polynom[countTemp] = 0; //At that degree the value should be zero
/*2*/		else if (countRhs >= 0) //Until all of the values in the righ polynom are multipled by the right polynom
				temp.polynom[powDiff + countRhs] = rhs.polynom[countRhs--] * R.polynom[degLeft]; 
/*3*/		else //After the right polynom is passed any remaining degree is set to 0
				temp.polynom[countTemp] = 0;

			//ex. left poly:2x^2+3x+1 right poly:x +2
			//first step: powDiff=1 because left size degLeft is 2 and right size degRight is 1
			//R == *this : 2x^2+3x+1 
			//temp.size==2  because powDiff==1 and right polynom's size==1
			//Q[powDiff==1]=2/1 -> 2
			// /*1*/ is skipped temp.size is not bigger than (powDiff+rhs.size-1)==2
			//At /*2*/ temp should look like this: 2x^2+4x
			//At /*3*/ 0 is set to temp.polynom[0] because that is the only degree which value is untouched 
		}

		for (int countLeft = 0; countLeft < temp.size; ++countLeft) //The remainder is made by multiplying the most right value of the right polynom with every value in the right poly
			R.polynom[countLeft] = R.polynom[countLeft] * rhs.polynom[degRight];

		//ex. R should look like this: rhs.polynom[degRight]==1, so R won't be changed

		R -= temp;

		//ex. R:2x^2+3x+1  temp:2x^2+4 so R-temp== -x+1
		//The operation is repeated until R has a smaller degree than the right polynom==x+2
		//In this case the operation should be repeated only 1 more time  
		//At the end R and Q should look like this: R==3 and Q==2x-1

		degLeft--;
		powDiff--;
	}
	*this = Q;
	return *this; //Returns the quontent
}

template<typename Type> //Remainder operation same as dividing but the returned polynom is R
inline Polynom<Type> & Polynom<Type>::operator%=(const Polynom<Type> &rhs)
{
	if (size < rhs.size)
		throw std::invalid_argument("Left size must have larger power");
	if (size == 0)
		throw std::invalid_argument("Left side must be larger than 0");

	int degLeft = size - 1,
		degRight = rhs.size - 1;
	int powDiff = degLeft - degRight;

	Polynom<Type> R = *this;
	Polynom<Type> temp;
	temp.resize(rhs.size + degLeft - degRight);

	while (powDiff >= 0)
	{
		int countRhs = rhs.size - 1;

		for (int countTemp = temp.size - 1; countTemp >= 0; --countTemp)
		{
			if (countTemp > powDiff + rhs.size - 1)
				temp.polynom[countTemp] = 0;
			else if (countRhs >= 0)
				temp.polynom[powDiff + countRhs] = rhs.polynom[countRhs--] * R.polynom[degLeft];
			else
				temp.polynom[countTemp] = 0;
		}

		for (int countLeft = 0; countLeft < temp.size; ++countLeft)
			R.polynom[countLeft] = R.polynom[countLeft] * rhs.polynom[degRight];

		R -= temp;

		degLeft--;
		powDiff--;
	}
	*this = R;
	this->simplify();
	return *this;
}

template<typename Type> //Multiplies current polynom by a number
inline Polynom<Type> & Polynom<Type>::operator*=(const Type &num)
{
	for (int count = 0; count < size; ++count)
		polynom[count] *= num;
	return *this;
}

template<typename Type> //Multiplies a polynom by a number  
inline Polynom<Type> Polynom<Type>::operator*(const Type &num)
{
	Polynom<Type> temp = *this;
	return temp *= num;

}

template<typename Type>//Divides the current polynom with a number
inline Polynom<Type> & Polynom<Type>::operator/=(const Type &num)
{
	for (int count = 0; count < size; ++count)
		polynom[count] = polynom[count] / num;
	return *this;
}

template<typename Type> //Divides a polynom with a number
inline Polynom<Type> Polynom<Type>::operator/(const Type &num)
{
	Polynom<Type> temp = *this;
	return temp *= num;
}

template<typename Type> //Returns the value at the requested position
inline const Type Polynom<Type>::operator[](const int& pos) const
{
	return (pos >= size) ? 0 : polynom[pos];
}

template<typename Type>
inline Type & Polynom<Type>::operator[](const int& pos)
{
	Type badPos = 0;
	if (pos >= size)
		return badPos;

	return polynom[pos];
}

template<typename Type> //Finds the Derivative of a polynom
inline Type Polynom<Type>::operator()(const Type &point) const
{
	Type res = 0;
	for (int count = 0; count < size; ++count)
		res += polynom[count] * (pow(point, count));

	return res;
}

template<typename Type> //Finds the integral from num1 to num2
inline Type Polynom<Type>::operator()(const Type &num1, const Type &num2)
{
	Polynom<Type> lhs = *this;
	++lhs;
	Type left=lhs(num2);
	Polynom<Type> rhs = *this;
	++rhs;
	Type right=rhs(num1);
	return left-right;
}

template<typename Type> //Finds a integral of a polynom
inline Polynom<Type> & Polynom<Type>::operator++()
{
	Polynom<Type> temp;
	temp.resize(size+1);

	for (int count = temp.size-1; count > 0; --count)
		temp.polynom[count] = polynom[count - 1] / count;

	temp.polynom[0] = 0;
	temp.simplify();
	return *this = temp;
}

template<typename Type> //Finds a integral of a polynom
inline const Polynom<Type> Polynom<Type>::operator++(int)
{
	Polynom<Type> temp = *this;
	this->operator++();
	return temp;
}

template<typename Type> //Finds the Derivative of a polynom
inline Polynom<Type> & Polynom<Type>::operator--()
{
	Polynom<Type> temp(size-1);

	int countThis = size - 1,
		countTemp = size - 2;

	do
	{
		temp.polynom[countTemp--] = countThis * polynom[countThis--];
	} while (countTemp >= 0);

	*this = temp;
	return *this;
}

template<typename Type> //Finds the Derivative of a polynom
inline const Polynom<Type> Polynom<Type>::operator--(int)
{
	Polynom<Type> temp(*this);
	this->operator--();
	return temp;
}

template<typename Type> //Equal operator
inline bool Polynom<Type>::operator==(const Polynom<Type> &rhs) const
{
	if (size != rhs.size) //If the 2 polynom aren't the same size then they aren't equal
		return false;

	for (int count = 0; count < size; ++count) //Check every element until a diffrence is met 
		if (polynom[count] != rhs.polynom[count])
			return false;

	return true; //If every element in both polynoms are the same then the 2 polynoms are equal
}

template<typename Type>
inline bool Polynom<Type>::operator!=(const Polynom<Type> &rhs) const
{
	return !(*this==rhs);
}

bool Polynom<double>::operator==(const Polynom<double>&rhs) const //Equal operator for double type polynoms
{
		if (size != rhs.size)
			return false;
	
		for (int count = 0; count < size; ++count)
			if (fabs(polynom[count] - rhs.polynom[count]) > EPS)
				return false;
	
		return true;
}

bool Polynom<float>::operator==(const Polynom<float>&rhs) const //Equal operator for double type polynoms
{
	if (size != rhs.size)
		return false;

	for (int count = 0; count < size; ++count)
		if (fabs(polynom[count] - rhs.polynom[count]) > EPS)
			return false;

	return true;
}

template<typename Type>
inline bool Polynom<Type>::operator>(const Polynom<Type> &rhs) const
{
	return !(*this < rhs);
}

template<typename Type>
inline bool Polynom<Type>::operator<=(const Polynom<Type> &rhs) const
{
	return !(*this > rhs);
}

template<typename Type>
inline bool Polynom<Type>::operator>=(const Polynom<Type> &rhs) const
{
	return !(*this < rhs);
}

template<typename Type> //Returs the degree of the polynom
inline int Polynom<Type>::asInt() const
{
	return size-1;
}

template<typename Type> //Returns true is every element in the polynom is 0
inline Polynom<Type>::operator bool() const
{
	for (int count = 0; count < size; ++count)
		if (polynom[count] != 0)
			return false;

	return true;
}

template<typename Type>
inline bool Polynom<Type>::operator!() const
{
	return !this->operator bool();
}

template<typename Type>
inline int Polynom<Type>::zeroAtFirst() const
{
	int countZero = 0;
	for (int count = size - 1; count >= 0; --count)
	{
		if (polynom[count] != 0)
			break;
		else
			++countZero;
	}
	return countZero;
}

//Specialization
int Polynom<double>::zeroAtFirst() const
{
	int countZero = 0;
	for (int count = size - 1; count >= 0; --count)
	{
		if (fabs(polynom[count] - 0.0)>EPS)
			break;
		else
			++countZero;
	}
	return countZero;
}

//Specialization
int Polynom<float>::zeroAtFirst() const
{
	int countZero = 0;
	for (int count = size - 1; count >= 0; --count)
	{
		if (fabs(polynom[count] - 0.0)>EPS)
			break;
		else
			++countZero;
	}
	return countZero;
}


template<typename Type>
inline void Polynom<Type>::simplify() //Simplifies it by removing the zeros at the end
{									  //ex. 0x^2+2x^1+1 becomes 2x^1+1 with size 2
	int countZero = zeroAtFirst();

	if (countZero != 0)
	{
		Polynom<Type> temp;
		temp.resize(size - countZero);
		for (int countTemp = 0; countTemp < size - countZero; ++countTemp)
			temp.polynom[countTemp] = polynom[countTemp];

		*this = temp;
	}
}

template<typename Type> //Increases or Decreases the size
inline void Polynom<Type>::resize(const int newSize)
{
	Polynom<Type> temp = *this; //A temp polynom is created to store the current values

	this->clean();
	this->polynom = new Type[newSize]; //The size of the current polynom is changed

	if((temp.size<newSize)) //If newSize is bigger
		for(int count = 0; count < temp.size; ++count)
			this->polynom[count] = temp.polynom[count];
	else //If the old Size is bigger
		for (int count = 0; count < newSize; ++count) //The current polynom is filled with the old values
			this->polynom[count] = temp.polynom[count];

	this->size = newSize;
}

template<typename Type> //Used for input
inline void Polynom<Type>::resizeRev(const int newSize)
{
	if (newSize < size)
		throw std::invalid_argument("The new size must be bigger than the current");

	Polynom<Type> temp = *this;

	this->clean();
	this->polynom = new Type[newSize];

	int countNew = newSize-temp.size,
		countOld = 0;


	while (countOld < temp.size)
		this->polynom[countNew++] = temp.polynom[countOld++];

	this->size = newSize;
}

template<typename Type>
inline void Polynom<Type>::clean()
{
	size = 0;
	delete[] polynom;
}

////////////////////////////////////////////////////////////
//					Outside functions                    //
//////////////////////////////////////////////////////////

template<class Type>
bool operator<(const Polynom<Type> &rhs, const Polynom<Type> &lhs)
{
	if (lhs.size < rhs.size)
		return true;
	return false;
}

template <typename Type>
const Polynom<Type> operator+(const Polynom<Type>&lhs, const Polynom<Type>&rhs)
{
	Polynom<Type> temp = lhs;
	temp += rhs;

	return temp;
}

template <typename Type>
const Polynom<Type> operator-(const Polynom<Type>& lhs, const Polynom<Type> &rhs)
{
	Polynom<Type> temp = lhs;
	temp -= rhs;
	return temp;
}

template <typename Type>
const Polynom<Type> operator*(const Polynom<Type>& lhs, const Polynom<Type>& rhs)
{
	Polynom<Type> temp = lhs;
	temp *= rhs;
	return temp;

}

template <typename Type>
const Polynom<Type> operator/(const Polynom<Type>& lhs, const Polynom<Type>& rhs)
{
	Polynom<Type> temp = lhs;
	temp /= rhs;
	return temp;
}

template <typename Type>
const Polynom<Type> operator%(const Polynom<Type>& lhs, const Polynom<Type> & rhs)
{
	Polynom<Type> temp=lhs;
	temp %= rhs;
	return temp;
}

template <typename Type>
const Polynom<Type> operator*(const Type& num, const Polynom<Type>& rhs)
{
	Polynom<Type> temp = rhs;

	return temp *= num;
}
#endif // !TEMPLATE_H_INCLUDED
