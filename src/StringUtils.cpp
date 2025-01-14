/*
Copyright (c) 2015 - present Advanced Micro Devices, Inc. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "StringUtils.h"
#include "LLVMCompat.h"
#include "llvm/ADT/SmallString.h"

using namespace llvm;

llvm::StringRef unquoteStr(llvm::StringRef s) {
  if (s.size() > 1 && s.front() == '"' && s.back() == '"')
    return s.substr(1, s.size() - 2);
  return s;
}

void removePrefixIfPresent(std::string &s, const std::string &prefix) {
  if (s.find(prefix) != 0) return;
  s.erase(0, prefix.size());
}

std::string getAbsoluteFilePath(const std::string &sFile, std::error_code &EC) {
  if (sFile.empty())
    return sFile;
  if (!sys::fs::exists(sFile)) {
    llvm::errs() << "\n" << sHipify << sError << "source file: " << sFile << " doesn't exist\n";
    EC = std::error_code(static_cast<int>(std::errc::no_such_file_or_directory), std::generic_category());
    return "";
  }
  SmallString<256> fileAbsPath;
  EC = llcompat::real_path(sFile, fileAbsPath, true);
  if (EC) {
    llvm::errs() << "\n" << sHipify << sError << EC.message() << ": source file: " << sFile << "\n";
    return "";
  }
  EC = std::error_code();
  return fileAbsPath.c_str();
}

std::string getAbsoluteDirectoryPath(const std::string &sDir, std::error_code &EC,
  const std::string &sDirType, bool bCreateDir) {
  if (sDir.empty())
    return sDir;
  EC = std::error_code();
  SmallString<256> dirAbsPath;
  if (sys::fs::exists(sDir)) {
    if (sys::fs::is_regular_file(sDir)) {
      llvm::errs() << "\n" << sHipify << sError << sDir << " is not a directory\n";
      EC = std::error_code(static_cast<int>(std::errc::not_a_directory), std::generic_category());
      return "";
    }
  } else {
    if (bCreateDir) {
      EC = sys::fs::create_directory(sDir);
      if (EC) {
        llvm::errs() << "\n" << sHipify << sError << EC.message() << ": " << sDirType << " directory: " << sDir << "\n";
        return "";
      }
    }
    else {
      llvm::errs() << "\n" << sHipify << sError << sDirType << " directory: " << sDir << " doesn't exist\n";
      EC = std::error_code(static_cast<int>(std::errc::no_such_file_or_directory), std::generic_category());
      return "";
    }
  }
  EC = llcompat::real_path(sDir, dirAbsPath, true);
  if (EC) {
    llvm::errs() << "\n" << sHipify << sError << EC.message() << ": " << sDirType << " directory: " << sDir << "\n";
    return "";
  }
  return dirAbsPath.c_str();
}
