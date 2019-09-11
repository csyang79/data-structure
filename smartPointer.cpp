template <class T>
class shared_ptr
{
	public:
		shared_ptr( T* p ) :
			ptr( p ),
			count( new int (1) )
	{
	}


		/* copy constructor must copy the fields AND increment the reference count */
		shared_ptr( const shared_ptr<T> & other ) :
			ptr( other.ptr ),
			count( other.count )
	{
		incrementCount();
	}


		/* destructor must decrement reference count */
		~shared_ptr()
		{
			decrementCount();
		}


		/*
		 * assignment operator must decrement the reference count of the
		 * object the pointer no longer points to and increment the count
		 * of the object it now does point to
		 */
		shared_ptr<T> & operator=( const shared_ptr<T> & obj )
		{
			if ( this->ptr != obj.ptr )
			{
				decrementCount();
				ptr	= obj.ptr;
				count	= obj.count;
				incrementCount();
			}
			return(*this);
		}


		/* not a bad idea to have these, as someone else suggested */
		T* operator->()
		{
			return(ptr);
		}


		T & operator*()
		{
			return(*ptr);
		}


		T* get()
		{
			return(ptr);
		}


	private:
		inline void incrementCount()
		{
			(*count)++;
		}


		/*
		 * when decrementing, we must free the underlying
		 * pointer if there are no more copies of it
		 */
		inline void decrementCount()
		{
			(*count)--;
			if ( *count <= 0 )
			{
				delete ptr;
				delete count;
			}
		}


		T	* ptr;
		int	* count;
};
