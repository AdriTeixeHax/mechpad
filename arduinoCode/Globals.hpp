 #ifndef _GLOBALS__HPP_
#define _GLOBALS__HPP_

#include <Arduino.h>

using uint = unsigned int;

constexpr byte PWM_PINS[7] = { 3, 5, 6, 9, 10, 11, 13 };
constexpr byte ENCODER_PIN_A  = 3;
constexpr byte ENCODER_PIN_B  = 4;
constexpr byte ENCODER_PIN_SW = 5;
constexpr byte STRIP_PIN = 6;

template<typename Type>
struct ParamData
{
    String _name;
    Type   _value;
    Type   _maxValue;
    Type   _minValue;

    explicit ParamData(const String& name, const Type initialValue, const Type maxValue, const Type minValue) :
        _name(name), _value(initialValue), _maxValue(maxValue), _minValue(minValue)
    {
        if (initialValue < minValue) _value = minValue;
        if (initialValue > maxValue) _value = maxValue;
    }

    void increaseValue(const Type increment)
    {
        if (_value + increment <= _maxValue && _value + increment >= _minValue)
            _value += increment;
    }

    void resetValue(void) { _value = 0; }
    void resetAll  (void) { _value = 0; _maxValue = 0; _minValue = 0; }

    bool isMax(void) { return (_value == _maxValue); }
    bool isMin(void) { return (_value == _minValue); }
};

template<typename Type>
class ParamList
{
private:
    ParamData<Type>** _dataArray;
    uint              _numElem;
    uint              _maxElem;

public:
    /* CONSTRUCTOR and DESTRUCTOR */
    ParamList(const uint maxElem) :
        _dataArray(new ParamData<Type>*),
        _numElem(0),
        _maxElem(maxElem)
    { }

    ~ParamList(void)
    {
        for (int i = 0; i < _numElem; i++)
            delete _dataArray[i];

        delete[] _dataArray;
    }

    /* ELEMENT MANAGEMENT */
    void addElem(const ParamData<Type>& elem)
    {
        if (_numElem < _maxElem)
            _dataArray[++_numElem] = new ParamData<Type>(elem._name, elem._value, elem._maxValue, elem._minValue);
    }

    void deleteElem(const uint index)
    {
        if (index <= _numElem)
        {
            delete _dataArray[index];

            for (int i = index; i < _numElem; i++)
                _dataArray[i] = _dataArray[i + 1];

            if (index != _numElem)
                delete _dataArray[_numElem];

            _numElem--;
        }
    }

    void clear(void)
    {
        for (int i = 0; i < _numElem; i++)
            this->deleteElem(i);
    }

    ParamData<Type>* getElem(const uint index) { return _dataArray[index]; }
};

#endif