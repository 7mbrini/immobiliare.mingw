/******************************************************************************
	author:	Francesco Settembrini
	last update: 23/6/2021, 28/11/2021
	e-mail:	mailto:francesco.settembrini@poliba.it
******************************************************************************/

#ifndef sortingH
#define sortingH

#include <vector>
#include <string>
#include <algorithm>


namespace sort
{

class T;

/*!****************************************************************************
* @brief	Reorders a vector of T
* @note		T *pT Pointer to a vector of T types
* @note		Uses the Bubble Sort algorithm
******************************************************************************/
template <class T>
void Sort(T *pT, int nSize)
{
	assert(pT);

	for(int i=0; i<nSize; i++)
	{
		for(int j = i+1; j<nSize; j++)
		{
            if( pT[j] < pT[i] )
			{
                std::swap(pT[i], pT[j]);
			}
		}
	}
}


typedef std::vector<int> TVecIntegers;
typedef std::vector<std::string> TVecStrings;

/*!****************************************************************************
* @brief	Sorts a vector of T values
* @note		std::vector<T> Reference to a vector of T types
* @note		Uses the Bubble Sort algorithm
******************************************************************************/
template <class T>
void Sort(std::vector<T> &Vec)
{
	for(unsigned i=0; i<Vec.size(); i++)
	{
		for(unsigned j = i+1; j<Vec.size(); j++)
		{
			if( Vec[i] > Vec[j] )
			{
				std::swap(Vec[i], Vec[j]);
			}
		}
	}
}

class TStringSort
{
public:
	TStringSort()
    {
    	m_pPtr = NULL;
		m_strName = "";
    }

	TStringSort(std::string strName, void* pPtr)
    {
		m_strName = strName;
        m_pPtr = pPtr;
    }

    bool operator < (TStringSort& Other)
    {
		return bool(m_strName < Other.m_strName);
    }

public:
    void* m_pPtr;
    std::string m_strName;
};

class TIntegerSort
{
public:
	TIntegerSort()
    {
    	m_nVal = 0;
        m_pPtr = NULL;
    }

	TIntegerSort(int nVal, void* pPtr)
    {
		m_nVal = nVal;
        m_pPtr = pPtr;
    }

	bool operator < (TIntegerSort& Other)
    {
    	return bool(m_nVal < Other.m_nVal);
    }

public:
	int m_nVal;
    void* m_pPtr;
};

};	// namespace sort

//---------------------------------------------------------------------------
#endif
