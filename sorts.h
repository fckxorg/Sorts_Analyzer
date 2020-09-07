template <typename T>
void insertionSort(T* begin, T* end)  
{  
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