#include <string>
#include <vector>

//function declarations

//day1
bool is_prime_simple(int num);
int fuelCalculator(int mass);
//day2
std::vector<int> vectorCreator(std::string input);
void intCode(std::vector<int> &code_vector);
//day3
std::vector<std::string> makeInstr(std::string &string);
int *getSize(std::vector<std::string> &input, std::string axis);
void drawCable(std::vector<std::string> &instr, std::vector<std::vector<int> > &layout, int &x_pos, int &y_pos);

//day4
int giveCount(unsigned int const &low, unsigned int const &high);
