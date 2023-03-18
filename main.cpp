#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <random>

std::string convertTo(int& decimalValue);
int convertFrom(const std::string& name);
int log_base(const int& base, const int& argument);
char menuDisplay();
std::string randon_generator(const int& lower_bound, const int& upper_bound);

int main()
{
	char selector = 'y';
	std::string input, lower_bound, upper_bound;
	int decimalValue;
	std::cout<<"The numeral system is a base-6 system of letters in an alternating consonant-vowel pattern to render any numeral as a pronouncable word." <<std::endl;
	while(selector != 'q' && selector != 'Q')
	{
			selector = menuDisplay();
			switch(selector)
			{
				case '1':
					do
					{
						std::cout << "Enter decimal term.\n";
						std::cin >> input;
						decimalValue = stoi(input);
						std::cout << convertTo(decimalValue) <<
								"\nTo rerun, enter y.\n"
								"To exit enter q.\n"
								"To choose another option enter 4" << std::endl;
						std::cin >> selector;
					} while (selector =='y');
					break;

				case '2':
					do
					{
						std::cout << "Enter numeral.\n";
						std::cin >> input;
						decimalValue = convertFrom(input);
						std::cout << decimalValue <<
								"\nTo rerun, enter y.\n"
								"To exit enter q.\n"
								"To choose another option enter 4" << std::endl;
						std::cin >> selector;
					} while (selector == 'y');
					break;
				case '3':
					do
					{
						do
						{
						std::cout << "Enter lower bound\n";
						std::cin >> lower_bound;
						std::cout << "Enter upper bound\n";
						std::cin >> upper_bound;
						int lower_bound_int = stoi(lower_bound);
						int upper_bound_int = stoi(upper_bound);
						
						}while(lower_bound_int > upper_bound_int);
						std::string output = randon_generator(lower_bound_int, upper_bound_int);
						std::cout << output <<
								"\nTo rerun, enter y.\n"
								"To exit enter q.\n"
								"To choose another option enter 4" << std::endl;
						std::cin >> selector;

					} while (selector == 'y');
					break;
			}
		}
}

std::string convertTo(int& decimalValue)
{
	int size = log_base(6,decimalValue);
	if(size < 2)
	{
		size=2; //smallest numeral is still 2 letters long
	}

	std::stack<int> heximal; //the heximal is constructed as a deque with each index holding one place-value, 1's, 6's, 36's, etc.
	int remainder;
	for(unsigned i=0; i < size; i++)
	{
		if(decimalValue < 6)//base case, decimal < 6
		{
			heximal.push(decimalValue);
			decimalValue = 0; //kick out of loop
		}
		else //decimal has more than 6 left
		{
			remainder = decimalValue % 6; //modulus to get the remainder
			heximal.push(remainder); //push it into place
			decimalValue /= 6; //update decimal value
		}
	}

	std::string output;
	for (unsigned i = 0; i < size; i++) //iterate through the deque and construct a string out of each place-value's corresponding character
	{
		int next_int = heximal.top();
		heximal.pop();
		if(i%2 == 0) //place is even
		{
			switch (next_int)//place is 6^1, 6^3
			{
				case 0:
					output += "l";
					break;
				case 1:
					output += "z";
					break;
				case 2:
					output += "s";
					break;
				case 3:
					output += "m";
					break;
				case 4:
					output += "n";
					break;
				case 5:
					output += "f";
					break;
			}
		}
		else //place is odd
		{
			switch (next_int)//place is 6^0, 6^2
			{
				case 0:
					output += "y";
					break;
				case 1:
					output += "a";
					break;
				case 2:
					output += "i";
					break;
				case 3:
					output += "e";
					break;
				case 4:
					output += "u";
					break;
				case 5:
					output += "o";
					break;
			}
		}
	}

	return output;
}

int convertFrom(const std::string& name)
{
	int decimal = 0;
	int power;
	for (unsigned i = 0; i < name.size(); i++)
	{
		power = name.size() - 1 - i;
		switch (name[i])
		{
			case 'l':
			case 'y':
				//0
				decimal += (0 * std::pow(6,power));
				break;

			case 'z':
			case 'a':
				//1
				decimal += (1 * std::pow(6,power));
				break;

			case 's':
			case 'i':
				//2
				decimal += (2 * std::pow(6,power));
				break;

			case 'm':
			case 'e':
				//3
				decimal += (3 * std::pow(6,power));
				break;

			case 'n':
			case 'u':
				//4
				decimal += (4 * std::pow(6,power));
				break;

			case 'f':
			case 'o':
				//5
				decimal += (5 * std::pow(6,power));
				break;
		}
	}
	return decimal;
}

int log_base(const int& base, const int& argument)
{
	return ceil(log(argument)/log(base));
}

char menuDisplay()
{
	char selector;
	do
	{
		std::cout << "1) To convert a decimal number to numeral script enter 1.\n"
					 "2) To convert a numeral to a decimal number enter 2.\n"
					 "3) Generate a random numeral from set bounds\n"
					 "q  To quit enter q.\n";
			std::cin >> selector;
	} while (selector != '1' && selector != '2' && selector != '3' && selector != 'q' && selector != 'Q');
	return selector;

}

std::string randon_generator(const int& lower_bound, const int& upper_bound)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(lower_bound, upper_bound);
	int rand = distrib(gen);
	return convertTo(rand);
}