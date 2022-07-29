#include <vector>


namespace Sort{
    template <typename T>
    static void swap(T* a, T* b){
        T tmp = *a;
        *a = *b;
        *b =  tmp;
    }
    
    template<typename T>
    static int partition(std::vector<T>& vec, int low, int high){
        int pivotIndex = high;
        int i = (low - 1);
        for(int j = low; j <= high - 1; ++j){
            if(vec[j] < vec[pivotIndex]){
                ++i;
                swap(&vec[i], &vec[j]);
            }
        }
        swap(&vec[i+1], &vec[high]);
        return (i+1);
    }

    template<typename T>
    static void quickSort(std::vector<T>& vec, int low, int high){
        if(low < high){
            int pi = partition(vec, low, high);
            quickSort(vec, low, pi - 1);
            quickSort(vec, pi + 1, high);
        }
    }
}