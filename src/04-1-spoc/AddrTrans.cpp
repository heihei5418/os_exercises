#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

vector<int> mem, disk;
const int BASE = 3456;

void consult(int temp, ofstream& fout)
{
    fout << "Virtual Address " << hex << temp << ':' << endl;
    
    int pde_index = temp >> 10;
    int pde_contents = mem[pde_index + BASE];
    int valid = pde_contents >> 7;
    int pfn = pde_contents - valid * 128;
    fout << "  --> pde index:0x" << pde_index << " pde contents:(valid " << valid << ", pfn 0x" << pfn << ")" << endl;

    if (valid == 0)
    {
        fout << "      --> Fault (page directory entry not valid)" << endl;
        return;
    }

    int pte_index = (temp & 1023) >> 5;
    int pte_contents = mem[pfn * 32 + pte_index];
    valid = pte_contents >> 7;
    pfn = pte_contents - valid * 128;
    fout << "    --> pte index:0x" << pte_index << " pte contents:(valid " << valid << ", pfn 0x" << pfn << ")" << endl;

    int offset = temp &  31;
    int phiAddr = pfn * 32 + offset;

    if (valid == 0)
    {
        fout << "      --> Translates to Disk Sector Address 0x" << phiAddr << " -->Value: 0x" << disk[phiAddr] << endl;
        return;
    }

    fout <<"       --> Translates to Physical Address 0x" << phiAddr << " --> Value: 0x" << mem[phiAddr] << endl;
}

int main()
{
    int temp;
    ifstream fin;
    fin.open("mem.txt");
    while (fin >> hex >> temp)
        mem.push_back(temp);
    fin.close();
    fin.open("disk.txt");
    while (fin >> temp)
        disk.push_back(temp);
    fin.close();

    for (int i = 0; i < mem.size(); i++)
        cout << mem[i] << ' ';

    fin.open("in.txt");
    ofstream fout;
    fout.open("answer.txt");
    while (fin >> temp)
        consult(temp, fout);
    fin.close();
    fout.close();
    return 0;
}

