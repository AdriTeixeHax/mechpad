#ifndef _PARAMLIST__HPP_
#define _PARAMLIST__HPP_

template<typename Type>
class ParamList
{
private:
    Type* _dataArray;
    uint  _numElem;
    uint  _maxElem;

public:
    /* CONSTRUCTOR and DESTRUCTOR */
    ParamList(void) : _dataArray(nullptr), _numElem(0), _maxElem(0) { }
    ParamList(const uint maxElem) : _dataArray(new Type), _numElem(0), _maxElem(maxElem) { }
    ~ParamList(void)
    {
        for (int i = 0; i < _numElem; i++)
            delete _dataArray[i];

        delete[] _dataArray;
    }

    /* ELEMENT MANAGEMENT */
    void addElem(const Type& elem) { if (_numElem < _maxElem) _dataArray[++_numElem] = elem; }

    void deleteElem(const uint index)
    {
        if (index <= _numElem)
        {
            delete _dataArray[index];
            for (int i = index; i < _numElem; i++) _dataArray[i] = _dataArray[i + 1];
            if (index != _numElem) delete _dataArray[_numElem];
            _numElem--;
        }
    }

    void setMaxElem(const uint maxElem) { _maxElem = maxElem; }

    void increaseValue(const String& st, const Type increment)
    {
        for (int i = 0; i < _numElem; i++)
        {
            if (st == _dataArray[i]->_name) _dataArray[i]._value += increment;
            break;
        }
    }

    void clear(void) { for (int i = 0; i < _numElem; i++) this->deleteElem(i); }

    Type getElem(const uint index) { return _dataArray[index]; }
    
    Type getElemValue(const String& st)
    {
        for (int i = 0; i < _numElem; i++)
        {
            if (st == _dataArray[i]->_name)
                return _dataArray[i]._value;
        }
        return nullptr;
    }

    Type  operator[](const uint i)       { return _dataArray[i]; }
    Type& operator[](const uint i) const { return _dataArray[i]; }
};

#endif