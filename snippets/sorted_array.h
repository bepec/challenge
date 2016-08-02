#pragma once

//T* sorted_array_find_recur(T* data, T size, T value) {
    //if (size == 0) return data;
    //if (size == 1) return (*data < value ? data + 1 : data);
    //int p = size / 2;
    //if (data[p] == value) {
        //while (p < size - 1 && data[p+1] == value) p++;
        //return &data[p];
    //}
    //if (data[p] > value) return sorted_array_find(data, p, value);
    //return sorted_array_find(data + p + 1, size - p - 1, value);
//}

template<class T>
T* sorted_array_find(T* data, int size, T value) {
    while (size > 1) {
        int p = size / 2;
        if (data[p] == value) {
            while (p < size - 1 && data[p+1] == value) p++;
            return &data[p];
        }
        else if (data[p] > value) size = p;
        else {
            data += p + 1;
            size -= p + 1;
        }
    }
    if (size == 0) return data;
    return (*data < value ? data + 1 : data);
}

template<class T>
T* sorted_array_push(T* data, int size, T value) {
    T* pos = sorted_array_find(data, size, value);
    if (size > 0 && *pos == value) pos += 1;
    T* end = data + size;
    for (T* it = end; it > pos; it--) *it = *(it - 1);
    *pos = value;
    return pos;
}

