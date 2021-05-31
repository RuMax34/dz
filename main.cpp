#include <iostream>
#include <math.h>
template <class T>
class DynamicArray{
private:

    T* td;
    int m_size;
    int m_capacity;
public:

    DynamicArray(){
        td = NULL;
        m_size = 0;
        m_capacity = 0;
    }


    void Delete(){
        delete[] this->td;
    }
    DynamicArray(int size){
        m_size = size;
        m_capacity = size;
        td = new T[size];
    }

    DynamicArray(T* items,int count){
        if(items == nullptr){
            td = nullptr;
            m_size = 0;
            m_capacity = 0;
        }
        else{
            m_size = count;
            m_capacity = count;
            td = new T[count];
            for (int i = 0; i < count; ++i)
            {
                td[i] = items[i];
            }
        }
    }

    DynamicArray(const DynamicArray<T> &dynamicArray){
        if(&dynamicArray == nullptr){
            td = nullptr;
            m_size = 0;
            m_capacity = 0;
        }
        else{
            m_size = dynamicArray.m_size;
            m_capacity = m_size;
            td = new T[m_size];
            for (int i = 0; i < dynamicArray.m_size; ++i)
            {
                td[i] = dynamicArray.td[i];
            }
        }
    }


    void Resize(int newSize){
        if(newSize > m_capacity){
            int new_capacity = std::max(2 * m_size, newSize);
            T* new_DATA = new T[new_capacity];
            for (int i = 0; i < m_size; ++i)
            {
                new_DATA[i] = td[i];
            }
            delete[] td;
            td = new_DATA;
            m_capacity = new_capacity;
        }
        m_size = newSize;
    }

    T Get(int index){
        if(index < 0 || index >= m_capacity)
            throw "\nGet Message : Index Out Of Range\n";
        return td[index];
    }

    void Set(int index,T value){
        if(index < 0 || index > m_capacity)
            throw "\nSet Message : Index Out Of Range\n";
        td[index] = value;

    }

    int GetSize() const{
        return m_size;
    }

    void Append(T val){
        Resize(m_size + 1);
        td[m_size - 1] = val;
    }

    void Prepend(T val){
        Resize(m_size + 1);
        for (int i = m_size - 2; i >= 0; --i)
        {
            td[i + 1] = td[i];
        }
        td[0] = val;
    }

    T & operator [] (int i){
        return td[i];
    }

    void Print(){
        if(m_size > 0 && td != nullptr){
            std::cout << std::endl;
            for (int i = 0; i < m_size; ++i) {
                std::cout << td[i] << "\t";
            }
            std::cout << std::endl;
        }
        else{
            std::cout << "\nObject is empty!\n";
        }
    }
};


template <typename T>
std::ostream & operator << (std::ostream & out, DynamicArray<T> a){
    for(int i = 0; i < a.GetSize();++i){
        out << a[i] << " ";
    }
    return out;
}
//==================================================================================================================//
template<typename T>
class Node{
public:
    Node* pNext;
    Node* pPrev;
    T DATA;
    Node(T DATA = T(),Node* pPrev = nullptr,Node* pNext = nullptr){
        this->DATA = DATA;
        this->pPrev = pPrev;
        this->pNext = pNext;
    }
};

template<typename T>
class LinkedList{
public:



    ~LinkedList(){
        clear();
    }


    LinkedList(){
        Size = 0;
        HEAD = nullptr;
    }


    LinkedList(T* items,int count){
        if(items == nullptr){
            Size = 0;
            HEAD = nullptr;
        }
        else{
            Size = 0;
            this->HEAD = nullptr;
            this->TAIL = nullptr;
            for (int i = 0; i < count; ++i) {
                Append(items[i]);
            }
        }
    }


    LinkedList(const LinkedList<T>& list){
        Size = 0;
        this->HEAD = nullptr;
        Node<T>* current = list.HEAD;
        for (int i = 0; i < list.Size; ++i) {
            this->Append(current->DATA);
            current = current->pNext;
        }

    }


