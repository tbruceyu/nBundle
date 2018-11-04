#include "Bundle.h"

#include <sstream>
#include <cstdlib>
class BundleValue {
public:

    /*
     bundle_bool = 1,		// 值：bool
     bundle_int,			// 值：int
     bundle_float,			// 值：float
     bundle_double,		// 值：double
     bundle_number,		// 值：数字类型,存储为Double
     bundle_string,		// 值：std::string
     bundle_bundle,		// 值：Bundle
     bundle_int_array,		// 值：std::vetor<int>
     bundle_float_array,	// 值：std::vetor<float>
     bundle_float_number_array,     // 值：std::vetor<float>
     bundle_double_number_array,    // 值：std::vetor<double>
     bundle_string_array,	// 值：std::vetor<std::string>
     bundle_bundle_array,	// 值：std::vetor<Bundle>
     */

    // BundleValue的创建函数
    static BundleValue *CreatBool(bool bValue);

    static BundleValue *CreatInt(int64_t iValue);

    static BundleValue *Creatulong(unsigned long iValue);

    static BundleValue *CreatFloat(float fValue);

    static BundleValue *CreatDouble(double dValue);

    static BundleValue *CreatString(const std::string &strValue);

    static BundleValue *CreatBundle(const Bundle &bundValue);

    static BundleValue *CreatFloatArray(const std::vector<float> &arrValue);

    static BundleValue *CreatDoubleArray(const std::vector<double> &arrValue);

    static BundleValue *CreatStringArray(const std::vector <std::string> &arrValue);

    static BundleValue *CreatBundleArray(const std::vector <Bundle> &arrValue);

    // 拷贝一份BundleValue
    static BundleValue *Clone(BundleValue *pValue);

    // 释放Bundle
    static void Release(BundleValue *pObj);

    // 获取对应的值
    bool GetBool() const;

    int64_t GetInt() const;

    unsigned long GetULong() const;

    float GetFloat() const;

    double GetDouble() const;

    std::string *GetString() const;

    Bundle *GetBundle() const;

    std::vector<float> *GetFloatArray() const;

    std::vector<double> *GetDoubleArray() const;

    std::vector <std::string> *GetStringArray() const;

    std::vector <Bundle> *GetBundleArray() const;

public:

    int m_eType;
protected:

    void *m_pValue;

protected:

    BundleValue();

    // 析构函数
    virtual ~BundleValue();

    template<class Type>
    static BundleValue *CreatValueTempl(const Type &valueTmp);

    template<class Type>
    static void ReleaseValueTempl(Type *pValue);
};

template<class Type>
BundleValue *BundleValue::CreatValueTempl(const Type &valueTmp) {
    BundleValue *pObj = (BundleValue *) malloc(sizeof(BundleValue));

    if (!pObj)
        return NULL;

    ::new(pObj) BundleValue;

    void *pBuf = malloc(sizeof(Type));
    Type *pValue = new(pBuf) Type();

    if (!pValue) {
        free(pObj);
        pObj = NULL;
        return NULL;
    }

    *pValue = valueTmp;
    pObj->m_pValue = pValue;
    return pObj;
}

template<class Type>
void BundleValue::ReleaseValueTempl(Type *pValue) {
    if (!pValue)
        return;

    pValue->~Type();
    free(pValue);
    pValue = NULL;
}

// BundleValue的创建函数
BundleValue *BundleValue::CreatBool(bool bValue) {
    BundleValue *pObj = CreatValueTempl(bValue);

    if (!pObj)
        return NULL;

    pObj->m_eType = bundle_bool;
    return pObj;
}

BundleValue *BundleValue::CreatInt(int64_t iValue) {
    BundleValue *pObj = CreatValueTempl(iValue);

    if (!pObj)
        return NULL;

    pObj->m_eType = bundle_integer;
    return pObj;
}

BundleValue *BundleValue::CreatFloat(float fValue) {
    return CreatDouble(double(fValue));
}

BundleValue *BundleValue::CreatDouble(double dValue) {
    BundleValue *pObj = CreatValueTempl(dValue);

    if (!pObj)
        return NULL;

    pObj->m_eType = bundle_float;
    return pObj;
}

