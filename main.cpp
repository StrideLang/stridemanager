/*
    Stride is licensed under the terms of the 3-clause BSD license.

    Copyright (C) 2017. The Regents of the University of California.
    All rights reserved.
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

        Redistributions of source code must retain the above copyright notice,
        this list of conditions and the following disclaimer.

        Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

        Neither the name of the copyright holder nor the names of its
        contributors may be used to endorse or promote products derived from
        this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.

    Authors: Andres Cabrera and Joseph Tilbian
*/

#include <iostream>
#include <string>
#include <vector>

#include "stride/codegen/toolmanager.hpp"

using namespace strd;

void printUsage(const std::string &programName) {
  std::cout << "Usage: " << programName << " [options] <strideroot path>\n\n"
            << "Stride command line tool manager (0.1-alpha)\n\n"
            << "Arguments:\n"
            << "  strideroot path       Path to strideroot\n\n"
            << "Options:\n"
            << "  -g, --generate        Generate all local configurations\n"
            << "  -l, --list            List all local configurations\n"
            << "  -n, --interactive     Update interactively\n"
            << "  -i, --install <name>  Install framework\n"
            << "  -h, --help            Displays this help\n"
            << "  -v, --version         Displays version information\n";
}

int main(int argc, char *argv[]) {
  bool generate = false;
  bool list = false;
  bool interactive = false;
  std::string installFramework;
  std::string strideRoot;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-h" || arg == "--help") {
      printUsage(argv[0]);
      return 0;
    } else if (arg == "-v" || arg == "--version") {
      std::cout << "strdtools version 0.1-alpha\n";
      return 0;
    } else if (arg == "-g" || arg == "--generate") {
      generate = true;
    } else if (arg == "-l" || arg == "--list") {
      list = true;
    } else if (arg == "-n" || arg == "--interactive") {
      interactive = true;
    } else if (arg == "-i" || arg == "--install") {
      if (i + 1 < argc) {
        installFramework = argv[++i];
      } else {
        std::cerr << "Error: -i/--install requires a framework argument.\n";
        return -1;
      }
    } else if (arg.rfind("-i=", 0) == 0) {
      installFramework = arg.substr(3);
    } else if (arg.rfind("--install=", 0) == 0) {
      installFramework = arg.substr(10);
    } else if (!arg.empty() && arg[0] == '-') {
      std::cerr << "Unknown option: " << arg << "\n";
      printUsage(argv[0]);
      return -1;
    } else {
      if (strideRoot.empty()) {
        strideRoot = arg;
      }
    }
  }

  if (strideRoot.empty()) {
    printUsage(argv[0]);
    return -1;
  }

  (void)interactive; // TODO use interactive mode

  ToolManager toolManager(strideRoot);

  for (const auto &toolTemplate : toolManager.toolTemplates) {
    std::cout << "Tool Template: " << toolTemplate->strideName << "\n"
              << "  displayName: " << toolTemplate->displayName << "\n";
  }

  if (generate) {
    std::cout << "Updating local tools config\n";
    toolManager.updateAllLocalConfigs();
  }

  if (list) {
    // TODO add list
  }

  if (!installFramework.empty()) {
    // TODO add framework installation logic
  }

  return 0;
}