    LinkedList<T>* Concat(LinkedList<T>* list){
        this->TAIL->pNext = list->HEAD;
        list->HEAD->pPrev = this->TAIL;
        this->TAIL = list->TAIL;
        Size+=list->Size;

        return this;
    }


    T Get(int index){
        if(index < 0 || index >= Size)
            throw "\nGet Message : Index Out Of Range\n";

        Node<T>* current;

        if(index < Size/2){
            current = HEAD;
            for (int i = 0; i < index; ++i) {
                current = current->pNext;
            }
        }else{
            current = TAIL;
            for (int i = 0; i < Size-index-1; ++i) {
                current = current->pPrev;
            }
        }
        return current->DATA;

    }


    T GetFirst() {
        if(Size == 0)
            throw "\nGetFirst Message : Index Out Of Range\n";
        return Get(0);
    }


    T GetLast(){
        if(Size == 0)
            throw "\nGetLast Message : Index Out Of Range\n";
        return Get(Size - 1);
    }


    LinkedList<T>* GetSubLinkedList(int startIndex,int endIndex){
        if(startIndex < 0 || endIndex < 0 || startIndex >= Size || endIndex >=Size)
            throw "\nGetSubLinkedList Message : Index Out Of Range\n";
        Node<T>* current = this->HEAD;
        for (int i = 0; i < startIndex; ++i) {
            current = current->pNext;
        }
        T* items;
        items = (T*)malloc(sizeof(T*)*(endIndex - startIndex + 1));
        for (int i = 0; i < endIndex - startIndex + 1; ++i) {
            items[i] = current->DATA;
            current = current->pNext;
        }

        LinkedList<T>* result = new LinkedList<T>(items,endIndex - startIndex + 1);
        return result;

    }


    void PrintFromEnd(){
        Node<T>* tmp = this->TAIL;
        if(Size == 1)
            std::cout << TAIL->DATA << " ";
        else{
            while(tmp != nullptr){
                std::cout << tmp->DATA <<" ";
                tmp = tmp->pPrev;
            }
        }
        std::cout << std::endl;
    }


    void PrintFromBegin(){
        if(HEAD != nullptr){
            Node<T>* tmp = this->HEAD;
            if(Size == 1)
                std::cout << HEAD->DATA << " ";
            else{
                while(tmp != nullptr){
                    std::cout << tmp->DATA <<" ";
                    tmp = tmp->pNext;
                }
            }
            std::cout << std::endl;
        }
    }



    void Append(T DATA){
        if(HEAD == nullptr){
            HEAD = new Node<T>(DATA);
            this->TAIL = HEAD;

        }else{
            Node<T>* current = this->HEAD;
            Node<T>* tmp;
            while(current->pNext != nullptr){
                tmp = current;
                current = current->pNext;
                current->pPrev = tmp;
            }

            this->TAIL = new Node<T>(DATA,current,current->pNext);
            current->pNext = TAIL;
        }
        Size++;
    }


    void Prepend(T DATA) {
        if(HEAD == nullptr){
            HEAD = new Node<T>(DATA);
            this->TAIL = HEAD;
        }
        else{
            Node<T>* one_more = new Node<T>(DATA,HEAD->pPrev,HEAD);
            HEAD->pPrev = one_more;
            this->HEAD = one_more;
            Node<T>* current = HEAD;
            while(current->pNext != nullptr){
                current = current->pNext;
            }
            this->TAIL = current;
        }
        Size++;
    }


    void pop_front() {
        if(Size == 1){
            delete [] TAIL;
            Size--;
        }
        else{
            Node<T>* tmp = HEAD;
            HEAD = HEAD->pNext;
            HEAD->pPrev = nullptr;
            delete [] tmp;
            Size--;
        }

    }


    void pop_back(){
        Node<T>* tmp = TAIL;
        TAIL = TAIL->pPrev;
        TAIL->pNext = nullptr;
        delete [] tmp;
        Size--;
    }

