#pragma once

#include <string>
#include <vector>
#include <map>

enum {
    bundle_error = 0,
    bundle_bool = 1,
    bundle_float,
    bundle_integer,
    bundle_string,
    bundle_bundle,
    bundle_float_number_array,
    bundle_double_number_array,
    bundle_string_array,
    bundle_bundle_array,
};

class Bundle {
public:

    Bundle();

    ~Bundle();

    Bundle(Bundle &r);

    Bundle(const Bundle &r);

    Bundle &operator=(const Bundle &r);

    /**
      *  清空数据实体
      *	@note N/A
      */
    void clear();

    /**
      *  删除指定键值
      *  @param strKey  要删除的键值
      *  @notes N/A
      */
    void remove(const std::string &strKey);

    bool containsKey(const std::string &strKey) const;

    void getKeys(std::vector<std::string> &arrKey) const;

    int getType(std::string &strKey) const;

    bool getBool(const std::string &strKey) const;

    bool getBool(const std::string &strKey, bool &value) const;

    void setBool(const std::string &strKey, bool bValue);

    int64_t getInt(const std::string &strKey) const;

    bool getInt(const std::string &strKey, int64_t &value) const;

    void setInt(const std::string &strKey, int64_t iValue);

    float getFloat(const std::string &strKey) const;

    void setFloat(const std::string &strKey, float fValue);

    double getDouble(const std::string &strKey) const;

    void setDouble(const std::string &strKey, double dValue);

    std::string *getString(const std::string &strKey) const;

    void setString(const std::string &strKey, const std::string &strValue);

    Bundle *getBundle(const std::string &strKey) const;

    void setBundle(const std::string &strKey, const Bundle &bundleValue);

    std::vector<float> *getFloatArray(const std::string &strKey) const;

    void setFloatArray(const std::string &strKey, const std::vector<float> &arrValue);

    std::vector<double> *getDoubleArray(std::string &strKey) const;

    void setDoubleArray(const std::string &strKey, const std::vector<double> &arrValue);

    std::vector<std::string> *getStringArray(const std::string &strKey) const;

    void setStringArray(const std::string &strKey, const std::vector<std::string> &arrValue);

    std::vector<Bundle> *getBundleArray(const std::string &strKey) const;

    void setBundleArray(const std::string &strKey, const std::vector<Bundle> &arrValue);

    void *getHandle(const std::string &strKey) const;

    void setHandle(const std::string &strKey, const void *iValue);

protected:
    std::map<std::string, void *> m_mapBundle;
};
