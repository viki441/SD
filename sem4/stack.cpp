//zadacha za linked stack

/*
tova e stack

* xx *
* 10 *
* 11 *
* 12 *
* __ *

tova e linked stack:
		*********     *********      *********
list--->* 10 |------->* 11 |-------->* 12 | -----> nullptr
		********      ********       *********

kudeto kutiikata s 10 e tos
ottam se vadi i dobavq elemeti

*/

#include <stdexcept>
#include <iostream>
using namespace std;
#include <string>

template<typename T> // hubavo e da e template za da raboti za vsichko
class linkedStack
{
public:
	//--------------------------------------PUSH------------------------------------------------
	void push(T& value) // dobavqne na element PREDI segashniq tos
	{
		//primerno {       46, [10 | pointer kum 11]       } cqloto e pointer A
		//
		node* data = new node{ value, tos }; //tuk redirektvame nai-noviq node (46) da sochi kum segashniq tos koeto e node(10)
		tos = data; // Veche lista zapocha ot pointer A koeto znachi che tos sochi kum node (46)
	}


	//---------------------------------------POP----------------------------------------------
	T pop()
	{
		if (tos != nullptr)
		{
			node* temporary = tos; //vzimame elementa kum kojto sochi list
			tos = temporary->next; /*tuk veche sme vzeli elementa kum koito sochi list
			i mu vzimame puk negovata kutiika na kude sochi, i kazvame na
			list da sochi napravo natam*/

			T data = temporary->data; //poneje sa kazali pop da ne e void shte polzvame tova, za da vurnem samo stojnostta na kuttikata kum koqto sochi list
			delete temporary;//triem
			/*poluchava se da se iztrie zashtoto veche sme redirectnali tos, i sme napravili temporary, koito e edinstvenoto pointerche, koeto sochi kum stariq tos*/
			return data;

		}
		throw std::out_of_range("error");
	}


	//-------------------------------TOP------EMPTY-----------------------------------------
	bool isEmpty()
	{
		return tos == nullptr;
	}

	T top() // tuk se vzima ne addresa za tos, a koq stoinost (data) e pri kutiikata kum koqto sochi lista
	{
		if (tos != nullptr) return tos->data;
		throw std::out_of_range("Error");
	}

	//-------------------------------SIZE-----------------------------------------------------

	int getSize()
	{
		int counter = 0;
		node* runner = tos; // runner will 'run' through the list until end
		while (runner != nullptr)
		{
			counter++;
			runner = runner->next;
		}
		return counter;
	}

	//-------------------------------CLEAR---------------------------------------------------
	bool clearStack()
	{
		if (isEmpty()) 
			return false;

		while (!isEmpty())
			pop();
		
		return true;
	}
private:
	//tuk imame edin elemet koito e pointer kum tip struct node 
	// toi e top of stack
	// node* tos;
	struct node
	{
		T data; //vmesto onova int data
		node* next;
	} *tos; // toest pravim neshto kato vlojeno konteinerche
	//to go vzimame cqloto kato pointer
};


template<typename T>
class CompositeStack
{
private:
	linkedStack<T> stack1; // undo history
	linkedStack<T> stack2; // redo history


public:
	void push1(T& value)
	{
		stack1.push(value);
	}
	void push2(T& value)
	{
		stack2.push(value);
	}

	T pop1()
	{
		return stack1.pop();
	}
	T pop2()
	{
		return stack2.pop();
	}

	T peek1()
	{
		return stack1.top();
	}
	T peek2()
	{
		return stack2.top();
	}

	bool isEmpty1() {
		return stack1.isEmpty();
	}
	bool isEmpty2() {
		return stack2.isEmpty();
	}
};


class UndoRedoStringBuilder
{
private:
	string _s;
	CompositeStack<string> stacks;


public:
	void append(string& s)
	{
		stacks.push1(_s); //slaga se poslednata komanda  
		_s += s;
		while (!stacks.isEmpty2())
			stacks.pop2();
	}

	string getResult()
	{
		return this->_s;
	}

	void undo()
	{
		if (!stacks.isEmpty1())
		{
			stacks.push2(_s);
			_s = stacks.pop1();
		}
		throw std::out_of_range("cant undo\n");
	}
	void redo()
	{
		if (!stacks.isEmpty2())
		{
			stacks.push1(_s);
			stacks.pop2();
		}
		throw std::out_of_range("cant redo\n");
	}
};


int main()
{
	CompositeStack<int> s;
	int a = 1;
	int b = 2;


	s.push1(a);
	s.push2(b);

	std::cout << s.peek1() << " " << s.peek2() << std::endl;

	s.push1(b);
	s.push2(a);

	std::cout << s.peek1() << " " << s.peek2() << std::endl;

	std::cout << s.pop1() << " " << s.pop2() << std::endl;
	std::cout << s.peek1() << " " << s.peek2() << std::endl;
}