    void InsertAt(T DATA, int index) {
        if(index < 0 || index >= Size)
            throw "\nInsertAt Message : Index Out Of Range\n";
        Node<T>* previous;
        Node<T>* new_elem;
        Node<T>* tmp;

        if(index <= Size/2){
            if(index == 0)
                Prepend(DATA);
            previous = HEAD;
            for (int i = 0; i < index - 1; ++i) {
                previous = previous->pNext;
            }
        }
        else{

            previous = TAIL;
            for (int i = 0; i < Size - index; ++i) {
                previous = previous->pPrev;
            }
        }
        tmp = previous->pNext;
        new_elem = new Node<T>(DATA,previous,previous->pNext);
        previous->pNext = new_elem;
        tmp->pPrev = new_elem;

        Size++;
    }

    void removeAt(int index) {
        if(index < 0 || index >= Size)
            throw "removeAt Message : Index Out Of Range\n";
        if(index == 0)
            pop_front();
        else{
            if(index == Size - 1)
                pop_back();
            else{
                Node<T>* previous;
                Node<T>* toDelete;
                if(index <= Size/2){
                    previous = HEAD;
                    for (int i = 0; i < index - 1; ++i) {
                        previous = previous->pNext;
                    }
                }
                else{
                    previous = TAIL;
                    for (int i = 0; i < Size - index; ++i) {
                        previous = previous->pPrev;
                    }
                }

                toDelete = previous->pNext;
                previous->pNext = toDelete->pNext;
                toDelete->pNext->pPrev = previous;

                delete[] toDelete;
            }
            Size--;
        }
    }
    void ChangeValue(int index,T value){
        Node<T>* curr = HEAD;
        for (int i = 0; i < index; ++i) {
            curr = curr->pNext;
        }
        curr->DATA = value;
    }
    void clear(){
        while(Size){
            pop_front();
        }
    }


    T& operator[](const int index) {
        int counter;
        Node<T> *current;
        if (index <= Size / 2) {
            counter = 0;
            current = this->HEAD;
            while (current != nullptr) {
                if (counter == index) {
                    return current->DATA;
                }
                current = current->pNext;
                counter++;
            }
        } else {
            counter = Size - 1;
            current = this->TAIL;
            while (current != nullptr) {
                if (counter == index) {
                    return current->DATA;
                }
                current = current->pPrev;
                counter--;
            }
        }
    }
private:
    int Size;
    Node<T>* HEAD;
    Node<T>* TAIL;
};

//==================================================================================================================//


template<typename T>
class Sequence{
public:
    virtual Sequence<T>* GetSubsequence(int startIndex,int endIndex) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;

    virtual T GetFirst() = 0;
    virtual T GetLast() = 0;
    virtual T Get(int index) = 0;
    virtual int GetLength() = 0;

    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item,int index) = 0;

    virtual void Print() = 0;
};
//==================================================================================================================//
template<typename T>
class ArraySequence : public Sequence<T>{
public:
    ArraySequence(){
        DynamicArray<T>* tmp = new DynamicArray<T>();
        DATA = *tmp;
    }

    ArraySequence(T* item,int count){

        DynamicArray<T>* tmp = new DynamicArray<T>(item,count);
        DATA = *tmp;

    }

    ArraySequence(ArraySequence<T>& array){

        DynamicArray<T>* tmp = new DynamicArray<T>(array.DATA);
        DATA = *tmp;
    }

    ArraySequence(LinkedList<T>& list){
        T* items;
        items = (T*)malloc(sizeof(T)*(list.GetLength()));
        for (int i = 0; i < list.GetLength(); ++i) {
            items[i] = list.Get(i);
        }

        DynamicArray<T>* tmp = new DynamicArray<T>(items,list.GetLength());
        DATA = *tmp;
    }
    int GetLength(){
        return DATA.GetSize();
    }
    T Get(int index){
        return DATA.Get(index);
    }
    T GetFirst(){
        return DATA.Get(0);
    }
    T GetLast(){
        return DATA.Get(DATA.GetSize()-1);
    }

