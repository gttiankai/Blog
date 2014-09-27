int main(int argc, char *argv[])
{
    Runtime::Options options;
    options.push_back(std::make_pair("compiler", reinterpret_cast<void*>(NULL)));
    std::vector<const DexFile*>boot_class_path;
    options.push_back(std::make_pair(boot_image_option.c_str(), reinterpret_cast<void*>(NULL)));
    CreateRuntime(options, instruction_set);
    return 0;
}