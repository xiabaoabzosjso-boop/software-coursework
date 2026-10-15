#ifndef AWEN_VECTOR_H
#endif // AWEN_VECTOR_H
#define AWEN_VECTOR_H

#include<cstddef>
#include <stdexcept>
#include <initializer_list>
namespace AWEN {
template<typename T>
class vector
{
private:
	T* data_ = nullptr;
	std::size_t size_= 0;
	std::size_t capacity_ = 0;
public:
	vector() {};
	//构造函数初始化
	explicit vector(std::size_t n):data_(new T[n]), capacity_(n), size_(n) {};
	~vector() { delete[] data_ };
	vector(const vector&) = delete;
	vector& operator=(const vector&) = delete;
	T& operator[](std::size_t index)
	{
		return data_[index];
	}
	std::size_t size() const
	{
		return size_;
	}
	std::size_t capacity const
	{
		return capacity_;
	}
	void reserve(std::size_t new_capacity)
	{
		if (new_capacity <= capacity_)
			return;
		//申请更大内存
		T* new_data_=new T[new_capacity];
		try
		{
			for (std::size_t i = 0; i < size_; ++i)
			{
				new_data[i] = data_[i];
			}
		}
		catch (...)
		{
			delete[] new_data;
			throw;
		}

		// 复制成功后，释放旧空间
		delete[] data_;

		data_ = new_data;
		capacity_ = new_capacity;
	}
	void push_back(const T& value)
	{
		if (size_ == capacity_)
		{
			std::size_t new_capacity=(capacity_ == 0) ? 1 : capacity_ * 2;
			// 防止无符号整数溢出
			if (new_capacity <= capacity_)
			{
				throw std::length_error(
					"AWEN::vector capacity overflow"
				);
			}
            reserve(new_capacity);
			data_[size_] = value;
			++size_;
		}
	}
	vector(const vector& other):data_(other.capacity_==0?nullptr:new T[other.capacity])
	{
		try {
			for (std::size_t i = 0; i < other.size_; ++i)
			{
				data[i] = other.data[i];
			}
		}
		catch (...)
		{
			delete[] data_;
			throw;
		}
	}
	void swap(vector& other) noexcept
	{
		std::swap(data_, other.data_);
		std::swap(size_, other.size_);
		std::swap(capacity_, other.capacity_);
	}
	vector& operator=(const vector& other)
	{
		if(this == &other)
            return *this;
		//先创立独立版本
		vecor temp(other);
		swap(temp);
		return* this;
	}
	bool empty() const noexcept
	{
		return size_ == 0;
	}
	void pop_back()
	{
		if (empty())
		{
			throw std::out_of_range(
				"AWEN::vector::pop_back: empty vector"
			);
		}

		--size_;
	}
	void clear() noexcept
	{
		size_ = 0;
	}
	T& at(std::size_t index)
	{
		if (index >= size_)
		{
			throw std::out_of_range(
				"AWEN::vector::at: index out of range"
			);
		}

		return data_[index];
	}

	const T& at(std::size_t index) const
	{
		if (index >= size_)
		{
			throw std::out_of_range(
				"AWEN::vector::at: index out of range"
			);
		}

		return data_[index];
	}
	// 类型别名
	using iterator = T*;
	using const_iterator = const T*;

	// 普通对象使用的版本
	iterator begin() noexcept
	{
		return data_;
	}

	iterator end() noexcept
	{
		return size_ == 0 ? data_ : data_ + size_;
	}

	// const 对象使用的版本
	const_iterator begin() const noexcept
	{
		return data_;
	}