    void Append(T item){
        DATA.Append(item);
    }
    void Prepend(T item){
        DATA.Prepend(item);
    }
    void InsertAt(T item,int index){
        if(index >= DATA.GetSize() || index < 0)
            throw "\nInsertAt Message : Index Out Of Range";
        DATA.Resize(DATA.GetSize()+1);
        for (int i = DATA.GetSize()-2; i >= index ; --i) {
            DATA.Set(i+1,DATA.Get(i));
        }
        DATA.Set(index,item);
    }
    void Print(){
        DATA.Print();
    }

    ArraySequence<T>* GetSubsequence(int startIndex,int endIndex){
        T* items = (T*)malloc(sizeof(T)*(endIndex-startIndex));
        for (int i = startIndex; i < endIndex; ++i) {
            items[i-startIndex] = DATA.Get(i);
        }
        ArraySequence<T>* result = new ArraySequence<T>(items,endIndex-startIndex);
        return result;
    }

    ArraySequence<T>* Concat(Sequence<T>* list){
        if(list->GetLength() != 0){
            T* items = (T*)malloc(sizeof(T)*(DATA.GetSize()+list->GetLength()));
            for (int i = 0; i < DATA.GetSize(); ++i) {
                items[i] = DATA.Get(i);
            }
            for (int i = 0; i < list->GetLength(); ++i) {
                items[i+DATA.GetSize()] = list->Get(i);
            }
            ArraySequence<T>* result = new ArraySequence<T>(items,DATA.GetSize()+list->GetLength());

            return result;
        }else{
            ArraySequence<T>* result = new ArraySequence<T>(*this);
            return result;
        }

    }
private:
    DynamicArray<T> DATA;
};
//==================================================================================================================//
template<typename T>
class LinkedListSequence : public Sequence<T>{
public:
    LinkedListSequence(){
        LinkedList<T>* tmp = new LinkedList<T>();
        DATA = *tmp;
    }
    LinkedListSequence(T* items,int count){
        LinkedList<T>* tmp = new LinkedList<T>(items,count);
        DATA = *tmp;

    }

    LinkedListSequence<T>* Concat(Sequence<T>* list){
        for (int i = 0; i < list->GetLength(); ++i) {
            DATA.Append(list->Get(i));
        }
        T* items;
        items = (T*)malloc(sizeof(T*)*(DATA.GetLength()+list->GetLength()));
        for (int i = 0; i < DATA.GetLength(); ++i) {
            items[i] = DATA.Get(i);
        }

        LinkedListSequence<T>* result = new LinkedListSequence<T>(items,DATA.GetLength());
        return result;
    }

    LinkedListSequence(const LinkedList<T>& list){
        LinkedList<T>* tmp = new LinkedList<T>(list);
        std::cout<< "Constructor by object . . .\n";
        DATA = *tmp;
    }
    LinkedListSequence<T>* GetSubsequence(int startIndex,int endIndex){
        LinkedList<T>* tmp = DATA.GetSubLinkedList(startIndex,endIndex);
        T* items;
        items = (T*)malloc(sizeof(T*)*(endIndex-startIndex));
        for (int i = 0; i < endIndex-startIndex; ++i) {
            items[i] = tmp->Get(i);
        }

        LinkedListSequence<T>* result = new LinkedListSequence<T>(items,endIndex-startIndex);

        return result;
    }
    int GetLength(){
        return DATA.GetLength();
    }
    T GetFirst(){
        DATA.GetFirst();
    }
    T GetLast(){
        DATA.GetLast();
    }
    T Get(int index){
        DATA.Get(index);
    }

    void Append(T item){
        DATA.Append(item);
    }
    void Prepend(T item){
        DATA.Prepend(item);
    }
    void InsertAt(T item,int index){
        DATA.InsertAt(item,index);
    }
    void removeAt(int index){
        DATA.removeAt(index);
    }
    void Print(){
        DATA.PrintFromBegin();
    }
private:
    LinkedList<T> DATA;
};
//==================================================================================================================//
template<typename T>
class DiagonalMatrix{
private:
    DynamicArray<T> data;
    int m;
public:
    DiagonalMatrix(){
        m = 0;
    }
    DiagonalMatrix(T* items,int count){
        m = count;
        data.Resize(count);
        for (int i = 0; i < m; ++i) {
            data.Set(i,items[i]);
        }
    }
    DiagonalMatrix(DiagonalMatrix<T>* example){
        m = example->GetSize();
        data.Resize(m);
        for (int i = 0; i < m; ++i) {
            data.Set(i,example->Get(i));
        }
    }


