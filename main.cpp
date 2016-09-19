#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <direct.h>
using namespace std;
void DeleteAllFiles(char* folderPath)
{
 char fileFound[256];
 WIN32_FIND_DATA info;
 HANDLE hp;
 sprintf(fileFound, "%s\\*.*", folderPath);
 hp = FindFirstFile(fileFound, &info);
 do
    {
       sprintf(fileFound,"%s\\%s", folderPath, info.cFileName);
       DeleteFile(fileFound);

    }while(FindNextFile(hp, &info));
 FindClose(hp);
}
inline bool exists_test (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}
void copy_file( const char* srce_file, const char* dest_file )
{
    ifstream srce( srce_file, ios::binary ) ;
    ofstream dest( dest_file, ios::binary ) ;
    dest << srce.rdbuf() ;
}
template <class T>
string to_string(T obj)
{
    stringstream ss;
    ss << obj;
    return ss.str();
}
int main ()
 {
    DeleteAllFiles("OUT");
    mkdir("OUT");
    string iloscS;
    int ilosc;
    string plik;
    ifstream myfile ("Config.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,plik,'\t') )
        {

            string inS="IN/"+plik;
            const char *in = inS.c_str();

            string plik_bez=plik;
            size_t pos = plik.find(".");
            string dot = plik.substr (pos);
            plik_bez.replace(plik_bez.find(dot),dot.length(),"");
            string autS = "OUT/"+plik_bez;
            getline (myfile,iloscS,'\n');
            ilosc = atoi(iloscS.c_str());
            int licznik = 1;
            string liczniks;
            for(int i= 0;ilosc>i;i++)
            {
                autS = "OUT/"+plik_bez;
                autS+="_";
                liczniks = to_string(licznik);
                autS+=liczniks;
                licznik++;
                autS+=dot;
                if(exists_test(in)== 0)
                    break;
                const char *aut = autS.c_str();
                copy_file(in,aut);
            }
        }
    myfile.close();
    }
    else cout << "Unable to open file";
    return 0;
}
