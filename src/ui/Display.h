#ifndef DISPLAY_H 
#define DISPLAY_H

#include<string>

#include "../model/Students.h"

std::string printLeft(std::string text, int Width);
std::string printRight(std::string text, int Width);
std::string printCentre(std::string text, int Width);

void Header();
void DisplayEachRecord(Students& Student);

void HighlightSearchedStudent(const std::string& Line,
                              const int& startIdx,
                              const int& endIdx);

#endif