/*
 * Request.h
 *
 *  Created on: 18/05/2019
 *      Author: Gustavo
 */

#ifndef SRC_REQUEST_H_
#define SRC_REQUEST_H_

#include "Graph.h"

template <class T> class Request {
  T inicio;
  T fim;
  string especialidade;

public:
  Request(T inicio, T fim, string especialidade);
  T getInicio() const;
  T getFim() const;
  void setInicio(T inicio);
  void setFim(T fim);
  string getEspecialidade() const;
};

template <class T>
Request<T>::Request(T inicio, T fim, string especialidade)
    : inicio(inicio), fim(fim), especialidade(especialidade) {}

template <class T> T Request<T>::getInicio() const { return inicio; }

template <class T> T Request<T>::getFim() const { return fim; }

template <class T> void Request<T>::setInicio(T inicio) {
  this->inicio = inicio;
}

template <class T> void Request<T>::setFim(T fim) { this->fim = fim; }

template <class T> string Request<T>::getEspecialidade() const {
  return especialidade;
}

#endif /* SRC_REQUEST_H_ */
