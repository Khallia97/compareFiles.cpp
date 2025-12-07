#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

ofstream logfile; // log output file

// overload << output goes to console and log
ostream& operator<<(ostream& out, const string& msg) {
    out.write(msg.c_str(), msg.size());
    logfile.write(msg.c_str(), msg.size());
    return out;
}

// overload == for string comparison
bool operator==(const string &a, const string &b) {
    return a.compare(b) == 0;
}

int main() {
    string file1, file2;
    ifstream f1, f2;
    string line1, line2;
    int lineNum = 1;

    logfile.open("log.txt");

    cout << string("Enter first file name: ");
    cin >> file1;
    cout << string("Enter second file name: ");
    cin >> file2;

    try {
        f1.open(file1);
        f2.open(file2);

        if (!f1.is_open() || !f2.is_open())
            throw runtime_error("File failed to open\n");
    }
    catch(const runtime_error &e){
        cout << string(e.what());            // overload so error also goes to log
        logfile.close();
        return 0;
    }

    while (true) {
        bool read1 = static_cast<bool>(getline(f1, line1));
        bool read2 = static_cast<bool>(getline(f2, line2));

        if (!read1 && !read2) {              // both ended
            cout << string("same\n");
            break;
        }
        if (!read1 && read2) {          // file1 ended first
            cout << file1 + string(" is shorter\n");
            break;
        }
        if (read1 && !read2) {               // file2 ended first
            cout << file2 + string(" is shorter\n");
            break;
        }
        if (!(line1 == line2)) {                 // lines differ
            cout << string("Different at line ") + to_string(lineNum) + string(":\n");
            cout << string("File1: ") + line1 + string("\n");
            cout << string("File2: ") + line2 + string("\n");
            break;
        }
        lineNum++;
    }

    f1.close();                // close
    f2.close();
    logfile.close();        
    return 0;
}

