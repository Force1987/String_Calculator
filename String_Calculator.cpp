#include <iostream>
#include <string>

using namespace std;
#define cin cin.ignore(cin.rdbuf()->in_avail())

string calc(string input)
{
        for (int i = 0; i < input.size(); ++i)
        {
            if ((input[i] < '0' || input[i] > '9') && input[i] != '*' && input[i] != '+' && input[i] != '-' && input[i] != '/' && input[i] != '(' && input[i] != ')' && input[i] != ',' && input[i] != '.') break;

            if (i == input.size() - 1)
            {
                for (int i = 0; i < input.size(); ++i)
                {
                    if (input[i] == '(')
                    {
                        int j = i;
                        for (int i = 1; i > 0; --i)
                        {
                            while (input[j] != ')')
                            {
                                ++j;
                                if (input[j] == '(')
                                    ++i;
                            }
                            if (i > 1) ++j;
                        }

                        input.replace(i, j - i + 1, calc(input.substr(i + 1, j - i - 1)));
                    }
                }

                for (int step = 1; step <= 2; ++step)
                {
                    char x, y;

                    if (step == 1)
                        x = '*', y = '/';
                    else
                        x = '+', y = '-';

                    for (int i = 0; i < input.size(); )
                    {
                        if (input[i] == x || input[i] == y)
                        {
                            long double leftOp = 0, rightOp = 0;
                            int rightIterator = i, s = i;
                            short sign = 1;
                            bool flag = 0;

                            for (int k = 0; i > 0 && (input[i - 1] >= '0' && input[i - 1] <= '9' || input[i - 1] == '-' || input[i - 1] == ',' || input[i - 1] == '.'); ++k)
                            {
                                flag = 1;
                                if (input[i - 1] == '-')
                                {
                                    if ((i - 2) >= 0 && (input[i - 2] == '*' || input[i - 2] == '+' || input[i - 2] == '-' || input[i - 2] == '/') || i == 1)
                                    {
                                        leftOp *= -1;
                                        --i;
                                    }
                                    break;
                                }
                                else if (input[i-1] == ',' || input[i-1] == '.')
                                {
                                    if (leftOp == 0)
                                    {
                                        --i;
                                        continue;
                                    }
                                    else
                                    {
                                        while ((int)leftOp > 0) leftOp /= 10;
                                        int temp = i;
                                        while (input[temp++] == '0') leftOp /= 10;
                                        k = -1;
                                    }
                                }
                                else
                                    leftOp += (input[i - 1] - 48) * pow(10, k);

                                --i;
                            }

                            short floatCounter = 0;

                            for (rightIterator; rightIterator < input.size() && (input[rightIterator + 1] >= '0' && input[rightIterator + 1] <= '9' || input[rightIterator + 1] == '-' || input[rightIterator + 1] == ',' || input[rightIterator + 1] == '.'); ++rightIterator)
                            {  
                                if (input[rightIterator + 1] == '-' && (input[rightIterator] == '*' || input[rightIterator] == '+' || input[rightIterator] == '-' || input[rightIterator] == '/'))
                                    sign = -1;
                                else if (input[rightIterator + 1] == '-')
                                    break;
                                else if (input[rightIterator + 1] == ',' || input[rightIterator + 1] == '.')
                                    floatCounter = 1;
                                else if (floatCounter == 0)
                                    rightOp = rightOp * 10 + input[rightIterator + 1] - 48;
                                else
                                    rightOp += (input[rightIterator + 1] - 48) * pow(10, -1 * floatCounter++);
                            }

                            rightOp *= sign;

                            if (flag == 0)
                            {
                                ++i;
                                continue;
                            }

                            if (step == 2)
                                input[s] == '+' ? leftOp += rightOp : leftOp -= rightOp;
                            else if (input[s] == '*')
                                leftOp *= rightOp;
                            else if (rightOp != 0)
                                leftOp /= rightOp;
                            else
                            {
                                cout << "Exception! Division by zero." << endl;
                                return input;
                            }
                            string temp = to_string(leftOp);
                            if (temp[temp.size() - 1] == '0')
                            {
                                for (int i = temp.size() - 1; temp[i] == '0'; i--)
                                    temp.erase(i, 1);

                                if (temp[temp.size() - 1] == '.')
                                    temp.erase(temp.size() - 1, 1);
                            }
                            input.replace(i, rightIterator - i + 1, temp);
                        }
                        else
                            ++i;
                    }
                }
                return input;
            }
        }
        return "Incorrect input!";
}

int main()
{
    string input;

    cout << "\t\tString calculator" << endl<<endl;

    do 
    {
        cout << "Enter an arithmetic expression: ";
        cin>>input;
        if(input!="exit") cout << "Result: "<<calc(input) << endl << endl;
    } while (input != "exit");
}