BundleValue *BundleValue::CreatString(const std::string &strValue) {
    BundleValue *pObj = CreatValueTempl(strValue);

    if (!pObj)
        return NULL;

    pObj->m_eType = bundle_string;
    return pObj;
}

BundleValue *BundleValue::CreatBundle(const Bundle &bundValue) {
    BundleValue *pObj = CreatValueTempl(bundValue);

    if (!pObj)
        return NULL;

    pObj->m_eType = bundle_bundle;
    return pObj;
}

BundleValue *BundleValue::CreatFloatArray(const std::vector<float> &arrValue) {
    BundleValue *pObj = CreatValueTempl(arrValue);

    if (!pObj)
        return NULL;

    pObj->m_eType = bundle_float_number_array;
    return pObj;
}

BundleValue *BundleValue::CreatDoubleArray(const std::vector<double> &arrValue) {
    BundleValue *pObj = CreatValueTempl(arrValue);

    if (!pObj)
        return NULL;

    pObj->m_eType = bundle_double_number_array;
    return pObj;
}

BundleValue *BundleValue::CreatStringArray(const std::vector <std::string> &arrValue) {
    BundleValue *pObj = CreatValueTempl(arrValue);

    if (!pObj)
        return NULL;

    pObj->m_eType = bundle_string_array;
    return pObj;
}

BundleValue *BundleValue::CreatBundleArray(const std::vector <Bundle> &arrValue) {
    BundleValue *pObj = CreatValueTempl(arrValue);

    if (!pObj)
        return NULL;

    pObj->m_eType = bundle_bundle_array;
    return pObj;
}

// 拷贝一份BundleValue
BundleValue *BundleValue::Clone(BundleValue *pValue) {
    if (pValue == NULL) {
        return NULL;
    }

    switch (pValue->m_eType) {
        case bundle_bool: {
            return BundleValue::CreatBool(pValue->GetBool());
        }
            break;

        case bundle_float: {
            return BundleValue::CreatDouble(pValue->GetDouble());
        }
            break;

        case bundle_string: {
            std::string *pValueTemp = pValue->GetString();
            if (pValueTemp) {
                return BundleValue::CreatString(*pValueTemp);
            }
        }
            break;

        case bundle_bundle: {
            Bundle *pValueTemp = pValue->GetBundle();
            if (pValueTemp) {
                return BundleValue::CreatBundle(*pValueTemp);
            }
        }
            break;

        case bundle_float_number_array: {
            std::vector<float> *pValueTemp = pValue->GetFloatArray();
            if (pValueTemp) {
                return BundleValue::CreatFloatArray(*pValueTemp);
            }
        }
            break;

        case bundle_double_number_array: {
            std::vector<double> *pValueTemp = pValue->GetDoubleArray();
            if (pValueTemp) {
                return BundleValue::CreatDoubleArray(*pValueTemp);
            }
        }
            break;

        case bundle_string_array: {
            std::vector <std::string> *pValueTemp = pValue->GetStringArray();
            if (pValueTemp) {
                return BundleValue::CreatStringArray(*pValueTemp);
            }
        }
            break;

        case bundle_bundle_array: {
            std::vector <Bundle> *pValueTemp = pValue->GetBundleArray();
            if (pValueTemp) {
                return BundleValue::CreatBundleArray(*pValueTemp);
            }
        }
            break;

        default:
            break;
    }

    return NULL;
}

// 释放Bundle
void BundleValue::Release(BundleValue *pObj) {
    if (!pObj)
        return;

    pObj->~BundleValue();
    free(pObj);
    pObj = NULL;
}

// 获取对应的值
bool BundleValue::GetBool() const {
    return *((bool *) m_pValue);
}

int64_t BundleValue::GetInt() const {
    if (!m_pValue)
        return 0;
    else
        return *((int64_t *) m_pValue);
}

unsigned long BundleValue::GetULong() const {
    if (!m_pValue)
        return 0;
    else
        return *((unsigned long *) m_pValue);
}

float BundleValue::GetFloat() const {
    return (float) GetDouble();
}

double BundleValue::GetDouble() const {
    if (!m_pValue)
        return 0.0;
    else
        return *((double *) m_pValue);
}

std::string *BundleValue::GetString() const {
    return (std::string *) m_pValue;
}

