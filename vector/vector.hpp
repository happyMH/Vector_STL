#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>
#include <vector>
#include <cstdlib>

using namespace std;

namespace sjtu
{

	template<typename T>
	class vector
	{
	public:
		T* a;
		size_t max_capacity;
		size_t curr_size;

		class const_iterator;
		class iterator
		{
		private:
	
			int i;
			vector* content;

		public:
			typedef T value_type;
			iterator() {}
			iterator(vector* _con, size_t _i) : content(_con), i(_i) {}
			iterator(const vector* _con, size_t _i) : content(const_cast<vector *>(_con)), i(_i) {}

			iterator operator+(const int &n)
			{
				return iterator(content, i + n);
			}

			iterator operator-(const int &n)
			{
				return iterator(content, i - n);
			}

			int operator-(const iterator &rhs)
			{
				if (content != rhs.content)
					throw invalid_iterator();

				return i - rhs.i;
			}

			int operator-(const const_iterator &rhs)
			{
				if (content != rhs.con)
					throw invalid_iterator();

				return i - rhs.i;
			}

			iterator operator+=(const int &n)
			{
				return *this = *this + n;
			}

			iterator operator-=(const int &n)
			{
				return *this = *this - n;
			}

			iterator operator++(int)
			{
				size_t tmp_i = i;
				++i;
				return iterator(content, tmp_i);
			}

			iterator& operator++()
			{
				++i;
				return *this;
			}

			iterator operator--(int)
			{
				size_t tmp_i = i;
				--i;
				return iterator(content, tmp_i);
			}
	
			iterator& operator--()
			{
				--i;
				return *this;
			}
	
			T& operator*() const
			{
				return (*content)[i];
			}

			bool operator==(const iterator &rhs) const
			{
				return (content == rhs.content && i == rhs.i);
			}
			bool operator==(const const_iterator &rhs) const
			{
				return (content == rhs.con && i == rhs.i);
			}

			bool operator!=(const iterator &rhs) const
			{
				return !(*this == rhs);
			}

			bool operator!=(const const_iterator &rhs) const
			{
				return !(*this == rhs);
			}

			bool operator<(const iterator &rhs) const
			{
				return i < rhs.i;
			}

			bool operator<(const const_iterator &rhs) const
			{
				return i < rhs.i;
			}
		};

		class const_iterator
		{
		private:

			int i;
			vector* con;

		public:
			typedef T value_type;
			const_iterator() {}
			const_iterator(vector* _con, size_t _i) : con(_con), i(_i) {}
			const_iterator(const vector* _con, size_t _i) : con(const_cast<vector *>(_con)), i(_i) {}
	
			const_iterator operator+(const int &n)
			{
				return const_iterator(con, i + n);
			}
			const_iterator operator-(const int &n)
			{
				return const_iterator(con, i - n);
			}

			int operator-(const iterator &rhs)
			{
				if (con != rhs.con)
					throw invalid_iterator();

				return i - rhs.i;
			}
			int operator-(const const_iterator &rhs)
			{
				if (con != rhs.con)
					throw invalid_iterator();

				return i - rhs.i;
			}
			const_iterator operator+=(const int &n)
			{
				return *this = *this + n;
			}
			const_iterator operator-=(const int &n)
			{
				return *this = *this - n;

			}

			const_iterator operator++(int)
			{
				size_t tmp_i = i;
				++i;
				return const_iterator(con, tmp_i);
			}

			const_iterator& operator++()
			{
				++i;
				return *this;
			}

			const_iterator operator--(int)
			{
				size_t tmp_i = i;
				--i;
				return const_iterator(con, tmp_i);
			}

			const_iterator& operator--()
			{
				--i;
				return *this;
			}

			const T& operator*() const
			{
				return (*con)[i];
			}
		
			bool operator==(const iterator &rhs) const
			{
				return (con == rhs.con && i == rhs.i);
			}
			bool operator==(const const_iterator &rhs) const
			{
				return (con == rhs.con && i == rhs.i);
			}
	
			bool operator!=(const iterator &rhs) const
			{
				return !(*this == rhs);
			}
			bool operator!=(const const_iterator &rhs) const
			{
				return !(*this == rhs);
			}

			bool operator<(const iterator &rhs) const
			{
				return i<rhs.i;
			}

			bool operator<(const const_iterator &rhs) const
			{
				return i<rhs.i;
			}
		};

