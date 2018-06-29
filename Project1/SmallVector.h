/**********************
*Name:Alperen Kantarci*
*Number: 150140140    *
*Date: 30/03/2016     *
***********************/
#include <cstring>
#define BUFFERSIZE 32  //Static Buffer size. Changing this value also will change static buffer size.
                        //Adding this constant makes program easy to modify.
class SmallVector {
    int numberOfElements=0;
    int numberOfDynamic=0;
    int staticBuffer[BUFFERSIZE];
    int* dynamicBuffer=NULL;
public:
    SmallVector(const int* = NULL,const int=BUFFERSIZE);        //DEFAULT INT SIZE
    SmallVector( const SmallVector &);               //COPY CONSTRUCTOR
    SmallVector operator+(const SmallVector&)const;  // + operator overload
    SmallVector operator*(const int)const;           // * operator overload
    int& operator[] (const int );                       // [] operator overload allows to make changes
    const int  operator[] (const int) const;          // [] does not make changes
    const SmallVector& operator=(const SmallVector&);// = operator overload
    int getSize() const;
    int getCapacity() const;
    SmallVector reverse();
    void push_back(const int);
    void push_back(const int*, int);
    int pop_back();

    ~SmallVector();
};

SmallVector::~SmallVector() {   //Destructor
    if(numberOfDynamic)
        delete [] dynamicBuffer;
}

SmallVector SmallVector::reverse() {
    int* array = new int[getSize()];
    if(dynamicBuffer != NULL) {
        int j,i;
        for(i = numberOfDynamic-1, j=0 ; i >= 0 ; i--,j++) {
            array[j]=dynamicBuffer[i];
        }

        for(i=BUFFERSIZE-1 ; i >=0 ; i--, j++)
            array[j] = staticBuffer[i];

    } else {
        int j,i;
        for(i=getSize()-1,j =0 ; i >=0 ; i--, j++)
            array[j] = staticBuffer[i];

    }

    return SmallVector(array,getSize());

}

int & SmallVector::operator[](int key) {            //Returns pointer so it can be changed
    if(key < 0) {           //if its negative
        key *= -1;
        if(key <= numberOfDynamic) {
            return dynamicBuffer[numberOfDynamic-key];
        } else {
            key -= numberOfDynamic;
            if(key > numberOfElements)
                return staticBuffer[0];
            else
                return staticBuffer[numberOfElements-key];
        }

    } else {               //if its positive
        if(key >= getSize() && getSize() <= BUFFERSIZE)
            return staticBuffer[getSize()-1];
        else if(key >= getSize() && getSize() > BUFFERSIZE)
            return dynamicBuffer[numberOfDynamic-1];
        else if(key <= BUFFERSIZE && key < numberOfElements) {
            return staticBuffer[key];
        }
        else{
            key -= BUFFERSIZE;
            if(key>numberOfDynamic-1)
                return dynamicBuffer[numberOfDynamic-1];
            else
                return dynamicBuffer[key];
        }
    }

}

const int  SmallVector::operator[](int key)const {          //Only print operations
   if(key < 0) {           //if its negative
        key *= -1;
        if(key <= numberOfDynamic) {
            return dynamicBuffer[numberOfDynamic-key];
        } else {
            key -= numberOfDynamic;
            if(key > numberOfElements)
                return staticBuffer[0];
            else
                return staticBuffer[numberOfElements-key];
        }

    } else {               //if its positive
        if(key >= getSize() && getSize() <= BUFFERSIZE)
            return staticBuffer[getSize()-1];
        else if(key >= getSize() && getSize() > BUFFERSIZE)
            return dynamicBuffer[numberOfDynamic-1];
        else if(key <= BUFFERSIZE && key < numberOfElements) {
            return staticBuffer[key];
        }
        else{
            key -= BUFFERSIZE;
            if(key>numberOfDynamic-1)
                return dynamicBuffer[numberOfDynamic-1];
            else
                return dynamicBuffer[key];
        }
    }

}

const SmallVector& SmallVector::operator=(const SmallVector &other) {
    if( getSize() != other.getSize() ) {
        if(getSize() > BUFFERSIZE)
            delete [] dynamicBuffer;

        if(other.getSize() <= BUFFERSIZE) {
            memcpy(staticBuffer,other.staticBuffer,other.getSize()*sizeof(int));
            numberOfDynamic=other.numberOfDynamic;
            numberOfElements=other.numberOfElements;
        } else {
            memcpy(staticBuffer,other.staticBuffer,BUFFERSIZE*sizeof(int));
            dynamicBuffer = new int[other.numberOfDynamic];
            memcpy(dynamicBuffer,other.dynamicBuffer,other.numberOfDynamic*sizeof(int));
            numberOfDynamic=other.numberOfDynamic;
            numberOfElements=other.numberOfElements;
        }
    } else {
        if(other.getSize() <= BUFFERSIZE) {
            memcpy(staticBuffer,other.staticBuffer,other.getSize()*sizeof(int));
        } else {
            memcpy(staticBuffer,other.staticBuffer,(other.getSize()-other.numberOfDynamic)*sizeof(int));
            memcpy(dynamicBuffer,other.dynamicBuffer,other.numberOfDynamic*sizeof(int));
        }
    }
    return *this;
}