Bundle *BundleValue::GetBundle() const {
    return (Bundle *) m_pValue;
}

std::vector<float> *BundleValue::GetFloatArray() const {
    return (std::vector<float> *) m_pValue;
}

std::vector<double> *BundleValue::GetDoubleArray() const {
    return (std::vector<double> *) m_pValue;
}

std::vector <std::string> *BundleValue::GetStringArray() const {
    return (std::vector <std::string> *) m_pValue;
}

std::vector <Bundle> *BundleValue::GetBundleArray() const {
    return (std::vector <Bundle> *) m_pValue;
}

BundleValue::~BundleValue() {
    if (!m_pValue)
        return;

    switch (m_eType) {
        case bundle_bool: {
            bool *pValue = (bool *) m_pValue;
            BundleValue::ReleaseValueTempl(pValue);
            break;
        }
        case bundle_float: {
            double *pValue = (double *) m_pValue;
            BundleValue::ReleaseValueTempl(pValue);
            break;
        }
        case bundle_integer: {
            int64_t *pValue = (int64_t *) m_pValue;
            BundleValue::ReleaseValueTempl(pValue);
            break;
        }

        case bundle_string: {
            std::string *pValue = (std::string *) m_pValue;
            BundleValue::ReleaseValueTempl(pValue);
            break;
        }

        case bundle_bundle: {
            Bundle *pValue = (Bundle *) m_pValue;
            BundleValue::ReleaseValueTempl(pValue);
            break;
        }

        case bundle_float_number_array: {
            std::vector<float> *pValue = (std::vector<float> *) m_pValue;
            BundleValue::ReleaseValueTempl(pValue);
            break;
        }

        case bundle_double_number_array: {
            std::vector<double> *pValue = (std::vector<double> *) m_pValue;
            BundleValue::ReleaseValueTempl(pValue);
            break;
        }

        case bundle_string_array: {
            std::vector <std::string> *pValue = (std::vector <std::string> *) m_pValue;
            BundleValue::ReleaseValueTempl(pValue);
            break;
        }

        case bundle_bundle_array: {
            std::vector <Bundle> *pValue = (std::vector <Bundle> *) m_pValue;
            BundleValue::ReleaseValueTempl(pValue);
            break;
        }

        default:
            break;
    }

    m_pValue = NULL;
}

BundleValue::BundleValue() {
    m_eType = 0;
    m_pValue = NULL;
}

Bundle::Bundle() {
}

Bundle::~Bundle() {
    clear();
}

Bundle::Bundle(Bundle &r) {
    if (this == &r)
        return;

    clear();

    std::map<std::string, void *>::iterator it;
    for (it = r.m_mapBundle.begin(); it != r.m_mapBundle.end();) {
        if (it->second) {
            BundleValue *pBundleValue = (BundleValue *) it->second;
            m_mapBundle[it->first] = BundleValue::Clone(pBundleValue);
        }

        it++;
    }
}

Bundle::Bundle(const Bundle &r) {
    if (this == &r)
        return;

    clear();

    for (auto &kv : r.m_mapBundle) {
        if (kv.second) {
            BundleValue *pBundleValue = (BundleValue *) kv.second;
            m_mapBundle[kv.first] = BundleValue::Clone(pBundleValue);
        }
    }
}

Bundle &Bundle::operator=(const Bundle &r) {
    if (this == &r)
        return *this;

    clear();

    for (auto &kv : r.m_mapBundle) {
        if (kv.second) {
            BundleValue *pBundleValue = (BundleValue *) kv.second;
            m_mapBundle[kv.first] = BundleValue::Clone(pBundleValue);
        }
    }

    return *this;
}

/**
 *	清空所有的内容
 *	@notes N/A
 */
void Bundle::clear() {
    std::map<std::string, void *>::iterator it;
    for (it = m_mapBundle.begin(); it != m_mapBundle.end();) {
        if (it->second) {
            BundleValue *pBundleValue = (BundleValue *) it->second;
            BundleValue::Release(pBundleValue);
        }

        it++;
    }

    m_mapBundle.clear();
}

/**
 *	移除指定Key
 *	@notes N/A
 */
void Bundle::remove(const std::string &strKey) {
    BundleValue *pValue = (BundleValue *) m_mapBundle[strKey];

    if (pValue) {
        BundleValue::Release(pValue);
    }

    m_mapBundle.erase(strKey);
}

