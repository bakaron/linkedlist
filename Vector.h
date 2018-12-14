#ifndef AISDI_LINEAR_VECTOR_H
#define AISDI_LINEAR_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace aisdi
{
// array doubles in size while going over extent;; STL does so
//
//
template <typename Type>
class Vector
{
public:
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using value_type = Type;
  using pointer = Type*;
  using reference = Type&;
  using const_pointer = const Type*;
  using const_reference = const Type&;

  class ConstIterator;
  class Iterator;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
private:
  size_type reserved_size;
  size_type act_size;
  pointer vec_array;

  void reserve(const size_type size_r){
    pointer arr = new Type[size_r];

    for(unsigned int i=0;i<act_size;i++){
      arr[i]=vec_array[i];
    }
    reserved_size=size_r;
    delete  vec_array;
    vec_array=arr;
    //delete arr;

  }


public:
  Vector()
  {
    act_size = 0;
    reserved_size = 0;
    vec_array = nullptr;
  }

  Vector(std::initializer_list<Type> l)
  {
  act_size = 0;

   // act_size = l.size();
    reserved_size = 2 * l.size();
    vec_array=new Type[reserved_size];
    unsigned int it=0;
    for(auto i=l.begin();i != l.end();i++,it++){
     // vec_array[it]=*i;
     append(*i);
    }


    //(void)l; // disables "unused argument" warning, can be removed when method is implemented.
   // throw std::runtime_error("TODO");
  }

  Vector(const Vector& other)
  {
    act_size = other.act_size;
    reserved_size = other.reserved_size;
    vec_array = new Type[reserved_size];

    for(unsigned int i = 0;i < act_size; i++){
      vec_array[i] = other.vec_array[i];
    }

    //(void)other;
    //throw std::runtime_error("TODO");
  }

  Vector(Vector&& other)
  {
    vec_array = other.vec_array;
    reserved_size = other.reserved_size;
    act_size = other.act_size;

    other.vec_array= nullptr;
    other.act_size=0;
    other.reserved_size=0;

    //(void)other;
    //throw std::runtime_error("TODO");
  }

  ~Vector()
  {
  if(vec_array != nullptr)  delete[] vec_array;
  }

  Vector& operator=(const Vector& other)
  {
    act_size = other.act_size;
    reserved_size = other.reserved_size;
    vec_array = new Type[reserved_size];

    for(unsigned int i = 0;i < act_size; i++){
      vec_array[i] = other.vec_array[i];
    }
    return *this;
   // (void)other;
  //  throw std::runtime_error("TODO");
  }

  Vector& operator=(Vector&& other)
  {
    vec_array = other.vec_array;
    reserved_size = other.reserved_size;
    act_size = other.act_size;

    other.vec_array= nullptr;
    other.act_size=0;
    other.reserved_size=0;

    return *this;
    //(void)other;
    //throw std::runtime_error("TODO");
  }

  bool isEmpty() const
  {
    return(act_size==0?1:0);
    //throw std::runtime_error("TODO");
  }

  size_type getSize() const
  {

    return act_size;
    //throw std::runtime_error("TODO");
  }

  void append(const Type& item)
  {

    if(act_size >= reserved_size){
        if (act_size==0)reserve(2);
        else
        reserve(reserved_size*2);
    }
    vec_array[act_size]=item;
    act_size+=1;
//why??
    //(void)item;
    //throw std::runtime_error("TODO");
  }

  void prepend(const Type& item)
  {
     if(act_size >= reserved_size){
        if (act_size==0)reserve(2);
        else
        reserve(reserved_size*2);
    }
      for(unsigned int i = act_size;i != 0;i--){
          vec_array[i]=vec_array[i-1];
      }
      vec_array[0]=item;
      act_size+=1;

    //(void)item;
    //throw std::runtime_error("TODO");
  }

  void insert(const const_iterator& insertPosition, const Type& item)
  {
    if(act_size >= reserved_size){
          reserve(reserved_size*2);
      }
    if(insertPosition.index==0){prepend(item);}
    else{
     for(unsigned int i = act_size;i != insertPosition.index;i--){
          vec_array[i]=vec_array[i-1];
      }
      vec_array[insertPosition.index]=item;
      }
      act_size+=1;


   // (void)insertPosition;
   // (void)item;
   // throw std::runtime_error("TODO");
  }

  Type popFirst()
  {
    if(act_size==0){throw std ::out_of_range("popfirst from empty");}
    Type var=vec_array[0];
    for(unsigned int i = 0;i<act_size-1;i++){
        vec_array[i]=vec_array[i+1];
    }
    act_size--;
      if (act_size < reserved_size/2){
          reserve(reserved_size/2);
      }
    return var;
   // throw std::runtime_error("TODO");
  }

  Type popLast()
  {
   if(act_size==0){throw std ::out_of_range("popfirst from empty");}
    Type var= vec_array[act_size-1];
    act_size--;
    if (act_size < reserved_size/2){
        reserve(reserved_size/2);
    }
      return var;
   // throw std::runtime_error("TODO");
  }

  void erase(const const_iterator& possition)
  {
  if (possition.index >= act_size){
        throw std::out_of_range("erase");}
    if(possition.index==0){popFirst();}
    else if(possition.index==act_size-1){popLast();}
    else
    for(unsigned int i = possition.index;i !=act_size-1 ;i++){
          vec_array[i]=vec_array[i+1];
      }

      act_size--;
   // (void)possition;
   // throw std::runtime_error("TODO");
  }

  void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded)
  {

    difference_type suv=lastExcluded.index-firstIncluded.index;
    for(unsigned int u=suv;u>0;u--){
        erase(firstIncluded);
    }

    //(void)firstIncluded;
   // (void)lastExcluded;
   // throw std::runtime_error("TODO");
  }

  iterator begin()
  {
    return Iterator(this,0);
   // throw std::runtime_error("TODO");
  }

  iterator end()
  {
    return Iterator(this,act_size);
    //throw std::runtime_error("TODO");
  }

  const_iterator cbegin() const
  {
    return ConstIterator(this,0);
    //throw std::runtime_error("TODO");
  }

  const_iterator cend() const
  {
    return ConstIterator(this,act_size);
    //throw std::runtime_error("TODO");
  }//

  const_iterator begin() const
  {
    return cbegin();
  }

  const_iterator end() const
  {
    return cend();
  }
};

