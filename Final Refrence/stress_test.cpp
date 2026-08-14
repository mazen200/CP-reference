#include <bits/stdc++.h>

using namespace std;

// Random test case generator (writes input to in.txt)
void generate_test_case()
{
    ofstream fout("io/input.txt");
    // TODO : Test Generation
    fout.close();
}

// Read entire file into a string (for output comparison)
string read_file(const string &filename)
{
    ifstream fin(filename);
    stringstream buffer;
    buffer << fin.rdbuf();
    return buffer.str();
}

int main()
{
    srand(time(0));
    int test_num = 0;

    for(; test_num < 1000;)
    {
        test_num++;
        generate_test_case();

        // Run both solutions on the same input
        system("./build/naive");
        system("./build/fast");
        // Compare outputs
        string out = read_file("io/output.txt");
        string brute = read_file("io/output_naive.txt");

        if (out != brute)
        {
            cout << "Test " << test_num << " FAILED!\n";
            // cout << "Input:\n" << read_file("io/input.txt") << "\n";
            // cout << "Fast output:\n" << out << "\n";
            // cout << "Brute output:\n" << brute << "\n";
            break;
        }
        else
        {
            cout << "Test " << test_num << " passed.\n";
        }
    }

    return 0;
}