/**
 *	检测指定的Key是否存在
 *	@param      strKey	[in]      指定Key
 *	@return     存在指定key返回true，否则返回false
 *	@notes  N/A
 */
bool Bundle::containsKey(const std::string &strKey) const {
    return m_mapBundle.find(strKey) != m_mapBundle.end();
}

/**
 *	获取所有Key
 *	@param arrKey	[out]	所有的Key集合
 *	@notes  N/A
 */
void Bundle::getKeys(std::vector <std::string> &arrKey) const {
    for (auto &kv : m_mapBundle) {
        arrKey.push_back(kv.first);
    }
}

/**
 *	根据指定Key获取值的类型
 *	@param strKey       [in]            指定Key
 *	@return 值的类型，如bundle_bool、bundle_bundle_array等
 *	@notes  N/A
 */
int Bundle::getType(std::string &strKey) const {
    std::map<std::string, void *>::const_iterator it = m_mapBundle.find(strKey);

    if (it != m_mapBundle.end()) {
        BundleValue *pValue = (BundleValue *) it->second;
        return pValue->m_eType;
    } else
        return bundle_error;
}

/**
 *	根据指定Key获取bool类型的值
 *	@param  strKey      [in]	指定Key
 *	@return bool类型的值
 *	@notes  N/A
 */
bool Bundle::getBool(const std::string &strKey) const {
    std::map<std::string, void *>::const_iterator it = m_mapBundle.find(strKey);

    if (it != m_mapBundle.end()) {
        BundleValue *pValue = (BundleValue *) it->second;
        return pValue->GetBool();
    } else
        return false;
}


bool Bundle::getBool(const std::string &strKey, bool &value) const {
    std::map<std::string, void *>::const_iterator it = m_mapBundle.find(strKey);

    if (it != m_mapBundle.end()) {
        BundleValue *pValue = (BundleValue *) it->second;
        value = pValue->GetBool();
        return true;
    } else
        return false;
}

/**
 *	根据指定Key获取int类型的值
 *	@param  strKey      [in]	指定Key
 *	@return int类型的值
 *	@notes  N/A
 */
int64_t Bundle::getInt(const std::string &strKey) const {
    std::map<std::string, void *>::const_iterator it = m_mapBundle.find(strKey);

    if (it != m_mapBundle.end()) {
        BundleValue *pValue = (BundleValue *) it->second;
        return pValue->GetInt();
    } else
        return 0;

}

/**
 *	根据指定Key获取int类型的值
 *	@param  strKey      [in]	指定Key
 *	@param  value       [out]   值
 *	@return 找到key返回true，否则返回false
 *	@notes  N/A
 */
bool Bundle::getInt(const std::string &strKey, int64_t &value) const {
    std::map<std::string, void *>::const_iterator it = m_mapBundle.find(strKey);

    if (it != m_mapBundle.end()) {
        BundleValue *pValue = (BundleValue *) it->second;
        value = pValue->GetInt();
        return true;
    } else {
        return false;
    }
}

/**
 *	根据指定Key获取float类型的值
 *	@param  strKey      [in]	指定Key
 *	@return float类型的值
 *	@notes  N/A
 */
float Bundle::getFloat(const std::string &strKey) const {
    std::map<std::string, void *>::const_iterator it = m_mapBundle.find(strKey);

    if (it != m_mapBundle.end()) {
        BundleValue *pValue = (BundleValue *) it->second;
        return pValue->GetFloat();
    } else
        return 0.0;

}

/**
 *	根据指定Key获取double类型的值
 *	@param  strKey      [in]	指定Key
 *	@return double类型的值
 *	@notes  N/A
 */
double Bundle::getDouble(const std::string &strKey) const {
    std::map<std::string, void *>::const_iterator it = m_mapBundle.find(strKey);

    if (it != m_mapBundle.end()) {
        BundleValue *pValue = (BundleValue *) it->second;
        return pValue->GetDouble();
    } else
        return 0.0;

}

/**
 *	根据指定Key获取std::string类型的值
 *	@param  strKey      [in]	指定Key
 *	@return string类型的指针
 *	@notes  N/A
 */
