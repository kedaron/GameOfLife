#include <iostream>
#include <cstring>
#include <string>
#include <map>

class InputReader{
private:
    int expectedParamsCount_, optionalParamsCount_;
    char **expectedParams_, **optionalParams_;
    void deleteParams(char ***params, int count){
        for(int i = 0; i < count; i++)
            delete [] (*params)[i];
        delete [] *params;
    }
    void setParams(const char **params, int count, char ***internParams, int *internCount){
        if(*internCount > 0){
            deleteParams(internParams, *internCount);
        }
        *internCount = count;
        *internParams = new char*[count];
        for(int i = 0; i < count; i++){
            int len = std::strlen(params[i]);
            (*internParams)[i] = new char[len+1];
            strcpy_s((*internParams)[i], len+1, params[i]);
        }
    }
    bool checkExpectedParams(char **argv, int argc) const{
        bool valid = true;
        for(int i = 0; i < expectedParamsCount_; i++){
            bool found = false;
            for(int j = 0; j < argc; j++){
                if(std::strcmp(expectedParams_[i], argv[j]) == 0){
                    found = true;
                    break;
                }
            }
            if(!found){
                valid = false;
                break;
            }
        }
        return valid;
    }
public:
    std::map<std::string, std::string> params;
    InputReader(){
        expectedParamsCount_ = 0;
        expectedParams_ = {};
        optionalParamsCount_ = 0;
        optionalParams_ = {};
    }
    InputReader(const InputReader &other) = delete;
    ~InputReader(){
        deleteParams(&expectedParams_, expectedParamsCount_);
        deleteParams(&optionalParams_, optionalParamsCount_);
    }
    void setExpectedParams(const char **expectedParams, int count){
        setParams(expectedParams, count, &expectedParams_, &expectedParamsCount_);
    }
    void setOptionalParams(const char **optionalParams, int count){
        setParams(optionalParams, count, &optionalParams_, &optionalParamsCount_);
    }
    bool parseParams(char **argv, int argc){
        if(!checkExpectedParams(argv, argc)){
            return false;
        }
        for(int i = 1; i < argc; i++){ // i = 1 => first param is program name => skip
            if(argv[i][0] == '-' && argv[i][1] == '-'){
                params[argv[i]] = "";
                if((i < argc-1) && !(argv[i+1][0] && argv[i+1][1] == '-')){
                    params[argv[i]] = argv[i+1];
                }
            }
        }
        return true;
    }
    void printParams() const{
        for(auto it = params.begin(); it != params.end(); it++)
            std::cout << it->first << ": " << it->second << std::endl;
    }
    void printExpectedParams() const{
        std::cout << "Expected Parameters: ";
        for(int i = 0; i < expectedParamsCount_; i++){
            std::cout << expectedParams_[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Optional Parameters: ";
        for(int i = 0; i < optionalParamsCount_; i++){
            std::cout << optionalParams_[i] << " ";
        }
        std::cout << std::endl;
    }
    InputReader& operator=(const InputReader &other) = delete;
};

int main(int argc, char** argv){
    InputReader reader;
    const int epCount = 3, opCount = 1;
    const char *ep[epCount] = {"--load", "--save", "--generations"};
    const char *op[opCount] = {"--measure"};

    reader.setExpectedParams(ep, epCount);
    reader.setOptionalParams(op, opCount);

    if(!reader.parseParams(argv, argc)){
        std::cout << "Invalid parameters..." << std::endl;
        reader.printExpectedParams();
        std::cout << "Please Use the following shape:" << std::endl;
        std::cout << "--load <param1> --save <param2> --generations <param3> --measure" << std::endl;
    }
    else{
        reader.printParams();
    }

    return 0;
}