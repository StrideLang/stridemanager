/*
    Stride is licensed under the terms of the GNU Affero General Public License
   version 3.

    Copyright (C) 2022-2026. The Regents of the University of California.
    All rights reserved.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Authors: Andres Cabrera
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
