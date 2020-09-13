#include <assert.h>

template <typename T>
class AbstractSort
{
    public:
        virtual void operator()(T* begin, T* end) const = 0;
};

template <typename T>
class InsertionSort : public AbstractSort<T>
{
    public:
        void operator()(T* begin, T* end) const override
        {
            assert(begin != nullptr);
            assert(end != nullptr);

            for (T* current = begin + 1; current != end; ++current) 
            {  
                T key = *current;  
                T* place = current - 1;  
                while (place >= begin && *place > key) 
                {  
                    *(place + 1) = *place;  
                    --place;
                }  
                *(place + 1) = key;  
            }  
        }
};