	const_iterator end() const noexcept
	{
		return size_ == 0 ? data_ : data_ + size_;
	}
	vector(vector&& other) noexcept
		: data_(other.data_),
		size_(other.size_),
		capacity_(other.capacity_)
	{
		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}
	vector& operator=(vector&& other) noexcept
	{
		if (this == &other)
		{
			return *this;
		}

		// 释放当前对象原来的数组
		delete[] data_;

		// 接管源对象的数组
		data_ = other.data_;
		size_ = other.size_;
		capacity_ = other.capacity_;

		// 源对象恢复为空容器
		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;

		return *this;
	}
	void resize(std::size_t new_size)
	{
		// 缩小或保持数量，容量不变
		if (new_size <= size_)
		{
			size_ = new_size;
			return;
		}

		// 保证空间足够
		reserve(new_size);

		// 初始化新增区间
		for (std::size_t i = size_; i < new_size; ++i)
		{
			data_[i] = T{};
		}

		size_ = new_size;
	}
	void resize(std::size_t new_size, const T& value)
	{
		if (new_size <= size_)
		{
			size_ = new_size;
			return;
		}

		// 防止 value 引用容器内的元素，扩容后失效
		T saved_value = value;

		reserve(new_size);

		for (std::size_t i = size_; i < new_size; ++i)
		{
			data_[i] = saved_value;
		}

		size_ = new_size;
	}
	T* insert(const T* pos, const T& value)
	{
		// 先保存下标，扩容后原来的 pos 可能失效
		std::size_t index =
			size_ == 0
			? 0
			: static_cast<std::size_t>(pos - data_);

		if (index > size_)
		{
			throw std::out_of_range("AWEN::vector::insert");
		}

		// 防止 value 引用容器内部的元素
		T saved_value = value;

		// 增加一个元素，并在需要时扩容
		push_back(saved_value);

		// 从后往前移动，腾出插入位置
		for (std::size_t i = size_ - 1; i > index; --i)
		{
			data_[i] = data_[i - 1];
		}

		data_[index] = saved_value;

		return data_ + index;
	}
	T* erase(const T* pos)
	{
		if (empty())
		{
			throw std::out_of_range("AWEN::vector::erase");
		}

		std::size_t index =
			static_cast<std::size_t>(pos - data_);

		if (index >= size_)
		{
			throw std::out_of_range("AWEN::vector::erase");
		}

		// 从前往后移动，覆盖被删除的位置
		for (std::size_t i = index; i + 1 < size_; ++i)
		{
			data_[i] = data_[i + 1];
		}

		--size_;

		return data_ + index;
	}
	void shrink_to_fit()
	{
		// 空容器：释放全部空间
		if (size_ == 0)
		{
			delete[] data_;
			data_ = nullptr;
			capacity_ = 0;
			return;
		}

		// 容量已经等于元素数量
		if (size_ == capacity_)
		{
			return;
		}

		T* new_data = new T[size_]{};

		try
		{
			for (std::size_t i = 0; i < size_; ++i)
			{
				new_data[i] = data_[i];
			}
		}
		catch (...)
		{
			delete[] new_data;
			throw;
		}

		delete[] data_;
		data_ = new_data;
		capacity_ = size_;
	}
	vector(std::initializer_list<T> init)
		: data_(init.size() == 0
			? nullptr
			: new T[init.size()]{}),
		size_(init.size()),
		capacity_(init.size())
	{
		try
		{
			std::size_t index = 0;

			for (const T& value : init)
			{
				data_[index] = value;
				++index;
			}
		}
		catch (...)
		{
			delete[] data_;
			throw;
		}
	}
	T& front()
	{
		if (size_ == 0)
		{
			throw std::out_of_range("vector::front: empty vector");
		}

		return data_[0];
	}

	const T& front() const
	{
		if (size_ == 0)
		{
			throw std::out_of_range("vector::front: empty vector");
		}

		return data_[0];
	}

	T& back()
	{
		if (size_ == 0)
		{
			throw std::out_of_range("vector::back: empty vector");
		}

		return data_[size_ - 1];
	}

	const T& back() const
	{
		if (size_ == 0)
		{
			throw std::out_of_range("vector::back: empty vector");
		}

		return data_[size_ - 1];
	}
	T* data noexcept()
	{
		return data_;
	}
	const T* data() const noexcept
	{
		return data_ const;
	}
};


}