SmallVector SmallVector::operator+(const SmallVector& other)const {
    int newSize = getSize() + other.getSize();
     int* array = new int[newSize];
    int tmp=0;
    if( getSize() <= BUFFERSIZE) {
        for(int i=0 ; i < getSize() ; i++ ) {
            array[i] = staticBuffer[i];
            tmp++;
        }
    } else {
        for(int i = 0 ; i < BUFFERSIZE ; i++) {
            array[i] = staticBuffer[i];
            tmp++;
        }
        for(int i = 0 ; i < numberOfDynamic ; i++) {
            array[i+BUFFERSIZE] = dynamicBuffer[i];
            tmp++;
        }
    }

    if(other.getSize() < BUFFERSIZE) {
        for(int i=0 ; i < other.getSize() ; i++ )
            array[i+tmp] = other.staticBuffer[i];

    } else {
        for(int i = 0 ; i < BUFFERSIZE ; i++)
            array[i+tmp] = other.staticBuffer[i];

        for(int i = 0 ; i < other.numberOfDynamic ; i++)
            array[i+tmp+BUFFERSIZE-1] = other.dynamicBuffer[i];

    }

    return  SmallVector(array,newSize);

}

SmallVector SmallVector::operator*(const int key)const {

    int newSize = getSize() * key ;
    int* array = new int[newSize];
    if(getSize() <= BUFFERSIZE) {
        for(int i = 0 ; i< getSize()*key ; i++) {
            array[i] = staticBuffer[i % getSize()];
        }

    } else {
        for(int i = 0 ; i < getSize() ; i++ ) {
            (i<=BUFFERSIZE) ? array[i] = staticBuffer[i] : array[i] = dynamicBuffer[i-32];
        }
        for(int i = getSize() ; i < getSize()*key ; i++) {
            array[i] = array[i%getSize()];
        }

    }

    return SmallVector(array,newSize);
}

SmallVector::SmallVector(const int* array,const int bufSize) { //ARRAY WITH SIZE CONSTRUCTOR
    if(array == NULL) {
        return;
    }
    if (bufSize > BUFFERSIZE) {
        numberOfDynamic=bufSize - BUFFERSIZE;
        memcpy(staticBuffer,array,BUFFERSIZE*sizeof(int));
        dynamicBuffer = new int [numberOfDynamic];
        const int *tmp= (array+BUFFERSIZE);
        memcpy(dynamicBuffer,tmp,numberOfDynamic*sizeof(int));
        numberOfElements = bufSize - numberOfDynamic;
    } else {

        memcpy(staticBuffer,array,bufSize*sizeof(int));
        numberOfElements = bufSize;
        numberOfDynamic = 0;
    }
}

SmallVector::SmallVector(const SmallVector &other ) {  //COPY COSNSTRUCTOR
    numberOfDynamic= other.numberOfDynamic;
    numberOfElements = other.numberOfElements;
    if(other.getSize() <= BUFFERSIZE) {
        memcpy(staticBuffer,other.staticBuffer,other.getSize()*sizeof(int));
    } else {
        delete [] dynamicBuffer;
        dynamicBuffer = new int[numberOfDynamic];
        memcpy(staticBuffer,other.staticBuffer,(BUFFERSIZE-getSize())*sizeof(int));
        memcpy(dynamicBuffer,other.dynamicBuffer,numberOfDynamic*sizeof(int));
    }
}

int SmallVector::getSize() const {
    return numberOfElements+numberOfDynamic;
}

int SmallVector::getCapacity() const {
    if(numberOfElements <= BUFFERSIZE)
        return BUFFERSIZE;
    else
        return numberOfElements+numberOfDynamic;
}

void SmallVector::push_back(const int key) {
    if(getSize()+1 > BUFFERSIZE ) {
        int* array = new int[numberOfDynamic+1];
        memcpy(array,dynamicBuffer,numberOfDynamic*sizeof(int));
        array[numberOfDynamic]=key;
        delete [] dynamicBuffer;
        dynamicBuffer = new int [numberOfDynamic+1];
        numberOfDynamic++;
        memcpy(dynamicBuffer,array,numberOfDynamic*sizeof(int));
        delete [] array;
    } else {
        staticBuffer[getSize()] = key ;
        numberOfElements++;
    }
}

void SmallVector::push_back(const int* array,int size) {
    if(getSize()+size <= BUFFERSIZE) {

        int* tmp = (staticBuffer+getSize());

        for(int i = 0 ; i < size ; i++)
            tmp[i] = array[i];

        numberOfElements += size;
    } else if (getSize()+size > BUFFERSIZE && getSize()<=BUFFERSIZE) {

        int* tmp = (staticBuffer+getSize());
        for(int i=0 ; i < BUFFERSIZE-getSize() ; i++)
            tmp[i] = array[i];

        size -= BUFFERSIZE-getSize();
        dynamicBuffer= new int[size];
        for(int i = 0 ; i < size ; i++ )
            dynamicBuffer[i] = array[BUFFERSIZE-getSize()+i];
        numberOfElements = BUFFERSIZE;
        numberOfDynamic += size;

    } else {
        if(dynamicBuffer==NULL) {
            dynamicBuffer = new int[size];
            for(int i = 0 ; i < size ; i ++)
                dynamicBuffer[i] = array[i];
            numberOfDynamic+=size;
        } else {
            int* tmp = new int[numberOfDynamic+size];
            memcpy(tmp,dynamicBuffer,(numberOfDynamic)*sizeof(int));
            for(int i=0 ; i < size ; i++)
                tmp[numberOfDynamic+i]=array[i];
            delete [] dynamicBuffer;
            dynamicBuffer = tmp;
            numberOfDynamic+=size;
        }
    }
}


int SmallVector::pop_back() {

    if(dynamicBuffer != NULL ) {
        int * tmp=new int[numberOfDynamic-1];
        int returnValue = dynamicBuffer[numberOfDynamic-1];
        numberOfDynamic--;
        memcpy(tmp,dynamicBuffer,(numberOfDynamic)*sizeof(int));
        delete [] dynamicBuffer;
        dynamicBuffer = tmp;
        return returnValue;
    } else {
        numberOfElements--;
        return staticBuffer[getSize()];
    }
}
