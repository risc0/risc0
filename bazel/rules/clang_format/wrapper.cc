#include <unistd.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#if defined(_WIN32) || defined(WIN32)
#define IS_WINDOWS true
#else
#define IS_WINDOWS false
#endif

std::string get_working_path() {
  char temp[1024];
  return (getcwd(temp, sizeof(temp)) ? std::string(temp) : std::string(""));
}

int execute(const std::string& exec_path,
            const std::vector<std::string>& arguments,
            const std::string& cwd) {
  std::string pwd = get_working_path();
  std::string command = IS_WINDOWS ? pwd + "\\" + exec_path : pwd + "/" + exec_path;

  for (const std::string& arg : arguments) {
    command += " " + arg;
  }

  int chdir_exit_code = 0;

  chdir_exit_code = chdir(cwd.c_str());
  if (chdir_exit_code) {
    return chdir_exit_code;
  }

  int exit_code = system(command.c_str());

  chdir_exit_code = chdir(pwd.c_str());
  if (chdir_exit_code) {
    return chdir_exit_code;
  }

  return exit_code;
}

int copy_file(std::string src, std::string dest) {
  std::string mkdir_command;
  // Normalize paths on windows
  if (IS_WINDOWS) {
    size_t src_pos;
    while ((src_pos = src.find('/')) != std::string::npos) {
      src.replace(src_pos, 1, "\\");
    }

    size_t dest_pos;
    while ((dest_pos = dest.find('/')) != std::string::npos) {
      dest.replace(dest_pos, 1, "\\");
    }

    // Create parent directory
    size_t sep_pos = dest.rfind("\\");
    if (sep_pos != std::string::npos) {
      std::string parent_dir = dest.substr(0, sep_pos);

      mkdir_command = std::string("mkdir " + parent_dir);
      int exit_code = system(mkdir_command.c_str());
      if (exit_code) {
        return exit_code;
      }
    }
  } else {
    // Create parent directory
    size_t sep_pos = dest.rfind("/");
    if (sep_pos != std::string::npos) {
      std::string parent_dir = dest.substr(0, sep_pos);

      mkdir_command = std::string("mkdir -p " + parent_dir);
      int exit_code = system(mkdir_command.c_str());
      if (exit_code) {
        return exit_code;
      }
    }
  }

  std::ifstream src_stream(src, std::ios::binary);
  std::ofstream dst_stream(dest, std::ios::binary);

  dst_stream << src_stream.rdbuf();

  return 0;
}

int run_clang_format(const std::string& clang_format_file,
                     const std::vector<std::string>& clang_format_arguments,
                     const std::string& config_file,
                     const std::vector<std::string>& sources,
                     const std::string& diff_tool_file) {
  std::string working_dir = "__clang_format__";

  // Install the config file if one was provided
  if (!config_file.empty()) {
    std::string dest = working_dir + "/.clang-format";
    int exit_code = copy_file(config_file, dest);
    if (exit_code) {
      return exit_code;
    }
  }

  // If a diff tool was given, a series of additional commands
  // will be run to ensure there are no differences while also
  // allowing nicely formatted errors to propogate to users.
  bool use_diff_tool = !diff_tool_file.empty();
  std::vector<std::string> diff_commands = {};
  if (use_diff_tool) {
    diff_commands.reserve(sources.size());
  }

  // Create copies of of the source files to format
  for (const std::string& src : sources) {
    std::string dest = working_dir + "/" + src;
    int exit_code = copy_file(src, dest);
    if (exit_code) {
      return exit_code;
    }

    if (use_diff_tool) {
      diff_commands.push_back(diff_tool_file + " " + src + " " + dest);
    }
  }

  // Run clang-format
  int format_exit_code = execute(clang_format_file, clang_format_arguments, working_dir);
  if (format_exit_code || !use_diff_tool) {
    return format_exit_code;
  }

  // Show diffs
  int diff_exit_code = 0;
  for (std::string& command : diff_commands) {
    int exit_code = system(command.c_str());
    diff_exit_code = diff_exit_code ? diff_exit_code : exit_code;
  }
  if (diff_exit_code) {
    return diff_exit_code;
  }

  return 0;
}

int main(int argc, char** argv) {
  std::string exec_path, diff_tool_file, config_file, touch_file = {};
  std::vector<std::string> arguments, diff_commands, sources = {};

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (++i == argc) {
      std::cerr << "process wrapper error: argument \"" << arg << "\" missing parameter.\n";
      return -1;
    } else if (arg == "--touch-file") {
      if (!touch_file.empty()) {
        std::cerr << "process wrapper error: \"--touch-file\" can only "
                     "appear "
                     "once.\n";
        return -1;
      }
      touch_file = argv[i];
    } else if (arg == "--diff-tool-file") {
      if (!diff_tool_file.empty()) {
        std::cerr << "process wrapper error: \"--diff-tool-file\" can "
                     "only appear "
                     "once.\n";
        return -1;
      }
      diff_tool_file = argv[i];
    } else if (arg == "--config-file") {
      if (!config_file.empty()) {
        std::cerr << "process wrapper error: \"--config-file\" can "
                     "only appear "
                     "once.\n";
        return -1;
      }
      config_file = argv[i];
    } else if (arg == "--source-file") {
      sources.push_back(argv[i]);
    } else if (arg == "--") {
      exec_path = argv[i];
      for (++i; i < argc; ++i) {
        arguments.push_back(argv[i]);
      }
      break;
    } else {
      std::cerr << "process wrapper error: unknown argument \"" << arg << "\"." << '\n';
      return -1;
    }
  }

  arguments.reserve(sources.size());
  for (const std::string& src : sources) {
    arguments.push_back(src);
  }

  int exit_code = run_clang_format(exec_path, arguments, config_file, sources, diff_tool_file);
  if (exit_code) {
    return exit_code;
  }

  if (!touch_file.empty()) {
    std::ofstream file(touch_file);
    if (file.fail()) {
      std::cerr << "process wrapper error: failed to create touch file: \"" << touch_file << "\"\n";
      return -1;
    }
    file.close();
  }

  return 0;
}
