#ifndef _CIRCULAR_BUFFER_H_
#define _CIRCULAR_BUFFER_H_

#include "Common/Allocator.h"
#include "Common/Iterator.h"
#include "Common/UninitializedFunctions.h"

#include <cassert>

namespace TinySTL
{
	template <class T, size_t N, class Alloc> // 元素类型、缓冲区大小、分配器
	class circular_buffer;
	namespace Detail
	{
		// the iterator of circular buffer
		template <class T, size_t N, class Alloc = allocator<T>>
		class cb_iter : iterator<bidirectional_iterator_tag, T>
		{ // bidirectional iterator
		private:
			typedef ::TinySTL::circular_buffer<T, N, Alloc> cb;
			typedef cb *cbPtr;

			T *ptr_;		  // 元素指针
			int index_;		  // 索引
			cbPtr container_; // 容器指针

		public:
			cb_iter() : ptr_(0), index_(0), container_(0) {}
			cb_iter(T *ptr, cbPtr container) : ptr_(ptr), index_(ptr - container->start_), container_(container) {}
			cb_iter(const cb_iter &cit) : ptr_(cit.ptr_), index_(cit.index_), container_(cit.container_) {} // 拷贝构造
			cb_iter &operator=(const cb_iter &cit);

		public:
			operator T *() { return ptr_; }
			T &operator*() { return *ptr_; }
			T *operator->() { return &(operator*()); }

			cb_iter &operator++();
			cb_iter operator++(int);
			cb_iter &operator--();
			cb_iter operator--(int);
			bool operator==(const cb_iter &it) const;
			bool operator!=(const cb_iter &it) const;

		private:
			void setIndex_(int index) { index_ = index; }
			void setPtr_(T *ptr) { ptr_ = ptr; }
			int nextIndex(int index) { return (++index) % N; }
			int prevIndex(int index);

		public:
			template <class T1, size_t N1, class Alloc1>
			friend Detail::cb_iter<T1, N1, Alloc1> operator+(const Detail::cb_iter<T1, N1, Alloc1> &cit, std::ptrdiff_t i);

			template <class T1, size_t N1, class Alloc1>
			friend Detail::cb_iter<T1, N1, Alloc1> operator-(const Detail::cb_iter<T1, N1, Alloc1> &cit, std::ptrdiff_t i);
		};
	} // end of Detail namespace

	// circular buffer
	template <class T, size_t N, class Alloc = allocator<T>>
	class circular_buffer
	{
		friend class Detail::cb_iter<T, N, Alloc>;

	public:
		typedef T value_type;
		typedef Detail::cb_iter<T, N> iterator;
		typedef iterator pointer;
		typedef T &reference;
		typedef int size_type;
		typedef ptrdiff_t difference_type;

	private:
		T *start_;
		T *finish_;
		int indexOfHead; // the first position
		int indexOfTail; // the last position
		size_type size_;

		typedef Alloc dataAllocator;

	public:
		explicit circular_buffer(const int &n, const value_type &val = value_type());
		template <class InputIterator>
		circular_buffer(InputIterator first, InputIterator last);
		circular_buffer(const circular_buffer &cb);
		circular_buffer &operator=(const circular_buffer &cb);
		circular_buffer &operator=(circular_buffer &&cb);
		circular_buffer(circular_buffer &&cb);
		~circular_buffer();

		bool full() { return size_ == N; }
		bool empty() { return size_ == 0; }
		difference_type capacity() { return finish_ - start_; }
		size_type size() { return size_; }
		void clear();

		iterator first() { return iterator(start_ + indexOfHead, this); }
		iterator last() { return iterator(start_ + indexOfTail, this); }

		reference operator[](size_type i) { return *(start_ + i); }
		reference front() { return *(start_ + indexOfHead); }
		reference back() { return *(start_ + indexOfTail); }
		void push_back(const T &val);
		void pop_front();

		bool operator==(circular_buffer &cb);
		bool operator!=(circular_buffer &cb);

		// Alloc get_allocator() { return dataAllocator; }

	private:
		void allocateAndFillN(const int &n, const value_type &val);
		template <class InputIterator>
		void allocateAndCopy(InputIterator first, InputIterator last);
		int nextIndex(int index) { return (index + 1) % N; }
		void copyAllMembers(const circular_buffer &cb);
		void zeroCircular(circular_buffer &cb);
		void clone(const circular_buffer &cb);

	public:
		template <class T1, size_t N1, class Alloc1>
		friend std::ostream &operator<<(std::ostream &os, circular_buffer<T1, N1, Alloc1> &cb);
	}; // end of circular buffer
}

#include "CircularBuffer.impl.h"
#endif