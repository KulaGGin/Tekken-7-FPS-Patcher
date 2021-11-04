#pragma once
#include <vector>
#include <Windows.h>

#include "Mods/MemoryManager.h"

/**
     * \brief Proxy class that allows access to game variables using a multi-pointer
     * \tparam Type Type of the variable this proxy will give access to
     */
template<typename Type>
class ObjectProxy {
public:
    ObjectProxy() = default;
    explicit ObjectProxy(std::vector<uintptr_t> multiLevelPointer);
    Type* GetPointer() const;
    Type GetValue() const;
    void Set(Type valueToSet) const;
private:
    std::vector<uintptr_t> multiLevelPointer{};
};

/**
 * \brief Initializes the proxy object from the multi-level pointer
 * \param multiLevelPointer Multi-level pointer to the variable. Should include base address.
 *  Will dereference multiLevelPointer[0] + multiLevelPointer[1] if size of the multiLevelPointer is bigger than 2,
 *  otherwise end address will equal to multiLevelPointer[0] or multiLevelPointer[0] + multiLevelPointer[1]
 *  \param offset applies additional last offset, used for class' member variables.
 */
template<typename Type>
ObjectProxy<Type>::ObjectProxy(std::vector<uintptr_t> multiLevelPointer) {
    this->multiLevelPointer = multiLevelPointer;
}

/**
 * \brief Gets the pointer to the variable from the multi-level pointer
 * \return Returns pointer to the variable if address can be calculated.
 * Returns 0 if address can't be calculated.
 */
template<typename Type>
Type* ObjectProxy<Type>::GetPointer() const {
    return reinterpret_cast<Type*>(MemoryManager::GetAddress(multiLevelPointer));
}

/**
 * \brief Gets the value of the variable from the multi-level pointer
 * \return Returns read value or a default-initialized variable if it can't read the value from the pointer.
 */
template<typename Type>
Type ObjectProxy<Type>::GetValue() const {
    auto pointer = GetPointer();

    if(pointer == nullptr || IsBadReadPtr(reinterpret_cast<void*>(pointer), sizeof Type))
        return Type();

    return *pointer;
}

/**
 * \brief Sets the value of the variable the proxy gives access to,
 * if the variable can be accessed from the multi-pointer.
 * Doesn't set the variable if it can't be accessed from the multi-pointer.
 * \param valueToSet is value to set.
 */
template<typename Type>
void ObjectProxy<Type>::Set(Type valueToSet) const {
    Type* pointerToVariable = GetPointer();

    if(pointerToVariable != nullptr)
        *pointerToVariable = valueToSet;
}