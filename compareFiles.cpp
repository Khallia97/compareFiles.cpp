#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ofstream logfile; // global operator<< can access it

// overload << write to screen & log
ostream& operator<<(ostream &out, const string &msg) {
    cout << msg;              // print to console
    logfile << msg;           // also write to log file
    return out;
}

// overload == to compare strings
bool operator==(const string &a, const string &b) {
    return a.compare(b) == 0;
}

int main() {
    string file1, file2;
    ifstream f1, f2;
    string line1, line2;
    int lineNum = 1;

    cout << "Enter first file name: ";
    cin >> file1;
    cout << "Enter second file name: ";
    cin >> file2;

    logfile.open("log.txt"); // 3rd file

    try {
        f1.open(file1);
        f2.open(file2);

        if (!f1.is_open() || !f2.is_open())
            throw runtime_error("File failed to open\n");
    }
    catch(const runtime_error &e){
        cout << e.what();
        logfile << e.what();
        return 0;
    }

    // line by line comparison
    while (true) {
        bool read1 = getline(f1, line1);
        bool read2 = getline(f2, line2);

        if (!read1 && !read2) { // both ended
            string msg = "same\n";
            operator<<(cout, msg);
            break;
        }

        if (!read1 && read2) { // file1 ended first
            string msg = file1 + " is shorter\n";
            operator<<(cout, msg);
            break;
        }

        if (read1 && !read2) { // file2 ended first
            string msg = file2 + " is shorter\n";
            operator<<(cout, msg);
            break;
        }

        if (!(line1 == line2)) { // difference found
            string msg = "Different at line " + to_string(lineNum) + ":\n";
            operator<<(cout, msg);
            operator<<(cout, "File1: " + line1 + "\n");
            operator<<(cout, "File2: " + line2 + "\n");
            break;
        }

        lineNum++;
    }

    f1.close();
    f2.close();
    logfile.close();
    return 0;
}
