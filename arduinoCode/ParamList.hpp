#ifndef _PARAMLIST__HPP_
#define _PARAMLIST__HPP_

template<typename Type>
class ParamList
{
private:
    Type*    _dataArray;
    uint8_t  _numElem;
    uint8_t  _maxElem;

public:
    /* CONSTRUCTOR and DESTRUCTOR */
    ParamList(void) : _dataArray(nullptr), _numElem(0), _maxElem(0) { }
    ParamList(const uint8_t maxElem) : _dataArray(new Type), _numElem(0), _maxElem(maxElem) { }
    ~ParamList(void) { for (int i = 0; i < _numElem; i++) delete _dataArray[i]; delete[] _dataArray; }

    /* ELEMENT MANAGEMENT */
    void addElem(const Type& elem)
    { 
        if ((_numElem + 1) <= _maxElem)
        {
            _dataArray[_numElem] = elem;
            _numElem++;
        }
    }
    void deleteElem(const uint8_t index)
    {
        if (index <= _numElem)
        {
            delete _dataArray[index];
            for (int i = index; i < _numElem; i++) _dataArray[i] = _dataArray[i + 1];
            if (index != _numElem) delete _dataArray[_numElem];
            _numElem--;
        }
    }
    void clear(void) { for (int i = 0; i < _numElem; i++) this->deleteElem(i); _numElem = 0; }

    /* GETTERS */
    uint8_t size      (void)            const { return _numElem; }
    Type    operator[](const uint8_t i)       { return _dataArray[i]; }
    Type&   operator[](const uint8_t i) const { return _dataArray[i]; }
};

#endif