//
// Created by amit levi on 22/12/2022.
///=============================================================================================
///=============================================================================================
//                         ##          #########       #########
//                       ##  ##        ##     ##       ##     ##
//                      ##    ##       #########       #########
//                     ##########      ##     ##       ##     ##
//                    ##        ##     ##      ##      ##      ##
//                   ##          ##    ##       ##     ##       ##
///=============================================================================================
///=============================================================================================
#ifndef DATASTRUCTHW2_O1ARRAY_H
#define DATASTRUCTHW2_O1ARRAY_H
#include <string>
#include <exception>
///=======================================O1ArrayException======================================================
class O1ArrayException: public std::exception {
public:
    explicit O1ArrayException(const char* message) :
            msg_(message) {
    }
    explicit O1ArrayException(const std::string& message) :
            msg_(message) {
    }
    virtual ~O1ArrayException() throw () {
    }
    virtual const char* what() const throw () {
        return msg_.c_str();
    }
protected:
    std::string msg_;
};


///=======================================O1Array======================================================
/*
 * Requirements: default-constructible, copy-constructible.
 *
 * Initialization: O(1) time
 *
 * Simulates an array of initialized to default value items. Though each item is
 * initialized on demand only, which doesn't require O
 */
template<typename T>
class O1Array {
    int array_size;
    T *values;
    /* init_indices is a stack of indices of initialized values
     * init_indices_top the index of top of the stack, first undefined value in stack. */
    int *init_indices;
    int init_indices_top;
    int *index_indices;
    T init_value;

//=============================================================================================
///=====================================FUNCTIONS==============================================
//=============================================================================================

///=======================================is_initialized======================================================
    bool is_initialized(int i) const {
        int index_in_init_indices = index_indices[i];
        if (index_in_init_indices >= init_indices_top
            || index_in_init_indices < 0)
            return false;
        return init_indices[index_in_init_indices] == i;
    }
///=======================================initialize======================================================
    /* Usage on initialized index undefined. Check before use */
    void initialize(int i) {
        init_indices[init_indices_top] = i;
        index_indices[i] = init_indices_top;
        ++init_indices_top;
        values[i] = init_value;
    }
///=======================================O1Array======================================================
    /* Since copying and assigning of arrays isn't O(1) operation,
     * copying and assigning O1Array isn't possible (otherwise it weren't O1).
     * If you need to copy an O1Array anyway, you can create a new empty one,
     * and copy value-by-value.
     */
    O1Array(const O1Array<T>&);
    O1Array<T>& operator=(const O1Array<T>&);

public:
///=======================================O1Array======================================================
    /* Creates an array, where each item will be initialized on demand with
     * init_value.
     */
    O1Array(int n, const T& init_value) :
            array_size(n),
            init_indices_top(0),
            init_value(init_value) {
        if (array_size <= 0)
            throw O1ArrayException("O1Array: array size negative or zero");
        values = new T[array_size];
        init_indices = new int[array_size];
        index_indices = new int[array_size];
    }
///=====================================O1ArrayException======================================================
    /* Returns a reference to i-th item in array. If index i had been never
     * used before, init_value (look C'tor description) is assigned
     * to i-th item.
     * If index is out of array bounds, O1ArrayException is thrown.
     */
    T& operator[](int i) {
        if (i < 0 || i >= array_size) {
            throw O1ArrayException("O1Array: index out of bounds");
        }
        if (!is_initialized(i)) {
            initialize(i);
        }
        return values[i];
    }
    const T& operator[](int i) const {
        if (i < 0 || i >= array_size) {
            throw O1ArrayException("O1Array: index out of bounds");
        }
        if (!is_initialized(i)) {
            return init_value;
        }
        return values[i];
    }
///========================================size======================================================
    int size() const {
        return array_size;
    }

    ~O1Array() {
        delete[] index_indices;
        delete[] init_indices;
        delete[] values;
    }
};
#endif //DATASTRUCTHW2_O1ARRAY_H
///=============================================================================================
///=============================================================================================
//                         ##          #########       #########
//                       ##  ##        ##     ##       ##     ##
//                      ##    ##       #########       #########
//                     ##########      ##     ##       ##     ##
//                    ##        ##     ##      ##      ##      ##
//                   ##          ##    ##       ##     ##       ##
///=============================================================================================
///=============================================================================================

