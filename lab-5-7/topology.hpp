#pragma once

#include <iostream>
#include <list>

template<class T>
class topology_t {
	private:
		using list_type = std::list< std::list<T> >;
		using iterator = typename std::list<T>::iterator;
		using list_iterator = typename list_type::iterator;

		list_type container;
		size_t container_size;
	public:
		topology_t() noexcept : container(), container_size(0) {}
		~topology_t() {}

		bool erase(const T & elem) { /*функция удаляет элемент типа T из контейнера container*/
			for (list_iterator it1 = container.begin(); it1 != container.end(); ++it1) {
				for (iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
					if (*it2 == elem) {
						if (it1->size() > 1) {
							it1->erase(it2);
						} else {
							container.erase(it1);
						}
						--container_size;
						return true;
					}
				}
			}
			return false;
		}

		long long find(const T & elem) {// в каком списке существует (или нет) элемент с идентификатором $id
			long long ind = 0;
			for (list_iterator it1 = container.begin(); it1 != container.end(); ++it1) {
				for (iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
					if (*it2 == elem) {
						return ind;
					}
				}
				++ind;
			}
			return -1;
		}

		bool insert(const T & parent, const T & elem) {
		/*Функция insert принимает на вход два аргумента: parent и elem. 
  		Она ищет элемент parent в контейнере и добавляет элемент elem после него в ту же подсписок, 
		если parent был найден. Если parent не найден, функция возвращает false, иначе - true*/
			for (list_iterator it1 = container.begin(); it1 != container.end(); ++it1) {
				for (iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
					if (*it2 == parent) {
						it1->insert(++it2, elem);
						++container_size;
						return true;
					}
				}
			}
			return false;
		}

		void insert(const T & elem) { /*добавляет элемент в структуру topology_t*/
			std::list<T> new_list;
			new_list.push_back(elem);
			++container_size;
			container.push_back(new_list);
		}

		size_t size() {
			return container_size;
		}

		template<class U> /*оператор вывода в поток*/
		friend std::ostream & operator << (std::ostream & of, const topology_t<U> & top) {
			for (auto it1 = top.container.begin(); it1 != top.container.end(); ++it1) {
				of << "{";
				for (auto it2 = it1->begin(); it2 != it1->end(); ++it2) {
					of << *it2 << " ";
				}
				of << "}" << std::endl;
			}
			return of;
		}
};