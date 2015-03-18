#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

vector<int> mem;
const int BASE = 544;

void consult(int temp)
{
    cout << "Virtual Address " << hex << temp << ':' << endl;
    
    int pde_index = temp >> 10;
    int pde_contents = mem[pde_index + BASE];
    int valid = pde_contents >> 7;
    int pfn = pde_contents - valid * 128;
    cout << "  --> pde index:0x" << pde_index << " pde contents:(valid " << valid << ", pfn 0x" << pfn << ")" << endl;

    if (valid == 0)
    {
        cout << "      --> Fault (page directory entry not valid)" << endl;
        return;
    }

    int pte_index = (temp & 1023) >> 5;
    int pte_contents = mem[pfn * 32 + pte_index];
    valid = pte_contents >> 7;
    pfn = pte_contents - valid * 128;
    cout << "    --> pte index:0x" << pte_index << " pte contents:(valid " << valid << ", pfn 0x" << pfn << ")" << endl;

    if (valid == 0)
    {
        cout << "      --> Fault (page directory entry not valid)" << endl;
        return;
    }

    int offset = temp &  31;
    int phiAddr = pfn * 32 + offset;
    cout <<"       --> Translates to Physical Address 0x" << phiAddr << " --> Value: 0x" << mem[phiAddr] << endl;
}

int main()
{
    int temp;
    ifstream fin;
    fin.open("data.txt");
    while (fin >> hex >> temp)
        mem.push_back(temp);
    fin.close();
    
    cin >> hex >> temp;
    consult(temp);
    return 0;
}

