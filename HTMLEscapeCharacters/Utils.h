﻿#pragma once

#include <string>
#include <vector>

int Execute(int argc, char *argv[]);


std::wstring EncodeHTML(std::wstring &strSource);
std::wstring DecodeHTML(std::wstring &strSource);

std::vector<std::string> Split(std::string str, const std::string &strDelimiter);
std::string Trim(const std::string &s);

std::vector<std::string> GetDirectoryFiles(const std::string &strDir, const std::vector<std::string> &strExtensions, bool bSub = false);