template <typename Type>
class Vector<Type>::ConstIterator
{
    friend Vector<Type>;
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename Vector::value_type;
  using difference_type = typename Vector::difference_type;
  using pointer = typename Vector::const_pointer;
  using reference = typename Vector::const_reference;
protected:
  size_t index;
  const Vector<Type> *v_pointer;//pointer to whole clas cvector
public:
  explicit ConstIterator()
  {}

  ConstIterator(const Vector<Type> *pt, const size_t newindex):v_pointer(pt){
      //v_pointer=pt;
      index=newindex;
  }
  reference operator*() const
  {
    if (index >= v_pointer->act_size){ throw std::out_of_range ("operator*");}
      return v_pointer->vec_array[index];
   // throw std::runtime_error("TODO");
  }

  ConstIterator& operator++()
  {
   if (index >= v_pointer->act_size){ throw std::out_of_range ("++operator");}
    index++;
    return *this;
    //throw std::runtime_error("TODO");
  }

  ConstIterator operator++(int)
  {
 if (index >= v_pointer->act_size){ throw std::out_of_range ("operator++");}
          ConstIterator temp = *this;

      if(index<v_pointer->act_size-1) {
          this->index++;}
          return temp;

   // throw std::runtime_error("TODO");
  }

  ConstIterator& operator--()
  {
   if ((int)index - 1 < (int)v_pointer->act_size){ throw std::out_of_range ("++operator");}
    if(index>0) index--;
      return *this;
   // throw std::runtime_error("TODO");
  }

  ConstIterator operator--(int)
  {
  if ((int)index - 1 < (int)v_pointer->act_size){ throw std::out_of_range ("operator--");}
      ConstIterator temp = *this;

      if(index > 0) {
          this->index--;}
      return temp;

    //throw std::runtime_error("TODO");
  }

  ConstIterator operator+(difference_type d) const
  {
if(index+d>v_pointer->act_size-1){ throw std::out_of_range ("operator+d");}
   ConstIterator temp =*this;
      temp.index+=d;
      if(temp.index>=v_pointer->act_size){ temp.index=v_pointer->act_size-1;}
   return temp;

    //(void)d;
   // throw std::runtime_error("TODO");
  }

  ConstIterator operator-(difference_type d) const
  {

      ConstIterator temp =*this;
      temp.index-=d;
      if((int)temp.index<0){ temp.index=0;}
      return temp;

      //(void)d;
    //throw std::runtime_error("TODO");
  }

  bool operator==(const ConstIterator& other) const
  {
      if(v_pointer==other.v_pointer && index==other.index)return 1;
      else return 0;

   // (void)other;
    //throw std::runtime_error("TODO");
  }

  bool operator!=(const ConstIterator& other) const
  {

      if(v_pointer!=other.v_pointer || index!=other.index)return 1;
      else return 0;
      //(void)other;
    //throw std::runtime_error("TODO");
  }
};

template <typename Type>
class Vector<Type>::Iterator : public Vector<Type>::ConstIterator
{
public:
  using pointer = typename Vector::pointer;
  using reference = typename Vector::reference;

   Iterator(const Vector<Type> *pt,size_t newindex):ConstIterator(pt,newindex)
   {}


  explicit Iterator()
  {}

  Iterator(const ConstIterator& other)
    : ConstIterator(other)
  {}

  Iterator& operator++()
  {
    ConstIterator::operator++();
    return *this;
  }

  Iterator operator++(int)
  {
    auto result = *this;
    ConstIterator::operator++();
    return result;
  }

  Iterator& operator--()
  {
    ConstIterator::operator--();
    return *this;
  }

  Iterator operator--(int)
  {
    auto result = *this;
    ConstIterator::operator--();
    return result;
  }

  Iterator operator+(difference_type d) const
  {
    return ConstIterator::operator+(d);
  }

  Iterator operator-(difference_type d) const
  {
    return ConstIterator::operator-(d);
  }

  reference operator*() const
  {
    // ugly cast, yet reduces code duplication.
    return const_cast<reference>(ConstIterator::operator*());
  }
};

}

#endif // AISDI_LINEAR_VECTOR_H