std::string *Bundle::getString(const std::string &strKey) const {
    std::map<std::string, void *>::const_iterator it = m_mapBundle.find(strKey);

    if (it != m_mapBundle.end()) {
        BundleValue *pValue = (BundleValue *) it->second;
        return pValue->GetString();
    } else
        return NULL;
}

/**
 *	根据指定Key获取Bundle类型的值
 *	@param  strKey      [in]	指定Key
 *	@return Bundle类型的指针
 *	@notes  N/A
 */
Bundle *Bundle::getBundle(const std::string &strKey) const {
    std::map<std::string, void *>::const_iterator it = m_mapBundle.find(strKey);

    if (it != m_mapBundle.end()) {
        BundleValue *pValue = (BundleValue *) it->second;
        return pValue->GetBundle();
    } else
        return NULL;
}

/**
 *	根据指定Key获取double[]类型的值
 *	@param  strKey      [in]	指定Key
 *	@return double数组的指针
 *	@notes  N/A
 */
std::vector<float> *Bundle::getFloatArray(const std::string &strKey) const {
    std::map<std::string, void *>::const_iterator it = m_mapBundle.find(strKey);

    if (it != m_mapBundle.end()) {
        BundleValue *pValue = (BundleValue *) it->second;
        return pValue->GetFloatArray();
    } else
        return NULL;
}

/**
 *	根据指定Key获取double[]类型的值
 *	@param  strKey      [in]	指定Key
 *	@return double数组的指针
 *	@notes  N/A
 */
std::vector<double> *Bundle::getDoubleArray(std::string &strKey) const {
    std::map<std::string, void *>::const_iterator it = m_mapBundle.find(strKey);

    if (it != m_mapBundle.end()) {
        BundleValue *pValue = (BundleValue *) it->second;
        return pValue->GetDoubleArray();
    } else
        return NULL;
}

/**
 *	根据指定Key获取std::string[]类型的值
 *	@param  strKey      [in]	指定Key
 *	@return std::string数组的指针
 *	@notes  N/A
 */
std::vector <std::string> *Bundle::getStringArray(const std::string &strKey) const {
    std::map<std::string, void *>::const_iterator it = m_mapBundle.find(strKey);

    if (it != m_mapBundle.end()) {
        BundleValue *pValue = (BundleValue *) it->second;
        return pValue->GetStringArray();
    } else
        return NULL;
}

/**
 *	根据指定Key获取Bundle[]类型的值
 *	@param  strKey      [in]	指定Key
 *	@return Bundle数组的指针
 *	@notes  N/A
 */
std::vector <Bundle> *Bundle::getBundleArray(const std::string &strKey) const {
    std::map<std::string, void *>::const_iterator it = m_mapBundle.find(strKey);

    if (it != m_mapBundle.end()) {
        BundleValue *pValue = (BundleValue *) it->second;
        return pValue->GetBundleArray();
    } else
        return NULL;
}

/*******根据指定Key设定对应值********************/

/**
 *	根据指定Key获取bool类型的值
 *	@param  strKey      [in]	指定Key
 *	@param  bValue      [in]	指定Value
 *	@notes  N/A
 */
void Bundle::setBool(const std::string &strKey, bool bValue) {
    remove(strKey);
    BundleValue *pValue = BundleValue::CreatBool(bValue);
    if (pValue) {
        m_mapBundle[strKey] = pValue;
    }
}

/**
 *	根据指定Key获取int类型的值
 *	@param  strKey      [in]	指定Key
 *	@param  iValue      [in]	指定Value
 *	@notes  N/A
 */
void Bundle::setInt(const std::string &strKey, int64_t iValue) {
    remove(strKey);
    BundleValue *pValue = BundleValue::CreatInt(iValue);
    if (pValue) {
        m_mapBundle[strKey] = pValue;
    }
}

/**
 *	根据指定Key获取float类型的值
 *	@param  strKey      [in]	指定Key
 *	@param  fValue      [in]	指定Value
 *	@notes  N/A
 */
void Bundle::setFloat(const std::string &strKey, float fValue) {
    remove(strKey);
    BundleValue *pValue = BundleValue::CreatFloat(fValue);
    if (pValue) {
        m_mapBundle[strKey] = pValue;
    }
}

