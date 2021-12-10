#include <map>
#include <string>

class ParameterReader{
private:
    int expectedParamsCount_, optionalParamsCount_;
    char **expectedParams_, **optionalParams_;
    void deleteParams(char ***params, int count);
    void setParams(const char **params, int count, char ***internParams, int *internCount);
    bool checkExpectedParams(char **argv, int argc) const;
public:
    std::map<std::string, std::string> params;
    ParameterReader();
    ParameterReader(const ParameterReader& other) = delete;
    ~ParameterReader();
    void setExpectedParams(const char **expectedParams, int count);
    void setOptionalParams(const char **optionalParams, int count);
    bool parseParams(char **argv, int argc);
    void printParams() const;
    void printExpectedParams() const;
    ParameterReader& operator=(const ParameterReader& other) = delete;
};