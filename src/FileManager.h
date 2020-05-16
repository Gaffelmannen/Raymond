#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <regex>

#include "../lib/toojpeg.h"

using namespace std;

class FileManager
{
    private:
    static const string BASE_DIR;
    static const string SETTINGS_DIR;
    static const string FILE_ABBREVATION_PPM;
    static const string FILE_ABBREVATION_JPEG;
    static const string FILE_ABBREVATION_TXT;
    void WriteOutput(unsigned char);
    
    public:
    FileManager(void);
    int WriteToPPMFile(string, int, int, vector<vector<int>>);
    int WriteToJpegFile(string, int, int, vector<vector<int>>);
};

#endif
