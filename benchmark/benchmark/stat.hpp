#ifndef STAT_HPP
#define STAT_HPP

template <typename T>
class Stat 
{
    public:
        T value;
        static size_t n_comparisons;
        static size_t n_assignments;

        Stat() : value(T()) {}; 

        Stat(T value) : value(value) {}

        Stat& operator=(const Stat& other)
        {
            if(this == &other)
            {
                return *this;
            }

            ++n_assignments;
            this->value = other.value;

            return *this;
        }

        Stat(const Stat& other)
        {
            ++n_assignments; //ask Dedinskiy
            value = other.value;
        }

        Stat& operator=(Stat&& other)
        {
            ++n_assignments;
            swap(*this, other);

            return *this;
        }

        Stat(Stat&& other)
        {
            ++n_assignments; //ask Dedinskiy
            swap(*this, other);
        }
        

        friend void swap(Stat<T>& first, Stat<T>& second)
        {
            std::swap(first.value, second.value);
        }
};

template <typename T> size_t Stat<T>::n_assignments;
template <typename T> size_t Stat<T>::n_comparisons;

template<typename T>
auto operator<=>(const Stat<T>& first, const Stat<T>& second)
{
    ++Stat<T>::n_comparisons;
    return first.value <=> second.value;
}

template<typename T>
bool operator==(const Stat<T>& first, const Stat<T>& second)
{
    ++Stat<T>::n_comparisons;
    return first.value == second.value;
}

#endif