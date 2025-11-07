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
		********     *********      ********* 

kudeto kutiikata s 10 e tos 
ottam se vadi i dobavq elemeti

*/

#include <stdexcept>
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

			T data = temp->data; //poneje sa kazali pop da ne e void shte polzvame tova, za da vurnem samo stojnostta na kuttikata kum koqto sochi list
			delete temp;//triem
			/*poluchava se da se iztrie zashtoto veche sme redirectnali tos, i sme napravili temporary, koito e edinstvenoto pointerche, koeto sochi kum stariq tos*/
			return data;

		}
		throw std::out_of_range("error");
	}


//------------------------------- TOP I EMPTY (peek is top i guess)
	bool isEmpty()
	{
		return tos == nullptr;
	}
	T top() // tuk se vzima ne addresa za tos, a koq stoinost (data) e pri kutiikata kum koqto sochi lista
	{
		if (tos != nullptr) return tos->data;
		throw std::out_of_range("Error");
	}

//---------------------------------------------//PROVERI!!!!!!!!!!!!!!!!!!!!!!!!!!

	int getSize() //PROVERI!!!!!!!!!!!!!!!!!!!!!!!!
	{
		int counter = 0;
		node* runner = tos; // runner will 'run' through the list until end
		while (runner)
		{
			counter++;
			runner = runner->next;
		}
		return counter;
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
	linkedStack<T> stack1;
	linkedStack<T> stack2;
};


int main()
{
	linkedStack<int> stack1;
	int n = 1;
	stack1.push(n);


}