		vector(int _size = 16) : curr_size(0), max_capacity(_size)
		{
			a = (T *) operator new(max_capacity * sizeof(T));
		}
		vector(const vector<T> &other)
		{
			curr_size = max_capacity = other.size();
			a = (T *) operator new(max_capacity * sizeof(T));
			for (size_t i = 0; i != curr_size; ++i)
			{
				new (a + i)T(other[i]);
			}
		}
		vector(const std::vector<T> &other)
		{
			curr_size = max_capacity = other.size();
			a = (T *) operator new(max_capacity * sizeof(T));
			for (size_t i = 0; i != curr_size; ++i)
			{
				new (a + i)T(other[i]);
			}
		}
		void del()
		{
			for (size_t i = 0; i != curr_size; ++i)
				a[i].~T();
			operator delete(a);
		}

		~vector()
		{
			del();
		}

		vector<T>& operator=(const vector<T> &other)
		{
			if (this == &other)
				return *this;

			del();

			curr_size = other.size();
			max_capacity = other.capacity();
			a = (T *) operator new(max_capacity * sizeof(T));


			size_t i = 0;
			for (const_iterator it = other.cbegin(); it != other.cend(); ++it, ++i) {
				new (a + i)T(*it);
			}

			return *this;
		}

		T & at(const size_t &pos)
		{
			if (pos < 0 || pos >= curr_size)
				throw index_out_of_bound();

			return a[pos];
		}
		const T & at(const size_t &pos) const
		{
			if (pos<0 || pos >= curr_size)
				throw index_out_of_bound();

			return a[pos];
		}

		T & operator[](const size_t &pos)
		{
			if (pos<0 || pos >= curr_size)
				throw index_out_of_bound();

			return a[pos];
		}
		const T & operator[](const size_t &pos) const
		{
			if (pos<0 || pos >= curr_size)
				throw index_out_of_bound();

			return a[pos];
		}

		const T & front() const
		{
			if (curr_size == 0)
				throw container_is_empty();

			return a[0];
		}

		const T & back() const
		{
			if (curr_size == 0)
				throw container_is_empty();

			return a[curr_size - 1];
		}

		iterator begin()
		{
			return iterator(this, 0);
		}
		const_iterator cbegin() const
		{
			return const_iterator(this, 0);
		}
	
		iterator end()
		{
			return iterator(this, curr_size);
		}
		const_iterator cend() const
		{
			return const_iterator(this, curr_size);
		}

		bool empty() const
		{
			return curr_size == 0;
		}

		size_t size() const
		{
			return curr_size;
		}

		size_t capacity() const
		{
			return max_capacity;
		}

		void clear()
		{
			del();
			curr_size = 0;
			max_capacity = 16;
			a = (T *) operator new(max_capacity * sizeof(T));
		}
		void double_space()
		{
			max_capacity <<= 1;
			T* b = (T *) operator new(max_capacity * sizeof(T));
			for (size_t i = 0; i != curr_size; ++i)
				new (b + i)T(a[i]);
			del();
			a = b;
		}

		iterator insert(iterator pos, const T &value)
		{
			if (curr_size + 1>max_capacity)
				double_space();

			++curr_size;

			new (a + curr_size - 1)T(value);

			for (iterator it = end() - 1; it != pos; --it)
				*it = *(it - 1);

			*pos = value;

			return pos;
		}

		iterator insert(const size_t &ind, const T &value)
		{
			if (ind<0 || ind>curr_size)
				throw index_out_of_bound();

			if (curr_size + 1>max_capacity)
				double_space();

			++curr_size;

			new (a + curr_size - 1)T(value);

			for (size_t i = curr_size - 1; i != ind; --i)
				a[i] = a[i - 1];

			a[ind] = value;

			return iterator(this, ind);
		}

		iterator erase(iterator pos)
		{
			for (iterator it = pos; it != end() - 1; ++it)
				*it = *(it + 1);

			a[curr_size - 1].~T();
			--curr_size;

			return pos;
		}

		iterator erase(const size_t &ind)
		{
			if (ind<0 || ind >= curr_size)
				throw index_out_of_bound();

			for (size_t i = ind; i != curr_size - 1; ++i)
				a[i] = a[i + 1];

			a[curr_size - 1].~T();
			--curr_size;

			return iterator(this, ind);
		}

		void push_back(const T &value)
		{
			if (curr_size + 1 > max_capacity)
			{
				double_space();
			}

			new (a + (curr_size++))T(value);
		}

		void pop_back()
		{
			if (curr_size == 0)
				throw container_is_empty();

			a[curr_size - 1].~T();
			--curr_size;
		}

		void double_space(const size_t _size)
		{
			del();
			curr_size = _size;
			max_capacity = 1;
			while (max_capacity <= curr_size)
				max_capacity <<= 1;
			a = (T *) operator new(max_capacity * sizeof(T));
			for (size_t i = 0; i<curr_size; ++i)
				new (a + i)T();
		}
	};
}

#endif
