#include "arguments.hh"

void parse_cmd(int argc, char **argv, std::map<std::string, Folder> &map,
               std::string &path, std::string &folder)
{
    std::string command;
    if (folder == ".")
    {
        for (int i = 2; i < argc; i++)
        {
            command += argv[i];
            command += ' ';
        }
    }
    else 
    {
        for (int i = 2; i < argc - 1; i++)
        {
            command += argv[i];
            command += ' ';
        }
    }
    Convertor::instance().add_command(map, folder, command);
    Convertor::instance().write(map, path);
}

void parse_folder(int argc, char **argv, std::map<std::string, Folder> &map,
               std::string &path, std::string &folder)
{
    std::string new_folder;
    for (int i = 2; i < argc; i++)
    {
        new_folder += argv[i];
        new_folder += ' ';
    }
    Convertor::instance().add_folder(map, folder, new_folder);
    Convertor::instance().write(map, path);
}

void remove_cmd(int argc, char **argv, std::map<std::string, Folder> &map/*, std::string &path*/, std::string &folder)
{
    auto elms = map[folder].get_elements();
    size_t i = 0;   
    std::string cmd;
    if (folder == ".")
    {
        for (int i = 2; i < argc; i++)
        {
            cmd += argv[i];
            cmd += ' ';
        }
    }
    else 
    {
        for (int i = 2; i < argc - 1; i++)
        {
            cmd += argv[i];
            cmd += ' ';
        }
    }
    for (auto elm : elms)
    {
        if (elm.get_name() == cmd)
        {
            Convertor::instance().remove_command(map, folder, i);
            break;
        }
        i++;
    }
}

void parse_arg(int argc, char **argv, std::map<std::string, Folder> &map,
               std::string &path)
{
    std::string folder;
    if (argv[argc - 1][0] == '_') 
    {
        std::string str = argv[argc - 1];
        auto len = str.size();
        folder = str.substr(1, len - 2);
    }
    else
        folder = ".";
    // il faut gerer le cas ou l'utilisateur donne un folder inexistant ?
    if (strcmp(argv[1],"-ac") == 0)
        parse_cmd(argc, argv, map, path, folder);
    else if (strcmp(argv[1],"-af") == 0)
        parse_folder(argc, argv, map, path, folder);
    else if (strcmp(argv[1], "-rc") == 0)
        remove_cmd(argc, argv, map/*, path*/, folder);
    else
    {
        std::cerr << "Invalid argument: " << argv[1] << "\n";
        exit(1);
    }
}