#ifndef __STATEMACHINE_HEADER__
#define __STATEMACHINE_HEADER__

#include <iostream>
#include <vector>

#define stateNumber 3				// numero di stati all'interno della macchina.

template <class T>
class StateMachine {
private:
	static int currentState;				// puntatore allo stato corrente.
	static std::vector<T*> stack;			// struttura dati (pila) che contiene i puntatori agli stati.

public:

	static void init() {
		currentState = -1;
	}

	/* Aggiunge 'state' in cima alla pila e lo rende lo stato attivo. */
	static void push(T* state) {
		stack.push_back(state);
		currentState++;
	}

	/* Elimina l'ultimo stato dalla pila e mette il puntatore sulla nuova cima della pila. */
	static void pop() {
		stack.pop_back();
		currentState--;
	}

	/* Restituisce l'elemento in cima alla pila. */
	static T* top() {
		return stack.back();
	}

	/* Elimina tutti gli stati all'interno della state machine. */
	static void clear() {
		for (int i = currentState; i >= 0; i--)
			stack.pop_back();
		currentState = 0;
	}
};


#endif