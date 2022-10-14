#include <iostream>
#include <sstream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <math.h>

#define WORSTCASELEN 16      //The biggest fraction will be 2000000/1000000 (15 chars plus '\0')

/*defines for the sieve-of-erastothenes algorithm*/
#define TAIL 1
#define HEAD 0
#define PRIME_NUMBER 2

#define BIGGEST_NUMBER 2000000

std::vector<int> sieve_of_erastothenes(int N);

/*Prime numbers will be necessary to simplify the fractions.
Just the prime numbers lower or equal to the square root of the biggest possible number will be needed*/
const std::vector<int> prime_numbers = sieve_of_erastothenes(sqrt(BIGGEST_NUMBER));

class operations{
    private:
        int numerator, denominator;
        char str_result[WORSTCASELEN];
        char str_simplified[WORSTCASELEN];
    public:
        std::string get_sum(int n1, int d1, int n2, int d2){
            numerator = n1 * d2 + n2 * d1;
            denominator = d1 * d2;
            
            snprintf(str_result, WORSTCASELEN, "%d/%d", numerator, denominator);
            return str_result; 
        }
        std::string get_sub(int n1, int d1, int n2, int d2){
            numerator = n1 * d2 - n2 * d1;
            denominator = d1 * d2;

            snprintf(&str_result[0], WORSTCASELEN, "%d/%d", numerator, denominator);
            return str_result;
        }
        std::string get_mult(int n1, int d1, int n2, int d2){
            numerator = n1 * n2;
            denominator = d1 * d2;
            snprintf(&str_result[0], WORSTCASELEN, "%d/%d", numerator, denominator);
            return str_result;
        }
        std::string get_divi(int n1, int d1, int n2, int d2){
            numerator = n1 * d2;
            denominator = n2 * d1;
            snprintf(&str_result[0], WORSTCASELEN, "%d/%d", numerator, denominator);
            return str_result;
        }
        std::string get_simplified(){
            int i;
            for(i = 0; i < prime_numbers.size(); i++){
                while(numerator % prime_numbers.at(i) == 0 
                        and denominator % prime_numbers.at(i) == 0){
                    numerator /= prime_numbers.at(i);
                    denominator /= prime_numbers.at(i);
                }
            }
            snprintf(&str_simplified[0], WORSTCASELEN, "%d/%d", numerator, denominator);
            return str_simplified;
        }
};

int main(){
    int numberof_cases, operands[4], i;
    std::string str_stream, str_result;
    char aux, operation;
    operations opr;
    std::vector<std::string> results;

    std::cin >> numberof_cases;
    //ignore() to make getline get the desired input
    std::cin.ignore();
    i = 0;
    while(i < numberof_cases){
        getline(std::cin, str_stream);
        std::stringstream(str_stream) >> operands[0] 
                                        >> aux  
                                        >> operands[1]
                                        >> operation
                                        >> operands[2]
                                        >> aux
                                        >> operands[3]
                                        ;
        //Execute operation and push the result and simplified result in the vector
        switch(operation){
            case '+':
                str_result = opr.get_sum(operands[0], operands[1], operands[2], operands[3]);
                str_result = str_result + " = " + opr.get_simplified();
                results.push_back(str_result);
                break;
            case '-':
                str_result = opr.get_sub(operands[0], operands[1], operands[2], operands[3]);
                str_result = str_result + " = " + opr.get_simplified();
                results.push_back(str_result);
                break;
            case '*':
                str_result = opr.get_mult(operands[0], operands[1], operands[2], operands[3]);
                str_result = str_result + " = " + opr.get_simplified();
                results.push_back(str_result);
                break;
            case '/':
                str_result = opr.get_divi(operands[0], operands[1], operands[2], operands[3]);
                str_result = str_result + " = " + opr.get_simplified();
                results.push_back(str_result);
                break;
        }
        i++;
    }
    for(i = 0; i < results.size(); i++){
        std::cout << results.at(i) << "\n";
    }
    return 0;

}

std::vector<int> sieve_of_erastothenes(int N){
    /*The sieve will have N - 1 size.
    Will store both the number and the marks
    The marks will stay in the end of each vector inside the vector,
    while the number will stay in the beginning
    */
    std::vector<std::vector<int>> sieve;
    int i, j;
    std::vector<int> prime_numbers;

    sieve.resize(N - 1);
    for(i = 2, j = 0; i <= N; i++, j++){
        sieve.at(j).push_back(i);
        //Now the mark (zero for not marked)
        sieve.at(j).push_back(0);
    }
    /*For each number element of the sieve,
    if the number is not marked, then mark it and
    for each number after it, if the number is divisible by it, 
    and is greater than or equal to the square of it,
    then mark the number
    */
    for(j = 0; j < sieve.size(); j++){
        if(sieve.at(j).at(TAIL) == 0){
            sieve.at(j).pop_back(), sieve.at(j).push_back(PRIME_NUMBER);
            for(i = j + 1; i < sieve.size(); i++){
                if(sieve.at(i).at(HEAD) % sieve.at(j).at(HEAD) == 0 and sieve.at(i).at(HEAD) >= pow(sieve.at(j).at(HEAD), 2) ){
                    sieve.at(i).at(TAIL) = 1;
                }
            }
        }
    }
    /*Put all the prime numbers below or equal to N in a result vector*/
    for(i = 0; i < sieve.size(); i++){
        if(sieve.at(i).at(TAIL) == PRIME_NUMBER){
            prime_numbers.push_back(sieve.at(i).at(HEAD));
        }
    }
    return prime_numbers;
}