/**
 *	根据指定Key获取double类型的值
 *	@param  strKey      [in]	指定Key
 *	@param  dValue      [in]	指定Value
 *	@notes  N/A
 */
void Bundle::setDouble(const std::string &strKey, double dValue) {
    remove(strKey);
    BundleValue *pValue = BundleValue::CreatDouble(dValue);
    if (pValue) {
        m_mapBundle[strKey] = pValue;
    }
}

/**
 *	根据指定Key获取std::string类型的值
 *	@param  strKey      [in]	指定Key
 *	@param  strValue    [in]	指定Value
 *	@notes  N/A
 */
void Bundle::setString(const std::string &strKey, const std::string &strValue) {
    remove(strKey);
    BundleValue *pValue = BundleValue::CreatString(strValue);
    if (pValue) {
        m_mapBundle[strKey] = pValue;
    }
}

/**
 *	根据指定Key获取VBundle类型的值
 *	@param  strKey      [in]	指定Key
 *	@param  bundleValue [in]	指定Value
 *	@notes  N/A
 */
void Bundle::setBundle(const std::string &strKey, const Bundle &bundleValue) {
    remove(strKey);
    BundleValue *pValue = BundleValue::CreatBundle(bundleValue);
    if (pValue) {
        m_mapBundle[strKey] = pValue;
    }
}

/**
 *	根据指定Key获取double[]类型的值
 *	@param  strKey      [in]	指定Key
 *	@param  arrValue    [in]	指定Value
 *	@notes  N/A
 */
void Bundle::setFloatArray(const std::string &strKey, const std::vector<float> &arrValue) {
    remove(strKey);
    BundleValue *pValue = BundleValue::CreatFloatArray(arrValue);
    if (pValue) {
        m_mapBundle[strKey] = pValue;
    }
}

/**
 *	根据指定Key获取double[]类型的值
 *	@param  strKey      [in]	指定Key
 *	@param  arrValue    [in]	指定Value
 *	@notes  N/A
 */
void Bundle::setDoubleArray(const std::string &strKey, const std::vector<double> &arrValue) {
    remove(strKey);
    BundleValue *pValue = BundleValue::CreatDoubleArray(arrValue);
    if (pValue) {
        m_mapBundle[strKey] = pValue;
    }
}

/**
 *	根据指定Key获取std::string[]类型的值
 *	@param  strKey      [in]	指定Key
 *	@param  arrValue    [in]	指定Value
 *	@notes  N/A
 */
void Bundle::setStringArray(const std::string &strKey, const std::vector <std::string> &arrValue) {
    remove(strKey);
    BundleValue *pValue = BundleValue::CreatStringArray(arrValue);
    if (pValue) {
        m_mapBundle[strKey] = pValue;
    }
}

/**
 *	根据指定Key获取Bundle[]类型的值
 *	@param  strKey      [in]	指定Key
 *	@param  arrValue    [in]	指定Value
 *	@notes  N/A
 */
void Bundle::setBundleArray(const std::string &strKey, const std::vector <Bundle> &arrValue) {
    remove(strKey);
    BundleValue *pValue = BundleValue::CreatBundleArray(arrValue);
    if (pValue) {
        m_mapBundle[strKey] = pValue;
    }
}

/**
 *	根据指定Key获取unsigle long类型的值
 *	@param  strKey      [in]	指定Key
 *	@return 指针的值
 *	@notes  用于指针传递的情况
 */
void *Bundle::getHandle(const std::string &strKey) const {
    std::map<std::string, void *>::const_iterator it = m_mapBundle.find(strKey);

    if (it != m_mapBundle.end()) {
        BundleValue *pValue = (BundleValue *) it->second;
        unsigned long nValue = pValue->GetDouble();
        return (void *) nValue;
    } else
        return NULL;
}

/**
 *	根据指定Key获取unsigle long类型的值
 *	@param  strKey      [in]	指定Key
 *	@param  iValue      [in]	指定Value
 *	@notes  用于指针传递的情况
 */
void Bundle::setHandle(const std::string &strKey, const void *iValue) {
    remove(strKey);
    double dValue = *(unsigned long *) &iValue;
    m_mapBundle[strKey] = BundleValue::CreatDouble(dValue);
}