    int GetSize(){
        return m;
    }
    T Get(int i){
        return data.Get(i);
    }
    void Set(int i,T value){
        data.Set(i,value);
    }

    DiagonalMatrix<T>* Sum(DiagonalMatrix<T>* example){
        if(m == example->GetSize()){
            DiagonalMatrix<T>* result = new DiagonalMatrix<T>(this);
            for (int i = 0; i < m; ++i) {
                result->Set(i,result->Get(i) + example->Get(i));
            }
            return result;
        }else{
            std::cout << "Can't sum ! ! !\n";
            return nullptr;
        }
    }
    void multiplying_a_diagonal_matrix_by_a_scalar(T scalar){
        if(this != nullptr){
            for (int i = 0; i < m; ++i) {
                data.Set(i,data.Get(i) * scalar);
            }
        }
    }
    T calculating_the_norm_of_a_matrix(){
        if(this != nullptr && m != 0){
            T result = data.Get(0);
            for (int i = 0; i < m; ++i) {
                if(data.Get(i) >= result)
                    result = data.Get(i);
            }
            return result;
        }else{
            std::cout << "Error of calculations ! ! !\n";
            return -1;
        }
    }

    void Print(){
        if(this != nullptr){
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < m; ++j) {
                    if(i == j)
                        std::cout << data.Get(i) << "\t";
                    else
                        std::cout << "0" << "\t";
                }
                std::cout << std::endl;
            }
        }else{
            std::cout << "Can't print ! ! !\n";
        }

    }

};
//==================================================================================================================//
template<typename T>
class SquareMatrix{
private:
    DynamicArray<DynamicArray<T>> data;
    int m;//количество строк или столбцов
public:
    int isFailed = 0;
    SquareMatrix();

    ~SquareMatrix(){
        for (int i = 0; i < m; ++i) {
            data[i].Delete();
        }
        std::cout << "\nDestructor call . . ." << this << std::endl;
    }


