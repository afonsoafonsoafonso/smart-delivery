/*
 * Request.h
 *
 *  Created on: 18/05/2019
 *      Author: Gustavo
 */

#ifndef SRC_REQUEST_H_
#define SRC_REQUEST_H_

#include "Graph.h"

template<class T>
class Request{

	T inicio;
	T fim;
	string especialidade;
	bool valid = true;

public:
	Request(T inicio , T fim, string especialidade);
	T getInicio() const;
	T getFim() const;
	string getEspecialidade() const;
	bool isValid()const;
	void setValid(bool v);

};


template<class T>
Request<T>::Request(T inicio, T fim,string especialidade) : inicio(inicio) , fim(fim) , especialidade(especialidade){}

template<class T>
T Request<T>::getInicio() const{return inicio;}

template<class T>
T Request<T>::getFim() const{return fim;}

template<class T>
string Request<T>::getEspecialidade() const{return especialidade;}

template<class T>
bool Request<T>::isValid()const{ return valid;}
template<class T>
void Request<T>::setValid(bool v){valid = v;}



#endif /* SRC_REQUEST_H_ */