    SquareMatrix(int m,T** items)
    {
        this->m = m;
        data.Resize(m);
        for (int i = 0; i < m; ++i) {
            data[i].Resize(m);
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                data[i].Set(j,items[i][j]);
            }
        }
        std::cout << "Constructor by array done for " << this << std::endl;
    }


    SquareMatrix(int m){
        this->m = m;
        data.Resize(m);
        for (int i = 0; i < m; ++i) {
            data[i].Resize(m);
        }
        T value;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                if((std::cin >> value)){
                    data[i].Set(j,value);
                }else{
                    std::cout << "Incorrect input";
                    isFailed = 1;
                    return;
                }
            }
        }
        std::cout << "Constructor done for " <<this<<std::endl;
    }

    int getM(){return m;}
    T Get(int i,int j){return data[i].Get(j);}


    void Transposition(){
        DynamicArray<DynamicArray<T>> tmp;
        tmp.Resize(m);
        for (int i = 0; i < m; ++i) {
            tmp[i].Resize(m);
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                tmp[i].Set(j,data[j].Get(i));
            }
        }

        this->data = tmp;
        this->m = m;
    }


    void swapStrings(int first,int second){
        if(first >= m || second >= m){
            isFailed = 1;
            std::cout << "Incorrect indexes for swap strings";
            return;
        }
        else{
            DynamicArray<T> tmp = data[first];
            data[first] = data[second];
            data[second] = tmp;
        }
    }


    void swapColumns(int first,int second){
        if(first >= m || second >= m){
            isFailed = 1;
            std::cout << "Incorrect indexes for swap columns";
            return;
        }else{
            this->Transposition();
            this->swapStrings(first,second);
            this->Transposition();
        }
    }


    void stringsScalarMultiplication(T k,int index){
        if(index >= m){
            isFailed = 1;
            std::cout << "Incorrect index for string scalar multiplication";
            return;
        }else{
            for (int i = 0; i < m; ++i) {
                data[index].Set(i,k*data[index].Get(i));
            }
        }
    }


    void columnsScalarMultiplication(T k,int index){
        if(index >= m){
            isFailed = 1;
            std::cout << "Incorrect index for columns scalar multiplication";
            return;
        }else{
            this->Transposition();
            this->stringsScalarMultiplication(k,index);
            this->Transposition();
        }
    }


    void additionoftwoStrings(int first,int second){
        if(first >= m || second >=m){
            isFailed = 1;
            std::cout << "Incorrect indexes for addition of two strings";
            return;
        }else{
            for (int i = 0; i < m; ++i) {
                data[first].Set(i,data[first].Get(i) + data[second].Get(i));
            }
        }
    }

    void additionoftwoColumns(int first,int second){
        if(first >= m || second >= m){
            isFailed = 1;
            std::cout << "Incorrect indexes for addition of two columns";
            return;
        }else{
            this->Transposition();
            this->additionoftwoStrings(first,second);
            this->Transposition();
        }
    }


    void matrixMultiplicationByNumber(T k){
        for (int i = 0; i < m; ++i) {
            stringsScalarMultiplication(k,i);
        }
    }

    SquareMatrix<T>* Sum(SquareMatrix<T>& first,SquareMatrix<T>& second){
        if(first.getM() != second.getM()){
            isFailed = 1;
            std::cout << "Can't sum";
            return nullptr;
        }else{

            T** tmp = (T**)malloc(sizeof(T*)*m);
            for (int i = 0; i < m; ++i) {
                tmp[i] = (T*)malloc(sizeof(T)*m);
            }

            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < m; ++j) {
                    tmp[i][j] = first.Get(i,j) + second.Get(i,j);
                }
            }
            SquareMatrix<T>* result = new SquareMatrix<T>(m,tmp);
            for (int i = 0; i < m; ++i) {
                delete[] tmp[i];
            }
            delete[] tmp;
            return result;
        }
    }


    SquareMatrix<T>* Multiply(SquareMatrix<T>& first,SquareMatrix<T>& second){
        if(first.getM() != second.getM()){
            isFailed = 1;
            std::cout << "Can't multiply";
            return nullptr;
        }else{
            int M = first.getM();
            int N = second.getM();
            int Q = first.getM();
            T** tmp = (T**)malloc(sizeof(T*)*M);
            for (int i = 0; i < M; ++i) {
                tmp[i] = (T*)malloc(sizeof(T)*N);
            }
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < N; ++j) {
                    tmp[i][j] = 0;
                    for (int k = 0; k < Q; ++k) {
                        tmp[i][j]+=first.Get(i,k)*second.Get(k,j);
                    }
                }
            }
            SquareMatrix<T>* result = new SquareMatrix<T>(M,tmp);
            for (int i = 0; i < M; ++i) {
                delete[] tmp[i];
            }
            delete[] tmp;
            return result;
        }
    }

    T MatrixNorm(){
        T max = 0;
        for (int i = 0; i < m; ++i) {
            max+=data[0].Get(i);
        }
        T tmp;
        for (int i = 0; i < m; ++i) {
            tmp = 0;
            for (int j = 0; j < m; ++j) {
                tmp+=data[i].Get(j);
            }
            if(tmp >= max)
                max = tmp;
        }
        return max;
    }

    void Print(){
        if(this != nullptr && isFailed == 0){
            std::cout<<std::endl;
            for (int i = 0; i < m; ++i) {
                data[i].Print();
                std::cout << std::endl;
            }
            std::cout<<std::endl;
        }else
            std::cout << "\nCan't print, invalid input" << std::endl;
    }
};

int main(){
    int flag;
    std::cout << "Enter 1 to work with square matrices, 2 - to work with diagonal matrices :\n";
    std::cin >> flag;
    if(flag == 1){
        std::cout << "Enter the number of rows and columns for a first square matrix :\n";
        int m,n;
        std::cin >> m;//ввод первой матрицы
        std::cout << "Enter values for the first square matrix:\n";
        SquareMatrix<int> first(m);
        first.Print();
        std::cout << "MartixNorm : " <<first.MatrixNorm() << "\n";

        std::cout << "Enter the number of rows and columns for a first square matrix :\n";
        std::cin >> m;//ввод второй матрицы
        std::cout << "Enter values for the second square matrix:\n";
        SquareMatrix<int> second(m);
        second.Print();
        std::cout << "MartixNorm : " <<second.MatrixNorm() << "\n";

        //демонстрация смены строк и столбцов для первой матрицы
        std::cout << "First matrix :\n";
        first.Print();
        std::cout << "Enter the indices of the rows to be swapped : \n";//вводить,считая индексы не с 0,а с 1
        std::cin >> m >> n;
        first.swapStrings(m,n);
        first.Print();

        std::cout << "Enter the indices of the columns to be swapped : \n";
        std::cin >> m >> n;
        first.swapColumns(m,n);
        first.Print();

        //транспонирование изменённой матрицы
        std::cout << "Transposed modified first matrix :\n";
        first.Transposition();
        first.Print();

        double k;//умножение строки и столбца на число
        std::cout << "Enter the number to multiply by row and column :\n";
        std::cin >> k;
        std::cout << "Enter the indices of the row and column to be multiply on this number : \n";

        std::cin >> m >> n;
        first.stringsScalarMultiplication(k,m);
        first.columnsScalarMultiplication(k,n);
        first.Print();

        //сложение двух строк и двух столбцов
        std::cout << "Enter the indices of the rows to be summed : \n";
        std::cin >> m >> n;
        first.additionoftwoStrings(m,n);
        first.Print();

        std::cout << "Enter the indices of the columns to be summed : \n";
        std::cin >> m >> n;
        first.additionoftwoColumns(m,n);
        first.Print();

        std::cout << "Enter the number to multiply by first matrix :\n";
        std::cin >> k;
        first.matrixMultiplicationByNumber(k);
        first.Print();

        //сложение первой и второй матрицы
        std::cout << "Sum of the first and second matrix :\n";
        SquareMatrix<int>* sum = first.Sum(first,second);
        sum->Print();

        //умножение первой матрицы на вторую
        std::cout << "Multiply of the first and second matrix :\n";
        SquareMatrix<int>* multiply = first.Multiply(first,second);
        multiply->Print();

    }else{
        if(flag == 2){
            int m;
            std::cout << "Enter size of matrix :\n";
            std::cin >> m;
            int* items = new int[m];
            int tmp;
            std::cout << "Enter " << m << " elements for diagonal:\n";
            for (int i = 0; i < m; ++i) {
                std::cin >> tmp;
                items[i] = tmp;
            }
            DiagonalMatrix<int>* test1 = new DiagonalMatrix<int>(items,m);
            test1->Print();

            std::cout << "Enter size of matrix :\n";
            std::cin >> m;
            items = new int[m];
            std::cout << "Enter " << m << " elements for diagonal:\n";
            for (int i = 0; i < m; ++i) {
                std::cin >> tmp;
                items[i] = tmp;
            }
            DiagonalMatrix<int>* test2 = new DiagonalMatrix<int>(items,m);
            test2->Print();

            DiagonalMatrix<int>* sum = test1->Sum(test2);
            std::cout << "Sum of first and second matrix :\n";
            sum->Print();

            int scalar;
            std::cout << "Enter scalar for multiplication on a first matrix :\n";
            std::cin >> scalar;
            std::cout << "Multiplication of the first matrix by a scalar = " << scalar << ":\n";
            test1->multiplying_a_diagonal_matrix_by_a_scalar(scalar);
            test1->Print();

            std::cout << "The norm of the first matrix : " << test1->calculating_the_norm_of_a_matrix() << std::endl;
        }
    }

    return 0;
}